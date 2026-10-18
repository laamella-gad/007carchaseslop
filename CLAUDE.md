# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

"007 Car Chase" (c) 1985 Coplin Software, a C64 game: a Deflower disassembly of the original and a C rewrite for
oscar64 that plays at the original's speed, plus fixes. `NOTES.md` is the reference: the rewrite's structure,
timing, the original's bugs, and **every difference from the original**. Keep it up to date with each change.

The original is a BASIC V2 program (`007.bas`, listing `07.bas`, grep that) driving a machine code helper at
$C000 (`007`). Disk image `007CARCH.d64`. `007.prg`, `code.asm`, `1.bin`, `2.bin` are an older unused attempt.

## Commands

```sh
make                         # src/ -> build/007carchase_raw.prg -> crunched 007carchase.prg
make run                     # VICE
deflower --verify 007.flo    # disassembly -> out/007.asm and the .bin exports (must stay 0 differ, 0 gaps)
petcat -2 -- 007.bas         # BASIC listing
```

No tests. The user plays and tests in VICE; build only, and don't drive VICE from scripts.

## Architecture of the rewrite

`src/main.c` includes everything; each header ends with `#pragma compile("x.c")`. One file per part of the game.
Comments describe what the code does, not the original's BASIC lines or variables; differences from the original
go in `NOTES.md`.

- `frame.c` is what moves in the raster IRQ (keys, joystick, sprite moves, weapon, hits, crash). `system.c` writes text and numbers
  to a row and column of the screen, and has the keys and the name input. `sound.c` has the sounds.
- `game.c` holds the shared variables and `play_rows`. `src/text.c` holds the road and the screens as
  pictures (`country_a`, `title_page`...): a line of characters per screen row, with stand-ins for the
  graphics, and colour runs (format and stand-ins in `text.h`). `play_rows` draws a line a frame, `show_rows`
  all at once. Made once from `007.bas` (tools deleted, in git history up to eb9235c), edited by hand.
- `road.c` (sections), `cars.c` (spawns, collisions, crash), `plan.c` (track plan, bonus), `title.c`,
  `hiscore.c`. The plan is the list of sections the road goes through (`plan[]`); `game()` runs them in turn.

Timing: everything goes by frames of the raster IRQ (`frame_count`). The road goes a row a frame (`row_wait()`
before each row); the screens show at once and wait for a key or fire (`wait_key`).

Memory: VIC bank 0 (screen $0400, ROM charset). Sprites are blocks 40-59 at $0a00-$0eff
(their own section, `#embed` of the `.bin` files from Deflower's exports), code and data from $0f00 to $a000.

oscar64 quirks seen here: no zero-argument function-like macros, `sizeof` needs parentheses, `#embed` emits its
own trailing comma, and token pasting inside a nested macro call fails.

Needs oscar64 at commit fbca293 or later.
