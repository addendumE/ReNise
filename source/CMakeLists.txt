cmake_minimum_required(VERSION 3.4.3)
# cmake ../source/ -DLVGL_DIR=/home/maurizio/repos/alwinner_D1/package/gui/littlevgl-8/lvgl -DUSE_SUNXIFB -DUSE_SDL
project(renise C CXX)
set(CMAKE_BUILD_TYPE Debug)


option(USE_SDL "Use SDL2 backend" OFF)
option(USE_SUNXIFB "Use USE_SUNXIFB backend" ON)

if(NOT LVGL_DIR)
    message(FATAL_ERROR "LVGL_DIR non definito")
endif()

set(LV_DRIVERS_DIR
    "${LVGL_DIR}/../lv_drivers"
)


file(GLOB_RECURSE LVGL_SOURCES
    "${LVGL_DIR}/src/*.c"
)

if(NOT LVGL_SOURCES)
    message(FATAL_ERROR "Nessun sorgente LVGL trovato")
endif()

file(GLOB_RECURSE LV_DRIVERS_SOURCES
    "${LV_DRIVERS_DIR}/*.c"
)

if(NOT LV_DRIVERS_SOURCES)
    message(FATAL_ERROR "Nessun sorgente LVGL DRIVER trovato")
endif()

add_library(lvgl STATIC
    ${LVGL_SOURCES}
)

add_library(lv_drivers STATIC
    ${LV_DRIVERS_SOURCES}
)

target_include_directories(lvgl PUBLIC
    "${LVGL_DIR}/src"
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl
)

target_include_directories(lv_drivers PUBLIC
    "${LVGL_DIR}/.."
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl
)

target_compile_definitions(lvgl PRIVATE
    LV_CONF_INCLUDE_SIMPLE
)

target_compile_definitions(lv_drivers PRIVATE
    LV_CONF_INCLUDE_SIMPLE
)

add_executable(renise
    main.cpp
)

if(USE_SDL)
    message(STATUS "USE_SDL = ON")
    find_package(SDL2 REQUIRED)
    target_compile_definitions(renise PRIVATE
        USE_SDL=1
    )

    target_compile_definitions(lv_drivers PRIVATE
        USE_SDL=1
    )

endif()

if(USE_SUNXIFB)
    target_compile_definitions(renise PRIVATE
        USE_SUNXIFB=1
    )

    target_compile_definitions(lv_drivers PRIVATE
        USE_SUNXIFB=1
    )
endif()


target_link_libraries(renise PRIVATE
    lvgl
    lv_drivers
    cdio
)
if(USE_SDL)
    target_link_libraries(renise PRIVATE
        SDL2::SDL2
    )
endif()

install(TARGETS renise
    RUNTIME DESTINATION bin
)