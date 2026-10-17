# BrainfuckPC documentation

| Page | What's inside |
|---|---|
| [architecture.md](architecture.md) | registers, the parallel-carry adder, clock phases, timing diagrams, performance |
| [instruction_set.md](instruction_set.md) | Brainfuck++ encoding, CTRLIO bits, examples, the 2017 draft ISA |
| [hardware.md](hardware.md) | relays, modules, blocks, latches, memory board, indicators, schematic map |
| [firmware.md](firmware.md) | AVR firmware projects, building, flashing, CI |
| [programming.md](programming.md) | bfutils compiler & emulator, binary format, writing programs |
| [videos.md](videos.md) | all 34 YouTube videos in order, with English titles; transcripts tooling |

Articles on Habr (in Russian) — the most complete story of the build:

1. [Мои маленькие реле: Brainfuck компьютер это магия](https://habr.com/ru/articles/402629/) — 2017, the design
2. [Мои маленькие реле: Brainfuck компьютер — это реальность](https://habr.com/ru/articles/411145/) — 2018, first blocks
3. [Мои маленькие реле: Тройной Brainfuck, или что такое безумие](https://habr.com/ru/articles/442732/) — 2019, the finished machine

Build log: [hackaday.io/project/18599](https://hackaday.io/project/18599-brainfuck-relay-computer) ·
progress notes: [roadmap.md](../roadmap.md)

## Other material in this folder

| Path | |
|---|---|
| [`slides/`](slides) | presentation about the project (ODP / PPTX / PDF) |
| [`075_brainfuckPC_gantt.gan`](075_brainfuckPC_gantt.gan) | GanttProject plan |
| [`sch.spl7`](sch.spl7) | structural drawings, sPlan 7 |
| [`Brainfuck/`](Brainfuck) | "Building a C-processor" paper |
| [`witch/`](witch), [`HP 5060-8331/`](HP%205060-8331) | historic computer documentation (Harwell WITCH, HP 2100A) |
| `Z80-…pdf`, `U880_System.pdf` | CPU references |
| `S6130_UserManual_Ger.pdf`, `robotron_s6130-schema.pdf` | the Robotron typewriter meant to become the terminal |
| `um61512ak-15.pdf` | SRAM datasheet |
