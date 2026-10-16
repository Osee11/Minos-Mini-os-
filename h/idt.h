#ifndef IDT_H
#define IDT_H
#include "types.h"
typedef struct{
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;

} __attribute__((packed)) idt_entry;

typedef struct {
    uint16_t limits;
    uint32_t base;
}__attribute__((packed)) idt_load;
void idt_init();
void set_gate(uint32_t n,uint32_t handler,uint16_t sel,uint8_t flags);
#endif