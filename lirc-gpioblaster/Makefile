#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=lirc_gpioblaster
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/lirc_gpioblaster
  SUBMENU:=Other modules
  DEPENDS:=
  KCONFIG:= \
	CONFIG_MEDIA_SUPPORT=y \
	CONFIG_INPUT=y \
	CONFIG_LIRC_STAGING=y \
	CONFIG_STAGING_MEDIA=y \
	CONFIG_LIRC=y \
	CONFIG_RC_CORE=y \
	CONFIG_IR_SANYO_DECODER=n \
	CONFIG_IR_MCE_KBD_DECODER=n \
	CONFIG_RC_ATI_REMOTE=n \
	CONFIG_IR_REDRAT3=n \
	CONFIG_LIRC_BT829=n \
	CONFIG_LIRC_IGORPLUGUSB=n \
	CONFIG_LIRC_IMON=n \
	CONFIG_LIRC_SASEM=n \
	CONFIG_LIRC_SERIAL=n \
	CONFIG_LIRC_SIR=n \
	CONFIG_LIRC_TTUSBIR=n \
	CONFIG_RC_LOOPBACK=n
  TITLE:=Driver for LIRC GPIO transmitter
  FILES:=$(PKG_BUILD_DIR)/lirc_gpioblaster.ko
  AUTOLOAD:=$(call AutoLoad,99,lirc_gpioblaster)
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(BUILDFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,lirc_gpioblaster))
