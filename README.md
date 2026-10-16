# 007 Car Chase

A C64 car chase from 1985 by Coplin Software: drive down a road of country, city, tunnel, curve and bridge
sections, and shoot or smoke out the cars and the helicopter that come after you.

This is a C rewrite of it for [oscar64](https://github.com/drmortalwombat/oscar64), made from a disassembly of
the original.

## Download

[007carchase.prg](007carchase.prg): load and run it like any C64 program (`LOAD"007CARCHASE",8` and `RUN`), or
open it in VICE. Press `I` on the title screen for the instructions.

## The original

The original is a BASIC V2 program that does most of the work, from the road to the collisions and the score. It
has a small machine code helper at $c000 for the sprites, the keys and the sound. Because BASIC is slow, the
whole game runs at the speed of the interpreter.

The rewrite plays at that same speed. `tools/c64time.c` is a small C64 emulator that ran the original from a
snapshot for 20000 emulated seconds and timed every BASIC line in PAL cycles. The C version waits on a CIA timer
after each part until the original would have finished that line.

## Changes

Bugs fixed from the original:

- The title tune plays the 76 notes of its table. The original skips the first note and ends each pass with two
  notes read from past the end of the table.
- High scores: a score that ties one in the table is entered. The original stops the program with `END`
  instead. A new entry now moves the lower ones down without losing 9th place, and the name you type no longer
  picks up the rest of the old 10th place name.
- The car stops at the kerbs from any position. After a crash near the left kerb, the original lets the car
  drive off the road, and the next move stops the game with `?ILLEGAL QUANTITY ERROR`.
- Smoke from the `,` key stays while the key is held, as it does with the joystick. In the original it shows for
  a single frame.

`NOTES.md` has the full list of differences, the memory map, the timing and everything found in the disassembly.

## Building

Needs oscar64, pucrunch, python3 and a C compiler; VICE to play.

```sh
make            # 007carchase.prg
make run        # starts it in VICE
make timing     # times the original again (takes minutes), then `make text` for src/text.c
```

`deflower --verify 007.flo` rebuilds the disassembly in `out/` with Deflower.
