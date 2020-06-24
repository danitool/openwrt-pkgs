#
# Copyright (C) 2020 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=call_qcsapi
PKG_RELEASE:=1
PKG_VERSION:=1.0.1

PKG_BUILD_DEPENDS:=libtirpc
include $(INCLUDE_DIR)/package.mk


define Package/call_qcsapi
  SECTION:=net
  CATEGORY:=Network
  TITLE:=call_qcsapi tools
  DEPENDS:=+libtirpc
endef

TARGET_CFLAGS  += -include string.h -I$(STAGING_DIR)/usr/include/tirpc -I. -D_GNU_SOURCE \
		  -fPIC -O -g -Wall  -Wno-unused-variable -Wno-unused-parameter
TARGET_LDFLAGS += -ltirpc

define Package/call_qcsapi/description
	call_qcsapi tools
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Package/call_qcsapi/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/call_qcsapi_sockrpc $(1)/usr/bin/call_qcsapi_sockrpc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/call_qcsapi_raw $(1)/usr/bin/call_qcsapi_raw
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/quantenna.init $(1)/etc/init.d/quantenna
	$(INSTALL_DIR) $(1)/etc/wlan
	$(INSTALL_BIN) ./files/wlan/u-boot.bin $(1)/etc/wlan/u-boot.bin
	$(INSTALL_BIN) ./files/wlan/topaz-linux.lzma.img $(1)/etc/wlan/topaz-linux.lzma.img
endef

$(eval $(call BuildPackage,call_qcsapi))
