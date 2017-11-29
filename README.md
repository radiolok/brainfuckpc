![image](/img/adder_block.png?raw=true "Adder block")

Adder block photo

# GENERAL INFORMATION

* Von-neuman 16-bit architecture

* Brainfuck instruction set with RLE support and additional commands [(see instruction set DRAFT)](/doc/instruction_set.md)

* 16-bit Address space - rev.1 would use 65536 x 16 SRAM, rev.2 would have ferrite core memory;

* 16-bit Instruction length;

* 16-bit Data, with 8-bit backward-compatibility mode for executing 8-bit programms;

* Use reed relay only - soviet RES55 and RES64;

* One adder - 256 relays, 4 registers - 48 relay each, and instruction decoding logic takes about 200 relays ~= 700 relays.

* Clock frequency up to 100 Hz.

# BRAINFUCK

Brainfuck is an esoteric programming language created in 1993 by Urban Müller, and notable for its extreme minimalism.

The language consists of only eight simple commands and an instruction pointer. While it is fully Turing-complete, it is not intended for practical use, but to challenge and amuse programmers.

The language's name is a reference to the slang term brainfuck, which refers to things so complicated or unusual that they exceed the limits of one's understanding.

Classic Brainfuck arch has eight commands:

* \>	increment the address pointer (to point to the next cell to the right).

* <	decrement the address pointer (to point to the next cell to the left).

* \+	increment (increase by one) the byte at the address pointer.

* \-	decrement (decrease by one) the byte at the address pointer.

* .	output the byte at the address pointer.

* ,	accept one byte of input, storing its value in the byte at the address pointer.

* \[	if the byte at the address pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.

* ]	if the byte at the address pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching \[ command.

As each relay has very big latency I add RLE compressing of +- and <> commands.

If source file contain "+++++" or "-----" sequence, when listing will be loaded this sequence will be transformed into "+Constant" command - My computer has fully - functionaland 16-bit Adder for Data/Address/Instruction and this hack improve computer performance in many times.

Loop command are work as JZ to the end of the cycle and JNZ to begin using second Adder input and 12-bit jump

Use DipTrace 2.3 or higher  to open project files

Use Splan 7 to open spl7 files - there are some structures.

