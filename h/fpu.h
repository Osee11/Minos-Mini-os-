#ifndef FPU_H
#define FPU_H
#include "types.h"
void fpu_init();
static inline void fpu_save(uint8_t* buffer){
    __asm__ __volatile__("fxsave (%0)"::"r"(buffer));
}
static inline void fpu_rstor(uint8_t* buffer){
    __asm__ __volatile__("fxrstor (%0)"::"r"(buffer));
}
#endif