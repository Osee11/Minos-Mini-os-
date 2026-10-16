#include "h/task.h"
#include "h/types.h"
void create_task(task_t *t,uint32_t (*func)(),uint32_t *stack){
    uint32_t *st = stack;
    st--;
    *st = (uint32_t)func;
    for(volatile uint32_t i = 0;i<8;i++){
        st--;
        *st = 0;
    }
    t->esp = (uint32_t)st;
}