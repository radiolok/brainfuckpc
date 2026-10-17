import os
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..") + "/"
from common import Svg

s = Svg(1000, 610, "BrainfuckPC architecture block diagram")
s.text(30, 40, "BrainfuckPC — architecture", "t", 22, weight=700)
s.text(30, 62, "One 16-bit adder does everything: IP++, AP±n, *AP±n and relative jumps", "m", 14)

AB, DB = 100, 520   # bus y
# buses
s.line([(40, AB), (960, AB)], "bus", 7)
s.text(960, AB - 12, "ADDRESS BUS · 16 bit", "m", 12, "end", 600)
s.line([(40, DB), (960, DB)], "bus", 7)
s.text(960, DB + 24, "DATA BUS · 16 bit", "m", 12, "end", 600)

# --- registers on the left
s.box(110, 160, 170, 74, "relay", "TMP", "16-bit · 16 D-triggers")
s.box(110, 300, 170, 64, "relay", "CMD", "12-bit immediate")
s.box(110, 364, 170, 40, "relay", "OPCODE · 4 bit", None, rx=6, tsize=13)

# data riser into TMP and CMD (instruction / old *AP value)
s.line([(70, DB), (70, 197), (110, 197)], "ln", 2, "arr")
s.line([(70, 332), (110, 332)], "ln", 2, "arr")
s.text(62, 470, "*AP / insn", "m", 11, extra='transform="rotate(-90 62 470)"')
# address → TMP (old IP / AP)
s.line([(195, AB), (195, 160)], "ln", 2, "arr")
s.text(203, 138, "IP or AP", "m", 11)

# --- adder (trapezoid)
s.add('<path class="relay" d="M350,165 L470,215 L470,355 L350,405 Z" stroke-width="1.6"/>')
s.text(410, 272, "ADDER", "t", 17, "middle", 700)
s.text(410, 291, "16-bit", "m", 12, "middle")
s.text(410, 306, "parallel carry", "m", 12, "middle")
s.text(410, 330, "≈2 ms", "a", 12, "middle", 600)
s.line([(280, 197), (315, 197), (315, 225), (350, 225)], "lnA", 2.4, "arrA")
s.text(318, 215, "A", "a", 12, weight=700)
s.line([(280, 332), (315, 332), (315, 345), (350, 345)], "lnA", 2.4, "arrA")
s.text(318, 365, "B ±", "a", 12, weight=700)

# result bus
RX = 545
s.line([(470, 285), (RX, 285)], "lnA", 3)
s.line([(RX, 175), (RX, DB)], "lnA", 3, "arrA")
s.text(RX + 8, 500, "*AP ← sum", "a", 11, weight=600)
s.add(f'<circle class="arrA" cx="{RX}" cy="285" r="4.5"/>')

# IP / AP
s.box(600, 150, 150, 70, "relay", "IP", "instruction pointer")
s.box(600, 270, 150, 70, "relay", "AP", "address pointer")
s.line([(RX, 185), (600, 185)], "lnA", 2.4, "arrA")
s.line([(RX, 305), (600, 305)], "lnA", 2.4, "arrA")
# IP / AP → address bus via latches
s.line([(750, 185), (785, 185), (785, AB)], "ln", 2, "arr")
s.line([(750, 305), (785, 305), (785, 185)], "ln", 2)
s.text(675, 250, "via 16-bit RES43 latches", "m", 11, "middle")

# RAM
s.box(820, 135, 130, 100, "si", "RAM", "64K × 16 SRAM")
s.line([(885, AB), (885, 135)], "ln", 2, "arr")
s.line([(935, 235), (935, DB)], "ln", 2)
s.add(f'<path class="arr" d="M935,{DB} l-5,-10 l10,0 Z"/>')
s.add('<path class="arr" d="M935,235 l-5,10 l10,0 Z"/>')

# console
s.box(800, 290, 110, 46, "si", "COUT", None, tsize=14)
s.box(800, 350, 110, 46, "si", "CIN", None, tsize=14)
s.line([(890, DB), (890, 336)], "ln", 2, "arr")
s.line([(820, 396), (820, DB)], "ln", 2, "arr")
s.text(855, 418, "MCU · UART", "m", 11, "middle")

# logic / sequencer
s.box(300, 430, 220, 54, "logic", "CONTROL LOGIC", "11-step impulse sequencer", tsize=14, ssize=11)
s.line([(195, 404), (195, 457), (300, 457)], "lnR", 2, "arrR")
s.text(660, 470, "drives every latch / WR / RD line", "r", 11, "middle")
s.line([(520, 457), (535, 457)], "lnR", 2)
s.line([(555, 457), (575, 457)], "lnR", 2, "arrR", dash="4 3")

# legend
ly = 575
s.add(f'<rect class="relay" x="40" y="{ly-12}" width="22" height="14" rx="3" stroke-width="1.4"/>')
s.text(70, ly, "reed-relay logic (RES55 / RES64 / RES43)", "m", 12)
s.add(f'<rect class="si" x="350" y="{ly-12}" width="22" height="14" rx="3" stroke-width="1.4"/>')
s.text(380, ly, "silicon periphery", "m", 12)
s.add(f'<rect class="logic" x="520" y="{ly-12}" width="22" height="14" rx="3" stroke-width="1.4"/>')
s.text(550, ly, "control", "m", 12)
s.text(960, ly, "578 relays total", "a", 12, "end", 700)

s.save(OUT + "architecture.svg")
