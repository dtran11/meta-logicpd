require u-boot.inc

SRCREV = "190649fb4309d1bc0fe7732fd0f951cb6440f935"

PV = "2012.07"
PR = "r1"

SRC_URI = "git://git.denx.de/u-boot.git;branch=master;protocol=git \
	   file://uboot-fixes.patch;apply=yes \
	   file://uboot-fast-boot.patch;apply=yes \
          "

S = "${WORKDIR}/git"


do_configure_prepend() {

	if [ "${UBOOT_SERIAL_CONSOLE}" = "ttyS2" ]; then
            sed -i 's:ttyO2:ttyS2:g' ${S}/include/configs/omap3_overo.h
        fi

	if [ "${UBOOT_SERIAL_CONSOLE}" = "ttyO2" ]; then
            sed -i 's:ttyS2:ttyO2:g' ${S}/include/configs/omap3_overo.h
        fi

        if [ "${UBOOT_FAST_MODE}" = "nand" ]; then
            sed -i 's:/\*#define CONFIG_FAST_BOOT\*/:#define CONFIG_FAST_BOOT:g' ${S}/include/configs/omap3_overo.h ${S}/include/configs/omap3_logic.h
            sed -i 's:/\*#define CONFIG_FAST_BOOT_NAND\*/:#define CONFIG_FAST_BOOT_NAND:g' ${S}/include/configs/omap3_overo.h ${S}/include/configs/omap3_logic.h
        fi

        if [ "${UBOOT_FAST_MODE}" = "mmc" ]; then
            sed -i 's:/\*#define CONFIG_FAST_BOOT\*/:#define CONFIG_FAST_BOOT:g' ${S}/include/configs/omap3_overo.h ${S}/include/configs/omap3_logic.h
            sed -i 's:/\*#define CONFIG_FAST_BOOT_MMC\*/:#define CONFIG_FAST_BOOT_MMC:g' ${S}/include/configs/omap3_overo.h ${S}/include/configs/omap3_logic.h
        fi
}

