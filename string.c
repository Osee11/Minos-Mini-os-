#include "h/string.h"

uint32_t strcmp(uint8_t* str1,uint8_t* str2){
    while(*str1 && (*str1 == *str2)){
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}