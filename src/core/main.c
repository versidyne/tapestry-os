// main.c -- Defines the kernel entry point and calls initialization routines.
//           File Version: 1.2

#include "main.h"

extern u32int placement_address;
u32int initial_esp;

int main(struct multiboot *mboot_ptr, u32int initial_stack) {
  
  // Set initial esp
  initial_esp = initial_stack;
  
  // Initialize all the ISRs and segmentation
  init_descriptor_tables();
  
  // Initialize the screen (by clearing it)
  monitor_clear();
  
  // Enable Interrupts
  sti();
  
  // Initialize the PIT to 250kHz
  init_pit(250000);

  // Find the location of our initial ramdisk.
  ASSERT(mboot_ptr->mods_count > 0);
  u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
  u32int initrd_end = *(u32int*)(mboot_ptr->mods_addr+4);
  
  // Don't trample our module with placement accesses, please!
  placement_address = initrd_end;

  // Start paging.
  initialize_paging();

  // Start multitasking.
  initialize_tasking();
  
  // Initialize the keyboard
  init_keyboard();
  
  // Initialize the initial ramdisk, and set it as the filesystem root.
  fs_root = initialize_initrd(initrd_location);
  
  // Display logo      
  logo_disp();
  
  // Start command line interface
  cl_interface(fs_root);
  
  return 0;
  
}
