##########################################################################
# "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware
# license):
# <dev@layer128.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and
# you think this stuff is worth it, you can buy me a be(ve)er(age) in
# return. (I don't like beer much.)
#
# Matthias Kleemann
##########################################################################

cmake_minimum_required(VERSION 3.1)

cmake_policy(SET CMP0015 NEW)

project(bfpc_fw)

### TOOLCHAIN SETUP AREA #################################################
# Set any variables used in the toolchain prior project() call. In that
# case they are already set and used.
##########################################################################

##########################################################################
# tools to beused for programming the AVR
##########################################################################
set(AVR_UPLOADTOOL avrdude)
set(AVR_PROGRAMMER avrispmkII)
set(AVR_UPLOADTOOL_PORT usb)

##########################################################################
# AVR and fuses needs to be set
##########################################################################
set(AVR_MCU atmega2560)
set(AVR_H_FUSE 0xd9)
set(AVR_L_FUSE 0xc3)

### END TOOLCHAIN SETUP AREA #############################################

# Intentionally left blank, due to a different approach of using the
# toolchain file via -DCMAKE_TOOLCHAIN_FILE=path/to/generic-gcc-avr.cmake
# at the cmake command line call
#
# include(../generic-gcc-avr.cmake)


##########################################################################
# status messages
##########################################################################
message(STATUS "Current uploadtool is: ${AVR_UPLOADTOOL}")
message(STATUS "Current programmer is: ${AVR_PROGRAMMER}")
message(STATUS "Current upload port is: ${AVR_UPLOADTOOL_PORT}")
message(STATUS "Current uploadtool options are: ${AVR_UPLOADTOOL_OPTIONS}")
message(STATUS "Current MCU is set to: ${AVR_MCU}")
message(STATUS "Current H_FUSE is set to: ${AVR_H_FUSE}")
message(STATUS "Current L_FUSE is set to: ${AVR_L_FUSE}")

##########################################################################
# set build type
##########################################################################
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

##########################################################################
# needs to be defined for AVR toolchain
##########################################################################
set(MCU_SPEED "16000000UL")

##########################################################################
# some cmake cross-compile necessities
##########################################################################
if(DEFINED ENV{AVR_FIND_ROOT_PATH})
    set(CMAKE_FIND_ROOT_PATH $ENV{AVR_FIND_ROOT_PATH})
else(DEFINED ENV{AVR_FIND_ROOT_PATH})
    if(EXISTS "/opt/local/avr")
      set(CMAKE_FIND_ROOT_PATH "/opt/local/avr")
    elseif(EXISTS "/usr/avr")
      set(CMAKE_FIND_ROOT_PATH "/usr/avr")
    elseif(EXISTS "/usr/lib/avr")
      set(CMAKE_FIND_ROOT_PATH "/usr/lib/avr")
    elseif(EXISTS "/usr/local/CrossPack-AVR")
      set(CMAKE_FIND_ROOT_PATH "/usr/local/CrossPack-AVR")
    else(EXISTS "/opt/local/avr")
      message(FATAL_ERROR "Please set AVR_FIND_ROOT_PATH in your environment.")
    endif(EXISTS "/opt/local/avr")
endif(DEFINED ENV{AVR_FIND_ROOT_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# not added automatically, since CMAKE_SYSTEM_NAME is "generic"
set(CMAKE_SYSTEM_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
set(CMAKE_SYSTEM_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")

##########################################################################
# status messages for generating
##########################################################################
message(STATUS "Set CMAKE_FIND_ROOT_PATH to ${CMAKE_FIND_ROOT_PATH}")
message(STATUS "Set CMAKE_SYSTEM_INCLUDE_PATH to ${CMAKE_SYSTEM_INCLUDE_PATH}")
message(STATUS "Set CMAKE_SYSTEM_LIBRARY_PATH to ${CMAKE_SYSTEM_LIBRARY_PATH}")

##########################################################################
# set compiler options for build types
##########################################################################
if(CMAKE_BUILD_TYPE MATCHES Release)
   set(CMAKE_C_FLAGS_RELEASE "-Os")
   set(CMAKE_CXX_FLAGS_RELEASE "-Os")
endif(CMAKE_BUILD_TYPE MATCHES Release)

if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
   set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
   set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
endif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)

if(CMAKE_BUILD_TYPE MATCHES Debug)
   set(CMAKE_C_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
   set(CMAKE_CXX_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

##########################################################################
# compiler options for all build types
##########################################################################
add_definitions("-DF_CPU=${MCU_SPEED}")
add_definitions("-fpack-struct")
add_definitions("-fshort-enums")
add_definitions("-Wall")
add_definitions("-Werror")
add_definitions("-pedantic")
add_definitions("-pedantic-errors")
add_definitions("-funsigned-char")
add_definitions("-funsigned-bitfields")
add_definitions("-ffunction-sections")
add_definitions("-c")
add_definitions("-std=c++11")
add_definitions("-fno-threadsafe-statics")


set (CMAKE_BUILD_FILES_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_BUILD_DIRECTORY ${CMAKE_BINARY_DIR})


include_directories(
    ${PROJECT_SOURCE_DIR}/util
    ${PROJECT_SOURCE_DIR}/ramOld
    ${PROJECT_SOURCE_DIR}/ram
    ${PROJECT_SOURCE_DIR}/driver
    ${PROJECT_SOURCE_DIR}/binary
    ${PROJECT_SOURCE_DIR}/bfpc
    ${PROJECT_SOURCE_DIR}/../mcuUtil
)

set (McuUtil
    ${PROJECT_SOURCE_DIR}/../mcuUtil/MTask.cpp
    ${PROJECT_SOURCE_DIR}/../mcuUtil/MTask.h
    ${PROJECT_SOURCE_DIR}/../mcuUtil/spi.cpp
    ${PROJECT_SOURCE_DIR}/../mcuUtil/spi.h
    ${PROJECT_SOURCE_DIR}/../mcuUtil/uart.cpp
    ${PROJECT_SOURCE_DIR}/../mcuUtil/uart.h
)

set (SOURCES 
        main.cpp 
        ${McuUtil}
        ${PROJECT_SOURCE_DIR}/bfpc/core.cpp
        ${PROJECT_SOURCE_DIR}/bfpc/core.h
        ${PROJECT_SOURCE_DIR}/bfpc/io.cpp
        ${PROJECT_SOURCE_DIR}/bfpc/io.h
        ${PROJECT_SOURCE_DIR}/binary/Bfheader.h
        ${PROJECT_SOURCE_DIR}/binary/BinaryDecoder.cpp
        ${PROJECT_SOURCE_DIR}/binary/BinaryDecoder.h

        ${PROJECT_SOURCE_DIR}/driver/addrIO.cpp
        ${PROJECT_SOURCE_DIR}/driver/addrIO.h
        ${PROJECT_SOURCE_DIR}/driver/ControlIO.cpp
        ${PROJECT_SOURCE_DIR}/driver/ControlIO.h
        ${PROJECT_SOURCE_DIR}/driver/dataIO.cpp
        ${PROJECT_SOURCE_DIR}/driver/dataIO.h
        ${PROJECT_SOURCE_DIR}/driver/led.cpp
        ${PROJECT_SOURCE_DIR}/driver/led.h
        ${PROJECT_SOURCE_DIR}/driver/pinIO.cpp
        ${PROJECT_SOURCE_DIR}/driver/pinIO.h
        ${PROJECT_SOURCE_DIR}/driver/TLC5941.cpp
        ${PROJECT_SOURCE_DIR}/driver/TLC5941.h

        ${PROJECT_SOURCE_DIR}/ram/ExternalRam.cpp
        ${PROJECT_SOURCE_DIR}/ram/ExternalRam.h

        )

add_avr_executable(bfrun 
    ${SOURCES}
)

find_library(C_LIB c)
message(STATUS "avr-libc: ${C_LIB}")

#avr_target_link_libraries(bfrun ${C_LIB})