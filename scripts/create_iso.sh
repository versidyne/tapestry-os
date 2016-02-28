#!/bin/bash

# Copy files to iso folder
cp ../bin/kernel ../iso/kernel
cp ../bin/initrd.img ../iso/initrd

# Build CD Format
genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o ../img/tapestry.iso -A Tapestry ../iso
