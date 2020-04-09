[bits 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x1000
init:
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000 ; Set the stack.
    mov sp, bp

clearScreen: ;Clears the screen for our console
    pusha
    mov ax, 0x0700  ; function 07, AL=0 means scroll whole window
    mov bh, 0x07    ; character attribute = white on black
    mov cx, 0x0000  ; row = 0, col = 0
    mov dx, 0x184f  ; row = 24 (0x18), col = 79 (0x4f)
    int 0x10        ; call BIOS video interrupt
setCursorTopLeft: ;Set cursor to the top left
    mov ax, 0x0200
    mov bh, 0
    mov dx, 0x0000
    int 0x10
    popa


    mov bx, MSG_REAL ;Print message in 16-bit
    call printstr

    call load_kernel

    call switch_pm

    jmp $

%include "print16.asm"
%include "disk.asm"
%include "gdt.asm"
%include "print32.asm"
%include "start_prot.asm"
[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL ; Print a message to say we are loading the kernel
    call printstr
    mov bx, KERNEL_OFFSET ; Set -up parameters for our disk_load routine , so
    mov dh, 15 ; that we load the first 15 sectors ( excluding
    mov dl, [BOOT_DRIVE] ; the boot sector ) from the boot disk ( i.e. our
    call disk_load ; kernel code ) to address KERNEL_OFFSET
    ret

[bits 32]
start_protected_mode:
;32-bit mode now
    mov ebx, MSG_PROT_MODE
    call print_string_pm ;Print in 32-bit
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE: db 0
MSG_REAL:
    db "InOS Bootloader v1.0.0 for x86 Systems",10,13, "All Rights Reserved",10,13, 0
MSG_PROT_MODE:
    db "Running Kernel in 32-bit Mode", 0
MSG_LOAD_KERNEL:    db  "Loading InOS Kernel",10,13,0

times 510-($-$$) db 0
dw 0xaa55
