import os
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..") + "/"
from common import Svg

s = Svg(1000, 740, "BrainfuckPC front panel layout")
s.text(30, 40, "What is where on the frame", "t", 22, weight=700)
s.text(30, 62, "Front view of the finished machine (2019). Relay CPU in the middle, silicon periphery on top.", "m", 14)

FX, FY, FW, FH = 60, 90, 440, 610
s.add(f'<rect class="neutral" x="{FX}" y="{FY}" width="{FW}" height="{FH}" rx="10" stroke-width="2"/>')
# wooden base
s.add(f'<rect class="relay" x="{FX-10}" y="{FY+FH-50}" width="{FW+20}" height="56" rx="6" stroke-width="1.6"/>')
s.text(FX + 30, FY + FH - 15, "BrainfuckPC", "a", 16, weight=700, mono=True)
for i in range(3):
    s.add(f'<rect class="si" x="{FX+300+i*34}" y="{FY+FH-30}" width="24" height="12" rx="2" stroke-width="1.2"/>')

def leds(x, y, n, step=9, r=2.4):
    for i in range(n):
        s.add(f'<circle class="r" cx="{x+i*step}" cy="{y}" r="{r}" fill-opacity="0.85"/>')

# IV-6 indicator modules (4)
for i in range(4):
    y = FY + 18 + i * 40
    s.add(f'<rect class="si" x="{FX+18}" y="{y}" width="92" height="32" rx="4" stroke-width="1.2"/>')
    for k in range(6):
        s.add(f'<rect class="b" x="{FX+26+k*13}" y="{y+8}" width="9" height="16" rx="3" opacity="0.55"/>')
# LED matrix (32x16)
MX, MY = FX + 160, FY + 18
s.add(f'<rect class="si" x="{MX}" y="{MY}" width="262" height="112" rx="4" stroke-width="1.2"/>')
for row in range(10):
    leds(MX + 10, MY + 10 + row * 10.2, 28, 8.95, 2.1)
# VFD terminal
s.add(f'<rect class="si" x="{MX+46}" y="{MY+124}" width="170" height="28" rx="4" stroke-width="1.2"/>')
s.text(MX + 131, MY + 143, "HELLO WORLD!", "b", 12, "middle", 700, mono=True)

def latch_row(y):
    for i in range(4):
        x = FX + 22 + i * 102
        s.add(f'<rect class="relay" x="{x}" y="{y}" width="90" height="46" rx="4" stroke-width="1.2"/>')
        for k in range(4):
            s.add(f'<rect class="neutral" x="{x+8+k*20}" y="{y+8}" width="16" height="30" rx="2" stroke-width="0.8"/>')

def block(x, y, filled=True):
    s.add(f'<rect class="{"relay" if filled else "neutral"}" x="{x}" y="{y}" width="128" height="104" rx="5" stroke-width="1.4"'
          + ('' if filled else ' stroke-dasharray="5 4"') + '/>')
    if not filled:
        s.text(x + 64, y + 57, "free slot", "m", 12, "middle")
        return
    for r in range(4):
        for c in range(8):
            cx, cy = x + 10 + c * 14.5, y + 10 + r * 23.5
            s.add(f'<rect class="neutral" x="{cx}" y="{cy}" width="10" height="17" rx="2" stroke-width="0.6"/>')
            s.add(f'<circle class="r" cx="{cx+5}" cy="{cy+4}" r="2"/>')

latch_row(FY + 200)
for i in range(3):
    block(FX + 18 + i * 138, FY + 258)
latch_row(FY + 372)
block(FX + 18, FY + 428 - 5)
block(FX + 156, FY + 428 - 5, filled=False)
block(FX + 294, FY + 428 - 5)

# callouts
CX = 560
def call(y, title, body, cls="t"):
    s.line([(FX + FW + 6, y - 5), (CX - 10, y - 5)], "ln", 1.2, dash="3 3")
    s.add(f'<circle class="arr" cx="{FX + FW + 6}" cy="{y - 5}" r="3"/>')
    s.text(CX, y, title, cls, 15, weight=700)
    s.text(CX, y + 19, body, "m", 12, extra='xml:space="preserve"')

call(140, "IV-6 status modules ×4", "IP, AP, CMD and retired-instruction counter (ATmega168 each)", "b")
call(196, "Memory board", "64K×16 SRAM + ATmega loader, 32×16 LED view of RAM", "b")
call(252, "VFD terminal", "console output of the '.' instruction", "b")
call(318, "16-bit latches ×8", "RES43 relays route data between blocks", "a")
call(405, "CPU core · 3 relay blocks", "16-bit adder with parallel carry, TMP/CMD and IP/AP registers", "a")
call(490, "16-bit latches", "second latch row", "a")
call(570, "Control logic blocks", "impulse sequencer + decoder; one slot kept free for expansion", "r")
call(683, "Wooden base", "power, mode switches, 36-pin programming connector", "m")
s.text(CX, 622, "5 relay blocks × 32 modules · 3–4 reed relays per module", "a", 12, weight=600)
s.text(CX, 640, "each block is powered from 5 V / 3 A", "a", 12, weight=600)
s.save(OUT + "front-panel.svg")
