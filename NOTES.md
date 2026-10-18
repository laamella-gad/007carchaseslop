# 007 Car Chase notes

"007 Car Chase", (c) 1985 Coplin Software: a James Bond style car chase for the C64. You drive down a road
made of country, city, tunnel, curve and bridge sections. You shoot enemy cars with guns or lay smoke behind you,
and you can shoot the helicopter with a missile. This is a C rewrite for oscar64 that plays at the original's
speed, with its bugs fixed.

## Files

| File | What |
|---|---|
| `007CARCH.d64` | The original disk: a loader, the game program and its machine code ($c000-$cfff) |
| `007.bas`, `07.bas` | The original program as loaded at $1001, and its listing |
| `007` | The original's machine code as on the disk, load address $c000 |
| `007.vsf` | VICE snapshot taken during a game, the input for Deflower |
| `007.flo` | Deflower annotations: `deflower --verify 007.flo` writes `out/007.asm` (0 differ, 0 gaps) and the exports below |
| `out/sprites_40_54.bin`, `out/sprites_13_15.bin`, `out/sprites_33_34.bin` | The sprites |
| `out/tune_notes.bin` | The tune's note table |
| `007.prg`, `code.asm`, `1.bin`, `2.bin` | An older attempt, not used |
| `src/` | The rewrite |
| `tools/branchcheck.py` | Checks the oscar64 listing for branches into the middle of an instruction (`make` runs it) |
| `007carchase.prg` | The rewrite, crunched (`make`) |

## The rewrite

| File | What |
|---|---|
| `main.c` | Memory layout, setup, the main loop |
| `system.c` | Screen writes, keys, the name input, `rnd` |
| `frame.c` | What moves in the raster IRQ: the cars, the player, the helicopter, the weapon, the crash, the keys |
| `sound.c` | The raster IRQ, the explosion, the tune, the crash noise and the siren |
| `text.c` | The pictures of the road and the screens |
| `game.c` | The game's state, drawing the pictures, the panel |
| `cars.c` | Spawns, the collision pass, explosions, the crash |
| `road.c` | The sections: country, city, tunnel, curves, bridge |
| `plan.c` | The plan at the bottom right, the bonus |
| `title.c` | Title and instructions |
| `hiscore.c` | Top 10 |

The game: the title (I for the instructions), a new plan, then the road section by section as the plan says.
Each section draws its road from `text.c` a row a frame, and after each half runs the collision pass
(`collide`): the cars the guns or the smoke hit explode for points, a crash costs one of 3 cars, F7 and the
helicopter's hit are scored. Off the road the enemy cars come back on. At the end of the plan comes the bonus
car and a new plan; with no cars left, the high score table.

The plan (`plan[]`, `plan_new`) is five random steps from the section the road is in, by `roads_after`: country
to tunnel, left curve or bridge; city to country or tunnel; tunnel to city or country; a curve to country or
the other curve; a bridge always to country. The road and the drawing both read it.

The raster IRQ (`music_irq` in sound.c), once a frame below the screen, plays the tune and the sounds, reads
F1 (turbo), F3, F5 (pause) and F7 (end the game), moves the cars, the player, the helicopter, its bomb and the
weapon, tests the hits and the crashes, runs the crash animation, flashes a hit helicopter, writes the credit,
scrolls the title's logo and moves the bonus animation. The main code only draws the road and reacts to what
the IRQ found (`car_shot`, `crash_pending`, `heli_hit`, `quit_request`). Its CIA interrupt goes on to the
KERNAL's, so the keyboard scan stays at 60 Hz.

Timing: everything goes by frames of the raster IRQ (`frame_count`). The road goes a row a frame: `row_wait()`
waits for the next frame before each row, and the rest of the road code takes no time. The screens (title,
instructions, high scores, track plan) show at once and wait for a key or fire.

Text: `text.c` holds the road and the screens as pictures, a line of characters per screen row and its colours
as runs (the format and the stand-ins for the graphics characters are in `text.h`). `play_rows` draws a line
a frame, `show_rows` a screen at once. The city's houses take the colour of their block (`play_rows_ink`),
which turns each pass. Everything else is written to a row and column (`text_at`, `number_at`, `char_at`).

Memory: VIC bank 0 (screen $0400, ROM character set). The sprites are blocks 40-59 at $0a00-$0eff, code and
data from $0f00 to $a000.

Compiler bug: oscar64 1.32.271 at `-O2` turned the sign extension `AND #$80 / BPL +2 / LDA #$ff / STA` into
`TYA` (Y was $ff) after placing the branch, so the `BPL` landed in the middle of the `STA`. That was in
`plan_new` with `signed char x, y`, and still happens with oscar64 at commit 2357b11 (October 2026); fixed in
commit a92fd0c ("Fix size reduction breaking branch offset"). When a plan was drawn, the game ran into garbage
and ended at READY. `make` runs `tools/branchcheck.py` on the listing, which fails the build if any branch or
jump misses an instruction start.

## The original

A BASIC V2 program and a machine code helper at $c000. The loader sets BASIC's start to $1001 and loads the
program, which loads the helper. The program draws the road with PRINT and calls the helper between the rows
for a frame of the cars, the player, the helicopter and the weapon, and for the tune, a note a call. The
collisions are tested in BASIC by comparing sprite coordinates. There is no frame sync: the game runs as fast as
the BASIC goes, measured at 1-1.5 frames a road row and about 12.4 frames a collision pass.

Bugs and oddities:

- The tune starts at its second note, and the last two notes of a pass are read from past the table (a very
  low note, then a very high one).
- The sprite copy at the start copies from source addresses 63 to 65 bytes apart; the rewrite uses the copied
  blocks.
- With the keyboard the smoke shows for at most a frame: only the joystick held down keeps it.
- The player stops only at exactly the kerbs' x. After a crash near the left kerb the car can drive off past it
  to x 0, and the next move left stops the program with ?ILLEGAL QUANTITY ERROR. The crash slide and the right
  curve's push can do the same.
- The high score table stops the program on a score equal to one in it. Its shift loses the 9th place and keeps
  the 10th, and a 10th place keeps the rest of the old name after the typed one ("AB" over "ZORRO" is
  "ABRRO").
- The city and the tunnel clear the whole screen, so the panel and the plan are gone until the next crash or
  bonus.
- The road doesn't follow the plan it draws: a curve that goes on to the country reads its choice again and goes
  into the tunnel, and from there on the road is a section behind the drawing. After the bonus, the section the
  road is in goes on by a choice the drawing never shows.
- The missile is tested against the helicopter once a collision pass, when it has moved 35-50 pixels since the
  last test, so it almost never hits the 15 pixel high window; a hit flashes too fast to see and the helicopter
  flies on.
- The guns' hits and the crashes are tested once a collision pass, about every 45 frames: a car can drive
  through the player between two, and the shorter gun fire mostly misses.
- The bridge's edge is tested twice a pass of the bridge, so a player could get across between two.
- F5 and F7 are read once a collision pass, so a short press is missed.

## Differences from the original

- Nothing of the loader: the sprites and the tune are in the PRG.
- Fixes:
  - The kerbs stop the player from any x, and a car past a kerb can only move back onto the road. The crash
    slide, the bonus slide and the curves stop at the screen's edges.
  - The city and the tunnel clear the road's rows 0-19 only, so the panel and the plan stay. In the tunnel the
    plan and the TRACK/PLAN labels are black on black. The tunnel's left walls on row 5 are yellow like the rest.
  - The tune plays its 76 notes from the first.
  - High scores: a new score goes below the scores it doesn't beat, so a tie is entered too; the entries below
    move down one, 10th place drops out. The name column is cleared before the input, and the spaces after the
    name are cut.
  - Smoke stays while ',' is held down, as with the joystick down.
  - The joystick reads each bit, so diagonals steer and fire at once, and fire works while steering.
  - The random numbers are seeded when a key or fire leaves the title (`rnd_seed`: the frame count and the
    raster line), so the first game after a start isn't always the same. The original never seeds `RND`.
  - The road follows the plan. A country section after a curve always starts with its first rows, and the city
    ends on its last pass.
  - The missile can hit the helicopter, tested at each step; a hit takes the missile and any falling bomb off
    and stops the helicopter, which flashes for 40 frames and is gone until the next country road.
  - The hits, the crashes and the bridge's edge are tested every frame. A crash is a car whose coloured pixels
    touch the player's (`shape_box`, the black outline left out), or the bomb's; an exploding car can't be hit
    again or crash.
- Gameplay changes:
  - The sections are 1.5 times as long (`ROAD_LENGTH`, `CURVE_LENGTH`, `BRIDGE_LENGTH` in game.h).
  - The road goes a row a frame with no time for the collision pass, so passes (spawns, the helicopter,
    sections) come about twice as often: the game is faster and harder.
  - The track plan, the title, the high scores and the bonus's points show at once.
  - Everything moves in the raster IRQ at a steady speed, in 8.8 fixed point, doubled with turbo: the cars 1
    pixel a frame down, the player 2, the helicopter and its bomb 1, the missile 1.5, the curve's push 1, the
    crash slide 2, the bonus car 2. The gun frames show 4 frames each. A landed bomb goes off the screen at once.
  - An exploding enemy car shows for 22 frames, then goes off the road.
  - The tune plays a note every 12 frames while it's on (`music_on`), stops during the crash and the F5 pause,
    and on the high score table plays while the name is typed. The crash's noise has 16 steps of 12 frames.
  - The explosion does a hard restart (the gate off and the envelope 0 for 2 frames) so the SID takes each as a
    new note.
  - F5 pauses on a key press and goes on at the next; F7 ends the game at the next collision pass.
  - The credit is written to row 23 every frame while the cars move.
  - On the bridge the player is the boat over the water (x 76-170) and the car on the bank and the road, every
    frame.
- The title, the instruction pages, the credits page and the high score table go on with a key or the
  joystick's fire button (pressed after the page is up); on the title fire starts the game. The prompts say
  "press fire to continue" and "press fire to start game".
- The controls page also shows the keys next to the joystick's directions.
- The name input: DEL rubs out the last character, no cursor keys, no "? " prompt, at most 8 characters.
- The high score table is in columns: the rank right-aligned to column 3, the name from column 5, the score
  right-aligned to column 25.
- The road tables draw a screen row a frame; the right curve's cell in column 39 comes a frame earlier.
