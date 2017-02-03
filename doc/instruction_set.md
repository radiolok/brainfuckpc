#Overview

All instructions are 16-bit wide.

* Bits 15, 14, 13 - define instruction class
* Bit 12 - Signed bit
* Bits 11-0 - contain least 12bit of signed integer. Master 4 bits generates automatically: 0 for positive and 1 for negative values.

# Assembler instruction set

|Instruction |Opcode | Operation| Brainfuck Equivalent | Description|
|------------|-------|----------|----------------------|------------|
|add m16     |0X XX  |DP ← DP + m16 | '+' (Repeat m16 times) | Add base to current data value |
|sub m16     |1X XX  |DP ← DP - m16 | '-' (Repeat m16 times) | Substract base from  current data value |
|rsh m16     |2X XX  |AP ← AP + m16 | '>' (Repeat m16 times) | Increase memory address |
|lsh m16     |3X XX  |AP ← AP - m16 | '<' (Repeat m16 times) | Decrease memory address |
|jz m16      |4X XX  |(DP == 0)? IP ← IP + m16 : IP ← IP | '['  | Jump to IP + m16 if  current data value is zero |
|jz m16      |5X XX  |(DP == 0)? IP ← IP - m16 : IP ← IP | None  | Jump to IP - m16 if  current data value is zero |
|jnz m16     |6X XX  |(DP != 0)? IP ← IP + m16 : IP ← IP | None  | Jump to IP + m16 if  current data value is not zero |
|jnz m16     |7X XX  |(DP != 0)? IP ← IP - m16 : IP ← IP | ']'  | Jump to IP - m16 if  current data value is not zero |
|and m16     |8X XX  |DP ← DP AND m16 | None | Logical AND of current data value with positive constant|
|and m16     |9X XX  |DP ← DP AND m16 | None | Logical AND of current data value with negative constant|
|or m16      |aX XX  |DP ← DP OR m16 | None | Logical OR of current data value with positive constant|
|or m16      |bX XX  |DP ← DP OR m16 | None | Logical OR of current data value with negative constant|
|in          |c0 00  |DP ← CIN  | ','  | Read one symbol from console. If Cin buffer is empty, wait it |
|out         |c0 01  |COUT ← IP | '.'  | Write symbol to console |
|clr.ap      |d0 01  |AP ← 0 | None  | Clear AP register. Can be combined with other clr commands |
|clr.ip      |d0 02  |IP ← 0 | None  | Clear IP register. Can be combined with other clr commands |
|clr.dp      |d0 04  |DP ← 0 | '[+]' or '[-]'  | Clear current data cell. Can be combined with other clr commands |
|set.ap      |d0 10  |AP ← DP | None  | Write current data value to AP register |
|set.ip      |d0 20  |IP ← DP | None  | Write current data value to IP register |
|get.ap      |d1 00  |DP ← AP | None  | Read current data value from AP register |
|get.ip      |d2 00  |DP ← IP | None  | Read current data value from IP register |
|mode.b8     |e1 00  |        | None  | 8-bit mode activated  |
|mode.b16    |e2 00  |        | None  | 16-bit mode activated |
|halt        |f0 00  |        | None  | halt machine          |

* AP - Address pointer Register
* IP - Instruction pointer register
* DP - Current Data cell
* CIN - Console input
* COUT - console output
