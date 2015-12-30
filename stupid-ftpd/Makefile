#
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=stupid-ftpd
PKG_VERSION:=1.5beta
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://downloads.sourceforge.net/project/stupid-ftpd/stupid-ftpd/V1_5beta/
PKG_MD5SUM:=be5700570bc38376515d33595e416663

PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/stupid-ftpd
  SUBMENU:=File Transfer
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Lightweight easy FTP server
  URL:=http://stupid-ftpd.sourceforge.net/
  MAINTAINER:=Daniel González <dgcbueu@gmail.com>
endef

define Package/stupid-ftpd/description
	stupid-ftpd is an ftp server, which provides a normal ftp-daemon functionality
	and a command-line mode. It has got a /etc/passwdindependent user database 
	which allows many variations of permissions. The server is easy to configure 
	and very flexible
endef

define Package/stupid-ftpd/conffiles
/etc/stupid-ftpd/stupid-ftpd.conf
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS)"
endef

define Package/stupid-ftpd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME).Linux6 $(1)/usr/sbin/$(PKG_NAME)
	$(INSTALL_DIR) $(1)/etc/stupid-ftpd
	$(INSTALL_CONF) ./files/$(PKG_NAME).conf $(1)/etc/stupid-ftpd/$(PKG_NAME).conf
endef

$(eval $(call BuildPackage,stupid-ftpd))
