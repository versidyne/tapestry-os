#!/bin/bash

sudo test

cd ../img

sudo /sbin/losetup /dev/loop0 cd.iso
sudo mount -o loop -t iso9660 cd.iso /mnt2

sudo dd if=floppy.img of=/dev/loop0

sudo umount /mnt2
sudo /sbin/losetup -d /dev/loop0
