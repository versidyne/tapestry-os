Tapestry OS - Universal Operating System
=====
#####Overview
This is the complete core of Tapestry OS, a Unix-Like Operating System in C.  This will eventually be utilized to run long range wireless networking and thin clients for the Tapestry network.

#####Goals
* Maintain a solid system for which networking, radio frequency modulation, and custom-rom thin clients/video games can be developed with ease.

* Develop a robust, abstract, kernel with several different architectures and internal gateways that will provide different types of functionality for switching roms to various games, applications, methods, etc, running directly from the kernel as a window manager.  This makes reboots for modes more frequent but will boost performance greatly.

Installation
=====
#####Overview
This is a simple process and will remain as such if instructions are followed carefully.

#####Configuration
This is currently not an option, though it will be in the future.

#####Virtualization
Simply run tapestry.iso as a CD Rom.  This can be done with bochs, qemu, or virtualbox-ose easily.

```sh
qemu --cdrom img/tapestry.iso --boot d -soundhw all
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