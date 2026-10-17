# Brainfuck++ instruction set

![Instruction format](../img/svg/instruction-format.svg)

BrainfuckPC executes **Brainfuck++** — classic Brainfuck where runs of identical
`+ - < >` commands are collapsed into one instruction carrying a constant, and
loops become relative conditional jumps. A Brainfuck source must therefore be
*compiled* (with [`bfpp`](programming.md)) before it can be loaded into RAM.

This page describes the encoding used by the finished hardware (2019), the
[`bfutils`](https://github.com/radiolok/bfutils) toolchain and the memory-board
firmware. The early 2017 draft is kept at the end for history.

## Instruction word

All instructions are 16 bits wide and take exactly one clock tick.

| Bits | Field | Meaning |
|---|---|---|
| 15–13 | **class** | what the instruction does |
| 12 | **S** — sign | copied into bits 15–13 of the operand |
| 11–0 | **imm12** | constant, jump offset, or CTRLIO bit mask |

The adder always works on 16 bits. The operand is `sign_extend(insn[12:0])`, so a
single instruction can move by **−4096 … +4095**. Longer runs are simply split
into several instructions.

So the upper nibble is effectively *class + sign*:

| Nibble | Mnemonic | Operation | Brainfuck |
|---|---|---|---|
| `0x0` | `NOP` | nothing | — |
| `0x1` | `CTRLIO mask` | console I/O, mode, halt (see below) | `.` `,` |
| `0x2` / `0x3` | `ADD imm` | `*AP ← *AP + imm` | `+` / `-` runs |
| `0x4` / `0x5` | `ADA imm` | `AP ← AP + imm` | `>` / `<` runs |
| `0x6` / `0x7` | `JZ imm` | `if *AP == 0: IP ← IP + imm` | `[` |
| `0x8` / `0x9` | `JNZ imm` | `if *AP != 0: IP ← IP + imm` | `]` |
| `0xA` | `XOR imm` | reserved in `bfutils`, not built in hardware | — |
| `0xB`–`0xF` | — | free | — |

The even nibble is the positive form, the odd one the negative form:
`0x2FFE` adds `0x0FFE`, while `0x3FFE` adds `0xFFFE` (i.e. subtracts 2).

### Jumps

`IP` is incremented during *fetch*, before the instruction executes. A taken
jump therefore lands **on** the matching bracket and the next fetch moves one
step past it:

```
addr  code    source
0003  600B    [        ; *AP == 0 → IP = 0x0003 + 11 = 0x000E, next fetch 0x000F
 ...           ...
000E  9FF5    ]        ; *AP != 0 → IP = 0x000E − 11 = 0x0003, next fetch 0x0004
```

### Zero flag and 8/16-bit mode

`JZ`/`JNZ` test the current cell. In **16-bit mode** the whole word is tested,
in **8-bit mode** only the low byte (`(*AP & 0x00FF) == 0`). Arithmetic is
always 16-bit, so 8-bit programs written for classic Brainfuck still run
unchanged. Console I/O always transfers the low byte.

## CTRLIO

For `0x1···` the low 12 bits are a mask of independent control lines. Several
bits may be set at once (setting conflicting ones is undefined behaviour — a
feature, not a bug).

| Bit | Mask | Name | Meaning |
|---|---|---|---|
| 0 | `0x001` | `CIN` | read a character from the console into `*AP` |
| 1 | `0x002` | `COUT` | write the low byte of `*AP` to the console |
| 2 | `0x004` | `SYNC` | blocking console read — stop the clock until data arrives |
| 4 | `0x010` | `CLR.DATA` | `*AP ← 0` (`bfutils` only) |
| 5 | `0x020` | `CLR.AP` | `AP ← 0` (`bfutils` only) |
| 8 | `0x100` | `PAUSE` | (`bfutils` only) |
| 9 | `0x200` | `MODE8` | switch to 8-bit mode |
| 10 | `0x400` | `MODE16` | switch to 16-bit mode |
| 11 | `0x800` | `HALT` | stop the machine |

> **Hardware status.** `COUT`, `MODE8/16` and `HALT` work. `CIN` is not wired
> yet: the console read is tied to the clock logic (the machine has to stop and
> wait in sync mode), which was never finished. Programs that need no input
> run fine.

## Examples

| Source | Machine code |
|---|---|
| `++++++++++` | `200A` |
| `-` | `3FFF` |
| `>` | `4001` |
| `<<<<` | `5FFC` |
| `.` | `1002` |
| end of program | `1800` (HALT) |

Hello World from Wikipedia compiles into 45 words; that image is embedded in
[`fw/memorybrd/main.cpp`](../fw/memorybrd/main.cpp) as `helloworldApp[]`.

---

## History: the 2017 draft

The first article (April 2017) proposed a wider ISA with `AND`/`OR` with a
constant and a block of register-transfer instructions. They were never built
— the final relay logic only implements the classes above. The draft is kept
here because the 2017 Habr article refers to it.

| Instruction | Opcode | Operation | Brainfuck |
|---|---|---|---|
| `add m16` | `0XXX` | `*AP ← *AP + m16` | `+` |
| `sub m16` | `1XXX` | `*AP ← *AP − m16` | `-` |
| `ada m16` | `2XXX` | `AP ← AP + m16` | `>` |
| `ads m16` | `3XXX` | `AP ← AP − m16` | `<` |
| `jz m16` | `4XXX` / `5XXX` | `(*AP == 0) ? IP ← IP ± m16` | `[` |
| `jnz m16` | `6XXX` / `7XXX` | `(*AP != 0) ? IP ← IP ± m16` | `]` |
| `and m16` | `8XXX` / `9XXX` | `*AP ← *AP AND m16` | — |
| `or m16` | `AXXX` / `BXXX` | `*AP ← *AP OR m16` | — |
| `in` / `out` | `C000` / `C001` | console | `,` / `.` |
| `clr.ap/ip/dp` | `D001/2/4` | clear register / cell | `[-]` |
| `set.ap/ip` | `D010/20` | `AP/IP ← *AP` | — |
| `get.ap/ip` | `D100/D200` | `*AP ← AP/IP` | — |
| `mode.b8/b16` | `E100/E200` | 8/16-bit mode | — |
| `halt` | `F000` | stop | — |
