[bits 16]
[org 0x7C00]
;initialiser segments
;lire disque
;charger gdt
;protected_mode
;Saut kernel
start:
    xor ax,ax
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov sp,0x7C00
    mov ax,0x1000
    mov es,ax
    mov [boot_drive],dl

    mov ah,0x02
    mov al,9
    mov ch,0
    mov cl,2
    mov dh,0
    mov dl,[boot_drive]
    mov bx,0x0000
    int 0x13
    jc .erreur
    .succes:
        mov si,lecture_ok
        call print_string
        cli
        lgdt [gdt_descriptor]
        mov eax,cr0
        or eax,0x01
        mov cr0,eax
        jmp 0x08:protected_mode
        jmp $

        .erreur:
            mov si,lecture_no
            call print_string
            hlt
            cld
            jmp $

        [bits 32]
        protected_mode:
            mov ax,0x10
            mov es,ax
            mov ds,ax
            mov ss,ax
            mov fs,ax
            mov gs,ax
            mov esp,0x90000
            jmp 0x08:0x10000
            jmp $


        gdt_start:
            dq 0

            dw 0xFFFF
            dw 0x0000
            db 0x00
            db 10011010b
            db 11001111b
            db 0x00

            dw 0xFFFF
            dw 0x0000
            db 0x00
            db 10010010b
            db 11001111b
            db 0x00
        gdt_end:

    gdt_descriptor:
        dw gdt_end - gdt_start - 1
        dd gdt_start


    print_string:
        push si
        .loop:
            lodsb
            cmp al,0
            je .fin
            mov ah,0x0E
            int 0x10
            jmp .loop
            .fin:
                pop si
                ret

boot_drive db 0
lecture_no db "Disque non lu",0x0D,0x0A,0
lecture_ok db "Disque lu",0x0D,0x0A,0

times 510 - ($ - $$) db 0
dw 0xAA55