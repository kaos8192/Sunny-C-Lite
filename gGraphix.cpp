/*  Graphics Generator File by Alex Sedgwick and Geir Anderson
 *  
 *  TODO: General Goals for this file
 *  
 *  [] Create function(s) for point!
 *  [] Create function(s) for triangle
 *  [] Tie into rest of compiler!!
 *  _______________________________________________________________________________
 *  
 *  TODO: Generation NEEDED
 *  
 *  [] Accounts for the 40x24 nature of screen (960 pointers, too big)
 *      [] Must split into indirect blocks of pointing
 *      [] Inserts two bytes of pointer info
 *  [] Userside must be easier to use the compilers (we ain't hand compiling this)
 *  _______________________________________________________________________________
 *
 */

//Includes
#include "gAll.h"
#include "helper.h"
#include "opcodes.h"
#include "node.h"
#include "symtab.h"
#include <vector>
extern std::vector <int> bytes;

//Code
void make_point(int x, int y)
{
    if(x<0){
        return;
    }
    int addx = slap.address(x);
    if(addx < 0){
        return;
    }
    int addy = slap.address(y);
    if(addy < 0){
        return;
    }

    lda_imm(0x00);
    sta_z(0xfc);
    lda_imm(0x04);
    sta_z(0xfd);

    ldy_abs(addy);
    int end = 0xc000 + bytes.size();
    beq(end+16);

    int top = 0xc000+bytes.size();
    lda_imm(40);
    clc();
    adc_z(0xfc);
    sta_z(0xfc);
    lda_imm(0);
    adc_z(0xfd);
    sta_z(0xfd);
    dey();
    bne(top);

    lda_imm(81);
    ldy_abs(addx);
    sta_indy(0xfc);
    //rts();
}


void make_rect(int tlx, int tly, int w, int l)
{
    if(tlx<0){
        return;
    }
    int addx = slap.address(tlx);
    if(addx < 0){
        return;
    }
    int addy = slap.address(tly);
    if(addy < 0){
        return;
    }

    lda_imm(0x00);
    sta_z(0xfc);
    lda_imm(0x04);
    sta_z(0xfd);

    ldy_abs(addy);
    int end = 0xc000 + bytes.size();
    beq(end+16);

    int top = 0xc000+bytes.size();
    lda_imm(40);
    clc();
    adc_z(0xfc);
    sta_z(0xfc);
    lda_imm(0);
    adc_z(0xfd);
    sta_z(0xfd);
    dey();
    bne(top);

    lda_imm(81);
    ldy_abs(addx);
    sta_indy(0xfc);
}

//EoF
