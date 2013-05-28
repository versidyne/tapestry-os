#!/bin/bash

# Generate Emulated Floppy
genisoimage -pad -b floppy.img -R -o ../img/cd.iso ../img/floppy.img

# Other Emulated Floppy Options
#sudo dd if=/dev/loop0 of=../img/cd.iso
#sudo genisoimage -o ../img/cd.iso /mnt2
