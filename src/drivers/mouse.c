// mouse.c -- Initializes the mouse, logs current coordinates.
//            File Version: 1.1

// Runtime headers
#include "mouse.h"
#include "../proc/isr.h"
#include "monitor.h"

// Other functions
unsigned int coordcount = 0;
u32int lastcoord;

// Mouse variables
volatile unsigned char mouse_cycle=0;
volatile char mouse_byte[3];
volatile char mouse_x=0;
volatile char mouse_y=0;
volatile char mouse_lbtn, mouse_rbtn;

//Static functions prototypes
static void mouse_wait(unsigned char a_type);
static unsigned char mouse_read();
static void mouse_write(unsigned char a_write);

//extern int graphical_mode;
//extern unsigned long g_wd, g_ht;
unsigned long g_wd, g_ht;

//These are the ACTUAL positions
volatile int mx, my;

extern int wid;
//extern window_t* window_list;
//extern window_t current_window;

//Cursor
static char cursor[8] = {0xF0, 0xE0, 0xE0, 0x90, 0x08, 0x0, 0x0, 0x0};

// Handles the mouse interrupt
static void mouse_handler(registers_t *regs) {
  
  // Declares variable
  //u32int scancode;

  // Read from the mouse's data buffer
  //scancode = inb(0x60);

  // Press count increment
  //coordcount++;

  // Capture coordinates
  //lastcoord = scancode;
  
  switch(mouse_cycle) {
	
    case 0:
      mouse_byte[0]=inb(0x60);
      mouse_cycle++;
      
      mouse_lbtn = mouse_byte[0] & 0x1; //bit 0
      mouse_rbtn = mouse_byte[0] & 0x2; //bit 1
      
      //Note: rbtn is 2 when set, lbtn is 1
      
      break;
    case 1:
      mouse_byte[1]=inb(0x60);
      mouse_cycle++;
      
      mouse_x=mouse_byte[1];
      mx += mouse_x;
      if (mx >= g_wd) mx = g_wd-1;
      if (mx <= 1) mx = 1;
      
      break;
    case 2:
      mouse_byte[2]=inb(0x60);
      mouse_cycle=0;
      
      mouse_y=mouse_byte[2];
      my -= mouse_y;
      if (my >= g_ht) my = g_ht-1;
      if (my <= 1) my = 1;
      
      break;
  }
  
  //Window focus
  /*for(int i = 1; i <= wid; i++) {
	   
       if(mouse_lbtn)
       {
            if(mx >= window_list[i].x && mx <= window_list[i].x+window_list[i].width)// && window_list[i].z < 1)
                 if(my >= window_list[i].y && my <= window_list[i].y+window_list[i].height)
                 {
                      //And now redraw the old focus'd window's topbar
                      for(int y=1;y<10;y++)
                           for(int x=1; x<current_window.width-1; x++)
                                if(g_read_pixel(current_window.x+x,current_window.y+y) != WINDOW_COLOUR_TOPBAR_TEXT)
                                     plot_pixel(x,y,WINDOW_COLOUR_TOPBAR,current_window.width,(u32int*)current_window.data); 
                                     
                      //The focus'd window needs to be the current window
                      current_window = (window_t)window_list[i];
                       
                      //Change topbar colour
                      //And later we will change oppacity
                      //We arent going to touch the text pixels
                      for(int y=1;y<10;y++)
                           for(int x=1; x<current_window.width-1; x++)
                                if(g_read_pixel(current_window.x+x,current_window.y+y) != WINDOW_COLOUR_TOPBAR_TEXT)
                                     plot_pixel(x,y,WINDOW_COLOUR_TOPBAR,current_window.width,(u32int*)current_window.data); 
                                
                      
                      //We now need to edit the Z settings for ALL the windows
                      //And change the current_window to z=1
                      for(int j=1;j<=wid;j++)
                           window_list[j].z--;
                      window_list[i].z = 1;
                          
                      
                      //Redraw the window on top
                      put_buffer(window_list[i].x,window_list[i].y,
                                   window_list[i].width,window_list[i].height,
                                   (u32int*)window_list[i].data);
                                
                                   
                      //Now update double_buffer             
                      write_buffer(window_list[i-1].x,window_list[i-1].y,
                                   window_list[i-1].width,window_list[i-1].height,
                                   (u32int*)window_list[i-1].data); 
                                   
                      g_put_pixel(mx, my, 0x00FFFFFF);
                      return;
                 }
       }           
  } */
  
  //Print mouse - TODO
  //g_put_pixel(mx, my, 0x00FFFFFF);

}

// Waits for mouse acknowledgement.
static void mouse_wait(unsigned char a_type) {
  unsigned int _time_out=100000;
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

// Writes to mouse port.
static void mouse_write(unsigned char a_write) {
  
  //Wait to be able to send a command
  mouse_wait(1);
  
  //Tell the mouse we are sending a command
  outb(0x64, 0xD4);
  
  //Wait for the final part
  mouse_wait(1);
  
  //Finally write
  outb(0x60, a_write);
  
}

// Reads from mouse port.
static unsigned char mouse_read() {
  
  //Gets response from mouse
  mouse_wait(0);
  
  // Returns response
  return inb(0x60);
  
}

// Initializes the mouse.
void init_mouse() {
  
  // Declare variables.
  unsigned char _status;
  
  mx = (int)g_wd/2;
  //mx = 5;
  my = (int)g_ht/2;
  //my = 5;
  
  //Enable the auxiliary mouse device
  mouse_wait(1);
  outb(0x64, 0xA8);
  
  //Enable the interrupts
  mouse_wait(1);
  outb(0x64, 0x20);
  mouse_wait(0);
  _status=(inb(0x60) | 2);
  mouse_wait(1);
  outb(0x64, 0x60);
  mouse_wait(1);
  outb(0x60, _status);
 
  //Tell the mouse to use default settings
  mouse_write(0xF6);
  mouse_read();  //Acknowledge
 
  //Enable the mouse
  mouse_write(0xF4);
  mouse_read();  //Acknowledge
  
  // Register the mouse handler.
  register_interrupt_handler(IRQ12, &mouse_handler);
  
}

// Detects the mouse.
int detect_mouse() {
    unsigned char tmp = mouse_read();
    if(tmp != 0xFA)
         return 0; //No mouse
    else
         return 1; //Mouse there
}

// Outputs the next pressed key.
u32int getcoords() {
  
  // Capture current spot
  int lastint = coordcount;
  
  // Wait for incrementation
  while (lastint==coordcount) {;;;}
  
  // Return new key
  return lastcoord;
  
}
