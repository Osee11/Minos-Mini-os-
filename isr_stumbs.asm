[bits 32]

extern irq1_interrupt_handler ;keyboard (irq1)
global irq1_handler
extern irq0_interrupt_handler
global irq0_handler

irq1_handler:
    pusha
    call irq1_interrupt_handler
    popa
    iret

irq0_handler:
    pusha
    call irq0_interrupt_handler
    popa
    iret