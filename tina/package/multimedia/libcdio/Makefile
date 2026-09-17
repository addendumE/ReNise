include $(TOPDIR)/rules.mk

PKG_NAME:=libcdio
PKG_VERSION:=2.1.0
PKG_RELEASE:=1

PKG_SOURCE:=libcdio-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://ftp.gnu.org/gnu/libcdio
PKG_MD5SUM:=aa7629e8f73662a762f64c444b901055

PKG_LICENSE:=GPL-3.0-or-later
PKG_LICENSE_FILES:=COPYING

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

PKG_BUILD_DIR:=$(COMPILE_DIR)/libcdio-$(PKG_VERSION)

include $(BUILD_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=GNU Compact Disc Input and Control Library
  URL:=https://www.gnu.org/software/libcdio/
  DEPENDS:=+libstdcpp
endef

define Package/$(PKG_NAME)/description
  GNU Compact Disc Input and Control Library.
  Provides access to CD-ROM and audio CD devices.
endef

CONFIGURE_ARGS += \
	--enable-static=no \
	--disable-cddb \
	--disable-vcd-info \
	--disable-cdda-player

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/* $(1)/usr/lib/pkgconfig/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

