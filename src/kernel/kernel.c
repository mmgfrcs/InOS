#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/x86/idt.h"
#include "../cpu/x86/isr.h"
#include "../cpu/x86/timer.h"
#include "../drivers/keyboard.h"

void main() {
    isr_install();
    clear_screen();
    print("InOS Kernel has been loaded. Welcome!\n");
    print("Key Mode\n\n");
    /* Test the interrupts */
    asm volatile("sti");
    init_keyboard();
/* Comment out the timer IRQ handler to read
 * the keyboard IRQs easier */

}
