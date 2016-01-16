# 
# Copyright (C) 2007 - 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=mpd-legacy
PKG_VERSION:=0.13.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://www.musicpd.org/uploads/files/
PKG_MD5SUM:=b461896369949ff3cff955692ead9f8b

include $(INCLUDE_DIR)/package.mk

define Package/mpd-legacy
  SECTION:=sound
  CATEGORY:=Sound
  TITLE:=Music Player Daemon 0.13.2
  DEPENDS:=+alsa-lib \
  +BUILD_PATENTED:libmad +libpthread +libiconv
  URL:=http://www.musicpd.org/
endef

define Package/mpd-legacy/description
	******0.13.2 version for devices with low resources *******
	Tested under Attitude Adjustment, in a router with 16MB RAM
	8MB flash. This package only enables support for mp3 and uses
	alsa sound system for the audio output.
	Focused on streaming online radio stations, but can also play
	mp3 files stored locally.
	
	MPD is a music player supporting flac, mp3 and ogg files.
	It is typically controlled over a network using one of it's many
	clients including mpc(console), gmpc(gnome), phpmp(php) etc.
endef

define Package/mpd-legacy/conffiles
/etc/mpd.conf
endef

CONFIGURE_VARS += \
	$(if $(CONFIG_BUILD_PATENTED),MAD_CFLAGS="$(TARGET_CFLAGS)") \
	$(if $(CONFIG_BUILD_PATENTED),MAD_LIBS="$(TARGET_LDFLAGS) -lmad") \

TARGET_CFLAGS += -std=gnu99
TARGET_LDFLAGS += -Wl,-rpath-link=$(STAGING_DIR)/usr/lib

# use gcc instead of g++ to avoid unnecessary linking against libstdc++
TARGET_CXX:=$(TARGET_CC)

define Build/Configure
	$(call Build/Configure/Default, \
	$(call autoconf_bool,CONFIG_BUILD_PATENTED,mad) \
	        --disable-mod \
	        --disable-audiofile \
	        --disable-mpc \
	        --disable-aac \
		--disable-lsr \
		--disable-id3 \
--disable-shout \
--disable-ao \
--disable-oss \
--disable-jack \
--disable-pulse \
--disable-oggvorbis \
--disable-oggflac \
--disable-flac \
--disable-ipv6 \
--disable-aotest \
--disable-oggtest \
--disable-vorbistest \
--disable-libFLACtest \
--disable-libOggFLACtest \
--disable-audiofiletest \
--disable-libmikmodtest \
	)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		all install
endef

define Package/mpd-legacy/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_CONF) ./files/mpd.conf $(1)/etc/ #mod
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/mpd.init $(1)/etc/init.d/mpd
	$(INSTALL_DIR) $(1)/etc/streamradio/playlists/ #mod
	$(INSTALL_CONF) ./files/radiostations.m3u $(1)/etc/streamradio/playlists/ #mod
	$(INSTALL_BIN) ./files/usbplay.sh $(1)/etc/streamradio/ #mod
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/mpd $(1)/usr/bin/
endef

$(eval $(call BuildPackage,mpd-legacy))
