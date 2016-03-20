#
# Copyright (C) 2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=dummy-irq
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/dummy-irq
  SUBMENU:=Other modules
  DEPENDS:=
  KCONFIG:=
  TITLE:=Dummy IRQ handler
  FILES:=$(PKG_BUILD_DIR)/dummy-irq.ko
  AUTOLOAD:=$(call AutoLoad,98,dummy-irq)
endef

define KernelPackage/dummy-irq/description
	  This module accepts a single 'irq' or 'gpio' parameter, 
	  which it should register for. For the gpio it gets the 
	  irq if any at the GPIO line. 

	  The module prints a kernel message every time the irq is 
	  triggered. The sole purpose of this module is to help with
	  debugging
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

$(eval $(call KernelPackage,dummy-irq))
