#include "h/vga.h"
#include "h/paging.h"
#include "h/keyboard.h"
#include "h/idt.h"
#include "h/pic.h"
#include "h/timer.h"
#include "h/task.h"
#include "h/stdlib.h"
#include "h/fpu.h"


#define PILE_SIZE 1024
/*uint32_t stack_A[PILE_SIZE];
uint32_t stack_B[PILE_SIZE];*/
task_t t[MAX_TASK];
volatile uint32_t current_task = 0;

extern void irq0_handler();
extern void irq1_handler();

uint32_t t_A(){
    __asm__ __volatile__("sti");
    while(1){
        kprint_char('A');
        kprint_char(' ');
        for(volatile uint32_t i = 0;i<10000000;i++);
    }
    return 0;
}
uint32_t t_B(){
    __asm__ __volatile__("sti");
    while(1){
        kprint_char('B');
        kprint_char(' ');
        for(volatile uint32_t t = 0;t<10000000;t++);
    }
    return 0;
}
void kernel_start(){
    init_paging();
    fpu_init();
    idt_init();
    set_gate(32,(uint32_t)irq0_handler,0x08,0x8E);
    set_gate(33,(uint32_t)irq1_handler,0x08,0x8E);
    pic_remap();
    pit_init(100);
    init_kmalloc();
    __asm__ __volatile__("sti");
    clear_screen();
    kprint("Paging activ2\n");
    kprint("Clavier bloquant activer\n");
    kprint("Pic remapper\n");
    kprint("Timer(irq0) actif\n");
    uint8_t *msg = "Hello world\n";
    kprint(msg);
    kprint("Idt configuree\n");
    kprint_int(0);
    kprint("\n");
    kprint_int(2565);
    kprint("\n");
    /*uint32_t *stack_A = kmalloc(PILE_SIZE * sizeof(uint32_t));
    uint32_t *stack_B = kmalloc(PILE_SIZE * sizeof(uint32_t));
    create_task(&t[0],t_A,&stack_A[PILE_SIZE]);
    create_task(&t[1],t_B,&stack_B[PILE_SIZE]);*/
    kprint(" > ");
    //t_A();

}