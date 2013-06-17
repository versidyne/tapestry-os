// vga.h -- Defines the all VGA functions.
//          File Version: 1.0

#ifndef VGA_H
#define VGA_H

#include "../core/common.h"

void VgaTest(void);
void VgaUpdateMouse(int x, int y);
void VgaDrawString(int x, int y, int reps, char font[8], char color);
void VgaDrawFont(int x, int y, char font[8], int c1);
void VgaDrawWindow(int x, int y, int size);
void VgaDrawRectangle(int x, int y, int w, int h, u8int color);
void vga_draw_vert(int x, int y, int length, u8int color);
void vga_draw_hort(int x, int y, int length, u8int color);
void VgaFillRectangle(int x, int y, int w, int h, u8int color);
void VgaGetFont(char *buffer);
void mode3(void);
void mode13(void);
void VgaClearScreen(void);
void VgaClear(u8int color);
u8int VgaReadPixel(int x, int y);
void VgaDrawPixel(unsigned x, unsigned y, unsigned c);
void VgaSetColor(u8int color, u8int red, u8int green, u8int blue);

#endif
