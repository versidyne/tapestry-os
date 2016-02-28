#!/bin/bash
# Tapestry OS Maintenance Script
# Credits: Scaery

Options=$@
Optnum=$#
sarguments='no '
sARG=empty
larguments='no '
lARG=empty

#Depended Tapestry OS

sclean='no '	#-c
smake='no ' 	#-m (reset and make)
sbuild='no ' 	#-b
sarchive='no ' 	#-a
smount='no ' 	#-l
sunmount='no '	#-u

lclean='no '	#--clean
lmake='no '	#--make
lbuild='no '	#--build
larchive='no '	#--archive
lmount='no '	#--mount (loop and mount)
lunmount='no'	#--unmount (destroy loop and unmount)

_usage() {
cat <<EOF
$Options $*
	Usage: control.sh <[options]>
	Options:
	#Normal Options
		-h	--help		Show this message
		-A	--arguments=...	Set arguments to yes ($arguments) AND get ARGUMENT ($ARG)
	#Depending Tapestry Commands
                -a      --archive       Archive the current project files ($archive)
                -b      --build         Build Project ($build)
		-c	--clean		Cleaning Project ($clean)
		-m	--remake	Clean and build from Scratch ($make)
		-l	--mount		Mount Project to /mnt2 ($mount)
		-u	--unmount	Unmount Project from /mnt2 ($unmount)
EOF
}

if [ $# = 0 ]; then _usage " SHORT: >>>>>> short commands..."; fi

while getopts ':abchmlu-A:BF-' OPTION ; do
  case "$OPTION" in
    h  ) _usage                         ;;
    A  ) sarguments=yes;sARG="$OPTARG"  ;;
    -  ) [ $OPTIND -ge 1 ] && optind=$(expr $OPTIND - 1 ) || optind=$OPTIND
         eval OPTION="\$$optind"
         OPTARG=$(echo $OPTION | cut -d'=' -f2)
         OPTION=$(echo $OPTION | cut -d'=' -f1)
         case $OPTION in
	--clean		) lclean=yes	;;
	--make		) lmake=yes	;;
	--build 	) lbuild=yes	;;
	--archive 	) larchive=yes	;;
	--mount 	) lmount=yes	;;
	--unmount	) lunmount=yes	;;
	--help		) _usage	;;
	--arguments ) larguments=yes;lARG="$OPTARG"	;;
         * ) _usage " Long: >>>>>>>> invalide options (long) "	;;
         esac
       OPTIND=1
       shift
      ;;

## tapestry commands support
	c) sclean=yes
		if [ "${1:1:0}" != "-" ]
		then
		make clean
		echo "make clean done"
	echo "==> CLEAN DONE"
	fi;;

	m) smake=yes
		if [ "${1:1:0}" != "-" ]
		then
		make
		mv kernel bin
		echo "make && mv kernel bin"
	echo "==> MAKE DONE "
	fi;;

	b) sbuild=yes
		if [ "${1:1:0}" != "-" ]
		then
		make clean
		make
		mv kernel bin
	echo "[+] MAKE KERNEL DONE"
		cd initrd
		./make_initrd config config driver driver
		mv initrd.img bin/initrd.img
	echo "[+]MAKE INITRD DONE"
		# Copy files to iso folder
		cp bin/kernel iso/kernel
		cp bin/initrd.img iso/initrd
		# Build CD Format
		genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o img/tapestry.iso -A Tapestry iso
	echo -ne "[+]Copy files to iso folder Done\n[+]Build CD Format Done\n"
	echo "==> BUILD DONE"
	fi;;

	a) sarchive=yes
	if [ "${1:1:0}" != "-" ]
		then
	echo "BUILD CLEAN AND ARCHIVE..."
		tar -czf Tapestry.tar.gz *
	echo "Files were with -czvf in Tapestry.tar.gz archived"
	echo "==> ARCHIVE DONE"
	fi;;

	l) smount=yes
		if [[ "${1:1:0}" != "-" && $EUID -ne 0 ]]
		then
                echo "You must be a root user or try with sudo" 2>&1
                exit 1
		#/sbin/losetup /dev/loop0 img/tapestry.iso
		else
		mnt2="/mnt2"
		if [ -s $mnt2 ]
		then echo "Mountpoint /mnt2 exists... "
		else mkdir -p $mnt2
		echo "Mountpoint /mnt2 created... "
		fi
		mount -o loop -t iso9660 img/tapestry.iso /mnt2
		echo "==> MOUNT DONE"
	fi;;
	u) sunmount=yes
                if [[ "${1:1:0}" != "-" && $EUID -ne 0 ]]
                then
		echo "You must be a root user or try with sudo" 2>&1
		exit 1
		else
		#umount /dev/loop0
		#echo "unmount loop0 #1 DONE"
		#/sbin/losetup -d /dev/loop0
		#echo "unmount loop0 #2 DONE"
		umount /mnt2
                echo "unmount /mnt2 DONE"
		echo "==> UNMOUNT DONE"
        fi;;

    ? )  _usage "Short: >>>>>>>> invalide options (short) "  ;;
  esac
done

################# NOTES ##########################################
# - pass arguments to build
# - making arguments for build or build clean and make
# - create archive with time stamp
# - check prequesites (gen2iso , mnt2, qemu, mod iso9660 etc...)
# - implement coommands from from scripts dir
# - clean my comments and document it better
##################################################################

echo ""
echo "------------------START DEBUG -------------------------"
echo "RESULT short-clean : $sclean		long-clean : $lclean"
echo "RESULT short-make : $smake			long-make : $lmake"
echo "RESULT short-build : $sbuild		long-build : $lbuild"
echo "RESULT short-archive : $sarchive		long-archive : $larchive"
echo "RESULT short-mount : $smount		long-mount : $lmount"
echo "RESULT short-unmount : $sunmount              long-unmount : $lunmount"
echo "RESULT short-arguments: $sarguments  with Argument = \"$sARG\"        long-arguments: $larguments and $lARG"
echo "----------------- END DEBUG ---------------------------"

