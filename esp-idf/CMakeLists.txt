# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
set(COMPONENTS bootloader esptool_py main test AudioInI2S)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ESP32-AudioInI2S)