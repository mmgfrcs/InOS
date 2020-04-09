#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/x86/idt.h"
#include "../cpu/x86/isr.h"

void main() {
    isr_install();
    clear_screen();
    print("InOS Kernel has been loaded. Welcome!\n");
    /* Test the interrupts */
    asm volatile("sti");
    init_timer(100);
/* Comment out the timer IRQ handler to read
 * the keyboard IRQs easier */

}
