Relay Computer 2

* Brainfuck arch with RLE support

* 16-bit Address Ptr - Use 65536 x 16 SRAM or you can use different memory types and linear address space;

* 16-bit IP;

* 16-bit Data/ Or you can enable 8-bit data mode for executing 8-bit programms;

* Use reed switch relay only;

* Main logic takes 520 relays, and we need about 200 relays for control signal routing

* Clock frequency up to 100 Hz.

Brainfuck is an esoteric programming language created in 1993 by Urban Müller, and notable for its extreme minimalism.

The language consists of only eight simple commands and an instruction pointer. While it is fully Turing-complete, it is not intended for practical use, but to challenge and amuse programmers.

The language's name is a reference to the slang term brainfuck, which refers to things so complicated or unusual that they exceed the limits of one's understanding.

Classic Brainfuck arch has eight commands:

* \>	increment the data pointer (to point to the next cell to the right).

* <	decrement the data pointer (to point to the next cell to the left).

* \+	increment (increase by one) the byte at the data pointer.

* \-	decrement (decrease by one) the byte at the data pointer.

* .	output the byte at the data pointer.

* ,	accept one byte of input, storing its value in the byte at the data pointer.

* [	if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.

* ]	if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.

As each relay has very big latency I add RLE compressing of +- and <> commands.

If source file contain "+++++" or "-----" sequence, when listing will be loaded this sequence will be transformed into "+Constant" command - My computer has fully - functional 8-bit ADD-er for Data and 16-bit Adder for Address and this hack improve computer performance in many times.

Loop command are work as JZ to the end of the cycle and LZN to begin using second Adder input and 12-bit jump

Use DipTrace 2.3 or higher  to open project files

Use Splan 7 to open spl7 files - there are some structures.

