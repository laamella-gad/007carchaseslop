# 007 Car Chase

A C64 car chase from 1985 by Coplin Software: drive down a road of country, city, tunnel, curve and bridge
sections, and shoot or smoke out the cars and the helicopter that come after you.

This is a C rewrite of it for [oscar64](https://github.com/drmortalwombat/oscar64), made from a disassembly of
the original.

## Download

[007carchase.prg](007carchase.prg): load and run it like any C64 program (`LOAD"007CARCHASE",8` and `RUN`), or
open it in VICE. Press `I` on the title screen for the instructions.

## The original

[A gameplay video.](https://www.youtube.com/watch?v=9VdxBlnnm0g)

The author clearly set high goals for this game - it is a 3D Spy Hunter clone with various enemies and locations.
The goals are much too high for a game written in BASIC, and it wobbled along in a humorous way.

The most interesting technical thing going on in this game is how it manages to draw a 3D road that has a somewhat convincing movement feeling.
It does this by running a few ticks of the main game loop, then updating one horizontal line of the road with a PRINT, and then the whole thing again but one line higher.
In a way it has implemented cooperative multitasking.

To give this game the glory it deserves, I let Claude Code rewrite it in C, and let it make a long list of improvements.
No longer does it wobble.

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

- No more BASIC, everything now runs at 50Hz from the raster IRQ.
- The joystick steers and fires at the same time, and diagonals work. The original only takes one direction or
  fire at a time.
- The name for the high score table can be typed right away, while the tune plays; the original makes you wait
  for the whole tune.
- F5 pauses at once and F5 again goes on; F7 is never missed.

`NOTES.md` has the full list of differences, the memory map, the timing and everything found in the disassembly.

## Building

Needs oscar64, pucrunch and python3; VICE to play.

```sh
make            # 007carchase.prg
make run        # starts it in VICE
```

`deflower --verify 007.flo` rebuilds the disassembly in `out/` with Deflower.
