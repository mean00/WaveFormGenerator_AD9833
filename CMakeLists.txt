#=============================================================================#
# cmake arduino cloned from https://github.com/ncasaril/arduino-cmake.git     #
#=============================================================================#
set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # Arduino Toolchain


cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(ArduinoExample C CXX)
#
# FOR UNO
#set(ARDUINO_DEFAULT_BOARD uno)        # Default Board ID, when not specified
#set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified
#set(ARDUINO_CPU          atmega328)
# FOR NANO
# this is needed for the nano, it should be set automatically, maybe something changed with sdk 1.8.x ?
set(ARDUINO_CPU          atmega328)
set(ARDUINO_CPUMENU .menu.cpu.${ARDUINO_CPU})
set(ARDUINO_DEFAULT_BOARD nano)        # Default Board ID, when not specified
#
print_board_list()
print_programmer_list()

PRINT_SETTINGS(${ARDUINO_DEFAULT_BOARD})

# Where you store your downloaded libs or manually installed
SET(CUSTOM_LIB_DIR /home/fx/Arduino/libraries)

link_directories( ${CUSTOM_LIB_DIR})
link_directories( ${CMAKE_BINARY_DIR})

# u8glib is complicated and needs special care
include_directories(${CUSTOM_LIB_DIR}/Wire/src)
include_directories(${CUSTOM_LIB_DIR}/U8g2/src)
set(U8g2lib_RECURSE True)
set(U8g2_RECURSE True)
#SET(ARDUINO_EXTRA_LIBRARIES_PATH ${CUSTOM_LIB_DIR}/U8g2/src)
#
# Be careful with the includes in the ino files
# #include <foo.h> // this is a comment
# will fail
# same with extra tabs or space after the #include "blah.h"
#
SET(libPrefix ${ARDUINO_DEFAULT_BOARD}_)

##ADD_DEFINITIONS(-DUSING_CMAKE)

generate_arduino_firmware(wavform_generator 
                SKETCH .              # Folder to get the .ino from, must follow DIR_NAME/DIR_NAME.ino patten !
               ## SRCS  ampmeter.ino amp_display.cpp
                LIBS ${libPrefix}AD9833
                LIBS ${libPrefix}Wire
                LIBS ${libPrefix}SPI
                LIBS ${libPrefix}U8g2lib
                LIBS ${libPrefix}Bounce2
                LIBS ${libPrefix}Rotary
                PORT ${ARDUINO_DEFAULT_PORT}
                )

# EOF
