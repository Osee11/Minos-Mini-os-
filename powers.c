#include "h/powers.h"
#include "h/types.h"
#include "h/io.h"

void reboot(){
    uint8_t temp;
    do{
        if((inb(0x64) & 0x01))inb(0x60);

    }while((inb(0x64)& 0x02));
    outb(0x64,0xFE);
}