Vexis OS - Universal Operating System
=====
#####Overview
This is the complete core of Vexis OS, a Unix-Like Operating System in C.  This will eventually be utilized for thin clients, various network nodes, websites, and anything else one's heart can desire.

#####Goals
* Maintain a solid system for which networking, radio frequency modulation, video gaming, etc can be had.  The issue in this scenario is the system is meant to be universal, so the intial installation must be very basic but still have all necessary components for expansion within the main administration panel.  This will be an interesting hurdle to jump over, but it will be important in maintain a solid, universal product for many generations to come.

* Maintain several different architectures and gateways that will provide different types of functionality for various games, applications, methods, etc running directly from the kernel as a window manager.  This makes reboots for modes more frequent but will boost performance greatly.

Installation
=====
#####Overview
This is a simple process and will remain as such if instructions are followed carefully.

#####Configuration
This is currently not an option, though it will be in the future.

#####Virtualization
Simply run vexis.iso as a CD Rom.  This can be done with bochs, qemu, or virtualbox-ose easily.

```sh
qemu --cdrom img/vexis.iso --boot d -soundhw all
```

#####Finalizing
There is currently nothing to finalize.

System Roles
=====
#####Overview
The roles that follow are separated within a directory specific to its name.  Within these directories, each role will have its format and place in the order of the system as it runs.  The role will dictate where a particular feature will need to go and from there we can maintain quite a vast sense of universal ability.

#####Boot
This is where various ASM Bootloader sources are held.

#####Source
Information regarding the code will be added soon.

Credits
=====
This project has always been built by only one programmer, Alex Gurrola.  One day he hopes this system will no longer require his influence to progress without feature creep.
