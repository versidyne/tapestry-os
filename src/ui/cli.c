// cli.c -- Defines input / output routines.
//          File Version: 1.2

#include "cli.h"

// Define types
typedef unsigned char uchar;
typedef uchar byte;

// Define ASM routines
extern void check_apm();
extern void init_apm();
extern void standby();
extern void suspend();
extern void shutdown();

//Set bit n to 1
#define bit(n) (1<<(n))

// Check if bit n in flags is set
#define check_flag(flags, n) ((flags) & bit(n))

// Creates a command line interface.
void cl_interface(fs_node_t *fs_root) {
  while (true) {
    char buffer[256];
    printf("# ");
    scanf(buffer);
    cl_handler(buffer, fs_root);
  }
}

// Handles a command issued by the user.
void cl_handler(char* buffer, fs_node_t *fs_root) {
  if (strcmp(buffer,"beep") == 0) {
    beep();
  }
  else if (strcmp(buffer,"clear") == 0) {
    monitor_clear();
  }
  else if (strcmp(buffer,"contents") == 0) {
    file_disp(fs_root);
  }
  else if (strcmp(buffer,"cpu") == 0) {
    detect_cpu();
  }
  else if (strcmp(buffer,"fork") == 0) {
    fork_disp();
  }
  else if (strcmp(buffer,"furelise") == 0) {
    felise();
  }
  else if (strcmp(buffer,"help") == 0) {
    help_disp();
  }
  else if (strcmp(buffer,"hibernate") == 0) {
    
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
	
	// Check for Advanced Power Management
	check_apm();
	
	// Initialize Advanced Power Management
	init_apm();
	
	// Send hibernation command
	suspend();
	
	// Halt the cpu if failed
	halt();
    
  }
  else if (strcmp(buffer,"logo") == 0) {
    logo_disp();
  }
  else if (strcmp(buffer,"ls") == 0) {
    dir_disp(fs_root);
  }
  else if (strcmp(buffer,"mary") == 0) {
    mary();
  }
  else if (strcmp(buffer,"mouse") == 0) {
	// Initialize the mouse
    init_mouse();
    // output current coordinates
    //monitor_write_dec(getcoords());
  }
  else if (strcmp(buffer,"nosound") == 0) {
    nosound();
  }
  else if (strcmp(buffer,"reboot") == 0) {
    reboot();
  }
  else if (strcmp(buffer,"shutdown") == 0) {
	
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
	
	// Check for Advanced Power Management
	check_apm();
	
	// Initialize Advanced Power Management
	init_apm();
	
	// Send shutdown command
	shutdown();
	
	// Halt the cpu if failed
	halt();
    
  }
  else if (strcmp(buffer,"sleep") == 0) {
	
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
	
	// Check for Advanced Power Management
	check_apm();
	
	// Initialize Advanced Power Management
	init_apm();
	
	// Send standby command
	standby();
	
	// Halt the cpu if failed
	halt();
    
  }
  else if (strcmp(buffer,"time") == 0) {
    time_disp();
  }
  else if (strcmp(buffer,"twinkle") == 0) {
    twinkle();
  }
  else if (strcmp(buffer,"usermode") == 0) {
    umode_disp(fs_root);
  }
  else if (strcmp(buffer,"version") == 0) {
    version_disp();
  }
  else if (strcmp(buffer,"vga") == 0) {
    VgaTest();
  }
  else if (strcmp(buffer,"wait") == 0) {
    timer_wait(250000);
  }
  else {
    printf("Unknown command: ");
    printf(buffer);
    printf("\n");
  }
}

// Displays all files in the file system.
void dir_disp(fs_node_t *fs_root) {
  
  // The next section of code is not reentrant so make sure we aren't interrupted during.
  //cli();

  // list the contents of /
  int i = 0;
  struct dirent *node = 0;
  while ((node = readdir_fs(fs_root, i)) != 0) {
    
    //printf("Found file ");
    printf(node->name);
    fs_node_t *fsnode = finddir_fs(fs_root, node->name);

    /*if ((fsnode->flags&0x7) == FS_DIRECTORY) {
      printf("\n\t(directory)\n");
    }
    
    else {
      
      printf("\n\t contents: \"");
      char buf[256];
      u32int sz = read_fs(fsnode, 0, 256, buf);
      int j;
      for (j = 0; j < sz; j++)
	monitor_put(buf[j]);
      
      printf("\"\n");
      
    }*/
    printf(" ");
    i++;
    
  }
  
  // Enable interrupts
  //sti();
  
  printf("\n");
  
}

// Displays all files in the file system and their contents.
void file_disp(fs_node_t *fs_root) {
  
  // The next section of code is not reentrant so make sure we aren't interrupted during.
  //asm volatile("cli");

  // list the contents of /
  int i = 0;
  struct dirent *node = 0;
  while ((node = readdir_fs(fs_root, i)) != 0) {
    
    printf("Found file ");
    printf(node->name);
    fs_node_t *fsnode = finddir_fs(fs_root, node->name);

    if ((fsnode->flags&0x7) == FS_DIRECTORY) {
      printf("\n\t(directory)\n");
    }
    
    else {
      
      printf("\n\t contents: \"");
      char buf[256];
      u32int sz = read_fs(fsnode, 0, 256, buf);
      int j;
      for (j = 0; j < sz; j++)
		monitor_put(buf[j]);
      
      printf("\"\n");
      
    }
    
    i++;
    
  }
  
  // Enable interrupts
  //asm volatile("sti");
  
  printf("\n");
  
}

// Tests a forking iteration.
void fork_disp() {

  // Create a new process in a new address space which is a clone of this.
  int ret = fork();

  printf("fork() returned ");
  monitor_write_hex(ret);
  printf(", and getpid() returned ");
  monitor_write_hex(getpid());
  printf("\n============================================================================\n");

  if (ret == 0) {
      // You are the child
      printf("Now writing to the kernel as the Child.\n");
  }
  else {
      // You are parent
      printf("Now writing to the kernel as the Parent.\n");
  }
  
}

// Displays the help menu on the main screen.
void help_disp() {
  
  // list commands
  printf("beep\t\tCreate a beep from built in speaker.\n");
  printf("clear\t\tClear all data from the screen.\n");
  printf("contents\tDisplays all files and their contents.\n");
  printf("cpu\t\tAttempt to display information about the CPU.\n");
  printf("fork\t\tAttempts to create a fork.\n");
  printf("furelise\tPlays the Fur Elise.\n");
  printf("help\t\tDisplays the help menu.\n");
  printf("hibernate\tDisplays the help menu.\n");
  printf("logo\t\tDisplays the system logo.\n");
  printf("ls\t\tDisplays all files.\n");
  printf("mary\t\tPlays Mary Had a Little Lamb.\n");
  printf("mouse\t\tInitializes the mouse.\n");
  printf("nosound\t\tStop sound coming from built in speaker.\n");
  printf("reboot\t\tReboots the system.\n");
  printf("shutdown\tShuts down the system.\n");
  printf("sleep\t\tPuts the system into a low energy state.\n");
  printf("time\t\tDisplays the current system time.\n");
  printf("twinkle\t\tPlays Twinkle, Twinkle Little Star.\n");
  printf("usermode\tAttempt to switch to user mode.\n");
  printf("version\t\tDisplays the system version.\n");
  printf("vga\t\tAttempts to switch to VGA Mode.\n");
  printf("wait\t\tAttempt to wait for one second.\n");
  
}

// Displays the logo on the main screen.
void logo_disp() {
  
  // display logo
  printf("oooooo     oooo                        o8o               .oooooo.    .oooooo..o ");
  printf(" `888.     .8'                         `''              d8P'  `Y8b  d8P'    `Y8 ");
  printf("  `888.   .8'    .ooooo.  oooo    ooo oooo   .oooo.o   888      888 Y88bo.      ");
  printf("   `888. .8'    d88' `88b  `88b..8P'  `888  d88(  '8   888      888  `'Y8888o.  ");
  printf("    `888.8'     888ooo888    Y888'     888  `'Y88b.    888      888      `'Y88b ");
  printf("     `888'      888    .o  .o8''88b    888  o.  )88b   `88b    d88' oo     .d8P ");
  printf("      `8'       `Y8bod8P' o88'   888o o888o 8''888P'    `Y8bood8P'  8''88888P'  ");

  // add blank line
  printf("\n");
  
}

// Time Display Function
void time_disp() {
  
  // display time
  monitor_write_dec(readCMOS(0x0));
  printf(" ");
  monitor_write_dec(readCMOS(0x2));
  printf(" ");
  monitor_write_dec(readCMOS(0x4));
  printf(" ");
  monitor_write_dec(readCMOS(0x7));
  printf(" ");
  monitor_write_dec(readCMOS(0x8));
  printf(" ");
  monitor_write_dec(readCMOS(0x9));
  //printf("\n");
  //monitor_write_dec(mktime(getDatetime()));

  // add blank line
  printf("\n");
  
}

// Tests a usermode iteration.
void umode_disp(fs_node_t *fs_root) {
  
  // Initialize the system calls
  initialise_syscalls();
  
  // user mode
  switch_to_user_mode();
  
  // begin cli
  ucl_interface(fs_root);
  
  // begin user cli
  /*while (true) {
    char buffer[256];
    syscall_monitor_write("$ ");
    scanf(buffer);
    cl_handler(buffer, fs_root);
  }*/
  
}

// Creates a command line interface.
void ucl_interface(fs_node_t *fs_root) {
  while (true) {
    char buffer[256];
    syscall_monitor_write("$ ");
    scanf(buffer);
    cl_handler(buffer, fs_root);
  }
}

// Displays the system version on the main screen.
void version_disp() {
  
  // display version
  printf(VEXIS_VERSION);
  printf(" - ");
  printf(VEXIS_BUILD_TIME);
  printf(" ");
  printf(VEXIS_BUILD_DATE);
  printf("\n");
  
}
