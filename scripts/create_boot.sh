#!/bin/bash

sudo test

cd ..
cd boot

nasm boot.asm -f bin -o boot.bin

mv boot.bin ../bin/boot.bin

cd ../bin/

sudo /sbin/losetup /dev/loop0 ../img/tapestryb.iso
sudo mount -o loop -t iso9660 ../img/tapestryb.iso /mnt2

sudo dd if=boot.bin of=/dev/loop0

sudo umount /mnt2
sudo /sbin/losetup -d /dev/loop0
