#!/bin/bash

sudo test

cd ..
cd boot

nasm boot.asm -f bin -o boot.bin

sudo /sbin/losetup /dev/loop0 ../img/floppyb.img
sudo mount /dev/loop0 /mnt2

sudo dd if=boot.bin of=/dev/loop0

sudo umount /dev/loop0
sudo /sbin/losetup -d /dev/loop0
