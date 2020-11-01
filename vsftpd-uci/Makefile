#
# Copyright (C) 2020 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=vsftpd-uci
PKG_VERSION:=3.0.3
PKG_RELEASE:=5

PKG_SOURCE:=vsftpd-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://security.appspot.com/downloads/
PKG_HASH:=9d4d2bf6e6e2884852ba4e69e157a2cecd68c5a7635d66a3a8cf8d898c955ef7

PKG_MAINTAINER:=Cezary Jackiewicz <cezary@eko.one.pl>
PKG_LICENSE:=GPLv2
PKG_CPE_ID:=cpe:/a:beasts:vsftpd-uci

BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_BUILD_DIR:=$(BUILD_DIR)/vsftpd-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/vsftpd-uci/Default
  SUBMENU:=File Transfer
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Fast and secure FTP server, with UCI support
  URL:=https://security.appspot.com/vsftpd.html
  DEPENDS+=+libuci +libcap
endef


define Package/vsftpd-uci
$(call Package/vsftpd-uci/Default)
  VARIANT:=notls
  TITLE+= (no TLS)
endef

define Package/vsftpd-uci-tls
$(call Package/vsftpd-uci/Default)
  VARIANT:=tls
  TITLE+= (TLS)
  DEPENDS+=+libopenssl
endef

define Package/vsftpd-uci/conffiles
/etc/vsftpd.conf
/etc/vsftpd
endef

Package/vsftpd-uci-tls/conffiles=$(Package/vsftpd-uci/conffiles)

ifneq ($(CONFIG_USE_MUSL),)
  NLSSTRING:=-lcrypt
else ifneq ($(CONFIG_USE_GLIBC),)
  NLSSTRING:=-lcrypt
else
  NLSSTRING:=-lcrypt -lnsl
endif

TARGET_CFLAGS += -D_GNU_SOURCE -include fcntl.h -luci
TARGET_LDFLAGS += -lcap

ifeq ($(BUILD_VARIANT),notls)
 define Build/Compile
	$(SED) 's/-lcrypt -lnsl/$(NLSSTRING)/' $(PKG_BUILD_DIR)/Makefile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)" \
		vsftpd
 endef
endif

ifeq ($(BUILD_VARIANT),tls)
 define Build/Compile
	$(SED) 's/#undef VSF_BUILD_SSL/#define VSF_BUILD_SSL/' $(PKG_BUILD_DIR)/builddefs.h
	$(SED) 's/-lcrypt -lnsl/-lcrypt -lnsl -lssl -lcrypto/' $(PKG_BUILD_DIR)/Makefile
	$(SED) 's/-lcrypt -lnsl/$(NLSSTRING)/' $(PKG_BUILD_DIR)/Makefile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)" \
		vsftpd
 endef
endif

define Package/vsftpd-uci/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/vsftpd $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/vsftpd.config $(1)/etc/config/vsftpd
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/vsftpd.init $(1)/etc/init.d/vsftpd
	$(INSTALL_DIR) $(1)/etc/vsftpd
endef

Package/vsftpd-uci-tls/install=$(Package/vsftpd-uci/install)

$(eval $(call BuildPackage,vsftpd-uci))
$(eval $(call BuildPackage,vsftpd-uci-tls))
