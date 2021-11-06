#include "keyboard.h"
#include "ports.h"
#include "vga.h"
#include "../cpu/isr.h"
#include "../cpu/types.h"



static bool key_presses[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


bool* get_key_presses(){
    return key_presses;
}

void handle_letter(u8 scancode);


static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    handle_letter(scancode);
}


void init_keyboard() {
    // Init Keyboard handler 
    register_interrupt_handler(IRQ1, keyboard_callback); 

    // Init all keypresses to 0 
    for(int i = 0; i < 160; i++){
        key_presses[i] = 0;
    }
}


void handle_letter(u8 scancode) {
    switch (scancode) {
        case 0x0:
            key_presses[KEY_ERROR] = true;
            return;
        case 0x1:
            key_presses[KEY_ESC] = 1;
            return;
        case 0x2:
            key_presses[KEY_1] = 1;
            return; 
        case 0x3:
            key_presses[KEY_2] = 1;
            return;
        case 0x4:
            key_presses[KEY_3] = 1;
            return;
        case 0x5:
            key_presses[KEY_4] = 1;
            return;
        case 0x6:
            key_presses[KEY_5] = 1;
            return;
        case 0x7:
            key_presses[KEY_6] = 1;
            return;
        case 0x8:
            key_presses[KEY_7] = 1;
            return;
        case 0x9:
            key_presses[KEY_8] = 1;
            return;
        case 0x0A:
            key_presses[KEY_9] = 1;
            return;
        case 0x0B:
            key_presses[KEY_0] = 1;
            return;
        case 0x0C:
            key_presses[KEY_UNDERSCORE] = 1;
            return;
        case 0x0D:
            key_presses[KEY_PLUS] = 1;
            return;
        case 0x0E:
            key_presses[KEY_BACKSPACE] = 1;
            return;
        case 0x0F:
            key_presses[KEY_TAB] = 1;
            return;
        case 0x10:
            key_presses[KEY_Q] = 1;
            return;
        case 0x11:
            key_presses[KEY_W] = 1;
            return;
        case 0x12:
            key_presses[KEY_E] = 1;
            return;
        case 0x13:
            key_presses[KEY_R] = 1;
            return;
        case 0x14:
            key_presses[KEY_T] = 1;
            return;
        case 0x15:
            key_presses[KEY_Y] = 1;
            return;
        case 0x16:
            key_presses[KEY_U] = 1;
            return;
        case 0x17:
            key_presses[KEY_I] = 1;
            return;
        case 0x18:
            key_presses[KEY_O] = 1;
            return;
        case 0x19:
            key_presses[KEY_P] = 1;
            return;
		case 0x1A:
			key_presses[KEY_LSQUARE] = 1;
			return;
		case 0x1B:
			key_presses[KEY_RSQUARE] = 1;
			return;
		case 0x1C:
			key_presses[KEY_ENTER] = 1;
			return;
		case 0x1D:
			key_presses[KEY_LCTRL] = 1;
			return;
		case 0x1E:
			key_presses[KEY_A] = 1;
			return;
		case 0x1F:
			key_presses[KEY_S] = 1;
			return;
        case 0x20:
            key_presses[KEY_D] = 1;
            return;
        case 0x21:
            key_presses[KEY_F] = 1;
            return;
        case 0x22:
            key_presses[KEY_G] = 1;
            return;
        case 0x23:
            key_presses[KEY_H] = 1;
            return;
        case 0x24:
            key_presses[KEY_J] = 1;
            return;
        case 0x25:
            key_presses[KEY_K] = 1;
            return;
        case 0x26:
            key_presses[KEY_L] = 1;
            return;
        case 0x27:
            key_presses[KEY_SCOLON] = 1;
            return;
        case 0x28:
            key_presses[KEY_APOSTROPHE] = 1;
            return;
        case 0x29:
            key_presses[KEY_BTICK] = 1;
            return;
		case 0x2A:
			key_presses[KEY_LSHIFT] = 1;
			return;
		case 0x2B:
			key_presses[KEY_BSLASH] = 1;
			return;
		case 0x2C:
			key_presses[KEY_Z] = 1;
			return;
		case 0x2D:
			key_presses[KEY_X] = 1;
			return;
		case 0x2E:
			key_presses[KEY_C] = 1;
			return;
		case 0x2F:
			key_presses[KEY_V] = 1;
			return;
        case 0x30:
            key_presses[KEY_B] = 1;
            return;
        case 0x31:
            key_presses[KEY_N] = 1;
            return;
        case 0x32:
            key_presses[KEY_M] = 1;
            return;
        case 0x33:
            key_presses[KEY_COMMA] = 1;
            return;
        case 0x34:
            key_presses[KEY_PERIOD] = 1;
            return;
        case 0x35:
            key_presses[KEY_FSLASH] = 1;
            return;
        case 0x36:
            key_presses[KEY_RSHIFT] = 1;
            return;
        case 0x37:
            key_presses[KEY_KBSTAR] = 1;
            return;
        case 0x38:
            key_presses[KEY_LALT] = 1;
            return;
        case 0x39:
            key_presses[KEY_SPC] = 1;
            return;
        default:
            break;
    }
    /* 'keuyp' event corresponds to the 'keydown' + 0x80 
     * it may still be a scancode we haven't implemented yet, or
     * maybe a control/escape sequence */
    if (scancode > 0x7f && scancode <= 0x39 + 0x80) {
        switch (scancode - 0x80) {
            case 0x0:
                key_presses[KEY_ERROR] = 0;
                return;
            case 0x1:
                key_presses[KEY_ESC] = 0;
                return;
            case 0x2: 
                key_presses[KEY_1] = 0;
                return;
            case 0x3:
                key_presses[KEY_2] = 0;
                return;
            case 0x4:
                key_presses[KEY_3] = 0;
                return;
            case 0x5:
                key_presses[KEY_4] = 0;
                return;
            case 0x6:
                key_presses[KEY_5] = 0;
                return;
            case 0x7:
                key_presses[KEY_6] = 0;
                return;
            case 0x8:
                key_presses[KEY_7] = 0;
                return;
            case 0x9:
                key_presses[KEY_8] = 0;
                return;
            case 0x0A:
                key_presses[KEY_9] = 0;
                return;
            case 0x0B:
                key_presses[KEY_0] = 0;
                return;
            case 0x0C:
                key_presses[KEY_UNDERSCORE] = 0;
                return;
            case 0x0D:
                key_presses[KEY_PLUS] = 0;
                return;
            case 0x0E:
                key_presses[KEY_BACKSPACE] = 0;
                return;
            case 0x0F:
                key_presses[KEY_TAB] = 0;
                return;
            case 0x10:
                key_presses[KEY_Q] = 0;
                return;
            case 0x11:
                key_presses[KEY_W] = 0;
                return;
            case 0x12:
                key_presses[KEY_E] = 0;
                return;
            case 0x13:
                key_presses[KEY_R] = 0;
                return;
            case 0x14:
                key_presses[KEY_T] = 0;
                return;
            case 0x15:
                key_presses[KEY_Y] = 0;
                return;
            case 0x16:
                key_presses[KEY_U] = 0;
                return;
            case 0x17:
                key_presses[KEY_I] = 0;
                return;
            case 0x18:
                key_presses[KEY_O] = 0;
                return;
            case 0x19:
                key_presses[KEY_P] = 0;
                return;
            case 0x1A:
                key_presses[KEY_LSQUARE] = 0;
                return;
            case 0x1B:
                key_presses[KEY_RSQUARE] = 0;
                return;
            case 0x1C:
                key_presses[KEY_ENTER] = 0;
                return;
            case 0x1D:
                key_presses[KEY_LCTRL] = 0;
                return;
            case 0x1E:
                key_presses[KEY_A] = 0;
                return;
            case 0x1F:
                key_presses[KEY_S] = 0;
                return;
            case 0x20:
                key_presses[KEY_D] = 0;
                return;
            case 0x21:
                key_presses[KEY_F] = 0;
                return;
            case 0x22:
                key_presses[KEY_G] = 0;
                return;
            case 0x23:
                key_presses[KEY_H] = 0;
                return;
            case 0x24:
                key_presses[KEY_J] = 0;
                return;
            case 0x25:
                key_presses[KEY_K] = 0;
                return;
            case 0x26:
                key_presses[KEY_L] = 0;
                return;
            case 0x27:
                key_presses[KEY_SCOLON] = 0;
                return;
            case 0x28:
                key_presses[KEY_APOSTROPHE] = 0;
                return;
            case 0x29:
                key_presses[KEY_BTICK] = 0;
                return;
            case 0x2A:
                key_presses[KEY_LSHIFT] = 0;
                return;
            case 0x2B:
                key_presses[KEY_BSLASH] = 0;
                return;
            case 0x2C:
                key_presses[KEY_Z] = 0;
                return;
            case 0x2D:
                key_presses[KEY_X] = 0;
                return;
            case 0x2E:
                key_presses[KEY_C] = 0;
                return;
            case 0x2F:
                key_presses[KEY_V] = 0;
                return;
            case 0x30:
                key_presses[KEY_B] = 0;
                return;
            case 0x31:
                key_presses[KEY_N] = 0;
                return;
            case 0x32:
                key_presses[KEY_M] = 0;
                return;
            case 0x33:
                key_presses[KEY_COMMA] = 0;
                return;
            case 0x34:
                key_presses[KEY_PERIOD] = 0;
                return;
            case 0x35:
                key_presses[KEY_FSLASH] = 0;
                return;
            case 0x36:
                key_presses[KEY_RSHIFT] = 0;
                return;
            case 0x37:
                key_presses[KEY_KBSTAR] = 0;
                return;
            case 0x38:
                key_presses[KEY_LALT] = 0;
                return;
            case 0x39:
                key_presses[KEY_SPC] = 0;
                return;
            default:
                break;
        }
    } 
}
