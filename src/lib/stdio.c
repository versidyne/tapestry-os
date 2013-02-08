// stdio.c -- Defines input / output routines.
//            Built for Vexis OS

#include "../core/common.h"
#include "stdio.h"
#include "../drivers/monitor.h"
#include "../drivers/keyboard.h"

// Outputs a null-terminated ASCII string to the monitor.
void printf(char* c) {
  int i = 0;
  while (c[i]) {
    monitor_put(c[i++]);
  }
}

// Outputs a null-terminated ASCII string from keyboard.
void scanf(char* buffer) {

  // Create variables
  char* keycap = buffer;
  char* keytemp;
  char curkey;

  // Begin loop during capture
  while (true) {

    // Wait for keypress
    curkey = getchar();

    // Display key
    monitor_put(curkey);

    // Check for enter Button
    if (curkey == '\n') {

      // Add null byte to character array
      *keycap = '\0';

      // Exit loop
      break;

    }      

    else {

      if (keycap == buffer) {
		  // Become
		  *keycap = curkey;
		  keycap++;
      }
      
      else {
		  // Increment
		  *keycap = curkey;
		  keycap++;
      }
      
    }
    
  }
  
}
