// vga.c -- Initializes and handles VGA routines.
//          File Version: 1.0

#include "vga.h"

int mx, my; // mouse data
char bg;

void VgaSetColor(u8int color, u8int red, u8int green, u8int blue)
{
	outb(0x3C8, color);
	outb(0x3C9, red);
	outb(0x3C9, green);
	outb(0x3C9, blue);
}

void VgaDrawPixel(unsigned x, unsigned y, unsigned c)
{
	u8int *vga = (u8int*)0xA0000;
	int offset = y * 320 + x;
	vga[offset] = c;
}

u8int VgaReadPixel(int x, int y)
{
	u8int *vga = (u8int*) 0xA0000;
	int offset = y * 320 + x;
	return vga[offset];
}

void VgaClear(u8int color)
{
	int w, h;
	for (w = 0; w < 320; w++)
	{
		for (h = 0; h < 200; h++)
			VgaDrawPixel(w, h, color);
	}
}

void VgaClearScreen(void)
{
	VgaClear(0);
}

void mode13(void)
{
	const u8int w[7] = { 0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0x28 };   // width = 320
	const u8int h[8] = { 0xBF, 0x1F, 0x41, 0x9C, 0x8E, 0x8F, 0x96, 0xB9 }; // height = 200
	const u8int w_regs[7] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x13 };
	const u8int h_regs[8] = { 0x6, 0x7, 0x9, 0x10, 0x11, 0x12, 0x15, 0x16 };
	int i;

	outb(0x3C2, 0x63); // mode switch
	outw(0x3D4, 0x0E11); // enable registers

	for (i = 0; i < 7; i++)
		outw(0x3D4, (short)((w[i]<<8)+w_regs[i]));
	for (i = 0; i < 8; i++)
		outw(0x3D4, (short)((h[i]<<8)+h_regs[i]));
	outw(0x3D4, 0x0008);
	outw(0x3D4, 0x4014);
	outw(0x3D4, 0xA317);
	outw(0x3C4, 0x0E04);

	outw(0x3C4, 0x0101);
	outw(0x3C4, 0x0F02); // enable writing to all planes

	outw(0x3CE, 0x4005); // 256color mode
	outw(0x3CE, 0x0506); // graph mode & A000-AFFF

	inb(0x3da);
	outb(0x3C0, 0x30); 
	outb(0x3C0, 0x41);
	outb(0x3C0, 0x33);
	outb(0x3C0, 0x00);

	// EGA Colors
	for (i = 0; i < 16; i++)
	{
		outb(0x3C0, (u8int)i);
		outb(0x3C0, (u8int)i);
	}
	outb(0x3C0, 0x20); // enable video
}

void VgaGetFont(char *buffer)
{
	int i;
	char *vga = (char *) 0xA0000;
	outb(0x3CE, 0x0204);
	for (i = 0; i < 0x2000; i++)
	buffer[i] = vga[i];
}

void VgaFillRectangle(int x, int y, int w, int h, u8int color)
{
	int a, b;
	for (a = y; a < (y + h); a++)
	{
		for (b = x; b < (x + w); b++)
			VgaDrawPixel(b, a, color);
	}
}

//void VgaDrawRectangle(Rectangle_t *rect, int color)
//{

void vga_draw_hort(int x, int y, int length, u8int color)
{
	int a;
	for (a = x; a < (x + length); a++)
	VgaDrawPixel(a, y, color);
}

void vga_draw_vert(int x, int y, int length, u8int color)
{
	int a;
	for (a = y; a < (y + length); a++)
	VgaDrawPixel(x, a, color); 
}

void VgaDrawRectangle(int x, int y, int w, int h, u8int color)
{
	vga_draw_hort(x, y, w, color);  // Draw top border
	vga_draw_hort(x, y+h, w, color); // Draw bottom border
	vga_draw_vert(x, y, h, color);  // Draw left border
	vga_draw_vert(x+w, y, h, color); // Draw right border
}

void VgaDrawWindow(int x, int y, int size)
{
	VgaFillRectangle(x, y, size, size, 2); // Green
	VgaDrawRectangle(x, y, size, size, 0); // Black
}

void VgaDrawFont(int x, int y, char font[8], int c1)
{
	int i, l;
	int j = x;
	int h = y;
	int c;
	for (l = 0; l < 8; l++)
	{
		for (i = 0; i < 8; i++)
		{
			if ((font[l] & (1<<i)))
				c = c1;  // New color
			else
				c = VgaReadPixel(j, h);  // Don't overwrite background
				VgaDrawPixel(j++, h, c);
		}
		h++;
		j = x;
	}
} 


void VgaDrawString(int x, int y, int reps, char font[8], char color)
{
	int i;
	int a = x;
	for (i = 0; i < reps; i++)
	{
		VgaDrawFont(a, y, font, color);
		a += 8;
	}
}


void VgaUpdateMouse(int x, int y)
{
	VgaDrawPixel(mx, my, bg);
	VgaDrawPixel(x, y, 0);
	mx = x;
	my = y;
}


void VgaTest(void)
{
	mode13();

	char a[10]="hi wassup";

	bg = 0;
	VgaClear(bg);

	VgaDrawWindow(96, 36, 128);

	char font_a[8] = {0x18, 0x3C, 0x66, 0x7E,
	0x66, 0x66, 0x66, 0x00};
	char font_b[8] = {0x7E, 0x66, 0x66, 0x7E,
	0x66, 0x66, 0x7E, 0x00 };
}

void init_vga(void)
{
	VgaTest();
}
