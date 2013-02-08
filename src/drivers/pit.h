// pit.h -- Defines the interface for all PIT-related functions.
//          File Version: 1.1

#ifndef PIT_H
#define PIT_H

#include "../core/common.h"

// Initializes the PIT
void init_pit(u32int frequency);

//Waits for desired amount of timer ticks
void timer_wait(int ticks);

typedef struct{
   unsigned char sec;
   unsigned char min;
   unsigned char hour;
   unsigned char day;
   unsigned char month;
   unsigned char year;
}datetime_t;

datetime_t getDatetime();

int mktime(datetime_t time);

#endif
