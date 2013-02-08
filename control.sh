#!/bin/sh

# Test Priveleges
sudo test

#Command Functions
help() {
	
	echo "All commands available will be listed below.\n"
	
}

clean() {
	
	make clean
	
}

make() {
	
	make
	mv kernel bin
	
}

build() {
	
	clean()
	make()
	./scripts/initrd.sh
	./scripts/create_iso.sh
	
}

archive() {
	
	clean()
	build()
	tar -czf Vexis.tar.gz *
	
}

mount() {
	
	#sudo /sbin/losetup /dev/loop0 ../img/cd.iso
	sudo /sbin/losetup /dev/loop0 ../img/floppy.img
	sudo mount /dev/loop0 /mnt2
	#sudo mount -o loop -t iso9660 ../img/cd.iso /mnt2
	
}

unmount() {
	
	sudo umount /dev/loop0
	sudo /sbin/losetup -d /dev/loop0
	#sudo umount /mnt2
	
}

# Loop until all parameters are used up
while [ "$1" != "" ]; do
	
	#echo "Parameter 1 equals $1"
	#echo "You now have $# positional parameters"
	
	# Evaluate variables
	if [ "$1" = "help" ]
	then
		help()
	fi
	
	if [ "$1" = "archive" ]
	then	
		archive()
	fi
	
	if [ "$1" = "build" ] then
		
		build()
		
	fi
	
	if [ "$1" = "mount" ] then
		
		mount=()
		
	fi
	
	if [ "$1" = "unmount" ] then
		
		unmount=()
		
	fi
	
	# Shift all the parameters down by one
	shift
	
done
