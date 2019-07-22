#=============================================================================#
# cmake arduino cloned from https://github.com/ncasaril/arduino-cmake.git     #
#=============================================================================#
set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # Arduino Toolchain

cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(WaveFormGen C CXX)
#
# FOR UNO
#set(ARDUINO_DEFAULT_BOARD uno)        # Default Board ID, when not specified
#set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified
#set(ARDUINO_CPU          atmega328)
# FOR NANO
# this is needed for the nano, it should be set automatically, maybe something changed with sdk 1.8.x ?
set(ARDUINO_CPU          atmega328)
set(ARDUINO_DEFAULT_BOARD_CPU ${ARDUINO_CPU})
set(ARDUINO_CPUMENU .menu.cpu.${ARDUINO_CPU})
set(ARDUINO_CPUMENU .menu.CPUS.${ARDUINO_CPU})
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


# our own u8g2
set(COMPONENT_SRCS "csrc/u8x8_setup.c"
                    "csrc/u8x8_u8toa.c"
                    "csrc/u8x8_d_ssd1306_96x16.c"
                    "csrc/u8g2_d_memory.c"
                    "csrc/u8g2_selection_list.c"
                    "csrc/u8g2_hvline.c"
                    "csrc/u8x8_d_ssd1306_128x64_noname.c"
                    "csrc/u8x8_message.c"
                    "csrc/u8x8_d_ssd1306_48x64.c"
                    "csrc/u8x8_d_ssd1305.c"
                    "csrc/u8g2_kerning.c"
                    "csrc/u8x8_input_value.c"
                    "csrc/u8x8_d_st7586s_s028hn118a.c"
                    "csrc/u8g2_polygon.c"
                    "csrc/u8x8_d_uc1604.c"
                    "csrc/u8x8_d_ssd1306_128x32.c"
                    "csrc/u8x8_d_ssd1322.c"
                    "csrc/u8x8_d_sbn1661.c"
                    "csrc/u8g2_input_value.c"
                    "csrc/u8x8_8x8.c"
                    "csrc/u8x8_debounce.c"
                    "csrc/u8x8_d_uc1638.c"
                    "csrc/u8g2_setup.c"
                    "csrc/u8x8_d_ist3020.c"
                    "csrc/u8x8_display.c"
                    "csrc/u8x8_d_ssd1317.c"
                    "csrc/u8x8_d_ks0108.c"
                    "csrc/u8g2_box.c"
                    "csrc/u8x8_selection_list.c"
                    "csrc/u8x8_d_ssd1326.c"
                    "csrc/u8x8_d_st75256.c"
                    "csrc/u8x8_d_ssd1309.c"
                    "csrc/u8x8_byte.c"
                    "csrc/u8x8_d_ssd1607_200x200.c"
                    "csrc/u8x8_d_pcd8544_84x48.c"
                    "csrc/u8log.c"
                    "csrc/u8x8_d_sh1107.c"
                    "csrc/u8log_u8x8.c"
                    "csrc/u8g2_message.c"
                    "csrc/u8x8_d_uc1610.c"
                    "csrc/u8x8_d_sh1106_72x40.c"
                    "csrc/u8g2_line.c"
                    "csrc/u8g2_intersection.c"
                    "csrc/u8g2_fonts.c"
                    "csrc/u8x8_d_sh1106_64x32.c"
                    "csrc/u8x8_d_sed1330.c"
                    "csrc/u8x8_d_pcf8814_hx1230.c"
                    "csrc/u8x8_d_il3820_296x128.c"
                    "csrc/u8x8_d_uc1701_dogs102.c"
                    "csrc/u8g2_cleardisplay.c"
                    "csrc/u8x8_d_ssd1325.c"
                    "csrc/u8g2_font.c"
                    "csrc/u8x8_d_uc1601.c"
                    "csrc/u8x8_d_pcf8812.c"
                    "csrc/u8x8_cad.c"
                    "csrc/u8x8_d_uc1611.c"
                    "csrc/u8x8_string.c"
                    "csrc/u8g2_ll_hvline.c"
                    "csrc/u8x8_fonts.c"
                    "csrc/u8x8_d_ld7032_60x32.c"
                    "csrc/u8x8_d_max7219.c"
                    "csrc/u8x8_d_st7588.c"
                    "csrc/u8x8_d_ssd1606_172x72.c"
                    "csrc/u8x8_d_st7586s_erc240160.c"
                    "csrc/u8x8_d_stdio.c"
                    "csrc/u8x8_d_sh1122.c"
                    "csrc/u8log_u8g2.c"
                    "csrc/u8g2_circle.c"
                    "csrc/u8x8_d_ssd1306_64x48.c"
                    "csrc/u8g2_buffer.c"
                    "csrc/u8g2_bitmap.c"
                    "csrc/u8x8_d_lc7981.c"
                    "csrc/u8x8_d_st7920.c"
                    "csrc/u8x8_d_t6963.c"
                    "csrc/u8x8_d_st7567.c"
                    "csrc/u8x8_d_ls013b7dh03.c"
                    "csrc/u8x8_d_ssd1327.c"
                    "csrc/u8x8_d_sh1108.c"
                    "csrc/u8x8_gpio.c"
                    "csrc/u8x8_d_uc1608.c"
                    "csrc/u8x8_d_uc1617.c"
                    "csrc/u8x8_d_ssd1329.c"
                    "csrc/u8x8_d_ssd1306_64x32.c"
                    "csrc/u8g2_d_setup.c"
                    "csrc/u8x8_d_uc1701_mini12864.c"
                    "csrc/u8x8_u16toa.c"
                    "csrc/u8x8_d_a2printer.c"
                    "csrc/u8x8_d_st7565.c"
                    "cppsrc/U8x8lib.cpp"
)

FOREACH(U8 ${COMPONENT_SRCS})
    LIST(APPEND COMPONENT_SRCS_EX u8g2/${U8})
ENDFOREACH(U8 ${COMPONENT_SRCS})
SET(libPrefix ${ARDUINO_DEFAULT_BOARD}.${ARDUINO_CPU}_)

generate_arduino_library(${libPrefix}U8G2
        SRCS ${COMPONENT_SRCS_EX}
        LIBS ${libPrefix}SPI
        BOARD ${ARDUINO_DEFAULT_BOARD})


include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/u8g2/cppsrc/)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/u8g2/csrc/)
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
#ADD_DEFINITIONS("-std=c++11") # For bounce2

##ADD_DEFINITIONS(-DUSING_CMAKE)

generate_arduino_firmware(wavform_generator 
                SKETCH .              # Folder to get the .ino from, must follow DIR_NAME/DIR_NAME.ino patten !
                SRCS wav_display.cpp  wav_gen.cpp  wav_irotary.cpp  wav_pushButton.cpp  wav_rotary.cpp  wav_run.cpp
                LIBS ${libPrefix}AD9833
                LIBS ${libPrefix}Wire
                LIBS ${libPrefix}SPI
                LIBS ${libPrefix}U8G2
                LIBS ${libPrefix}Bounce2
                LIBS ${libPrefix}Rotary
                PORT ${ARDUINO_DEFAULT_PORT}
                )
# EOF
