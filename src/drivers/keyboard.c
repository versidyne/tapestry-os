// keyboard.c -- Initializes the keyboard, counts keystrokes.
//               File Version: 1.0

// Runtime headers
#include "keyboard.h"
#include "../proc/isr.h"
#include "monitor.h"

// Localized driver
#include "keyboard_us.h"

// Functional keys
unsigned int alt = false;
unsigned int ctrl = false;
unsigned int shift = false;
unsigned int caps = false;

// Other functions
unsigned int presscount = 0;
char lastkey;

// Handles the keyboard interrupt
static void keyboard_callback(registers_t *regs) {
  
  // Declares variable
  unsigned char scancode;

  // Read from the keyboard's data buffer
  scancode = inb(0x60);

  // If the top bit is set, a key has just been released
  if (scancode & 0x80) {

    // Convert to normal code
    scancode = scancode - 0x80;

    // Determine functional keys

    if (scancode == 56) {
      alt = false;
    }

    if (scancode == 29) {
      ctrl = false;
    }

    if (scancode == 42 || scancode == 54) {
      shift = false;
    }

  }

  else {

    // Press count increment
    presscount++;

    // Determine functional keys
    if (scancode == 56) {
      alt = true;
    }

    else if (scancode == 29) {
      ctrl = true;
    }

    else if (scancode == 42 || scancode == 54) {
      shift = true;
    }

    else if (scancode == 58) {
      if (caps == true) {
	caps = false;
      }
      else {
	caps = true;
      }
    }

    // Not functional key
    else {

      // Translate scan code
      if (shift == true) {
	lastkey = skbdus[scancode];
      }
      else if (caps == true) {
	lastkey = skbdus[scancode];
      }
      else {
	lastkey = kbdus[scancode];
      }

    }

  }

}

// Initializes the keyboard.
void init_keyboard() {
  
  // Firstly, register our keyboard callback.
  register_interrupt_handler(IRQ1, &keyboard_callback);

}

// Outputs the next pressed key.
char getchar() {
  
  // Capture current spot
  int lastint = presscount;
  
  // Wait for incrementation
  while (lastint==presscount) {;;;}
  
  // Return new key
  return lastkey;
  
}
