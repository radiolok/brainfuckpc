import os
import shutil

from subprocess import call

#@echo off

avr_toolchain_path="C:\\Program Files (x86)\\Atmel\\Studio\\7.0\\toolchain\\avr8\\avr8-gnu-toolchain"
mingw_toolchain_path="C:\\MinGW\\bin"

path = os.environ.get('PATH')
path = "%s;%s\\bin;%s" % (path, avr_toolchain_path, mingw_toolchain_path)

avr_root_path="%s\\avr" % (avr_toolchain_path)

os.environ['PATH']=path

os.environ['AVR_FIND_ROOT_PATH']=avr_root_path

#set PATH=%PATH%;C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin

#set AVR_FIND_ROOT_PATH=C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\avr


script_path = os.path.dirname(os.path.abspath(__file__))

build_path="%s\\build" %(script_path)



if os.path.exists(build_path):
    shutil.rmtree(build_path)

os.makedirs(build_path)


os.chdir(build_path)

CMAKE_TOOLCHAIN_FILE="CMAKE_TOOLCHAIN_FILE=%s\\generic-gcc-avr.cmake" % (script_path)

PROJECT_FOLDER="%s\\memorybrd" % (script_path)

exit_code = call(["cmake", "-G", "MinGW Makefiles", "-D", CMAKE_TOOLCHAIN_FILE, "AVR_MCU", "atmega2560", PROJECT_FOLDER])

if exit_code:
    print ("CMake error!")
    exit()

exit_code = call(["mingw32-make","-j4"])

if exit_code:
    print ("MinGW error!")
    exit()

exit()

exit_code = call(["mingw32-make", "install"])

if exit_code:
    print ("MinGW error!")
    exit()