
#include "pci.h"

PCI_BIOS_t *pci_bios;

static u32int pci_read(int bus, int dev, int func, int reg);
static PCI_Device_t* pci_readdevice(int bus, int dev, int func);
static int pci_find_bios();
static PCI_Args_t* pci_fill_struct(PCI_Device_t* dev);

//This will scan the PCI Bus for all the devices
//and will determine which drivers need to be loaded
//or which are needed

//Reads DWORD config register
static u32int pci_read(int bus, int dev, int func, int reg)
{
  outl(0xCF8,
	    ((unsigned long) 0x80000000 | (bus << 16) | (dev << 11) |
	     (func << 8) | reg));
  return inl(0xCFC);
}


PCI_Device_t* ret;

static PCI_Device_t* pci_readdevice(int bus, int dev, int func)
{ 
  int place, total = sizeof(PCI_Device_t) / sizeof(unsigned long);

  for (place = 0; place < total; place++)
    ((u32int*)ret)[place] =  pci_read(bus, dev, func, (place * sizeof (unsigned long)));
  
  return ret;
}

static int pci_find_bios()
{
  unsigned long addr;
  unsigned char crc;
  int i;

  for (addr = 0xE0000; addr < 0xFFFFF; addr += 0x10)
    {
      pci_bios = (PCI_BIOS_t *) addr;
      if (pci_bios->Magic == 0x5F32335F)
	{
	  for (i = 0, crc = 0; i < (pci_bios->Pages * 16); i++)
	    crc += *((unsigned char *) (addr + i));
	  if (crc == 0)
	    {
          //found bios
          dprintf("[pci_find_bios] PCI BIOS found at 0x%x\n",addr);
	      return 0;
	    }
	}
    }
  //no bios
  dprintf("[pci_find_bios] PCI BIOS not found\n");
  return 1;
}

void init_pci()
{    
     //Check if there is a bios
     if(pci_find_bios())
     {
          kprintf("PCI not found...\n");
          return;
     }
     
     kprintf("Found PCI bios...\n");
     kprintf("Enumerating hardware...\n");
     
     ret = (PCI_Device_t*)kmalloc(sizeof(PCI_Device_t));
     
     //Now enumerate devices
     //if a driver is available, load it.
     //For now (boot) we will only load required drivers
     
     #ifdef DEBUG
     int invalid;
     #endif

     int bus, device, function;
     static int count = 0;
     PCI_Device_t *tmp;
     
     for (bus = 0; bus <= 0xFF; bus++)
     {
          for (device = 0; device < 32; device++)
	      {
               for (function = 0; function < 8; function++)
               {
	                tmp = pci_readdevice(bus, device, function);
	                if((tmp->VendorID == 0) || (tmp->VendorID == 0xFFFF) || (tmp->DeviceID == 0xFFFF)) {}
	                else{ 
                 
                         count++; 
                         
                         #ifdef DEBUG
                         invalid = 0;
                         #endif
                         
                                   switch(tmp->ClassCode)
                                   {
                                        //Pre-PCI Items
                                        case 0x00:
                                             if(tmp->SubClass == 0x01) //VGA
                                             {
                                                  kprintf("VGA driver loading (legacy)... \n");
                                                  break;
                                             }
                                        break;
                                        
                                        //Mass storage devices
                                        case 0x01:
                                             if(tmp->SubClass == 0x01) //IDE (And possibly CD?)
                                             {
                                                  kprintf("ATA (IDE) driver loading... [TODO]\n");
                                                  break;
                                             }
                                             
                                             if(tmp->SubClass == 0x02) //Floppy
                                             {
                                                  kprintf("Floppy driver loading (legacy)... [TODO]\n");
                                                  break;
                                             }
                                                  
                                             if(tmp->SubClass == 0x80)
                                             {
                                                  kprintf("Mass storage device controller driver loading... [TODO]\n");
                                                  break;
                                             }
                                        break;
                                        
                                        //NIC's
                                        case 0x02:
                                             if(tmp->SubClass == 0x00)
                                             {
                                                  //We need to find out which chipset here
                                                  kprintf("Ethernet driver loading... [TODO]\n");
                                                  
                                                  switch(tmp->VendorID)
                                                  {
                                                       /* Realtek RTL8139 and clones */
                                                       case 0x10EC:
                                                            if(tmp->DeviceID == 0x8139 || tmp->DeviceID == 0x8138)
                                                            {
                                                                 kprintf("Realtek RTL8139 Discovered...\n");
                                                            }
                                                       break;
                                                       
                                                       case 0x1113:
                                                            if(tmp->DeviceID == 0x1211)
                                                            {
                                                                 kprintf("SMC1211TX EZCard 10/100 (RTL8139 clone) Discovered...\n");
                                                            }
                                                       break;
                                                       
                                                       case 0x1500:
                                                            if(tmp->DeviceID == 0x1360)
                                                            {
                                                                 kprintf("Delta Electronics 8139 10/100BaseTX (RTL8139 clone) Discovered...\n");
                                                            }
                                                       break;
                                                       
                                                       case 0x4033:
                                                            if(tmp->DeviceID == 0x1360)
                                                            {
                                                                 kprintf("Addtron Technology 8139 10/100BaseTX (RTL8139 clone) Discovered...\n");
                                                            }
                                                       break;
                                                       
                                                       case 0x1186:
                                                            if(tmp->DeviceID == 0x1300)
                                                            {
                                                                 kprintf("D-Link DFE-538TX (RTL8139 clone) Discovered...\n");
                                                            }
                                                       break;
                                                       /* ------------------- */

                                                       
                                                       default:
                                                            kprintf("[ERROR] Unknown ethernet card, unable to load driver...\n");
                                                       break;
                                                  }
                                                  break;
                                             }
                                             
                                             if(tmp->SubClass == 0x80)
                                             {
                                                  kprintf("Network controller driver loading... [TODO]\n");
                                                  break;
                                             }
                                        break;
                                        
                                        //Video
                                        case 0x03:
                                             if(tmp->SubClass == 0x00)
                                             {
                                                  kprintf("VGA driver loading...\n");
                                                  break;
                                             }
                                                  
                                             if(tmp->SubClass == 0x01)
                                             {
                                                  kprintf("XGA/VESA driver loading...[TODO]\n");
                                                  break;
                                             }
                                        break;
                                        
                                        //Bridge Devices
                                        case 0x06:                                                  
                                             if(tmp->SubClass == 0x00)
                                             {
                                                  kprintf("Host/PCI Bridge discovered... (driver active)\n");
                                                  break;
                                             }
                                             
                                             if(tmp->SubClass == 0x01)
                                             {
                                                  kprintf("PCI/ISA Bridge driver loading... [TODO]\n");
                                                  break;
                                             }
                                             
                                             if(tmp->SubClass == 0x04)
                                             {
                                                  kprintf("PCI/PCI Bridge driver loading... [TODO]\n");
                                                  break;
                                             }
                                        break;
                                        
                                        //Other
                                        case 0x0C:
                                             if(tmp->SubClass == 0x03)
                                             {
                                                  kprintf("USB controller driver loading... [TODO]\n");
                                                  break;
                                             }
                                        break;
                                        
                                        //None of the above
                                        default:
                                             #ifdef DEBUG
                                             invalid++;
                                             #endif
                                        break;         
                                   }
                                   
                                   #ifdef DEBUG     
                                   if(invalid == 0)
                                   { 
                                        dprintf("[init_pci] VID:0x%x DID:0x%x\n",tmp->VendorID,tmp->DeviceID);
                                        dprintf("[init_pci] CC:0x%x SCC:0x%x\n",tmp->ClassCode,tmp->SubClass);
                                        dprintf("[init_pci] BAR0:0x%x BAR1:0x%x BAR2:0x%x\n",tmp->BAR0,tmp->BAR1,tmp->BAR2);
                                        dprintf("[init_pci] BAR3:0x%x BAR4:0x%x BAR5:0x%x\n",tmp->BAR3,tmp->BAR4,tmp->BAR5);
                                        dprintf("[init_pci] IRQ:%d\n",tmp->IRQ);
                                   }
                                   #endif
                    }
               }
	      }
     }
     
     kprintf("\tFound %d devices...\n",count);
     kfree(ret);
}

static PCI_Args_t* pci_fill_struct(PCI_Device_t* dev)
{
     PCI_Args_t* ret;
     
     //Vendor and Device ID's
     ret->VendorID = dev->VendorID;
     ret->DeviceID = dev->DeviceID;
     
     //IRQ
     ret->IRQ = dev->IRQ;
     
     //and finally the BAR's.
     //we leave the driver to determine if
     //they are I/O or memory addresses
     ret->BAR0 = dev->BAR0;
     ret->BAR1 = dev->BAR1;
     ret->BAR2 = dev->BAR2;
     ret->BAR3 = dev->BAR3;
     ret->BAR4 = dev->BAR4;
     ret->BAR5 = dev->BAR5;
     
     return ret;
}
