import html as _h

STYLE = """<style>
  .bg{fill:#fbf8f1}
  .t{fill:#1f2328}.m{fill:#6e6656}.a{fill:#9a6b00}.r{fill:#c93c37}.b{fill:#2f62a8}
  .relay{fill:#fbecc6;stroke:#b8860b}
  .si{fill:#e3ecf8;stroke:#4a77b4}
  .logic{fill:#fde2e1;stroke:#d1453b}
  .neutral{fill:#f1ebdd;stroke:#c9b98f}
  .bus{stroke:#57606a;fill:none}
  .busfill{fill:#57606a}
  .ln{stroke:#57606a;fill:none}
  .lnA{stroke:#b8860b;fill:none}
  .lnR{stroke:#d1453b;fill:none}
  .arr{fill:#57606a}.arrA{fill:#b8860b}.arrR{fill:#d1453b}
  .grid{stroke:#e2d8c3}
  .wave{stroke:#9a6b00;fill:none}
  @media (prefers-color-scheme: dark){
    .bg{fill:#0f1318}
    .t{fill:#e6edf3}.m{fill:#8b949e}.a{fill:#e3b341}.r{fill:#ff7b72}.b{fill:#79b0ff}
    .relay{fill:#2b2414;stroke:#c9a14a}
    .si{fill:#142033;stroke:#5a8fd0}
    .logic{fill:#2d1517;stroke:#e5534b}
    .neutral{fill:#1a1f27;stroke:#39404b}
    .bus{stroke:#8b949e}.busfill{fill:#8b949e}
    .ln{stroke:#8b949e}.arr{fill:#8b949e}
    .lnA{stroke:#c9a14a}.arrA{fill:#c9a14a}
    .lnR{stroke:#e5534b}.arrR{fill:#e5534b}
    .grid{stroke:#262c35}
    .wave{stroke:#e3b341}
  }
  text{font-family:-apple-system,'Segoe UI',Helvetica,Arial,sans-serif}
  .mono{font-family:ui-monospace,SFMono-Regular,Menlo,Consolas,'Liberation Mono',monospace}
</style>"""


def esc(s):
    return _h.escape(s)


class Svg:
    def __init__(self, w, h, label):
        self.w, self.h = w, h
        self.o = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{w}" height="{h}" '
                  f'viewBox="0 0 {w} {h}" role="img" aria-label="{esc(label)}">', STYLE,
                  f'<rect class="bg" width="{w}" height="{h}" rx="12"/>']

    def add(self, s):
        self.o.append(s)

    def text(self, x, y, s, cls="t", size=14, anchor="start", weight=None, mono=False, extra=""):
        c = cls + (" mono" if mono else "")
        wt = f' font-weight="{weight}"' if weight else ""
        self.o.append(f'<text class="{c}" x="{x}" y="{y}" font-size="{size}" '
                      f'text-anchor="{anchor}"{wt} {extra}>{esc(s)}</text>')

    def box(self, x, y, w, h, cls, title=None, sub=None, rx=8, tsize=16, ssize=12):
        self.o.append(f'<rect class="{cls}" x="{x}" y="{y}" width="{w}" height="{h}" rx="{rx}" stroke-width="1.6"/>')
        if title and sub:
            self.text(x + w / 2, y + h / 2 - 3, title, "t", tsize, "middle", 700)
            self.text(x + w / 2, y + h / 2 + 15, sub, "m", ssize, "middle")
        elif title:
            self.text(x + w / 2, y + h / 2 + tsize * 0.35, title, "t", tsize, "middle", 700)

    def line(self, pts, cls="ln", width=2, arrow=None, dash=None):
        d = "M" + " L".join(f"{x},{y}" for x, y in pts)
        da = f' stroke-dasharray="{dash}"' if dash else ""
        self.o.append(f'<path class="{cls}" d="{d}" stroke-width="{width}"{da} stroke-linejoin="round"/>')
        if arrow:
            (x1, y1), (x2, y2) = pts[-2], pts[-1]
            self.arrowhead(x2, y2, x2 - x1, y2 - y1, arrow)

    def arrowhead(self, x, y, dx, dy, cls="arr", s=9):
        import math
        L = math.hypot(dx, dy) or 1
        ux, uy = dx / L, dy / L
        px, py = -uy, ux
        p1 = (x, y)
        p2 = (x - ux * s + px * s * 0.55, y - uy * s + py * s * 0.55)
        p3 = (x - ux * s - px * s * 0.55, y - uy * s - py * s * 0.55)
        self.o.append(f'<path class="{cls}" d="M{p1[0]:.1f},{p1[1]:.1f} L{p2[0]:.1f},{p2[1]:.1f} L{p3[0]:.1f},{p3[1]:.1f} Z"/>')

    def save(self, path):
        self.o.append("</svg>")
        open(path, "w").write("\n".join(self.o))
