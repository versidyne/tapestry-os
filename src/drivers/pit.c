// pit.c -- Initializes the PIT, and handles clock updates.
//          File Version: 1.2

#include "pit.h"
#include "../proc/isr.h"
//#include "../proc/task.h"
#include "monitor.h"

// Variables
//u32int tick = 0;
volatile u32int tick = 0;
//extern task_t current_task;
volatile unsigned long wait_ticks = 0;
volatile unsigned int useconds = 0;
#define BCD2BIN(bcd) ((((bcd)&15) + ((bcd)>>4)*10))

// Time definitions
#define USEC (SEC/1000000)
#define MSEC (SEC/1000)
#define SEC 250000
#define MINUTE 60 * SEC
#define HOUR (60*MINUTE)
#define DAY (24*HOUR)
#define YEAR (365*DAY)

static void pit_callback(registers_t *regs) {
    
    tick++;
    /*monitor_write("Tick: ");
    monitor_write_dec(tick);
    monitor_write("\n");*/
    //switch_task();
    wait_ticks++;
    useconds += 4;
    
    /*if(useconds == 1000) {
		useconds = 0;
	}*/
    
    /*if (current_task.ready_to_run == 0) {
		schedule();
	}
	
    //Reduce the running tasks time in queue
    if(current_task.time_to_run > 0) {
        current_task.time_to_run--;
        current_task.time_running++;
    }
    
    else {
		schedule(); //No time left
	}*/
	
}

// Initializes the PIT
void init_pit(u32int frequency) {
	
    // Firstly, register our pit callback.
    register_interrupt_handler(IRQ0, &pit_callback);
    
    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    u32int divisor = 1193180 / frequency;
    
    // Send the command byte.
    outb(0x43, 0x36);
    
    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    u8int l = (u8int)(divisor & 0xFF);
    u8int h = (u8int)( (divisor>>8) & 0xFF );
    
    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
    
}

//Waits for desired amount of timer ticks
void timer_wait(int ticks) {
	
    wait_ticks = 0;
    while(wait_ticks <= ticks);
    
}

//Gets CMOS actual time
datetime_t getDatetime() {
   
   datetime_t now;
   
   cli();
   
   now.sec = BCD2BIN(readCMOS(0x0));
   now.min = BCD2BIN(readCMOS(0x2));
   now.hour = BCD2BIN(readCMOS(0x4));
   now.day = BCD2BIN(readCMOS(0x7));
   now.month = BCD2BIN(readCMOS(0x8));
   now.year = BCD2BIN(readCMOS(0x9));
   
   sti();
   
   return now;
   
}

// Seconds since 01/01/1970
int mktime(datetime_t time) {
	
	long res;
	int year;
	
	int month[12] = {
	0,
	DAY*(31),
	DAY*(31+29),
	DAY*(31+29+31),
	DAY*(31+29+31+30),
	DAY*(31+29+31+30+31),
	DAY*(31+29+31+30+31+30),
	DAY*(31+29+31+30+31+30+31),
	DAY*(31+29+31+30+31+30+31+31),
	DAY*(31+29+31+30+31+30+31+31+30),
	DAY*(31+29+31+30+31+30+31+31+30+31),
	DAY*(31+29+31+30+31+30+31+31+30+31+30)
    };

	year = time.year - 70;
	
	// magic offsets (y+1) needed to get leapyears right.
	res = YEAR*year + DAY*((year+1)/4);
	res += month[time.month];
	
	// and (y+2) here. If it wasn't a leap-year, we have to adjust
	if (time.month>1 && ((year+2)%4))
		res -= DAY;
	res += DAY*(time.day-1);
	res += HOUR*time.hour;
	res += MINUTE*time.min;
	res += time.sec;
	return res;
}
