// keyboard_us.h -- Maps the characters on the US keyboard.
// Plans: Make an overwrite for these arrays based on files within the file system  

#ifndef KEYBOARD_US
#define KEYBOARD_US

// Define standard US keyboard scancode table with an array index set to 0
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29 - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* 42 - Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* 54 - Right shift */
  '*',
    0,	/* 56 - Alt */
  ' ',	/* Space bar */
    0,	/* 58 - Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* 70 - Scroll Lock */
    0,	/* 71 - Home key */
    0,	/* 72 - Up Arrow */
    0,	/* 73 - Page Up */
  '-',
    0,	/* 75 - Left Arrow */
    0,
    0,	/* 77 - Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* 80 - Down Arrow */
    0,	/* 81 - Page Down */
    0,	/* 82 - Insert Key */
    0,	/* 83 - Delete Key */
    0,   0,   0,
    0,	/* 87 - F11 Key */
    0,	/* 88 - F12 Key */
    0,	/* 89 - All other keys are undefined */
};

// Shifted edition of the standard US keyboard
unsigned char skbdus[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29 - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '"', '~',   0,		/* 42 - Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0,				/* 54 - Right shift */
  '*',
    0,	/* 56 - Alt */
  ' ',	/* Space bar */
    0,	/* 58 - Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* 70 - Scroll Lock */
    0,	/* 71 - Home key */
    0,	/* 72 - Up Arrow */
    0,	/* 73 - Page Up */
  '-',
    0,	/* 75 - Left Arrow */
    0,
    0,	/* 77 - Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* 80 - Down Arrow */
    0,	/* 81 - Page Down */
    0,	/* 82 - Insert Key */
    0,	/* 83 - Delete Key */
    0,   0,   0,
    0,	/* 87 - F11 Key */
    0,	/* 88 - F12 Key */
    0,	/* 89 - All other keys are undefined */
};

#endif