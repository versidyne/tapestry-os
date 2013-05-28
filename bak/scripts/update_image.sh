#!/bin/bash

./mount_image.sh

sudo cp ../bin/kernel /mnt2/kernel
sudo cp ../img/initrd.img /mnt2/initrd

./unmount_image.sh
