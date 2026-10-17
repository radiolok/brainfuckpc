# Hardware

![Front panel](../img/svg/front-panel.svg)

Schematics and PCBs are drawn in **DipTrace** (`.dch` schematic, `.dip` PCB,
version 2.3 or newer). A few structural drawings are in **sPlan 7** (`.spl7`).

## Specifications (2019)

| | |
|---|---|
| Relays | 578 (RES55, RES64 reed relays; RES43 in latches) |
| Logic elements | 157 |
| Address bus | 16 bit, word addressing |
| Data bus | 16 bit, 8-bit compatibility mode |
| RAM | 64K words × 16 bit (128 KB) |
| Clock | 25 Hz nominal, 40 Hz max, 1 instruction / tick |
| Power | 70 W, 5 V / 3 A per relay block |
| Size | 1100 × 650 × 140 mm (approx.) |
| Weight | 15 kg |

## Hierarchy: relay → module → block → frame

### Relays

Soviet reed relays: **RES55** (1 changeover contact) and **RES64** (1 make
contact) in the logic, **RES43** (two make contacts) in the bus latches. A
RES55 driven through a transistor stage switches cleanly at **1.7 kHz** on the
bench — ordinary telephone relays give up at about 20 Hz.

<p align="center"><img src="../img/habr/res55_1700hz_scope.jpg" width="70%" alt="RES55 at 1.7 kHz"></p>

### Modules

Every logic function lives on a small plug-in module: a 40 × 64 mm PCB with up
to 4 relays, up to 4 status LEDs and a 16-pin connector (some use 12 or 14).

| Module | Schematic | Function | Used in |
|---|---|---|---|
| 2AND / 2XOR | [`sch/2AND_2XOR_module`](../sch/2AND_2XOR_module) | half-adder pair | adder block, 32 pcs (2 per bit) |
| D-trigger | [`sch/REG_module`](../sch/REG_module) | 1-bit register, Q and ~Q out | register blocks, 64 pcs |
| 2AND / 2OR | [`sch/2AND_2OR_module`](../sch/2AND_2OR_module) | universal: 4AND, 4OR, 4AND-NOT… | control logic |
| 2AND ×4 SW | [`sch/2ANDx4_SW_module`](../sch/2ANDx4_SW_module) | four relays on make contacts | latches, control logic |
| Diode | [`sch/Diode_module`](../sch/Diode_module) | 8 × D226 diodes, wired-OR with zero delay | carry chain, logic |
| Switch | [`sch/switch_module`](../sch/switch_module) | switch board (PCB layout only) | — |
| Relay driver | [`sch/Driver_module`](../sch/Driver_module) | transistor / MOSFET relay drivers (variants) | clock, I/O |

<p align="center">
  <img src="../img/habr/modules_types.jpg" width="60%" alt="D-trigger, diode and 2AND/2XOR modules"><br>
  <sub>Left to right: D-trigger, diode module, 2AND/2XOR</sub>
</p>

### Blocks

32 modules (8 × 4) plug into a **base board** — 200 × 150 mm, no copper
traces, just 32 sockets with long square pins for **wire-wrap**. Around 600
pins per board are wrapped by hand. A 3D-printed basket (PLA / HIPS) holds the
modules so they survive transport.

| Block | Contents |
|---|---|
| Adder | 16-bit adder, sum and XOR outputs, carry-in line |
| IP / AP registers | two 16-bit registers |
| TMP / CMD registers | 16-bit TMP, 12-bit CMD, 4-bit opcode register with enable |
| Control logic ×2 | impulse sequencer and instruction decoder; a third slot is left free |

Base board: [`sch/Base_board`](../sch/Base_board).

<p align="center">
  <img src="../img/habr/base_board_and_basket.jpg" width="49%" alt="Base board and printed basket">
  <img src="../img/habr/wire_wrap_adder_2.jpg" width="49%" alt="Wire-wrapped adder block">
</p>

### Latches

Eight 100 × 100 mm boards, each with eight RES43 relays and LEDs showing the
input and output state, route 16-bit words between blocks.

### Frame

A laser-cut, welded and painted 2 mm aluminium frame carries everything; it sits
on a wooden base with switches and connectors. Chassis CAD files are under
[`doc/Chassis`](Chassis) (not all of them are in git — see `.gitignore`).

<p align="center">
  <img src="../img/habr/chassis_cad.jpg" width="40%" alt="Frame CAD">
  <img src="../img/habr/adder_and_logic_blocks.jpg" width="55%" alt="Adder and logic blocks">
</p>

## Silicon periphery

### Memory board — [`sch/MemoryBrd`](../sch/MemoryBrd)

* Two 64 KB static RAM chips (UM61512AK-15, datasheet in [`doc/`](um61512ak-15.pdf)) → 64K × 16.
* Address and data buffers with protection, connected to the relay buses.
* `W/R` and `Sync` lines from the relay logic start a memory cycle.
* ATmega MCU (firmware: [`fw/memorybrd`](../fw/memorybrd)) for program loading,
  console UART and the LED view.
* 32 × 16 LED matrix (two 16 × 16 panels, TLC5941 / STP16 drivers) showing a
  region of RAM in real time.
* **rev.2** (`memoryBrd_rev2.dip`, `memory_rev2.dch`) keeps only the RAM and
  bus interface — the rev.1 board has a fault that sets bit 13, which forced the
  2019 demos into 8-bit mode. Address and data lines of rev.2 are routed.

<p align="center"><img src="../img/habr/memory_board.jpg" width="70%" alt="Memory board"></p>

### IV-6 indicator module — [`sch/IV6_module`](../sch/IV6_module)

100 × 100 mm board with six IV-6 VFD tubes, K155TM8 latches and an ATmega168.
It has a 16-bit parallel input for reading a register directly plus a UART.
Four of them show `IP`, `AP`, `CMD` and the retired instruction counter.
Firmware: [`fw/iv6brd`](../fw/iv6brd).

<p align="center"><img src="../img/habr/iv6_indicator_module.jpg" width="60%" alt="IV-6 module"></p>

### Programming connector

A 36-pin connector exposes 16 address lines, 16 data lines, power, ground and
read/write strobes, so any loader can fill the RAM: the on-board MCU, an
external programmer ([`sch/programmator`](../sch/programmator)), a toggle-switch
panel or a punched-tape reader ([`sch/Reader`](../sch/Reader)). The pinout is
meant to be LPT-compatible.

### Other boards

| Folder | What |
|---|---|
| [`sch/rs-232_output`](../sch/rs-232_output) | RS-232 console output |
| [`sch/[DEPRECATED]`](../sch/%5BDEPRECATED%5D) | earlier designs: ripple-carry `ADD+C`, `5AND`, big base board, PDP-11 style register module… |
| [`lib/`](../lib) | DipTrace libraries for Soviet relays and the module footprints |

## Terminal

A Robotron S6130 daisy-wheel typewriter was acquired to become a real
teletype-style terminal. Its controller board was damaged by leaking NiCd
cells, so this part is still a dream.

## Reference library

[`doc/`](.) also holds datasheets and historic material collected along the
way: Z80 and U880 manuals, the Harwell WITCH computer documentation, HP 2100A
booklets, ferrite core memory notes, the Robotron S6130 manual and schematics.
