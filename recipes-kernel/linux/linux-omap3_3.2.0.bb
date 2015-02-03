require linux.inc

DESCRIPTION = "Linux kernel for OMAP processors"
KERNEL_IMAGETYPE = "uImage"

PV = "3.2.0"

S = "${WORKDIR}/git"

SRCREV = "513770d80c0cfb26cc406c9ca3916df2e7afe46d"
SRC_URI = "git://www.github.com/gumstix/linux.git;branch=omap-3.2;protocol=git \
	   file://defconfig \ 
	   file://board.patch;apply=yes \	
	   file://omap-serial-baud-fix.patch;apply=yes \
           "
