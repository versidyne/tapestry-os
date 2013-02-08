#!/bin/bash

# run_bochs.sh
# mounts the correct loopback device, runs bochs, then unmounts.

sudo /sbin/losetup /dev/loop0 ../img/floppy.img
sudo bochs -f ../conf/bochsrc.txt
sudo /sbin/losetup -d /dev/loop0
