#include "h/fpu.h"
#include "h/types.h"

void fpu_init(){
    __asm__ __volatile(
        "movl %%cr0,%%eax\n\t"
        "orl $0x02,%%eax\n\t"
        "andl $0xFFFFFFBF,%%eax\n\t" //B = 1011
        "movl %%eax,%%cr0\n\t"
        "fninit"
        :
        :
        :"eax"
    );
}