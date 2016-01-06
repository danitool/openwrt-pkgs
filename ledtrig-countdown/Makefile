#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=ledtrig-countdown
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/ledtrig-countdown
  SUBMENU:=LED modules
  DEPENDS:= @GPIO_SUPPORT
  KCONFIG:= 
  TITLE:=LED Kernel Countdown Trigger
  FILES:=$(PKG_BUILD_DIR)/ledtrig-countdown.ko
  AUTOLOAD:=$(call AutoLoad,97,ledtrig-countdown)
endef

define KernelPackage/ledtrig-countdown/description
  LED Kernel Countdown Trigger
  Led trigger like oneshot, but more simple.
  
  EXAMPLE:
  ******************************************************
  register the trigger:
          echo countdown > /sys/class/leds/MYLED/trigger
  100 miliseconds MYLED on:
          echo 100 > /sys/class/leds/MYLED/countdown
  ******************************************************
  
  OpenWrt version tested
  --------------
  OK: Attitude Adjustment 12.09 (Linux 3.3.8)
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

$(eval $(call KernelPackage,ledtrig-countdown))
