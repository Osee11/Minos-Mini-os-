#include "h/paging.h"
#include "h/types.h"

uint32_t page_table[1024] __attribute__((aligned(4096)));
uint32_t page_directory[1024] __attribute__((aligned(4096)));

void init_paging(){
    for(uint32_t i = 0;i<1024;i++){
        page_table[i] =(i * 0x1000) | 3;
    }
    page_directory[0] = (uint32_t)page_table | 3;
    for(uint32_t i = 1;i<1024;i++){
        page_directory[i] = 0;
    }
//00000000//1234//1000 //8
    __asm__ __volatile__(
        "movl %0,%%cr3\n\t"
        "movl %%cr0,%%eax\n\t"
        "orl $0x80000000,%%eax\n\t"
        "movl %%eax,%%cr0\n\t"//pagination activee
        : 
        :"r"(page_directory)
        :"eax","memory"
    );

}