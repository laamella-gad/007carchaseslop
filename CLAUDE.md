# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

"007 Car Chase" (c) 1985 Coplin Software, a C64 game: a Deflower disassembly of the original and a C rewrite for
oscar64 that plays at the original's speed, plus fixes. `NOTES.md` is the reference: memory map, BASIC/ML
mailbox, timing, the original's bugs, and **every difference from the original**. Keep it up to date with each
change.

The original is a BASIC V2 program (`007.bas`, listing `07.bas`, grep that) driving a machine code helper at
$C000 (`007`). Disk image `007CARCH.d64`. `007.prg`, `code.asm`, `1.bin`, `2.bin` are an older unused attempt.

## Commands

```sh
make                         # src/ -> build/007carchase_raw.prg -> crunched 007carchase.prg
make run                     # VICE
make timing                  # tools/c64time.c times the original's BASIC lines -> build/timing.txt (minutes)
make text                    # tools/bas2c.py: 007.bas + timing -> src/text.c, src/text.h (generated, don't edit)
deflower --verify 007.flo    # disassembly -> out/007.asm and the .bin exports (must stay 0 differ, 0 gaps)
petcat -2 -- 007.bas         # BASIC listing
```

`make` also runs `tools/branchcheck.py` on the oscar64 listing and fails if a branch or jump lands mid
instruction. That catches an oscar64 bug (in 1.32.273 up to commit 2357b11, fixed in a92fd0c): sign extending
a `signed char` to `int` could produce a bad `BPL`.

No tests. The user plays and tests in VICE; build only, and don't drive VICE from scripts.

## Architecture of the rewrite

`src/main.c` includes everything; each header ends with `#pragma compile("x.c")`. One file per part of the
original, with comments naming the BASIC lines they port:

- `helper.c` is the $C000 machine code (keys, joystick, sprite moves, weapon). `system.c` has the PETSCII
  printer that mimics the KERNAL, keys, INPUT and pacing. `sound.c` has the sounds.
- `game.c` holds the shared BASIC variables and `play_rows`. Most road lines only PRINT and SYS, and
  `bas2c.py` turns runs of them into `rows_N` tables of `{cells, helper ops, cycles}` that `play_rows` replays.
  The tables are rendered at build time to screen/colour spans that `print_cells` copies to video memory;
  a table that prints before homing the cursor needs its entry in `ENTRY` in `bas2c.py`.
- `road.c` (sections), `cars.c` (spawns, collisions, crash), `plan.c` (track plan, bonus), `title.c`,
  `hiscore.c`.

Pacing: every ported BASIC line ends with `LINE(n)` = `pace(CYCLES_n)`, the line's measured PAL cycles from
`build/timing.txt`, waited on with CIA 2 timer B. Call `pace_restart()` after waiting for a key. Lines the timing
run never reached are 0 or estimated (listed in NOTES.md).

Memory: VIC bank 0 as in the original (screen $0400, ROM charset). Sprites are blocks 40-59 at $0a00-$0eff
(their own section, `#embed` of the `.bin` files from Deflower's exports), code and data from $0f00 to $a000.

oscar64 quirks seen here: no zero-argument function-like macros, `sizeof` needs parentheses, `#embed` emits its
own trailing comma, and token pasting inside a nested macro call fails.
