import os
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..") + "/"
W,H=1200,300
STYLE="""
<style>
  .bg{fill:#fbf8f1}.panel{fill:#f1ebdd;stroke:#d8ccb0}
  .t{fill:#1f2328}.m{fill:#6e6656}.a{fill:#9a6b00}.code{fill:#b08a3a}
  .led{fill:#e5484d}.ledoff{fill:#e9dcc6}.wire{stroke:#c9b98f}
  .relay{fill:#d9b45a;stroke:#a8842c}.pcb{fill:#2f5aa8}
  @media (prefers-color-scheme: dark){
    .bg{fill:#0f1318}.panel{fill:#171c23;stroke:#2a313b}
    .t{fill:#e6edf3}.m{fill:#8b949e}.a{fill:#e3b341}.code{fill:#6b5a2e}
    .led{fill:#ff5f56}.ledoff{fill:#2a1d1d}.wire{stroke:#3a3322}
    .relay{fill:#b8913c;stroke:#7d6324}.pcb{fill:#1d3b73}
  }
  text{font-family:ui-monospace,SFMono-Regular,Menlo,Consolas,'Liberation Mono',monospace}
  .sans{font-family:-apple-system,'Segoe UI',Helvetica,Arial,sans-serif}
</style>"""
o=[f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" role="img" aria-label="BrainfuckPC — 16-bit relay computer">',STYLE,
   f'<rect class="bg" width="{W}" height="{H}" rx="14"/>']
# code strip
import html; code=html.escape("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.")
o.append(f'<text class="code" x="40" y="276" font-size="15" letter-spacing="1">{code}</text>')
o.append('<text class="t" x="40" y="104" font-size="64" font-weight="700" letter-spacing="-1">Brainfuck<tspan class="a">PC</tspan></text>')
o.append('<text class="m sans" x="42" y="146" font-size="22">16-bit von Neumann computer built from 578 reed relays</text>')
specs=[("ISA","Brainfuck++"),("CLOCK","25–40 Hz"),("RAM","64K × 16"),("POWER","70 W")]
x=42
for k,v in specs:
    o.append(f'<text class="m" x="{x}" y="192" font-size="13" letter-spacing="2">{k}</text>')
    o.append(f'<text class="t" x="{x}" y="216" font-size="20" font-weight="600">{v}</text>')
    x+=165
# relay module panel on the right
px,py,pw,ph=700,34,460,196
o.append(f'<rect class="panel" x="{px}" y="{py}" width="{pw}" height="{ph}" rx="10" stroke-width="1.5"/>')
# relays row
for i in range(8):
    rx=px+28+i*52
    o.append(f'<rect class="pcb" x="{rx-6}" y="{py+18}" width="44" height="74" rx="3"/>')
    o.append(f'<rect class="relay" x="{rx}" y="{py+26}" width="32" height="14" rx="6" stroke-width="1"/>')
    o.append(f'<rect class="relay" x="{rx}" y="{py+46}" width="32" height="14" rx="6" stroke-width="1"/>')
    o.append(f'<rect class="relay" x="{rx}" y="{py+66}" width="32" height="14" rx="6" stroke-width="1"/>')
# 16-bit binary counter (IP) — SMIL discrete
o.append(f'<text class="m" x="{px+24}" y="{py+130}" font-size="13" letter-spacing="2">IP</text>')
o.append(f'<text class="m" x="{px+24}" y="{py+172}" font-size="13" letter-spacing="2">AP</text>')
base=0.25
for row,(yy,scale,offs) in enumerate([(py+125,1,0),(py+167,8,3)]):
    for b in range(16):
        cx=px+70+(15-b)*23
        o.append(f'<circle class="ledoff" cx="{cx}" cy="{yy}" r="7"/>')
        period=base*scale*(2**(b+1))
        if period>4000: continue
        o.append(f'<circle class="led" cx="{cx}" cy="{yy}" r="7" opacity="0"><animate attributeName="opacity" values="0;1" dur="{period:g}s" begin="{-offs*base*scale*(2**b):g}s" calcMode="discrete" repeatCount="indefinite"/></circle>')
o.append('</svg>')
open(OUT + 'banner.svg', 'w').write('\n'.join(o))
