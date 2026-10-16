import os
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..") + "/"
from common import Svg

s = Svg(1000, 470, "BrainfuckPC clock tick: fetch on falling edge, execute on rising edge")
s.text(30, 40, "One clock tick = one instruction", "t", 22, weight=700)
s.text(30, 62, "Fetch on the falling edge, execute on the rising edge. Both phases reuse the same adder.", "m", 14)

# clock waveform
CY_H, CY_L = 100, 140
s.line([(60, CY_H), (150, CY_H), (150, CY_L), (530, CY_L), (530, CY_H), (910, CY_H), (910, CY_L), (950, CY_L)], "wave", 2.6)
s.arrowhead(150, 128, 0, 1, "arrA", 10)
s.arrowhead(530, 112, 0, -1, "arrA", 10)
s.text(40, 125, "CLK", "m", 12, "end", 700, mono=True)
s.text(340, 128, "↓ falling edge", "a", 13, "middle", 600)
s.text(720, 92, "↑ rising edge", "a", 13, "middle", 600)

def phase(x, title, sub, steps, cls):
    s.box(x, 165, 400, 210, cls)
    s.text(x + 20, 195, title, "t", 18, weight=700)
    s.text(x + 20, 215, sub, "m", 12)
    for i, (a, b) in enumerate(steps):
        y = 248 + i * 42
        s.add(f'<circle class="{"lnA" if cls=="relay" else "lnR"}" cx="{x+32}" cy="{y-5}" r="12" stroke-width="1.8"/>')
        s.text(x + 32, y, str(i + 1), "t", 13, "middle", 700)
        s.text(x + 56, y - 4, a, "t", 14, mono=True)
        s.text(x + 56, y + 13, b, "m", 11)

phase(130, "1 · FETCH", "same for every instruction",
      [("TMP ← IP", "old IP goes through the address bus latches"),
       ("IP ← TMP + 1", "adder with carry-in = 1"),
       ("CMD ← RAM[IP]", "opcode → logic, imm12 → adder input B")], "relay")
phase(560, "2 · EXECUTE", "depends on opcode",
      [("TMP ← AP | *AP | IP", "source picked by the opcode"),
       ("SUM ← TMP + imm", "parallel carry: 3 relay delays ≈ 2 ms"),
       ("AP | *AP | IP ← SUM", "jumps write IP only if Z-flag matches")], "relay")

s.text(500, 410, "CTRLIO skips the adder: the logic strobes COUT / CIN / MODE / HALT lines instead.", "m", 13, "middle")
s.text(500, 440, "Nominal 25 Hz · max ≈ 40 Hz (adder alone runs at 500 Hz) · each phase is an 11-step relay impulse sequencer",
       "a", 13, "middle", 600)
s.save(OUT + "clock-cycle.svg")
