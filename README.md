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

A small C64 emulator (`tools/c64time.c`, now only in the git history) ran the original from a snapshot for
20000 emulated seconds and timed every BASIC line in PAL cycles. The title, the instructions, the bonus, the
track plan and the high scores keep those times. The road doesn't: it scrolls a row every frame, where the
original stalls for about a quarter of a second at every collision check, so the game is faster and harder.
The cars, the player, the weapons and the sounds move every frame in a raster interrupt, smoothly, where the
original moves them in jumps whenever BASIC gets round to it.

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
- The city and the tunnel no longer erase the panel with the score and the track plan.
- The tunnel's left walls stay yellow; in the original one row turns white after each collision check.
- The missile can hit the helicopter. The original checks so rarely that it almost never does.
- Crashes go by the cars' visible pixels. The original's box is larger than the cars, and the bomb's is off to
  the left, so a bomb beside the car hits and one on its right half misses.

Gameplay changes:

- The road sections are 1.5 times as long.
- The joystick steers and fires at the same time, and diagonals work. The original only takes one direction or
  fire at a time.
- The name for the high score table can be typed right away, while the tune plays; the original makes you wait
  for the whole tune.
- F5 pauses at once and F5 again goes on; F7 is never missed. No "wait for data transfer" at the start.

`NOTES.md` has the full list of differences, the memory map, the timing and everything found in the disassembly.

## Building

Needs oscar64, pucrunch and python3; VICE to play.

```sh
make            # 007carchase.prg
make run        # starts it in VICE
```

`deflower --verify 007.flo` rebuilds the disassembly in `out/` with Deflower.
