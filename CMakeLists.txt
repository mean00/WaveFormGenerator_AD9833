
cmake_minimum_required(VERSION 3.0)

include(../common_CMakeLists.cmake)

PROJECT(Hello_gd32_freetos NONE) # the NONE is very important !

enable_language(C CXX ASM) # this is important too!
include_directories(${CMAKE_SOURCE_DIR})        
add_subdirectory(${AF_FOLDER})


include(${AF_FOLDER}/setup.cmake)
        

USE_LIBRARY(simplerAD9833)
USE_LIBRARY(RotaryEncoder)

SET(s1306 ${CMAKE_SOURCE_DIR}/lnArduino/libraries/simplerSSD1306)
include_directories(${S1306})
ADD_LIBRARY(ssd1306  ${s1306}/ssd1306_i2c_lnGd32vf103.cpp ${s1306}/ssd1306_base.cpp ${s1306}/ssd1306_ex.cpp)

SET(SRCS)

GENERATE_GD32_FIRMWARE(waveForm src/main.cpp ${SRCS} ${AMG})
target_link_libraries(waveForm ssd1306)

target_include_directories(waveForm PRIVATE ${CMAKE_SOURCE_DIR}/include)        
