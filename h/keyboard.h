#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "types.h"
#define BUFFER_SIZE 126
void execute_cmd(uint8_t *cmd);
extern const uint8_t table_scancode[];
uint8_t get_scancode();
void keyboard_init();
void calculer();
#endif