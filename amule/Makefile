#
# Copyright (C) 2007-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=aMule
PKG_VERSION:=2.3.2
PKG_RELEASE:=1
PKG_MD5SUM:=f48efb9c7bb75d272e39c63e187a18bc
PKG_REV:=11066

PKG_SOURCE:=$(PKG_NAME)-SVN-r$(PKG_REV).tar.bz2
PKG_SOURCE_URL:=http://amule.sourceforge.net/tarballs
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-SVN-r$(PKG_REV)

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-SVN-r$(PKG_REV)
PKG_BUILD_DEPENDS:=libgd libcryptopp

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/amule/config
config AMULE_CRYPTOPP_STATIC_LINKING
	bool "Link libcryptopp statically"
	default n
endef

define Package/amule
  SECTION:=net
  SUBMENU:=P2P
  CATEGORY:=Network
  TITLE:=A multi-platform eMule-like ed2k client
  URL:=http://www.amule.org/
  DEPENDS:=+libpng +libpthread +libncurses +libreadline +libupnp +libwxbase +libbfd \
	$(ICONV_DEPENDS) $(INTL_DEPENDS) +!AMULE_CRYPTOPP_STATIC_LINKING:libcryptopp
endef

define Package/amule/description
   P2P ed2k amule daemon
endef

CONFIGURE_ARGS+= \
	--disable-static \
	--disable-rpath \
	--with-gnu-ld \
	--disable-ccache \
	--enable-optimize \
	--disable-profile \
	--disable-monolithic \
	--enable-amule-daemon \
	--enable-amulecmd \
	--enable-webserver \
	--disable-amule-gui \
	--disable-cas \
	--disable-wxcas \
	--disable-ed2k \
	--disable-alc \
	--disable-alcc \
	--disable-fileview \
	--disable-plasmamule \
	--without-wxdebug \
	--disable-dlp \
	--disable-upnp \
	--with-zlib="$(STAGING_DIR)/usr" \
	--with-gdlib-prefix="$(STAGING_DIR)/usr" \
	--with-libpng-prefix="$(STAGING_DIR)/usr" \
	--with-wx-prefix="$(STAGING_DIR)/usr" \
	--with-crypto-prefix="$(STAGING_DIR)/usr" \
	--with-libiconv-prefix="$(ICONV_PREFIX)" \
	--with-libintl-prefix="$(INTL_PREFIX)" \
	--with-libupnp-prefix="$(STAGING_DIR)/usr" \
	--without-x \
	--disable-debug \
	--enable-mmap

TARGET_LDFLAGS += -liconv 


define Build/Configure
	cd $(PKG_BUILD_DIR) && sh ./autogen.sh
	$(call Build/Configure/Default)
endef

ifeq ($(CONFIG_AMULE_CRYPTOPP_STATIC_LINKING),y)
	SED_CMD:=sed
else
	SED_CMD:=true
endif

define Build/Compile
	$(SED_CMD) -i 's;^CRYPTOPP_LIBS.*;CRYPTOPP_LIBS \= "$(STAGING_DIR)/usr/lib/libcryptopp.a";g' \
		$(PKG_BUILD_DIR)/src/Makefile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		HOSTCC="$(HOSTCC)" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		all
endef

define Package/amule/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/share/amule/webserver
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/amule{cmd,d} $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/webserver/src/amuleweb $(1)/usr/bin/
	$(CP) $(PKG_BUILD_DIR)/src/webserver/default $(1)/usr/share/amule/webserver
	$(INSTALL_DIR) $(1)/etc/amuled
	$(INSTALL_DATA) ./files/amule.conf $(1)/etc/amuled/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/amuled.init $(1)/etc/init.d/amuled
endef

$(eval $(call BuildPackage,amule))
