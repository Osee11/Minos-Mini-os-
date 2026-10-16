#ifndef STDLIB_H
#define STDLIB_H
#include "types.h"
extern uint8_t *current_heap;
extern uint8_t _end;
void init_kmalloc();
void *kmalloc(uint32_t size);
void kfree(void *ptr);
void meminfo();
#endif