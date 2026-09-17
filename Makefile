include $(TOPDIR)/rules.mk

PKG_NAME:=renise
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

USE_SOURCE_DIR:=$(CURDIR)/source

include $(BUILD_DIR)/package.mk
include $(BUILD_DIR)/cmake.mk

# Redirect build products and CMake metadata to the local 'build' directory
PKG_BUILD_DIR:=$(CURDIR)/build
CMAKE_SOURCE_DIR:=$(CURDIR)/source

CMAKE_OPTIONS += \
	-DLVGL_DIR=$(TOPDIR)/package/gui/littlevgl-8/lvgl

define Package/$(PKG_NAME)
  SECTION:=multimedia
  TITLE:=renise
  DEPENDS:= +libstdcpp +libcdio +libalsa
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Configure
	#$(RM) $(PKG_BUILD_DIR)/CMakeCache.txt
	$(call Build/Configure/Default)
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
