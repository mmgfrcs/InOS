#include "keyboard.h"
#include "ports.h"
#include "../cpu/x86/isr.h"
#include "screen.h"

int shift = 0;

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    // char *sc_ascii;
    // itoa(scancode, sc_ascii);
    // print("Keyboard scancode: ");
    // print(sc_ascii);
    // print(", ");
    print_letter(scancode);
    //print("\n");
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback);
}

void print_letter(u8 scancode) {
  /*
    switch (scancode) {
        case 0x0:
            print("ERROR");
            break;
        case 0x1:
            print("ESC");
            break;
        case 0x2:
            print("1");
            break;
        case 0x3:
            print("2");
            break;
        case 0x4:
            print("3");
            break;
        case 0x5:
            print("4");
            break;
        case 0x6:
            print("5");
            break;
        case 0x7:
            print("6");
            break;
        case 0x8:
            print("7");
            break;
        case 0x9:
            print("8");
            break;
        case 0x0A:
            print("9");
            break;
        case 0x0B:
            print("0");
            break;
        case 0x0C:
            print("-");
            break;
        case 0x0D:
            print("+");
            break;
        case 0x0E:
            print("Backspace");
            break;
        case 0x0F:
            print("Tab");
            break;
        case 0x10:
            print("Q");
            break;
        case 0x11:
            print("W");
            break;
        case 0x12:
            print("E");
            break;
        case 0x13:
            print("R");
            break;
        case 0x14:
            print("T");
            break;
        case 0x15:
            print("Y");
            break;
        case 0x16:
            print("U");
            break;
        case 0x17:
            print("I");
            break;
        case 0x18:
            print("O");
            break;
        case 0x19:
            print("P");
            break;
    		case 0x1A:
      			print("[");
      			break;
    		case 0x1B:
      			print("]");
      			break;
    		case 0x1C:
      			print("ENTER");
      			break;
    		case 0x1D:
      			print("LCtrl");
      			break;
    		case 0x1E:
      			print("A");
      			break;
    		case 0x1F:
      			print("S");
      			break;
        case 0x20:
            print("D");
            break;
        case 0x21:
            print("F");
            break;
        case 0x22:
            print("G");
            break;
        case 0x23:
            print("H");
            break;
        case 0x24:
            print("J");
            break;
        case 0x25:
            print("K");
            break;
        case 0x26:
            print("L");
            break;
        case 0x27:
            print(";");
            break;
        case 0x28:
            print("'");
            break;
        case 0x29:
            print("`");
            break;
    		case 0x2A:
    		    print("LShift");
    			  break;
    		case 0x2B:
    			  print("\\");
    			  break;
    		case 0x2C:
    			  print("Z");
    			  break;
    		case 0x2D:
    			  print("X");
    			  break;
    		case 0x2E:
      			print("C");
      			break;
    		case 0x2F:
      			print("V");
      			break;
        case 0x30:
            print("B");
            break;
        case 0x31:
            print("N");
            break;
        case 0x32:
            print("M");
            break;
        case 0x33:
            print(",");
            break;
        case 0x34:
            print(".");
            break;
        case 0x35:
            print("/");
            break;
        case 0x36:
            print("Rshift");
            break;
        case 0x37:
            print("Keypad *");
            break;
        case 0x38:
            print("LAlt");
            break;
        case 0x39:
            print("Spc");
            break;
        default:

            if (scancode <= 0x7f) {
                print("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                print("key up ");
                print_letter(scancode - 0x80);
            } else print("Unknown key up");
            break;
    }
    */
    /* 'Keyup' event corresponds to the 'keydown' + 0x80
     * it may still be a scancode we haven't implemented yet, or
     * maybe a control/escape sequence */
     if(scancode == 0x2A || scancode == 0x36) {
        shift++;
     } else if (scancode == 0x2A+0x80 || scancode == 0x36+0x80) {
       shift--;
     }
     switch (scancode) {
        case 0x2:
            print(shift > 0 ? "!" : "1");
            break;
        case 0x3:
            print(shift > 0 ? "@" : "2");
            break;
        case 0x4:
            print(shift > 0 ? "#" : "3");
            break;
        case 0x5:
            print(shift > 0 ? "$" : "4");
            break;
        case 0x6:
            print(shift > 0 ? "^" : "5");
            break;
        case 0x7:
            print(shift > 0 ? "^" : "6");
            break;
        case 0x8:
            print(shift > 0 ? "&" : "7");
            break;
        case 0x9:
            print(shift > 0 ? "*" : "8");
            break;
        case 0x0A:
            print(shift > 0 ? "(" : "9");
            break;
        case 0x0B:
            print(shift > 0 ? ")" : "0");
            break;
        case 0x0C:
            print(shift > 0 ? "_" : "-");
            break;
        case 0x0D:
            print(shift > 0 ? "=" : "+");
            break;
        case 0x0E:
            backspace(); //Backspace
            break;
        case 0x0F:
            print("\t");
            break;
        case 0x10:
            print(shift == 0 ? "q" : "Q");
            break;
        case 0x11:
            print(shift == 0 ? "w" : "W");
            break;
        case 0x12:
            print(shift == 0 ? "e" : "E");
            break;
        case 0x13:
            print(shift == 0 ? "r" : "R");
            break;
        case 0x14:
            print(shift == 0 ? "t" : "T");
            break;
        case 0x15:
            print(shift == 0 ? "y" : "Y");
            break;
        case 0x16:
            print(shift == 0 ? "u" : "U");
            break;
        case 0x17:
            print(shift == 0 ? "i" : "I");
            break;
        case 0x18:
            print(shift == 0 ? "o" : "O");
            break;
        case 0x19:
            print(shift == 0 ? "p" : "P");
            break;
     		case 0x1A:
       	    print(shift > 0 ? "{" : "[");
       			break;
     		case 0x1B:
       			print(shift > 0 ? "}" : "]");
       			break;
     		case 0x1C:
       			print("\n");
       			break;
     		case 0x1E:
       			print(shift == 0 ? "a" : "A");
       			break;
     		case 0x1F:
       			print(shift == 0 ? "s" : "S");
       			break;
        case 0x20:
            print(shift == 0 ? "d" : "D");
            break;
        case 0x21:
            print(shift == 0 ? "f" : "F");
            break;
        case 0x22:
            print(shift == 0 ? "g" : "G");
            break;
        case 0x23:
            print(shift == 0 ? "h" : "H");
            break;
        case 0x24:
            print(shift == 0 ? "j" : "J");
            break;
        case 0x25:
            print(shift == 0 ? "k" : "K");
            break;
        case 0x26:
            print(shift == 0 ? "l" : "L");
            break;
        case 0x27:
            print(shift > 0 ? ":" : ";");
            break;
        case 0x28:
            print(shift > 0 ? "\"" : "'");
            break;
        case 0x29:
            print(shift > 0 ? "~" : "`");
            break;
     		case 0x2B:
     			  print(shift > 0 ? "|" : "\\");
     			  break;
     		case 0x2C:
     			  print(shift == 0 ? "z" : "Z");
     			  break;
     		case 0x2D:
     			  print(shift == 0 ? "x" : "X");
     			  break;
     		case 0x2E:
       			print(shift == 0 ? "c" : "C");
       			break;
     		case 0x2F:
       			print(shift == 0 ? "v" : "V");
       			break;
        case 0x30:
            print(shift == 0 ? "b" : "B");
            break;
        case 0x31:
            print(shift == 0 ? "n" : "N");
            break;
        case 0x32:
            print(shift == 0 ? "m" : "M");
            break;
        case 0x33:
            print(shift > 0 ? "<" : ",");
            break;
        case 0x34:
            print(shift > 0 ? ">" : ".");
            break;
        case 0x35:
            print(shift > 0 ? "?" : "/");
            break;
        case 0x37:
            print("*");
            break;
        case 0x39:
            print(" ");
            break;
     }
}
