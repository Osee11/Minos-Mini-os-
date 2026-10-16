#include "h/stdlib.h"
#include "h/vga.h"

uint8_t *current_heap;
void init_kmalloc(){
    current_heap = &_end;
}
void *kmalloc(uint32_t size){
    uint8_t *addresse = current_heap;
    current_heap+= size;
    return (void*)addresse;
}
void kfree(void *ptr){
    (void)ptr;
}

void meminfo(){
    uint8_t *hex = "0123456789ABCDEF";
    uint32_t ram_used = (uint32_t)current_heap - (uint32_t)&_end;
    kprint("Affichage via kprint_int = ");
    kprint_int(ram_used);
    kprint("\nFin\nEt via kprint hex\n");
    for(int o = 7;o >= 0;o--){
        kprint_char(hex[(ram_used >> (o*4)) & 0xF]);
    }
}

