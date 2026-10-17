#!/usr/bin/env python3
"""Makes src/text.c and src/text.h from the original BASIC program and its timing.

    tools/bas2c.py 007.bas build/timing.txt src

- Each string literal of the program becomes a PETSCII byte array (duplicates
  share one), named after the first line that has it: t200, t6010, t6010_2.
- A "row line" does nothing but SYS calls into the helper and one PRINT of a
  literal. Runs of row lines become Row tables (rows_200 for lines 200-214) that
  play_rows plays back.
- The PRINTs of the tables are printed here, with system.c's printer: each row
  becomes the screen and colour cells it writes and the printer's state after
  it, which print_cells copies straight to video memory. The colour and reverse
  a table finds can be the printer's at run time; where the cursor is must be
  known (ENTRY for the tables that print before homing it). Strings only the
  tables print are left out.
- CYCLES_<line> is the time the original spends on a line per pass, without the
  subroutines it calls (from tools/c64time.c). The rewrite waits that long.
"""
import re
import sys

PRINT, SYS, IF, THEN, REM, DATA = 0x99, 0x9e, 0x8b, 0xa7, 0x8f, 0x83

SYS_OPS = {
    b"49152": "OP_TURBO",    # turbo_frame
    b"49155": "OP_FRAME",    # frame_update
    b"49561": "OP_WEAPON",   # weapon_update
    b"51000": "OP_TUNE",     # tune_play
}


# never run: test code and an old loader
UNUSED = [(1200, 1600), (9000, 9011)]


def used(num):
    return not any(a <= num <= b for a, b in UNUSED)


def load_lines(path):
    data = open(path, "rb").read()
    base = data[0] | data[1] << 8
    mem = data[2:]
    addr = base
    lines = []
    while True:
        o = addr - base
        link = mem[o] | mem[o + 1] << 8
        if link == 0:
            break
        num = mem[o + 2] | mem[o + 3] << 8
        end = mem.index(0, o + 4)
        lines.append((num, mem[o + 4:end]))
        addr = link
    return lines


def statements(body):
    """Splits a tokenized line at colons outside quotes."""
    out, cur, quote = [], bytearray(), False
    for b in body:
        if b == 0x22:
            quote = not quote
        if b == ord(":") and not quote:
            out.append(bytes(cur))
            cur = bytearray()
        else:
            cur += bytes([b])
    out.append(bytes(cur))
    return [s.strip(b" ") for s in out]


def literals(body):
    return re.findall(rb'"([^"]*)"?', body)


def row_line(body):
    """(ops, text, newline) if the line is SYS calls and one PRINT of a literal."""
    ops = []
    stmts = [s for s in statements(body) if s]
    for s in stmts[:-1]:
        if s[0] != SYS or s[1:] not in SYS_OPS:
            return None
        ops.append(SYS_OPS[s[1:]])
    last = stmts[-1]
    m = re.fullmatch(rb'\x99"([^"]*)"(;?)', last)
    if not m:
        return None
    return ops, m.group(1), not m.group(2)


# PETSCII colour codes to colours, as system.c's put()
COLOURS = {0x05: 1, 0x1c: 2, 0x1e: 5, 0x1f: 6, 0x81: 8, 0x90: 0, 0x95: 9, 0x96: 10, 0x97: 11,
           0x98: 12, 0x99: 13, 0x9a: 14, 0x9b: 15, 0x9c: 4, 0x9e: 7, 0x9f: 3}


def screen_code(c):
    if c < 0x40:
        return c
    if c < 0x60:
        return c - 0x40
    if c < 0x80:
        return c - 0x20
    if c < 0xc0:
        return c - 0x40
    if c < 0xff:
        return c - 0x80
    return 0x5e


class Unknown(Exception):
    pass


# Where the cursor is when a table starts that prints before homing it: the
# PRINTs before the table, from one that homes or clears it
ENTRY = {
    391: range(381, 388),       # the table of lines 381-387
    401: [400],
    451: [450],
    12020: [12001, 12002],
    12101: [12100],
    12112: [12100] + list(range(12101, 12108)),
}

# Tables whose clear stops above the panel (rows 20-24), which the original
# erases and never redraws: the city and the tunnel
PANEL_KEPT = {381, 794}

# The rows a table is played from besides its first: goto800 in the tunnel
ENTRY_ROWS = {794: [5]}

# Cell colours and reverse that come from the printer when the table is played
INK = 0x40      # the printer's colour
REVERSE = 0x80  # the screen codes take the printer's reverse
SAME = 0x20     # end state: the reverse stays the printer's


class Printer:
    """system.c's put(), with the cursor, colour and reverse None while they're
    the printer's from before the table."""

    def __init__(self, keep_panel=False):
        self.row = self.col = self.ink = self.rev = None
        self.spans = []
        self.keep_panel = keep_panel

    def known(self):
        if self.row is None:
            raise Unknown

    def down(self):
        self.known()
        if self.row == 24:
            raise Unknown       # a scroll
        self.row += 1

    def right(self):
        self.known()
        self.col += 1
        if self.col == 40:
            self.col = 0
            self.down()

    def put(self, c):
        if c in COLOURS:
            self.ink = COLOURS[c]
        elif c in (0x0d, 0x8d):
            self.known()
            self.col = 0
            self.rev = 0
            self.down()
        elif c == 0x11:
            self.down()
        elif c == 0x12:
            self.rev = 0x80
        elif c == 0x92:
            self.rev = 0
        elif c == 0x13:
            self.row = self.col = 0
        elif c == 0x93:
            self.spans.append(("clear", INK if self.ink is None else self.ink))
            self.row = self.col = 0
        elif c == 0x1d:
            self.right()
        elif c == 0x91:
            self.known()
            if self.row:
                self.row -= 1
        elif c == 0x9d:
            self.known()
            if self.col:
                self.col -= 1
            elif self.row:
                self.col = 39
                self.row -= 1
        elif c < 0x20 or 0x80 <= c < 0xa0:
            pass
        else:
            self.known()
            o = self.row * 40 + self.col
            colour = (INK if self.ink is None else self.ink) | (REVERSE if self.rev is None else 0)
            sc = screen_code(c) | (self.rev or 0)
            last = self.spans[-1] if self.spans else None
            if last and last[0] != "clear" and last[0] + len(last[2]) == o and last[1] == colour:
                last[2].append(sc)
            else:
                self.spans.append((o, colour, [sc]))
            self.right()

    def print(self, lit, newline):
        for c in lit + (b"\r" if newline else b""):
            self.put(c)

    def cells(self):
        """The spans so far, then the state: [offset high, offset low, colour,
        length, screen codes]..., [0xfe, colour] for a clear ([0xfd, colour] for
        one that keeps the panel), then [0xff, row,
        column, colour | reverse]."""
        out = []
        for span in self.spans:
            if span[0] == "clear":
                out += [0xfd if self.keep_panel else 0xfe, span[1]]
            else:
                o, colour, codes = span
                out += [o >> 8, o & 0xff, colour, len(codes)] + codes
        self.spans = []
        self.known()
        ink = INK if self.ink is None else self.ink
        rev = SAME if self.rev is None else self.rev
        return out + [0xff, self.row, self.col, ink | rev]


def last_print(body):
    """The literal and newline of the last PRINT of a line."""
    m = re.findall(rb'\x99"([^"]*)"(;?)', body)[-1]
    return m[0], not m[1]


def render(run, bodies):
    """The cells each row of a table writes, as system.c's put() would print
    them. Stops if a row can't be rendered: it scrolls, or prints where the
    cursor was and ENTRY doesn't say where that is."""
    first = run[0][0]
    p = Printer(first in PANEL_KEPT)
    try:
        if first in ENTRY:
            for num in ENTRY[first]:
                p.print(*last_print(bodies[num]))
            p.spans = []
            # only the cursor: the colour and reverse are the printer's
            p.ink = p.rev = None
        out = []
        for i, (num, (ops, lit, newline)) in enumerate(run):
            if i in ENTRY_ROWS.get(first, []):
                row, col = p.row, p.col
                p = Printer(first in PANEL_KEPT)
                p.row, p.col = row, col
            p.print(lit, newline)
            out.append(p.cells())
    except Unknown:
        sys.exit("bas2c.py: can't render line %d: it scrolls, or the cursor isn't known" % num)
    return out


def load_timing(path):
    cycles = {}
    for l in open(path):
        f = l.split()
        if len(f) == 5 and f[0].isdigit():
            cycles[int(f[0])] = int(f[2])
    return cycles


def main():
    bas, timing, out = sys.argv[1:4]
    lines = load_lines(bas)
    cycles = load_timing(timing)

    names = {}      # bytes -> array name
    arrays = []
    line_texts = {}
    for num, body in lines:
        if body[:1] in (bytes([REM]), bytes([DATA])) or not used(num):
            continue
        refs = []
        for i, lit in enumerate(literals(body)):
            if lit not in names:
                names[lit] = "t%d" % num + ("_%d" % (i + 1) if i else "")
                arrays.append((names[lit], lit))
            refs.append(names[lit])
        line_texts[num] = refs

    runs, run = [], []
    for num, body in lines:
        r = row_line(body)
        if r and used(num):
            run.append((num, r))
            continue
        if len(run) > 1:
            runs.append(run)
        run = []

    # the tables rendered, and the strings only they print left out
    bodies = dict(lines)
    rendered = {run[0][0]: render(run, bodies) for run in runs}
    in_tables = set(num for run in runs for num, r in run)
    printed = set(lit for num, body in lines if num not in in_tables for lit in literals(body))
    arrays = [(name, lit) for name, lit in arrays if lit in printed]

    c = open(out + "/text.c", "w")
    h = open(out + "/text.h", "w")
    c.write("// Made by tools/bas2c.py from 007.bas and build/timing.txt: don't edit\n")
    c.write('#include "text.h"\n\n')
    for name, lit in arrays:
        c.write("const char %s[] = {%s0};\n" % (name, "".join("%d," % b for b in lit)))
    c.write("\n")
    for run in runs:
        for (num, r), row in zip(run, rendered[run[0][0]]):
            c.write("static const char s%d[] = {%s};\n" % (num, ",".join("%d" % b for b in row)))
        c.write("const Row rows_%d[%d] = {\n" % (run[0][0], len(run)))
        for num, (ops, lit, newline) in run:
            c.write("\t{s%d, %s, %d},\t// %d\n" % (num, " | ".join(ops) or "0",
                                                 cycles.get(num, 0), num))
        c.write("};\n\n")

    h.write("// Made by tools/bas2c.py from 007.bas and build/timing.txt: don't edit\n")
    h.write("#ifndef TEXT_H\n#define TEXT_H\n\n")
    h.write("// What a row line does before its PRINT, in this order\n")
    h.write("#define OP_TUNE\t\t1\t// sys51000\n#define OP_FRAME\t2\t// sys49155\n")
    h.write("#define OP_TURBO\t4\t// sys49152\n#define OP_WEAPON\t8\t// sys49561\n\n")
    h.write("// cells: what the PRINT writes, for print_cells\n")
    h.write("typedef struct {\n\tconst char *cells;\n\tchar ops;\n\tunsigned long cycles;\n} Row;\n\n")
    for name, lit in arrays:
        h.write("extern const char %s[];\n" % name)
    h.write("\n")
    for run in runs:
        h.write("extern const Row rows_%d[%d];\t// lines %d-%d\n" % (run[0][0], len(run), run[0][0], run[-1][0]))
    h.write("\n// Cycles per pass of each line in the original, without its subroutines\n")
    # 0 for the lines the measurement never reached
    for num, body in lines:
        if body[:1] not in (bytes([REM]), bytes([DATA])) and used(num):
            h.write("#define CYCLES_%d\t%dul\n" % (num, cycles.get(num, 0)))
    h.write('\n#pragma compile("text.c")\n\n#endif\n')


main()
