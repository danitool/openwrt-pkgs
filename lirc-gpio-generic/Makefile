#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=lirc_gpio_generic
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/lirc_gpio_generic
  SUBMENU:=Other modules
  DEPENDS:=
  KCONFIG:= \
	CONFIG_MEDIA_SUPPORT=y \
	CONFIG_INPUT=y \
	CONFIG_MEDIA_RC_SUPPORT=y \
	CONFIG_RC_DECODERS=y \
	CONFIG_LIRC_STAGING=y \
	CONFIG_STAGING_MEDIA=y \
	CONFIG_LIRC=y \
	CONFIG_RC_CORE=y \
	CONFIG_IR_SANYO_DECODER=n \
	CONFIG_IR_MCE_KBD_DECODER=n \
	CONFIG_RC_ATI_REMOTE=n \
	CONFIG_IR_REDRAT3=n \
	CONFIG_IR_SHARP_DECODER=n \
	CONFIG_IR_XMP_DECODER=n \
	CONFIG_RC_DEVICES=n \
	CONFIG_LIRC_BT829=n \
	CONFIG_LIRC_IGORPLUGUSB=n \
	CONFIG_LIRC_IMON=n \
	CONFIG_LIRC_SASEM=n \
	CONFIG_LIRC_SERIAL=n \
	CONFIG_LIRC_SIR=n \
	CONFIG_LIRC_ZILOG=n \
	CONFIG_RC_LOOPBACK=n
  TITLE:=Driver for LIRC GPIO receiver/transmitter
  FILES:=$(PKG_BUILD_DIR)/lirc_gpio_generic.ko
  AUTOLOAD:=$(call AutoLoad,99,lirc_gpio_generic)
endef

define KernelPackage/lirc_gpio_generic/description
  LIRC kernel module to emulate IR receiver/transmitter
  with GPIOs on any target.
  
  *************************************************************
  * This kernel module ONLY works if the device has GPIO IRQs * 
  * implemented in the GPIO driver.                           *
  *************************************************************

  OpenWrt version tested
  --------------
  OK: Chaos Calmer
endef

define Build/Prepare
	$(CP) ./kernel-patches/ar71xx/728-MIPS-ath79-add-gpio-irq.patch \
		$(TOPDIR)/target/linux/ar71xx/patches-3.18/
	$(CP) ./kernel-patches/brcm63xx/904-CC-irq_bcm_ext-gpio_to_irq.patch \
		$(TOPDIR)/target/linux/brcm63xx/patches-3.18/
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

$(eval $(call KernelPackage,lirc_gpio_generic))
