import os
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..") + "/"
from common import Svg
ev = [
    ("2002", "The book", ["Voitsekhovsky,", "“Radio-electronic toys”"], "m"),
    ("2008", "RCVM-1", ["4-bit relay ALU;", "RES55 runs at 50 Hz"], "a"),
    ("Nov 2016", "Architecture", ["Brainfuck++ ISA,", "parallel-carry adder"], "a"),
    ("2017", "Boards", ["home-etched PCBs,", "then a factory order"], "a"),
    ("2018", "Blocks alive", ["adder + registers,", "500 Hz adder test"], "a"),
    ("Jan 2019", "On the frame", ["all blocks mounted,", "memory board works"], "a"),
    ("Apr 2019", "Runs programs", ["Hello World,", "π ≈ 355/113 @ 25 Hz"], "r"),
]
W = 1000
s = Svg(W, 230, "BrainfuckPC project timeline")
s.text(30, 40, "Ten years of dreaming, two years of building", "t", 22, weight=700)
Y = 85
s.line([(40, Y), (W - 40, Y)], "bus", 4)
step = (W - 80) / len(ev)
for i, (d, t, body, c) in enumerate(ev):
    x = 40 + step * (i + 0.5)
    s.add(f'<circle class="{"logic" if c == "r" else "relay"}" cx="{x:.0f}" cy="{Y}" r="10" stroke-width="2.5"/>')
    s.text(x, Y + 38, d, c, 13, "middle", 700, mono=True)
    s.text(x, Y + 60, t, "t", 15, "middle", 700)
    for k, line in enumerate(body):
        s.text(x, Y + 82 + k * 16, line, "m", 12, "middle")
s.save(OUT + "timeline.svg")
