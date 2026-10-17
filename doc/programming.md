# Programming BrainfuckPC

The toolchain lives in its own repository,
[radiolok/bfutils](https://github.com/radiolok/bfutils), included here as the
`fw/bfutils` submodule.

| Tool | Purpose |
|---|---|
| `bfpp` | compiler: Brainfuck → BrainfuckPC binary, collapses `+ - < >` runs |
| `bfrun` | instruction-accurate emulator of the machine |
| `bfloader` | host side of the serial loader for the memory board (unfinished) |
| `dpcrun` | emulator for the follow-up project, the tube computer DekatronPC |

## Build the tools

```sh
git submodule update --init fw/bfutils
cmake -S fw/bfutils -B fw/bfutils/build
cmake --build fw/bfutils/build -j
ls fw/bfutils/bin        # bfpp bfrun bfloader dpcrun
```

## Hello World

```sh
fw/bfutils/bin/bfpp -i bf/examples/hello.b -o hello.bin      # compile
fw/bfutils/bin/bfpp -i bf/examples/hello.b -o hello.asm -s   # human-readable listing
fw/bfutils/bin/bfrun -f hello.bin
```

```
Hello World!

Istructions_retired:143
```

The retired-instruction counter is the most useful number: divide by the
clock (25 Hz) and you know how long the relay machine will take. The physical
machine has the same counter on its fourth IV-6 module, so you can watch it
catch up with the emulator.

`bfpp` options: `-s` text listing, `-H` hex listing, `-d` debug symbols,
`-On` optimisation level.
`bfrun` options: `-x` 16-bit word mode (default is classic 8-bit), `-p`
protected mode (IP and AP must stay inside their sections), `-s` statistics,
`-d` debug trace.

## Binary format

Big-endian 16-bit words, a header followed by section descriptors:

```c
typedef struct {
    uint16_t Magic;       // 0x4246, "BF"
    uint8_t  Machine;     // 8- or 16-bit mode
    uint8_t  HeaderSize;
    uint8_t  SectionNum;
    uint8_t  flags;       // protected mode, self-check, ...
    uint16_t IpEntry;     // IP after loading
    uint16_t ApEntry;     // AP after loading
} BfHeader_t;

typedef struct {
    uint16_t FileBase;    // offset of the section in the file
    uint16_t MemoryBase;  // where to load it
    uint16_t FileSize;    // bytes stored in the file
    uint16_t MemorySize;  // words to reserve in RAM
    uint8_t  type;        // 1 = code, 2 = data, 3 = video (LED window)
    uint8_t  pad;
} BfSection_t;
```

The memory-board MCU was meant to read this header, place the sections and
optionally act as a watchdog: raise *Segmentation Fault* when code is
executed from the data section, and run its own emulator in lock-step to
raise *Machine Error* if a relay module starts to fail.

## Writing programs that fit a relay machine

Brainfuck only knows "change a cell by a constant" and "is it zero?". Adding
two cells is a loop that moves one unit at a time:

```c
// *(mem + RbPos) += *mem;  *mem = 0
while (*mem) { mem += RbPos; (*mem)++; mem -= RbPos; (*mem)--; }
```

which for `RbPos = 4` is just `[>>>>+<<<<-]` — and `bfpp` turns each arrow
run into a single `ADA`. Building bigger operations out of such primitives
is how the π ≈ 355/113 division program was written. The C++ model used for
that (a 64K-cell `Memory` class that wraps around exactly like the hardware)
is in [`bf/calcPi`](../bf/calcPi).

Rules of thumb:

* Every executed instruction costs 40 ms. A program that runs a billion
  instructions in an emulator in a second would take **over a year** on the relay
  machine.
* Keep loops shallow and counters small; prefer 8-bit mode for classic
  Brainfuck programs.
* Programs must not need input yet — `CTRLIO.CIN` is not wired.

## Programs that ran on the hardware

| Program | Instructions | Time @ 25 Hz | Result |
|---|---|---|---|
| Hello World (Wikipedia) | ~140 | ~6 s | ✔ |
| Third-party π digits program, 4 digits | — | ~1.5 h (estimated) | printed π = 4 and halted |
| 355/113, 6 digits, 16-bit mode | ~60 000 | ~40 min | failed: memory board bit-13 fault |
| 355/113, 2 digits, 8-bit mode | ~1 600 | ~1 min | ✔ "3.14" |

The π runs and their bugs are the subject of
[“Пи=4! и другие ошибки вычислений на реле”](https://youtu.be/UwRxRw0NNDI);
the rest of the series is listed in [videos.md](videos.md).
