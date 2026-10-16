#include "h/timer.h"
#include "h/io.h"
#include "h/pic.h"
#include "h/task.h"
#include "h/vga.h"
#include "h/fpu.h"

volatile uint32_t tick_count = 0;

void pit_init(uint32_t freq){
    uint32_t diviseur_freq = 1193182 / freq;
    outb(0x43,0x36);//0x36 = 00110110 //on cible le canal 0 (00),
    //on va enoyer l'octet de poids faible puis l'octet qui suit de poids haut des 2 derniers octet (11)
    //Mode opereatoire : carree .genere onde stable (011)
    //Mode de comptage Minaire (0)
    outb(0x40,(diviseur_freq & 0xFF));
    outb(0x40,(diviseur_freq >> 8) & 0xFF);
}
void irq0_interrupt_handler(){
    tick_count++;
    pic_send_eoi(0);
    if(tick_count % 20 == 0){
        uint32_t prev = current_task;
        fpu_save(t[prev].fpu_state);
        current_task = (current_task + 1) % MAX_TASK;
        //switch_task(&t[prev].esp,t[current_task].esp);
        fpu_rstor(t[current_task].fpu_state);
    }
}