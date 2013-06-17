// common.h -- Defines typedefs and some global functions.
//             File Version: 1.0

#ifndef COMMON_H
#define COMMON_H

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;
//typedef          bool  u8int;

void outb(u16int port, u8int value);
void outw(u16int port, u16int value);
u8int inb(u16int port);
u16int inw(u16int port);

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

#define FALSE 0
#define TRUE 1
#define false 0
#define true 1

#define NULL (void*)0
#define null (void*)0

extern void panic(const char *message, const char *file, u32int line);
extern void panic_assert(const char *file, u32int line, const char *desc);

//char *strcat(char *dest, const char *src);

#endif
