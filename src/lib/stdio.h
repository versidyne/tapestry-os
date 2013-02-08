// stdio.h -- Defines input / output routines.
//            Built for Vexis OS

#ifndef STDIO_H
#define STDIO_H

#include "../core/common.h"

// Outputs a null-terminated ASCII string to the monitor.
void printf(char* c);

// Outputs a null-terminated ASCII string from keyboard.
void scanf(char* buffer);

#endif // STDIO_H
