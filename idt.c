#include "h/idt.h"

idt_entry idt[256];
idt_load load;
void set_gate(uint32_t n,uint32_t handler,uint16_t sel,uint8_t flags){
    idt[n].base_high = (uint16_t)(handler >>16);
    idt[n].always0 = 0;
    idt[n].flags = flags;
    idt[n].base_low = (uint16_t)(handler & 0xFFFF);
    idt[n].sel = sel;
}
void idt_init(){
    load.limits = sizeof(idt) - 1;
    load.base = (uint32_t)idt;
    for(uint32_t i = 0;i<256;i++){
        set_gate(i,0,0,0);
    }
    __asm__ __volatile__(
        "lidt %0\n\t"
        :
        :"m"(load)
    );
}