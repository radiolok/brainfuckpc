import os
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..") + "/"
from common import Svg

s = Svg(1000, 660, "BrainfuckPC instruction format and opcode map")
s.text(30, 40, "Brainfuck++ instruction word", "t", 22, weight=700)
s.text(30, 62, "16-bit, one instruction per clock tick. Runs of + − < > collapse into a single instruction.", "m", 14)

# bit field
X0, Y0, BW, BH = 60, 110, 55, 46
for (hi, lo, cls) in [(15, 13, "relay"), (12, 12, "logic"), (11, 0, "neutral")]:
    x = X0 + (15 - hi) * BW
    w = (hi - lo + 1) * BW
    s.add(f'<rect class="{cls}" x="{x}" y="{Y0}" width="{w}" height="{BH}" stroke-width="1.6"/>')
    for b in range(hi, lo, -1):
        tx = X0 + (16 - b) * BW
        s.add(f'<path class="ln" d="M{tx},{Y0} v7 M{tx},{Y0+BH} v-7" stroke-width="1" opacity="0.6"/>')
for i, b in enumerate(range(15, -1, -1)):
    s.text(X0 + i * BW + BW / 2, Y0 - 8, str(b), "m", 12, "middle", mono=True)
s.text(X0 + 1.5 * BW, Y0 + 29, "CLASS", "t", 15, "middle", 700)
s.text(X0 + 3.5 * BW, Y0 + 29, "S", "r", 15, "middle", 700)
s.text(X0 + 10 * BW, Y0 + 29, "IMM12 — constant / jump offset / CTRLIO mask", "t", 15, "middle", 700)
# braces / notes
s.text(X0 + 1.5 * BW, Y0 + BH + 22, "bits 15–13", "m", 12, "middle")
s.text(X0 + 3.5 * BW, Y0 + BH + 22, "sign", "m", 12, "middle")
s.text(X0 + 10 * BW, Y0 + BH + 22, "operand = sign_extend(insn[12:0])  →  −4096 … +4095", "a", 13, "middle", 600, mono=True)

# opcode table
rows = [
    ("0x0···", "NOP", "—", "no operation", "", "neutral"),
    ("0x1···", "CTRLIO", "IMM12 is a bit mask (below)", "console I/O, 8/16-bit mode, halt", ". ,", "logic"),
    ("0x2 / 0x3", "ADD", "*AP ← *AP + imm", "change current cell", "+ −", "relay"),
    ("0x4 / 0x5", "ADA", "AP ← AP + imm", "move along the tape", "> <", "relay"),
    ("0x6 / 0x7", "JZ", "if *AP = 0 :  IP ← IP + imm", "loop entry, skip body", "[", "relay"),
    ("0x8 / 0x9", "JNZ", "if *AP ≠ 0 :  IP ← IP + imm", "loop back-edge", "]", "relay"),
    ("0xA – 0xF", "—", "reserved (XOR planned)", "", "", "neutral"),
]
TY = 215
cols = [60, 190, 300, 600, 870]
heads = ["OPCODE", "MNEMONIC", "OPERATION", "PURPOSE", "BF"]
for c, h in zip(cols, heads):
    s.text(c, TY, h, "m", 12, weight=700, extra='letter-spacing="1.5"')
for i, (op, mn, oper, purp, bf, cls) in enumerate(rows):
    y = TY + 14 + i * 38
    s.add(f'<rect class="{cls}" x="48" y="{y}" width="904" height="32" rx="5" stroke-width="1" opacity="0.9"/>')
    s.text(cols[0], y + 21, op, "t", 14, mono=True)
    s.text(cols[1], y + 21, mn, "t", 14, weight=700, mono=True)
    s.text(cols[2], y + 21, oper, "t", 14, mono=True)
    s.text(cols[3], y + 21, purp, "m", 13)
    s.text(cols[4] + 30, y + 22, bf, "a", 18, "middle", 700, mono=True)

# CTRLIO mask
MY = 520
s.text(60, MY, "CTRLIO mask", "t", 15, weight=700)
s.text(175, MY, "(bits are independent — several may be set at once)", "m", 12)
bits = [(11, "HALT", 1), (10, "MODE16", 1), (9, "MODE8", 1), (8, "PAUSE", 0), (7, "", 0), (6, "", 0),
        (5, "CLR.AP", 0), (4, "CLR.DATA", 0), (3, "", 0), (2, "SYNC", 1), (1, "COUT", 1), (0, "CIN", 1)]
BW2 = 74
for i, (b, name, hw) in enumerate(bits):
    x = 60 + i * BW2
    cls = "logic" if hw else "neutral"
    s.add(f'<rect class="{cls}" x="{x}" y="{MY+14}" width="{BW2}" height="44" stroke-width="1.2"/>')
    s.text(x + BW2 / 2, MY + 31, str(b), "m", 11, "middle", mono=True)
    if name:
        s.text(x + BW2 / 2, MY + 50, name, "t" if hw else "m", 12, "middle", 700 if hw else None, mono=True)
s.text(60, MY + 82, "Examples:  0x1002 = '.' (COUT)    0x1800 = HALT    0x200A = +10    0x5FFC = <<<<    0x600B = '[' jump +11",
       "a", 13, mono=True, extra='xml:space="preserve"')
s.text(60, MY + 102, "Highlighted bits are used by the hardware; the rest are defined by the bfutils toolchain.", "m", 12)

s.save(OUT + "instruction-format.svg")
