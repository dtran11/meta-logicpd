DESCRIPTION = "U-Boot - the Universal Boot Loader"
HOMEPAGE = "http://www.denx.de/wiki/U-Boot/WebHome"
SECTION = "bootloaders"
PRIORITY = "optional"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb"

PROVIDES = "virtual/bootloader"

DEPENDS = "mtd-utils"

PACKAGE_ARCH = "${MACHINE_ARCH}"
PARALLEL_MAKE=""

EXTRA_OEMAKE = "CROSS_COMPILE=${TARGET_PREFIX}"

UBOOT_MACHINE ?= "${MACHINE}_config"
UBOOT_SPL ?= "MLO"
UBOOT_SPL_TARGET ?= "MLO-${MACHINE}-${PV}-${PR}"
UBOOT_BINARY ?= "u-boot.bin"
UBOOT_BIN_TARGET ?= "u-boot-${MACHINE}-${PV}-${PR}.bin"
UBOOT_IMAGE ?= "u-boot.img"
UBOOT_IMG_TARGET = "u-boot-${MACHINE}-${PV}-${PR}.img"
UBOOT_BIN_SYMLINK ?= "u-boot-${MACHINE}.bin"
UBOOT_IMG_SYMLINK ?= "u-boot-${MACHINE}.img"
UBOOT_MAKE_TARGET ?= "all"

do_configure () {
	oe_runmake ${UBOOT_MACHINE}
}

do_compile () {
	unset LDFLAGS
	unset CFLAGS
	unset CPPFLAGS
	oe_runmake ${UBOOT_MAKE_TARGET}
}

do_install () {
	install -d ${D}/boot
	install ${S}/${UBOOT_BINARY} ${D}/boot/${UBOOT_BIN_TARGET}
	ln -sf ${UBOOT_BIN_TARGET} ${D}/boot/${UBOOT_BINARY}
}

FILES_${PN} = "/boot"
# no gnu_hash in uboot.bin, by design, so skip QA
INSANE_SKIP_${PN} = "True"

PACKAGES += "${PN}-fw-utils"
FILES_${PN}-fw-utils = "${sysconfdir} ${base_sbindir}"
# u-boot doesn't use LDFLAGS for fw files, needs to get fixed, but until then:
INSANE_SKIP_${PN}-fw-utils = "True"

do_deploy () {
	install -d ${DEPLOY_DIR_IMAGE}
	install ${S}/${UBOOT_BINARY} ${DEPLOY_DIR_IMAGE}/${UBOOT_BIN_TARGET}
	package_stagefile_shell ${DEPLOY_DIR_IMAGE}/${UBOOT_BIN_TARGET}

	install ${S}/${UBOOT_SPL} ${DEPLOY_DIR_IMAGE}/${UBOOT_SPL_TARGET}
	install ${S}/${UBOOT_IMAGE} ${DEPLOY_DIR_IMAGE}/${UBOOT_IMG_TARGET}
	
	cd ${DEPLOY_DIR_IMAGE}
	rm -f ${UBOOT_BIN_SYMLINK}
	rm -f ${UBOOT_IMG_SYMLINK}
	ln -sf ${UBOOT_BIN_TARGET} ${UBOOT_BIN_SYMLINK}
	ln -sf ${UBOOT_IMG_TARGET} ${UBOOT_IMG_SYMLINK}
	package_stagefile_shell ${DEPLOY_DIR_IMAGE}/${UBOOT_BIN_SYMLINK}
}
do_deploy[dirs] = "${S}"
addtask deploy before do_package_stage after do_compile

