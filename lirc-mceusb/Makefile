#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=lirc_mceusb
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/lirc_mceusb
  SUBMENU:=Other modules
  DEPENDS:=+kmod-usb-core
  KCONFIG:= \
	CONFIG_MEDIA_SUPPORT=y \
	CONFIG_INPUT=y \
	CONFIG_RC_CORE=y \
	CONFIG_LIRC_STAGING=y \
	CONFIG_STAGING_MEDIA=y \
	CONFIG_LIRC=y \
	CONFIG_LIRC_BT829=n \
	CONFIG_LIRC_IGORPLUGUSB=n \
	CONFIG_LIRC_IMON=n \
	CONFIG_LIRC_SASEM=n \
	CONFIG_LIRC_SERIAL=n \
	CONFIG_LIRC_SIR=n \
	CONFIG_LIRC_TTUSBIR=n \
	CONFIG_IR_SANYO_DECODER=n \
	CONFIG_IR_MCE_KBD_DECODER=n \
	CONFIG_RC_ATI_REMOTE=n \
	CONFIG_IR_REDRAT3=n \
	CONFIG_RC_LOOPBACK=n \
	CONFIG_IR_LIRC_CODEC \
	CONFIG_IR_MCEUSB
  TITLE:=Driver for MCEUSB ir
  FILES:= \
	$(LINUX_DIR)/drivers/media/rc/mceusb.ko \
	$(LINUX_DIR)/drivers/media/rc/ir-lirc-codec.ko
  AUTOLOAD:=$(call AutoLoad,98,ir-lirc-codec mceusb)
endef

define KernelPackage/lirc_mceusb/description
    LIRC kernel modules for MCE USB IR receivers
    - modules: ir-lirc-codec, mceusb
endef

#touch package/kernel/linux/Makefile (on older revisions touch package/kernel/Makefile) 

define Build/Prepare
endef

define Build/Configure
endef

define Build/Compile
endef

$(eval $(call KernelPackage,lirc_mceusb)) 
