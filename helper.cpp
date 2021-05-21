#include "opcodes.h"
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

extern vector<int> bytes;

/* Generate a parsing error message and quit. */
void abort(string msg) {
   printf("Syntax Error: %s\n", msg.c_str());
   exit(-1);
}

//Return the low byte of an address
int low(const int address) {
   return address%256;
}

//Return the high byte of an address
int high(const int address) {
   return address/256;
}

//Calculate how many bytes the program counter is from an address.
int relative(int address)
{
   int rel_addr = address-(0xc000+bytes.size())-1;
   if (rel_addr < -128 || rel_addr > 127) {
      abort("Relative address out of range.");
   }
   return rel_addr;
}

//Add both bytes of a two-byte address to the program
void push_address(int address)
{
   bytes.push_back(low(address));
   bytes.push_back(high(address));
}

void print_program()
{
   //Read and poke each byte of the program into memory at address $C000
   printf("10 for i = 0 to %ld\n", bytes.size()-1);
   printf("20 read b\n");
   printf("30 poke 49152+i, b\n");
   printf("40 next i\n");

   //Execute the program at address $C000 (49152 in decimal)
   printf("50 sys 49152\n");

   //Encode the assembly program as bytes in DATA statements
   int lineno=100;
   for (int i=0; i < bytes.size(); ++i)
   {
      //Check for illegal bytes
      if (bytes[i] > 255 || bytes[i] < -128)
         abort("Opcode or byte value out of range\n");

      //We support a max of 16 bytes per DATA statement
      if (i % 16 == 0) {
         printf("\n%d data ", lineno);
         lineno += 10;

         //Use two's complement to encode negative bytes (sometimes encountered
         //in relative addresses)
         if (bytes[i] < 0) {
            printf("%d", 256+bytes[i]); 
         }
         else {
            printf("%d", bytes[i]); 
         }
      }
      else {
         //Use two's complement to encode negative bytes
         if (bytes[i] < 0) {
            printf(",%d", 256+bytes[i]); 
         }
         else {
            printf(",%d", bytes[i]); 
         }
      }
   }
   printf("\n");
}

void add_constant(int constant, int address) {
   lda_imm(low(constant));   
   clc();
   adc_abs(address);
   lda_imm(high(constant));
   adc_abs(address+1);
}

void add_variables(int address1, int address2) {
   lda_abs(address1);   
   clc();
   adc_abs(address2);
   sta_abs(address2);
   lda_abs(address1+1);
   adc_abs(address2+1);
   sta_abs(address2+1);
}

void sub_constant(int constant, int address)
{
   lda_imm(low(constant));
   sec();
   sbc_abs(address);
   sta_abs(address);
   lda_imm(high(constant));
   sbc_abs(address+1);
   sta_abs(address+1);
}

void sub_variables(int address1, int address2)
{
   lda_abs(address2);
   sec();
   sbc_abs(address1);
   sta_abs(address2);

   lda_abs(address2+1);
   sbc_abs(address1+1);
   sta_abs(address2+1);
}
