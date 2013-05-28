// cpu.c -- Handles CPU specific routines.
//          File Version: 1.0

#include "cpu.h"

// Define types
typedef unsigned char uchar;
typedef uchar byte;

//Set bit n to 1
#define bit(n) (1<<(n))

// Check if bit n in flags is set
#define check_flag(flags, n) ((flags) & bit(n))

// Start Interrupts
void sti() {
	asm volatile("sti");
}

// Close Interrupts
void cli() {
	asm volatile("cli");
}

// Halt System
void halt() {
	asm volatile("hlt");
}

// Reboot system
void reboot() {
	
	// Define variables
	byte temp;
	
	// Disable interrupts
	cli();
	
	// Clear all keyboard buffers (output and command buffers)
    do {
		
		// Empty user data
        temp = inb(0x64);
        
        // Empty keyboard data
        if (check_flag(temp, 0) != 0) {
			inb(0x60);
		}
		
    }
    
    while (check_flag(temp, 1) != 0);
	
	// Send reboot command (8042 reset pin)
	outb (0x64, 0xFE);
	
	// Halt the cpu if failed
	halt();
	
}

// Read CMOS data
unsigned char readCMOS(unsigned char addr) {
	
	unsigned char ret;
	
	outb(0x70,addr);
	asm volatile("jmp 1f; 1: jmp 1f;1:");
	ret = inb(0x71);
	asm volatile("jmp 1f; 1: jmp 1f;1:");
	
	return ret;
	
}

// Write CMOS data
void writeCMOS(unsigned char addr, unsigned int value) {
	
	outb(0x70, addr);
	asm volatile("jmp 1f; 1: jmp 1f;1:");
	outb(0x71, value);
	asm volatile("jmp 1f; 1: jmp 1f;1:");
	
}

// Detects the current CPU
int detect_cpu(void) {
	unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);
	switch(ebx) {
		case 0x756e6547: /* Intel Magic Code */
		do_intel();
		break;
		case 0x68747541: /* AMD Magic Code */
		do_amd();
		break;
		default:
		printf("Unknown x86 CPU Detected\n");
		break;
	}
	return 0;
}

// Print Registers
void printregs(int eax, int ebx, int ecx, int edx) {
	int j;
	char string[17];
	string[16] = '\0';
	for(j = 0; j < 4; j++) {
		string[j] = eax >> (8 * j);
		string[j + 4] = ebx >> (8 * j);
		string[j + 8] = ecx >> (8 * j);
		string[j + 12] = edx >> (8 * j);
	}
	printf("%s", string);
}

// AMD-specific information
int do_amd(void) {
	printf("AMD Specific Features:\n");
	unsigned long extended, eax, ebx, ecx, edx, unused;
	int family, model, stepping, reserved;
	cpuid(1, eax, unused, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	stepping = eax & 0xf;
	reserved = eax >> 12;
	//printf("Family: %d Model: %d [", family, model);
	printf("Family: ");
	monitor_write_dec(family);
	printf(" Model: ");
	monitor_write_dec(model);
	printf(" [");
	switch(family) {
		case 4:
		//printf("486 Model %d", model);
		printf("486 Model ");
		monitor_write_dec(model);
		break;
		case 5:
		switch(model) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 6:
			case 7:
			//printf("K6 Model %d", model);
			printf("K6 Model ");
			monitor_write_dec(model);
			break;
			case 8:
			printf("K6-2 Model 8");
			break;
			case 9:
			printf("K6-III Model 9");
			break;
			default:
			//printf("K5/K6 Model %d", model);
			printf("K5/K6 Model ");
			monitor_write_dec(model);
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			case 2:
			case 4:
			//printf("Athlon Model %d", model);
			printf("Athlon Model ");
			monitor_write_dec(model);
			break;
			case 3:
			printf("Duron Model 3");
			break;
			case 6:
			printf("Athlon MP/Mobile Athlon Model 6");
			break;
			case 7:
			printf("Mobile Duron Model 7");
			break;
			default:
			//printf("Duron/Athlon Model %d", model);
			printf("Duron/Athlon Model ");
			monitor_write_dec(model);
			break;
		}
		break;
	}
	printf("]\n");
	cpuid(0x80000000, extended, unused, unused, unused);
	if(extended == 0) {
		return 0;
	}
	if(extended >= 0x80000002) {
		unsigned int j;
		printf("Detected Processor Name: ");
		for(j = 0x80000002; j <= 0x80000004; j++) {
			cpuid(j, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		printf("\n");
	}
	if(extended >= 0x80000007) {
		cpuid(0x80000007, unused, unused, unused, edx);
		if(edx & 1) {
			printf("Temperature Sensing Diode Detected!\n");
		}
	}
	//printf("Stepping: %d Reserved: %d\n", stepping, reserved);
	printf("Stepping: ");
	monitor_write_dec(stepping);
	printf(" Reserved: ");
	monitor_write_dec(reserved);
	printf("\n");
	return 0;
}

/* Intel Specific brand list */
char *Intel[] = {
	"Brand ID Not Supported.", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Intel(R) Pentium(R) III Xeon(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) III processor-M", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Xeon(R) Processor", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) 4 processor-M", 
	"Mobile Intel(R) Pentium(R) Celeron(R) processor", 
	"Reserved", 
	"Mobile Genuine Intel(R) processor", 
	"Intel(R) Celeron(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Celeron(R) processor", 
	"Mobile Geniune Intel(R) processor", 
	"Intel(R) Pentium(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor"
};

/* This table is for those brand strings that have two values depending on the processor signature.
 * It should have the same number of entries as the above table. */
char *Intel_Other[] = {
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Celeron(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved"
};

// Intel-specific information
int do_intel(void) {
	printf("Intel Specific Features:\n");
	unsigned long eax, ebx, ecx, edx, max_eax, signature, unused;
	int model, family, type, brand, stepping, reserved;
	int extended_family = -1;
	cpuid(1, eax, ebx, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	type = (eax >> 12) & 0x3;
	brand = ebx & 0xff;
	stepping = eax & 0xf;
	reserved = eax >> 14;
	signature = eax;
	//printf("Type %d - ", type);
	printf("Type ");
	monitor_write_dec(type);
	printf(" - ");
	switch(type) {
		case 0:
		printf("Original OEM");
		break;
		case 1:
		printf("Overdrive");
		break;
		case 2:
		printf("Dual-capable");
		break;
		case 3:
		printf("Reserved");
		break;
	}
	printf("\n");
	//printf("Family %d - ", family);
	printf("Family ");
	monitor_write_dec(family);
	printf(" - ");
	switch(family) {
		case 3:
		printf("i386");
		break;
		case 4:
		printf("i486");
		break;
		case 5:
		printf("Pentium");
		break;
		case 6:
		printf("Pentium Pro");
		break;
		case 15:
		printf("Pentium 4");
	}
	printf("\n");
	if(family == 15) {
		extended_family = (eax >> 20) & 0xff;
		//printf("Extended family %d\n", extended_family);
		printf("Extended family ");
		monitor_write_dec(extended_family);
		printf("\n");
	}
	//printf("Model %d - ", model);
	printf("Model ");
	monitor_write_dec(model);
	printf(" - ");
	switch(family) {
		case 3:
		break;
		case 4:
		switch(model) {
			case 0:
			case 1:
			printf("DX");
			break;
			case 2:
			printf("SX");
			break;
			case 3:
			printf("487/DX2");
			break;
			case 4:
			printf("SL");
			break;
			case 5:
			printf("SX2");
			break;
			case 7:
			printf("Write-back enhanced DX2");
			break;
			case 8:
			printf("DX4");
			break;
		}
		break;
		case 5:
		switch(model) {
			case 1:
			printf("60/66");
			break;
			case 2:
			printf("75-200");
			break;
			case 3:
			printf("for 486 system");
			break;
			case 4:
			printf("MMX");
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			printf("Pentium Pro");
			break;
			case 3:
			printf("Pentium II Model 3");
			break;
			case 5:
			printf("Pentium II Model 5/Xeon/Celeron");
			break;
			case 6:
			printf("Celeron");
			break;
			case 7:
			printf("Pentium III/Pentium III Xeon - external L2 cache");
			break;
			case 8:
			printf("Pentium III/Pentium III Xeon - internal L2 cache");
			break;
		}
		break;
		case 15:
		break;
	}
	printf("\n");
	cpuid(0x80000000, max_eax, unused, unused, unused);
	/* Quok said: If the max extended eax value is high enough to support the processor brand string
	(values 0x80000002 to 0x80000004), then we'll use that information to return the brand information. 
	Otherwise, we'll refer back to the brand tables above for backwards compatibility with older processors. 
	According to the Sept. 2006 Intel Arch Software Developer's Guide, if extended eax values are supported, 
	then all 3 values for the processor brand string are supported, but we'll test just to make sure and be safe. */
	if(max_eax >= 0x80000004) {
		printf("Brand: ");
		if(max_eax >= 0x80000002) {
			cpuid(0x80000002, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000003) {
			cpuid(0x80000003, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000004) {
			cpuid(0x80000004, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		printf("\n");
	} else if(brand > 0) {
		//printf("Brand %d - ", brand);
		printf("Brand ");
		monitor_write_dec(brand);
		printf(" - ");
		if(brand < 0x18) {
			if(signature == 0x000006B1 || signature == 0x00000F13) {
				//printf("%s\n", Intel_Other[brand]);
				printf(Intel_Other[brand]);
				printf("\n");
			} else {
				//printf("%s\n", Intel[brand]);
				printf(Intel[brand]);
				printf("\n");
			}
		} else {
			printf("Reserved\n");
		}
	}
	//printf("Stepping: %d Reserved: %d\n", stepping, reserved);
	printf("Stepping: ");
	monitor_write_dec(stepping);
	printf(" Reserved: ");
	monitor_write_dec(reserved);
	printf("\n");
	
	return 0;
}
