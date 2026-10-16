#ifndef VGA_H
#define VGA_H
#include "types.h"
extern uint32_t cursor_x;
extern uint32_t cursor_y;
void kprint_char(uint8_t c);
void kprint(uint8_t *str);
void kprint_hex(uint8_t c);
void kprint_int(uint32_t i);
void clear_screen();
uint8_t bit_bas(uint8_t c);
uint8_t bit_haut(uint8_t c);
void scroll_screen();
#endif