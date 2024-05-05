# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Set cache variable for IDF_TOOLCHAIN to use clang
set(IDF_TOOLCHAIN "clang++")

idf_build_set_property(CXX_COMPILE_OPTIONS "-std=gnu++20;-DCHIP_HAVE_CONFIG_H" APPEND)

list(APPEND EXTRA_COMPONENT_DIRS
    ${extra_components_dirs_append})

project(driver_test)
