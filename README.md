<p align="center">
  <img src="img/svg/banner.svg" alt="BrainfuckPC — 16-bit relay computer" width="100%">
</p>

<p align="center">
  <a href="https://github.com/radiolok/brainfuckpc/actions/workflows/build.yml"><img src="https://github.com/radiolok/brainfuckpc/actions/workflows/build.yml/badge.svg" alt="build"></a>
  <a href="LICENCE"><img src="https://img.shields.io/badge/license-GPL--3.0-blue" alt="GPL-3.0"></a>
  <a href="https://habr.com/ru/articles/442732/"><img src="https://img.shields.io/badge/Habr-3%20articles-6a9fb5" alt="Habr"></a>
  <a href="https://www.youtube.com/playlist?list=PLHI3L7Als_GPlqEA98NgcnIerBVcbE5Fn"><img src="https://img.shields.io/badge/YouTube-34%20videos-red" alt="YouTube"></a>
  <a href="https://hackaday.io/project/18599-brainfuck-relay-computer"><img src="https://img.shields.io/badge/hackaday.io-build%20log-1a1a1a" alt="hackaday.io"></a>
  <img src="https://img.shields.io/badge/status-finished%20(98%25)-d4a72c" alt="status">
</p>

<p align="center"><b>English</b> · <a href="README.ru.md">Русский</a></p>

**BrainfuckPC** is a 16-bit von Neumann computer whose processor is built from
**578 Soviet reed relays**. Its native instruction set is Brainfuck — extended
just enough (`+10` instead of ten `+`) to make one relay adder do all the work.
It runs at 25 Hz, prints *Hello World!* in about six seconds and is, as far as
the author knows, the fastest relay computer ever built — and one of the
slowest computers that still finishes a job.

<p align="center">
  <img src="img/habr/bfpc_and_author_2019.jpg" width="70%" alt="BrainfuckPC and its author, 2019">
</p>

| | |
|---|---|
| **Architecture** | von Neumann, shared 64K × 16-bit memory, word addressing |
| **CPU** | 578 reed relays (RES55 / RES64 / RES43), 157 logic elements |
| **ISA** | [Brainfuck++](doc/instruction_set.md): run-length `+ - < >`, relative `JZ`/`JNZ`, `CTRLIO` |
| **Adder** | 16-bit, parallel carry, ≈ 2 ms per addition |
| **Clock** | 25 Hz nominal, 40 Hz max — one instruction per tick |
| **Periphery** | SRAM memory board with AVR loader, 32×16 LED RAM view, IV-6 VFD register displays |
| **Power / weight** | 70 W · 15 kg |

## How it works

![Architecture](img/svg/architecture.svg)

Brainfuck needs only a tape, a pointer into it and two loop brackets. The
machine mirrors that literally: an **instruction pointer** `IP`, an **address
pointer** `AP`, and a single **16-bit adder** with a temporary register on one
input and the instruction's 12-bit constant on the other.

Every instruction is "read a value, add a constant, write it back":
`IP++` during fetch, then `*AP += n`, `AP += n`, or `IP += n` for a taken jump.
The parallel-carry adder needs only three relay delays instead of 32 for a
ripple adder — that is where the speed comes from.

![Clock cycle](img/svg/clock-cycle.svg)

![Instruction format](img/svg/instruction-format.svg)

More: [architecture](doc/architecture.md) · [instruction set](doc/instruction_set.md) ·
[timing diagrams](waveforms)

## The hardware

![Front panel](img/svg/front-panel.svg)

Every logic function lives on a small plug-in **module** with up to four
relays. 32 modules form a **block** wired by hand with wire-wrap. Five blocks,
eight 16-bit bus latches, a memory board and four indicator modules make the
machine.

| | | |
|:---:|:---:|:---:|
| <img src="img/habr/modules_types.jpg" alt="Modules"> | <img src="img/habr/adder_block_modules.jpg" alt="Adder block"> | <img src="img/habr/wire_wrap_adder_1.jpg" alt="Wire-wrap"> |
| D-trigger, diode and 2AND/2XOR modules | 16-bit adder block — 32 modules | ~600 wire-wrapped pins per block |
| <img src="img/habr/latch_module.jpg" alt="Latch"> | <img src="img/habr/iv6_indicator_module.jpg" alt="IV-6 module"> | <img src="img/habr/memory_board.jpg" alt="Memory board"> |
| 16-bit latch, eight RES43 | IV-6 register display | memory board with 32×16 LED view |
| <img src="img/habr/res55_1700hz_scope.jpg" alt="RES55 at 1.7 kHz"> | <img src="img/habr/adder_and_regs_running.jpg" alt="Blocks running"> | <img src="img/habr/blocks_2018.jpg" alt="Blocks 2018"> |
| a RES55 relay switching at 1.7 kHz | adder + registers, first run | blocks and indicators, 2018 |

More: [hardware guide](doc/hardware.md) — modules, boards and where every schematic lives.

## Videos

The whole build is on video — 34 episodes from the first sketches in 2017 to the
finished machine computing π (in Russian):
**[▶ playlist](https://www.youtube.com/playlist?list=PLHI3L7Als_GPlqEA98NgcnIerBVcbE5Fn)** ·
[annotated list](doc/videos.md)

| | | |
|:---:|:---:|:---:|
| <a href="https://youtu.be/5hhbGBlP3_4"><img src="https://img.youtube.com/vi/5hhbGBlP3_4/mqdefault.jpg" alt="Perhaps the fastest relay computer in the world"></a> | <a href="https://youtu.be/CjOYOlJl9wg"><img src="https://img.youtube.com/vi/CjOYOlJl9wg/mqdefault.jpg" alt="Triple Brainfuck — meetup talk, 2018"></a> | <a href="https://youtu.be/UwRxRw0NNDI"><img src="https://img.youtube.com/vi/UwRxRw0NNDI/mqdefault.jpg" alt="Pi = 4! and other relay computing bugs"></a> |
| Perhaps the fastest relay computer in the world | Triple Brainfuck — meetup talk, 2018 | Pi = 4! and other relay computing bugs |

## Software

```sh
git clone --recursive https://github.com/radiolok/brainfuckpc
cd brainfuckpc

# Brainfuck compiler and emulator
cmake -S fw/bfutils -B fw/bfutils/build && cmake --build fw/bfutils/build -j
fw/bfutils/bin/bfpp -i bf/examples/hello.b -o hello.bin
fw/bfutils/bin/bfrun -f hello.bin            # Hello World!  Istructions_retired:143

# AVR firmware for the memory board and indicators
sudo apt install cmake gcc-avr avr-libc binutils-avr
./fw/build.sh                                # → fw/bin/*.hex
```

Every push is built by GitHub Actions; ready `.hex` files are attached to each
run as the `brainfuckpc-firmware` artifact.

More: [programming](doc/programming.md) · [firmware](doc/firmware.md)

## Repository map

```
├── doc/            documentation, datasheets, reference material, slides
├── img/
│   ├── svg/        diagrams used in the docs (+ src/ generators)
│   └── habr/       photos from the Habr articles
├── sch/            DipTrace schematics and PCBs of every module and board
├── lib/            DipTrace libraries: Soviet relays, module footprints
├── fw/
│   ├── memorybrd/  memory board firmware (ATmega2560)
│   ├── iv6brd/     IV-6 indicator firmware (ATmega168)
│   ├── mcuUtil/    shared scheduler / UART / SPI
│   ├── bfutils/    ⤷ compiler & emulator (submodule)
│   └── build.sh    builds all firmware
├── bf/             Brainfuck programs and the C++ model used to write them
├── waveforms/      WaveDrom timing diagrams of every instruction
├── mech/           mechanical parts (DXF / STL)
└── roadmap.md      build log 2017–2019
```

## Status

The machine is **finished at 98%** and runs any program that needs no input.
Left undone when the author moved on to the next projects:

- [ ] `CTRLIO.CIN` — console input, tied to the clock logic (the CPU must stop and wait)
- [ ] clock-sync logic — three modules to wire
- [ ] memory board rev.2 (RAM only; fixes the stuck bit 13 that limits demos to 8-bit mode)
- [ ] programmer firmware and external loader
- [ ] Robotron S6130 typewriter as the terminal

## History

![Timeline](img/svg/timeline.svg)

It started with a 1979 book, *Radio-electronic toys* by Y. Voitsekhovsky, which
had a simple relay computing machine in it. In 2008 that became **RCVM-1**, a
4-bit relay ALU. Ten years of collecting relays later, the 16-bit BrainfuckPC
was designed in November 2016 and ran its first programs in 2019.

<p align="center">
  <img src="img/habr/rcvm1_alu_2008.jpg" width="32%" alt="RCVM-1, 2008">
  <img src="img/habr/render_2017.jpg" width="32%" alt="2017 render">
  <img src="img/habr/infographic_2018.jpg" width="32%" alt="2018 infographic">
</p>

The full story, in Russian, with videos:

| Year | Article |
|---|---|
| 2017 | [Мои маленькие реле: Brainfuck компьютер это магия](https://habr.com/ru/articles/402629/) — the design |
| 2018 | [Мои маленькие реле: Brainfuck компьютер — это реальность](https://habr.com/ru/articles/411145/) — modules, blocks, first tests |
| 2019 | [Мои маленькие реле: Тройной Brainfuck, или что такое безумие](https://habr.com/ru/articles/442732/) — the finished machine |

Video series: [34 videos on YouTube](doc/videos.md).
Build log in English: [hackaday.io/project/18599](https://hackaday.io/project/18599-brainfuck-relay-computer).

BrainfuckPC was the first of three "impossible" computers: it was followed by
a fluidic (air-jet) computer and **DekatronPC**, a computer on dekatron tubes.

## License

[GPL-3.0](LICENCE) © Artem Kashkanov
