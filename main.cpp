#include "scanner.h"
#include <stdio.h>

int main()
{
   initialize_state("(3+4)*21/7%42+8000-((1000))");
   Token nt = next_token();
   while (nt.tok_id != END_OF_STRING) {
      printf(" ");
      print_token(nt);
      nt = next_token();
   }
   printf("\n");
}
