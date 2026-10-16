#include "h/vga.h"

uint32_t cursor_x = 0;
uint32_t cursor_y = 0;

void kprint_char(uint8_t c){
    uint8_t *vga= (uint8_t*)0xB8000;
    if(c == '\n'){
        cursor_x = 0;
        cursor_y++;
        return;
    }
    if(cursor_x >= 79){
        if(cursor_y >= 24){
            scroll_screen();
        }else{
            cursor_x = 0;
            cursor_y++;
        }
    }
    if(cursor_y >=25){
        scroll_screen();
    }

    uint32_t cursor = cursor_y * 80 + cursor_x;
    vga[cursor * 2] = c;
    vga[cursor * 2 + 1] = 0xF0;
    cursor_x++;
}
void kprint(uint8_t *str){
    uint32_t i = 0;
    while(str[i]){
        kprint_char(str[i]);
        i++;
    }
}
void kprint_hex(uint8_t c){
    char hex[] = "0123456789ABCDEF";
    kprint("0x");
    kprint_char(hex[bit_haut(c)]);
    kprint_char(hex[bit_bas(c)]);
}

void clear_screen(){
    uint8_t *vgaa = (uint8_t*)0xB8000;
    for(uint32_t i = 0;i < 25*80;i++){
        vgaa[i * 2] = ' ';
        vgaa[i * 2 + 1] = 0xFF;
    }
    cursor_x = 0;
    cursor_y = 0;
}
uint8_t bit_bas(uint8_t c){
    return (c & 0x0F);
}
uint8_t bit_haut(uint8_t c){
    return ((c & 0xF0) >> 4 );
}

void scroll_screen(){
    uint8_t *vga = (uint8_t*)0xB8000;
    for(uint32_t y = 0;y<24;y++){
        for(uint32_t x = 0;x<80;x++){
            uint32_t dest = (y * 80 + x) *2;
            uint32_t src = ((y+1) * 80 + x) * 2;
            vga[dest ] = vga[src];
            vga[dest + 1] = vga[src + 1];
        }
    }

    for(uint32_t i = 0;i<80;i++){
        uint32_t pos = 24 * 80 + i;
        vga[pos * 2] = ' ';
        vga[pos * 2 + 1] = 0xF0;
    }
    cursor_y = 24;
    cursor_x = 0;
}

void kprint_int(uint32_t n){
    uint8_t *vga= (uint8_t*)0xB8000;
    
    int index = 0;
    uint8_t buffer[12];
    if(n == 0){
        kprint_char('0');
        return;
    }
    while(n > 0 && index < 10){
        uint8_t c = (uint8_t)(n % 10);
        buffer[index++] = '0' + c;
        n = n/10;
    }
    buffer[index] = '\0';
        for(int i = index - 1;i>= 0;i--){
            kprint_char(buffer[i]);
        }
        
}
    