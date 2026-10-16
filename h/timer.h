#ifndef TIMER_H
#define TIMER_H
#include "types.h"
extern volatile uint32_t tick_count;
void pit_init(uint32_t freq);
void irq0_interrupt_handler();
#endif