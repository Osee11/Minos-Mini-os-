#include "h/io.h"
#include "h/keyboard.h"
#include "h/vga.h"
#include "h/pic.h"
#include "h/string.h"
#include "h/stdlib.h"
#include "h/powers.h"
uint8_t buffer[BUFFER_SIZE];
void execute_cmd(uint8_t *cmd){
    kprint(" > ");
    if(strcmp("clear",cmd) == 0){
        clear_screen();
    }else if(strcmp("help",cmd) == 0){
        kprint("cmd : help,reboot,meminfo,clear,af (afficher calcul float)\n");
    }else if(strcmp("meminfo",cmd) == 0){
        kprint("Ram used: ");
        meminfo();
        kprint(" octets\n");
    }else if(strcmp("af",cmd) == 0){
        kprint("Caluler 5.5f * 3:\n");
        float calcul = 5.5f * 3;
        kprint_hex(((uint8_t)calcul & 0xFF));
        kprint("\nFin\n");
        kprint("Kprint int = ");
        kprint_int((uint32_t)calcul);
        kprint("\nFin\n");
    }else if(strcmp("reboot",cmd) == 0 ){
        reboot();
    }else if(cmd[0] == '\0'){
        return;
    }else{
        kprint("Cmd <");
        kprint(cmd);
        kprint("> introuvable\n");
    }
    //kprint(" > ");

}
uint32_t buffer_index = 0;
const uint8_t table_scancode[] = {
    0,   0,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    '\n', 0,   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0,   '\\','z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,   '*',
    0,   ' '
};

uint8_t get_scancode(){
    return inb(0x60);
}

void irq1_interrupt_handler(){
    uint8_t scan = get_scancode();
    if(scan < 128){
        uint8_t c = table_scancode[scan];
        if(c == '\n'){
            buffer[buffer_index] = '\0';
            buffer_index = 0;
            kprint_char(c);
            execute_cmd(buffer);
        }else if(c  == '\b'){
            if(buffer_index > 0){
                buffer_index --;
            }
            kprint_char(c);
        }else if(c != 0 && buffer_index < BUFFER_SIZE - 1){
            buffer[buffer_index++] = c;
            kprint_char(c);
        }
    }
    pic_send_eoi(1);
}

void calculer(){
    
}


