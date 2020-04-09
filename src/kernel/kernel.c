#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/x86/idt.h"
#include "../cpu/x86/isr.h"

void main() {
    clear_screen();
    isr_install();
    print("InOS Kernel has been loaded. Welcome!\n");
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");

}
