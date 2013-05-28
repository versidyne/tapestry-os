// mouse.h -- Defines the interface for all mouse-related functions.

#ifndef MOUSE_H
#define MOUSE_H

#include "../core/common.h"

// Detects the mouse.
int detect_mouse();

// Initializes the mouse.
void init_mouse();

// Outputs the next pressed key.
u32int getcoords();

#endif
