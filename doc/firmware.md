# Firmware

[![build](https://github.com/radiolok/brainfuckpc/actions/workflows/build.yml/badge.svg)](https://github.com/radiolok/brainfuckpc/actions/workflows/build.yml)

The relay CPU itself has no firmware — but the silicon periphery around it
does. All of it is C++11 for 8-bit AVR, built with CMake and
[`fw/generic-gcc-avr.cmake`](../fw/generic-gcc-avr.cmake).

| Project | MCU | F_CPU | What it does |
|---|---|---|---|
| [`fw/memorybrd`](../fw/memorybrd) → `bfrun` | ATmega2560 | 16 MHz | memory board: loads the program into RAM, console UART, LED view of RAM |
| [`fw/iv6brd`](../fw/iv6brd) | ATmega168 | 8 MHz | IV-6 indicator module, five build variants (below) |
| [`fw/mcuUtil`](../fw/mcuUtil) | — | — | shared code: cooperative scheduler `MTask`, UART, SPI |
| [`fw/UARTBootloader`](https://github.com/AterLux/UARTBootloader) | — | — | submodule: UART bootloader by AterLux |
| [`fw/menuosv1`](https://github.com/radiolok/menuosv1) | — | — | submodule: tree-menu engine for MCUs |
| [`fw/bfutils`](https://github.com/radiolok/bfutils) | host | — | submodule: compiler and emulator, see [programming.md](programming.md) |
| `fw/[DEPRECATE]` | — | — | an early FreeRTOS-based memory board firmware, not built |

### IV-6 module variants

| Binary | CMake flags | Shows |
|---|---|---|
| `iv6brd_ip_show` | `-DSHOWER=IP_SHOW` | `I xxxx` — instruction pointer |
| `iv6brd_ap_show` | `-DSHOWER=AP_SHOW` | `A xxxx` — address pointer |
| `iv6brd_cmd_show` | `-DSHOWER=CMD_SHOW` | `C xxxx` — current instruction |
| `iv6brd_counter` | `-DCOUNTER=ON` | retired instruction counter |
| `terminal` | `-DTERMINAL=ON` | text terminal, UART 9600 baud |

The register variants read the 16-bit parallel port and print it in hex.
All variants except `terminal` run their UART at 38400 baud.

## Building

### Linux / macOS

```sh
sudo apt install cmake gcc-avr avr-libc binutils-avr   # Debian / Ubuntu
./fw/build.sh                 # all six images → fw/bin/
./fw/build.sh iv6brd_counter  # just one
```

`build.sh` finds the avr-libc root automatically; set `AVR_FIND_ROOT_PATH` if
your toolchain lives somewhere unusual. Any recent avr-gcc works — CI uses
Ubuntu's 7.3, it was also checked with 14.1.

### Windows

The original script still works with Atmel Studio 7 + MinGW:

```bat
python fw\build.py
```

(Edit the toolchain paths at the top of the script first.)

### By hand

```sh
cmake -S fw/memorybrd -B build/memorybrd \
      -DCMAKE_TOOLCHAIN_FILE=$PWD/fw/generic-gcc-avr.cmake -DAVR_MCU=atmega2560
make -C build/memorybrd
```

## Flashing

`build.sh` leaves configured build trees in `fw/build/<name>/`; each has an
`upload_*` target that calls **avrdude** with an AVRISP mkII over USB:

```sh
make -C fw/build/memorybrd upload_bfrun
make -C fw/build/iv6brd_ip_show upload_iv6brd_ip_show
```

Fuses are not written automatically. Values from the CMake projects:

| Board | High | Low |
|---|---|---|
| memory board (ATmega2560) | `0xD9` | `0xE2` |
| IV-6 module (ATmega168) | `0xDF` | `0xE2` |

```sh
avrdude -p m2560 -c avrispmkII -P usb -U hfuse:w:0xD9:m -U lfuse:w:0xE2:m
```

## Memory board firmware in its current state

[`main.cpp`](../fw/memorybrd/main.cpp) is the 2019 bring-up firmware:

* UART at 38400 baud logs every RAM read / write / console output the relay
  CPU performs — handy as a bus monitor.
* At reset it writes a hard-coded program into RAM: the π calculation demo
  (`calcpi[]`). `helloworldApp[]` and a RAM self-test are one comment away.
* The LED matrix shows RAM from address `0x400` — where the programs keep
  their tape.

Loading arbitrary binaries over UART / Wi-Fi (the `BF` header described in
[programming.md](programming.md)) was planned but never finished; `bfloader`
in `bfutils` is the host side of that idea.

## Continuous integration

[`.github/workflows/build.yml`](../.github/workflows/build.yml) runs on every
push and pull request:

1. **AVR firmware** — installs avr-gcc, runs `fw/build.sh`, publishes a size
   table and the `.hex` / `.elf` files as the `brainfuckpc-firmware` artifact.
2. **bfutils** — builds the compiler and emulator and runs
   [`bf/examples/hello.b`](../bf/examples/hello.b) on the emulator.
3. **Release** — pushing a `v*` tag attaches the `.hex` images to a GitHub release.
