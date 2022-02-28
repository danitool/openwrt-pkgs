#
# Copyright (C) 2009-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libcryptopp
PKG_VERSION:=8.6.0
PKG_RELEASE:=1

PKG_SOURCE:=cryptopp$(subst .,,$(PKG_VERSION)).zip
PKG_SOURCE_URL:=https://www.cryptopp.com/
PKG_MD5SUM:=c5441a67a351749bdeacc1ffb0c01878

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/libcryptopp
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+libpthread +libstdcpp
  TITLE:=Crypto++ is library for creating C++ programs which use cryptographic algorithms
  URL:=https://packages.debian.org/sid/libcrypto++-dev
endef

define Package/package/libcryptopp
  Crypto++ is library for creating C++ programs which use cryptographic algorithms.
  The library uses a Pipes & Filters architecture with heavy use of templates and
  abstract base classes.
endef

TARGET_CXXFLAGS += $(FPIC) -pthread
TARGET_LDFLAGS += -pthread 

UNPACK_CMD=cd $(PKG_BUILD_DIR) && unzip "$(DL_DIR)/$(PKG_SOURCE)"

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		CXXFLAGS="$(TARGET_CXXFLAGS)" \
		all
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/cryptopp
	$(CP) $(PKG_INSTALL_DIR)/usr/local/include/cryptopp/* $(1)/usr/include/cryptopp/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/libcryptopp.{a,so*} $(1)/usr/lib/
endef

define Package/libcryptopp/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/libcryptopp.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libcryptopp))
