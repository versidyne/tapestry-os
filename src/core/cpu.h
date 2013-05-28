// cpu.h -- Defines cpu specific routines.
//          File Version: 1.0

#ifndef CPU_H
#define CPU_H

// Read CMOS data
unsigned char readCMOS(unsigned char addr);

// Write CMOS data
void writeCMOS(unsigned char addr, unsigned int value);

// Reboot system
void reboot();

// Start Interrupts
void sti();

// Close Interrupts
void cli();

// Halt System
void halt();

// Define CPUID
#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

// Detects the current CPU
int detect_cpu(void);

// Print Registers
void printregs(int eax, int ebx, int ecx, int edx);

// Intel-specific information
int do_intel(void);

// AMD-specific information
int do_amd(void);

#endif // CPU_H
