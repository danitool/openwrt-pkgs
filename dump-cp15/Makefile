#
# Copyright (C) 2020 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=dump-cp15
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/dump-cp15
  SUBMENU:=Other modules
  DEPENDS:=
  KCONFIG:=
  TITLE:=Dump CP15 registers via procfs
  FILES:=$(PKG_BUILD_DIR)/dump_cp15_regs.ko
endef

define KernelPackage/dump-cp15/description
	  This module dumps mvebu cp15 registers via procfs
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(BUILDFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,dump-cp15))
