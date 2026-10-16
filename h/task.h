#ifndef TASK_H
#define TASK_H
#include "types.h"
#define MAX_TASK 2
extern volatile uint32_t current_task;
extern void switch_task(uint32_t *old_esp,uint32_t new_esp);
typedef struct {
    uint32_t esp;
    uint32_t *stack;
    uint8_t state;
    uint8_t fpu_state[512] __attribute__((aligned(16)));
}task_t;
void create_task(task_t *task,uint32_t (*entry)(),uint32_t *stack);
extern  task_t t[MAX_TASK];
#endif