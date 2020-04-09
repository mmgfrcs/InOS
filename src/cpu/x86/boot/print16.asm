[bits 16]
printstr:
    pusha
    mov ah, 0x0e

begin_print:
    mov al, [bx]
    cmp al, 0
    je end_print
    int 0x10
    add bx, 0x01
    jmp begin_print

end_print:
    popa
    ret