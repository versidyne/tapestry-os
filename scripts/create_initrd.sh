#!/bin/bash

cd ../initrd

./make_initrd config config driver driver

mv initrd.img ../bin/initrd.img

cd ../scripts
