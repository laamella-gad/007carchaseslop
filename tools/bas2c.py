#!/usr/bin/env python3
"""Makes src/text.c and src/text.h from the original BASIC program and its timing.

    tools/bas2c.py 007.bas build/timing.txt src

- Each string literal of the program becomes a PETSCII byte array (duplicates
  share one), named after the first line that has it: t200, t6010, t6010_2.
- A "row line" does nothing but SYS calls into the helper and one PRINT of a
  literal. Runs of row lines become Row tables (rows_200 for lines 200-214) that
  road.c plays back.
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

    c = open(out + "/text.c", "w")
    h = open(out + "/text.h", "w")
    c.write("// Made by tools/bas2c.py from 007.bas and build/timing.txt: don't edit\n")
    c.write('#include "text.h"\n\n')
    for name, lit in arrays:
        c.write("const char %s[] = {%s0};\n" % (name, "".join("%d," % b for b in lit)))
    c.write("\n")
    for run in runs:
        c.write("const Row rows_%d[%d] = {\n" % (run[0][0], len(run)))
        for num, (ops, lit, newline) in run:
            flags = ops + (["OP_NEWLINE"] if newline else [])
            c.write("\t{%s, %s, %d},\t// %d\n" % (names[lit], " | ".join(flags) or "0",
                                                 cycles.get(num, 0), num))
        c.write("};\n\n")

    h.write("// Made by tools/bas2c.py from 007.bas and build/timing.txt: don't edit\n")
    h.write("#ifndef TEXT_H\n#define TEXT_H\n\n")
    h.write("// What a row line does before its PRINT, in this order\n")
    h.write("#define OP_TUNE\t\t1\t// sys51000\n#define OP_FRAME\t2\t// sys49155\n")
    h.write("#define OP_TURBO\t4\t// sys49152\n#define OP_WEAPON\t8\t// sys49561\n")
    h.write("#define OP_NEWLINE\t16\t// the PRINT ends without ';'\n\n")
    h.write("typedef struct {\n\tconst char *text;\n\tchar ops;\n\tunsigned long cycles;\n} Row;\n\n")
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
