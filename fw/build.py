import os
import shutil
import sys

from subprocess import call

script_path = os.path.dirname(os.path.abspath(__file__))

def compile(param):

    build_path = "%s\\%s"  % (param[-1], "build")
    if os.path.exists(build_path):
        shutil.rmtree(build_path)

    os.makedirs(build_path)


    os.chdir(build_path)

    exit_code = call(param)

    if exit_code:
        print ("CMake error!")
        return -1

    exit_code = call(["mingw32-make","-j4"])

    if exit_code:
        print ("MinGW error!")
        return -1



    bin_path = "%s\\%s"  % (script_path, "bin")
    if not os.path.exists(bin_path):
        os.makedirs(bin_path)

    for file in os.listdir(build_path):
        
        if file.endswith('.elf') or file.endswith('.hex') or file.endswith('.hex') or file.endswith('.lst'):
            shutil.move(os.path.join(build_path,file), os.path.join(bin_path,file))

    return 0

    #exit_code = call(["mingw32-make", "install"])

    #if exit_code:
    #    print ("MinGW error!")
    #    exit()
    #return 0

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


CMAKE_TOOLCHAIN_FILE="CMAKE_TOOLCHAIN_FILE=%s\\generic-gcc-avr.cmake" % (script_path)

compile(["cmake", "-G", "MinGW Makefiles", "-D", CMAKE_TOOLCHAIN_FILE,  "-DAVR_MCU=atmega2560", "%s\\%s" % (script_path, "memorybrd")])
compile(["cmake", "-G", "MinGW Makefiles", "-D", CMAKE_TOOLCHAIN_FILE,  "-DTERMINAL=ON","-DBINARY_NAME=iv6brd_terminal","-DAVR_MCU=atmega168", "%s\\%s" % (script_path, "iv6brd")])
