[bits 32]
global _start 

extern kernel_start

_start:
mov ax,0x10
mov es,ax
mov ds,ax
mov ss,ax
mov fs,ax
mov gs,ax
mov esp,0x90000
call kernel_start
jmp $
