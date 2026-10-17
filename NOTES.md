# 007 Car Chase notes

"007 Car Chase", (c) 1985 Coplin Software: a James Bond style car chase for the C64. You drive down a road
made of country, city, tunnel, curve and bridge sections. You shoot enemy cars with guns or lay smoke behind you,
and you can shoot the helicopter with a missile. The original is a BASIC V2 program plus a small machine code
helper at $c000.

## Files

| File | What |
|---|---|
| `007CARCH.d64` | The disk: `007 car chase` (loader), `007.bas` (the game), `007` (the helper, $c000-$cfff) |
| `007.bas`, `07.bas` | The game as loaded at $1001, and its listing (`petcat -w2 -l 1001 -o 007.bas -- 07.bas` makes it again, byte for byte) |
| `007` | The helper as on the disk, load address $c000 |
| `007.vsf` | VICE snapshot taken during a game, the input for Deflower |
| `007.flo` | Deflower annotations: `deflower --verify 007.flo` writes `out/007.asm` (0 differ, 0 gaps) and the exports below |
| `out/sprites_13_15.bin` | Sprite blocks 13-15 ($0340-$03ff) |
| `out/sprites_33_34.bin` | Sprite blocks 33-34 ($0840-$08bf) |
| `out/sprites_40_54.bin` | Sprite blocks 40-54 ($0a00-$0dbf) |
| `out/tune_notes.bin` | The title tune's note table ($c800-$c8e3) |
| `out/007bas.prg` | The BASIC program, the same as `007.bas` |
| `007.prg`, `code.asm`, `1.bin`, `2.bin` | An older attempt: a WFDis paste that doesn't assemble, and a PRG with the sprite data one byte off. Not used (its Makefile was replaced by the rewrite's) |
| `src/` | The C rewrite for oscar64; `src/text.c` and `src/text.h` were made by `bas2c.py` (see Timing), now edited by hand |
| `tools/branchcheck.py` | Checks the oscar64 listing for branches into the middle of an instruction (`make` runs it) |
| `007carchase.prg` | The rewrite, crunched (`make`) |

## Loading

`007 car chase` at $0801 shows a title, does `poke44,16` (BASIC starts at $1001), and puts `LOAD"007.BAS",8` and
`RUN` in the keyboard buffer. Line 0 of `007.bas` loads `007` to $c000. Lines 2-4 copy the sprites (`gosub 8000`)
and set up. RUN again skips most of the copy, because `sprites_copied` ($cfd0) is 21 by then.

`007` on the disk and the snapshot's $c000-$cfff differ only in 5 variables: `tune_pos`, `sprites_copied` and three
car directions. The routines at $c6d4, $c738 and $cabc and the note table at $c800 are also in DATA lines
10000-10060. Lines 8019-8052 POKE them into place, with the same bytes as the file.

## Memory map

| Address | What |
|---|---|
| $0340-$03ff | Sprite blocks 13 player car, 14 enemy car, 15 helicopter |
| $0400-$07e7 | Screen (VIC bank 0, ROM charset) |
| $0800-$083f, $08c0-$09ff | Loader leftovers in blocks 32 and 35-39, never shown |
| $0840-$08bf | 33 explosion, 34 bomb |
| $0a00-$0b7f | 40-45 gun fire animation (44 and 45 are cleared: the flash ends) |
| $0b80-$0dbf | 46 missile, 47 smoke, 48/49 player/enemy car on the bridge, 50 headlights, 51 bonus car, 52-54 title logo |
| $1001-$9816 | BASIC program; variables after it, strings below $a000 |
| $c000-$c794 | Helper routines |
| $c7fe-$c7ff | `tune_loops`, `tune_pos` |
| $c800-$c8e3 | `tune_notes`: 76 notes of 3 bytes (freq hi, freq lo, SR) |
| $cabc-$cae0 | `title_scroll` |
| $cb20-$cf9d | `sprite_source`: the sprites before BASIC copies them into their blocks |
| $cfd0-$cfff | Shared with BASIC (below) |

All sprites are multicolour (`poke53276,255`), with shared colours 0 and 2.

## BASIC and helper

Shared variables:

| Address | Dec | Name | What |
|---|---|---|---|
| $cfd0 | 53200 | `sprites_copied` | 21 after the sprite copy |
| $cff0 | 53232 | `turbo` | 1 after F1, 0 after F3. Also a factor in the score: `(peek(53232)+1)*50` per car |
| $cff1 | 53233 | `headlights_on` | 1 in the tunnel: `headlights_follow` puts the headlights (sprite 5) at the player's x every frame. Line 846 does it too |
| $cff3 | 53235 | `crash_reset_on` | Never set by BASIC |
| $cff9-$cffb | 53241-3 | `car1..3_direction` | Enemy cars: 1-5 = direction, 0 = off the road (BASIC respawns them) |
| $cffc | 53244 | `car4_direction` | The car from behind, 1-5, 0 = gone |
| $cffd | 53245 | `heli_state` | 1 flying, 2 drop bomb, 3 bomb falling |
| $cffe | 53246 | `weapon_state` | 0 free, 1 guns, 2 missile, 3 smoke |

Entry points:

| SYS | Routine | What |
|---|---|---|
| 49152 | `turbo_frame` | A second `frame_update` if turbo is on, else nothing. Called between PRINT rows |
| 49155 | `frame_update` | One frame: keys, cars, F1/F3, car 4, helicopter, weapon |
| 49561 | `weapon_update` | Just the weapon |
| 50900 | `sound_explosion` | Noise on voice 1 |
| 51000 | `tune_play` | Next note of the tune, voice 2: on the title, and between the road rows of the tunnel and the curves |
| 51900 | `title_scroll` | Title logo sprites 0-3 left by 3 pixels |

BASIC patches the helper:
- Line 3 puts `jsr joystick_controls` at $c1de, and line 39 puts `rts` at $c1e1, at the end of `frame_extras`.
  `weapon_update` ends with `lda #5 : cmp weapon_state : beq rts : bne frame_extras`, so `frame_extras` runs on
  every `weapon_update` (states 0-3): `headlights_follow`, `crash_reset_check` (does nothing, `crash_reset_on` is
  0), `print_credit` and `joystick_controls`.
- Line 4 puts three `nop`s at $c015.
- Line 40 sets the y where the guns and the missile start ($c57c, $c5b2) to 120. They are already 120.

`frame_update` reads the keys from `last_key` ($c5): M right, Z left, SPACE guns, '.' missile, ',' smoke, F1 turbo,
F3 normal. BASIC reads F5 (pause) and F7 (restart) itself. `joystick_controls` reads the joystick in port 2 as
well: fire guns, up missile, down smoke, left, right (exact values, so no diagonals). Every move is a run of `inx`/`dex`: the player 10 pixels, the cars and
the helicopter 5, the slower car directions 2 or 3.

## The game (BASIC)

- 11000: title. The "007" logo is sprites 0-3 (pointers 52, 53, 53, 54), scrolled by `title_scroll` while
  `tune_play` plays the tune. 'i' shows the instructions (12000-12400).
- 7000: a new track. `cr(1..6)` are random section choices 1-3 and `cr(7)` = 6 is the end. They are drawn as a
  plan at the bottom right.
- Line 91: the panel (track, plan, cars, score). Lines 100-115 set up the sprites: the player at (180,160), enemy
  cars 1-3 at (180,80) with random directions, car 4 from below, and the helicopter at (80,55).
- Sections: each one PRINTs its road rows `d` times, with SYS calls between them. After a section, `cr()` picks
  the next one:

  | Section | Lines | d | cr=1 | cr=2 | cr=3 |
  |---|---|---|---|---|---|
  | Country | 188-251 | 10 | tunnel 500 | left curve 1000 | bridge 2100 |
  | City | 380-499 | 10 | country | tunnel | country |
  | Tunnel | 500-529, 780-850 | 10 | city | country | country |
  | Left curve | 1000-1060 | 3 | country | right curve | country |
  | Right curve | 1100-1160 | 3 | country | left curve | country |
  | Bridge | 2100-2250 | 30 | country | | |

  The country section says "bridge out on left" when the bridge is next. On the bridge, the player sails the
  water left of the road as a boat (sprite 48, the enemies 49); x 171-199, the edge between water and road,
  is a crash.
- `gosub 5`, each step: collisions are checked by comparing sprite coordinates.
  - An enemy within ±18 pixels in x is shot by the guns at y 110-140, or stopped by the smoke at y 175-200: 33
    explosion, `sound_explosion`, score `(turbo+1)*50`.
  - An enemy at y 140-180 is a crash: the car slides (5999/6000) and you lose one of 3 cars.
  - The bomb near the player is also a crash.
  - The missile at y 50-70 within ±15 of the helicopter scores 2000 (line 57).
- End of the track: bonus `bp += 1000` and the bonus animation (13000), then a new track (7100 → 7000).
- Out of cars: high score table (20000-20110, top 10 agents), then the title.
- Unused: line 9000 (a loader), lines 1300-1600 (test code).

## Bugs and oddities in the original

- **The tune's ends.** `tune_notes` holds (freq hi, freq lo, SR) per note. `tune_play` reads the 3 bytes after
  `tune_pos`, which starts at 2, so the tune starts at note 1, not 0. A pass ends at $e9, so the last two notes
  read 6 bytes past the table, from the power-on pattern at $c8e4 (a very low note with SR 0, then a very high
  one). After the first pass the tune loops from offset $5c (note 31), and after 3 loops it starts from the top.
- **Sprite copy offsets.** Lines 8000-8028 copy 63 bytes per sprite from `sprite_source`, but the source
  addresses are 63 to 65 bytes apart (52063 → 52127 → 52190 → 52255). The game shows what was copied, so the
  rewrite uses the copied blocks, not `sprite_source`.
- **Dead code.** `unused_smoke_follow` ($c5f3) and `unused_title_scroll` ($c6f9) are never called.
  `crash_reset_on` is never set, so `crash_reset_check` does nothing; `crash_reset` itself is reached from
  `player_left`/`player_right` at the kerbs, where x is never $b4, so it does nothing either.
- **Keyboard smoke.** ',' starts the smoke, but `smoke_follow` (weapon 3) ends it on the next `weapon_update`
  unless the joystick is held down. `unused_smoke_follow` tested the ',' key instead. With the keyboard the smoke
  shows for at most a frame, and `gosub 5` rarely sees weapon state 3.
- **The credit.** `print_credit` writes "(c) coplin software" to row 23 every frame, so the scrolling road
  can't wipe it out. Row 23 of the PRINTed road never shows in those columns.
- **?ILLEGAL QUANTITY.** `player_left` stops only at exactly x $50 (and `player_right` at $fa). Lines 6000/6001 (the
  crash slide) take 10 off while x > 60, so a crash near the left kerb leaves x at 50 or below; then 'Z' walks
  past $50 to 0, and the next `pokev,peek(v)-10` (6000) or `peek(v)-20` (1026, left curve) is negative: the
  game stops with ?ILLEGAL QUANTITY ERROR. Seen in the timing run (below) 15 times in 6000 s of random keys.
- **The high score table ENDs.** Lines 20002-20011 place a score with strict `>` and `<`. A score equal to one
  in the table falls through to line 20049, `end`.
- **The high score shift.** Line 20100 moves the entries down with `forn=9toxstep-1:sc(n)=sc(n-1)`, so the old
  9th place is lost and the old 10th stays. The input (20055) is on the new entry's row, and INPUT reads back
  the whole screen row: for a 10th place, line 20002 doesn't clear the old name, so its rest after the typed
  name becomes part of the new one (`left$` 8; "AB" over "ZORRO" is "ABRRO"). Short names keep the spaces up
  to 8 characters.
- **The panel goes.** The city (381) and the tunnel (794) start with `{clr}`, which erases the panel and the
  track plan. The score comes back with the next collision pass (line 11), CARS only after a crash (6010), and
  the TRACK/PLAN labels and the plan only at the next bonus.
- Line 235 tests `cr=1`, a plain variable that is always 0, next to the `cr(p)` tests: dead.
- The routines sit at round addresses with gaps of zeros between them. Some 3-byte instructions were cut to
  `rts nop nop` ($c154, $c187, $c193, $c1c6, $c1d2). $c1e2 still holds the operand of the instruction that was at
  $c1e1, `$c018`.

## Timing

The game has no frame sync: it runs as fast as BASIC goes, one `sys` of the helper between PRINTs. So the
rewrite takes its time from the original, line by line.

The road no longer uses these times; the rest of the game does. They were measured once with `tools/c64time.c`
and turned into `src/text.c`/`text.h` with `tools/bas2c.py`; both are deleted now and are in the git history up
to commit eb9235c. `c64time.c` (about 3.5 minutes) loaded `007.vsf` with the ROMs and emulated the CPU, the
KERNAL's 60 Hz IRQ and the keyboard. It held a random key (M, Z, space, '.', ',' or none) for 400000 cycles at
a time and put a key in the buffer where the game waits for one (space or 'I' at the title), for 20000
emulated seconds, without the joystick, and wrote `build/timing.txt`: per BASIC line
(CURLIN, $39/$3a) the number of passes and the average, minimum and maximum PAL cycles per pass, without the
time spent in the subroutines it calls (a line left with GOSUB, whose token $8d is on the stack, doesn't end a
pass). It restarted from the snapshot when the game stops: at READY after an error ($a474) and at the `end` in
line 20049. It also printed into a shadow of the screen with a simple PETSCII printer and compared it to the
real screen, which shows that the rewrite's printer (no logical lines) draws what the KERNAL draws.

A pass is from entering a line to leaving it, so a line that loops on itself (11070, a FOR loop in one line)
counts the whole loop as one pass. Those are divided by the number of loops in the rewrite: 11070 by the
title_scroll calls per wait (669 in 178 waits), 20058 by 77, the bonus lines 13012-13029 by their FOR counts.

`bas2c.py` wrote `CYCLES_<line>` for every line (0 for the lines the run never reached).
`pace(CYCLES_n)` in the C code waits until that much time has passed since the last pace: the target is
cumulative, so the C code can take any time up to the original's. CIA 2 timer A counts 256 cycles, timer B
counts its underflows. After a wait for a key, `pace_restart()` starts from now; when the C code is more than
2000 ticks (half a second) behind, the target catches up instead of rushing.

The road doesn't use the measured times: it goes a row a frame. `row_wait()` (game.c) waits for the next
frame of the raster IRQ (`frame_count`) before each road row, and the rest of the road code (the collision
pass, spawns, section tests) takes no time. The original takes 1-1.5 frames a row and about 12.4 frames for a
collision pass, about 2.5 frames a row on average (country 2.7, tunnel 2.35), so here the road scrolls at the
speed of the original's rows but without the stall of each pass. The crash waits for its animation in the
IRQ.

`LINES(a, b)` waits for the lines from a to b of the listing (from `SUM_<line>`, the cycles of all lines up to
it), `SPEND(a, b)` and `spend()` add their time without waiting. Only the start of a game (lines 39-43, in
`main.c`) still uses them.

Not measured, estimated: the pause delay (line 58, 1001 FOR loops at about 1350 cycles; not needed now, the
pause goes on a key press) and line 13010 (the player to the left before the bonus, about 2750 cycles a step,
7 pixels a frame).

## The rewrite

One file per part, each named after its BASIC lines in the comments:

| File | What | Lines |
|---|---|---|
| `main.c` | Memory layout, setup, the main loop | 2-4, 39-44 |
| `system.c` | PETSCII printer, keys, INPUT, pacing | the KERNAL |
| `helper.c` | The machine code helper: cars, keys, joystick, weapon, credit | $c000-$c6ff |
| `sound.c` | The explosion, the tune, the crash and the bonus siren | $c6d4, $c738, 6003, 13011 |
| `text.c` | (made) the PRINT strings and the row tables | all |
| `game.c` | The BASIC variables shared between the parts; playing back row tables | |
| `cars.c` | Spawns, the collision pass, explosions, the crash | 5-135, 5999-6099 |
| `road.c` | The panel and the sections: country, city, tunnel, curves, bridge | 91-98, 140-2250 |
| `plan.c` | The plan at the bottom right, the bonus | 7000-7500, 13000 |
| `title.c` | Title and instructions | 11000-12420 |
| `hiscore.c` | Top 10 | 20000-20110 |

Most of the road is lines that only `sys` into the helper and PRINT a string; `bas2c.py` turned each run of
them into a table of `{cells, tune}` (`rows_200` is lines 200-214) that `play_rows` plays back. The
helper calls other than the tune (`sys49152`, `49155`, `49561`) are left out: what they did is in the raster IRQ.
The other lines are written out in C; outside the road each is followed by its `LINE(n)` pace.

The tables' PRINTs were printed ahead: `bas2c.py` ran a copy of the printer on them and wrote each
row as the spans of screen codes and colours it leaves (`s200`; a `{clr}` is a clear), then the cursor, colour
and reverse after it. `play_rows` copies them into video memory (`print_cells`), so the tables' PETSCII strings
are left out. A colour or reverse a table uses before it sets one is the printer's at run time: the city's
houses take the colour line 400/419/450 printed, and the tunnel's line 800 the colour of the score after a
collision pass on `goto800` (the table is rendered from row 5 on as if played from there). Where the cursor is
must be known: the tables that print before homing it (391, 401, 451, 12020, 12101, 12112) start where the
PRINTs before them leave it, which `bas2c.py` printed too (`ENTRY`), and it refused a row that would scroll.

Memory: VIC bank 0 as in the original (screen $0400, ROM character set). The sprites are blocks 40-59 at
$0a00-$0eff: 40-54 where the original has them, and its blocks 13-15 and 33-34 (at $0340 and $0840) moved to
55-59. Code and data from $0f00 to $a000.

Compiler bug: oscar64 1.32.271 at `-O2` turned the sign extension `AND #$80 / BPL +2 / LDA #$ff / STA` into
`TYA` (Y was $ff) after placing the branch, so the `BPL` landed in the middle of the `STA`. That was in
`plan_new` with `signed char x, y`, and still happens with oscar64 at commit 2357b11 (October 2026); fixed in commit a92fd0c ("Fix size reduction breaking branch offset"). When a plan was drawn, the game ran into garbage and ended at READY. Those
variables are `int` now, and `make` runs `tools/branchcheck.py` on the listing, which fails the build if any
branch or jump misses an instruction start.

Differences from the original:

- Nothing of the loader: the helper's code is C, the sprites are in the PRG (no copy, no `sprites_copied`), the
  DATA lines are gone, and line 2's "wait for data transfer" isn't printed (only its clear and white).
- ?ILLEGAL QUANTITY: the crash slide (6000/6001) and the bonus (13010) stop x at 0 instead of stopping the
  program. The left curve's `-20` (1026, 1049) goes to 80 as the line meant.
- Phase 4 fixes:
  - The city and tunnel `{clr}` clear rows 0-19 only (`PANEL_KEPT` in `bas2c.py`: the 0xfd clear in `s381`, `s794`), so the panel and plan stay.
    In the tunnel the plan and the TRACK/PLAN labels are black on black, as they would be in the original.
  - The tunnel's left walls on row 5 are yellow like the rest (`INK_AT` in `bas2c.py`: yellow in `s800`, `s820`). Lines 800 and 820 print
    them before their `{yel}`, so in the original they take the score's white after each collision pass.
  - The tune plays its 76 notes from note 0, without the two notes from past the table.
  - High scores: a new score goes below the scores it doesn't beat, so a tie is entered too instead of `end`;
    the entries from there move down one, 10th place drops out. The name column of the entry is cleared before
    the input, and the spaces after the name are cut.
  - Smoke stays while ',' is held down, as with the joystick down.
  - The joystick reads each bit of $dc00 (`joystick()`), so diagonals steer and fire at once, and fire works
    while steering. The original compares $dc00 with one value per direction, so any two at once do nothing.
  - High score entry: the name can be typed at once, while the tune plays its 77 notes (`music_notes`, the
    volume off after the last). The original plays them first (line 20058, about 10 seconds) and only then
    takes INPUT. Return stops the tune.
  - The kerbs stop the player at or before $50 and $fa from any x, and a car past a kerb (after the crash
    slide) can only move back onto the road.
- Gameplay changes:
  - The sections are 1.5 times as long (`ROAD_LENGTH`, `CURVE_LENGTH`, `BRIDGE_LENGTH` in game.h): `d` goes to
    15 for the country, city and tunnel (10 in the original), 5 for the curves (3) and 45 for the bridge (30).
  - The road goes a row a frame (`row_wait`), with no time for the collision pass and the other lines
    between rows; the original takes 1-1.5 frames a row plus about 12.4 frames a pass. The road scrolls
    about as fast as the original's rows, but passes (spawns, the helicopter, sections) come about twice as
    often, so the game is faster and harder: a game has about 2.2 times the collision passes in the same time.
    The crash text needs no pace either (the crash waits for its animation).
  - The track plan takes no time: it shows at once, where the original draws it piece by piece (about 3
    seconds with the clearing of its area). The bonus has no measured line times either: the animation's
    moves all go at 2 pixels a frame (the original's loops take 1-7, the player's slide to the left the
    fastest), its pause (line 13018) and the siren take half the original's time, the lines between them
    none, and the points go to the score a step every 2 frames (3.5 in the original).
  - The high scores and the title take no time but the waits for keys (the credits page's delay loop, line
    12420, `forx=0to7000`, 8.4 seconds, is a wait for a key too): their screens show at once, where the original
    builds them up line by line (the title and the high score table in about 0.6 seconds each), and the
    tune and the logo start at once.
  - The tune plays from a raster IRQ (line 251), a note every 6 frames, where the original plays a note per
    `sys51000`, so at the speed of the BASIC around it: about 5.8 frames a note on the title, 6.6 on the high
    score table, slower and uneven during the game. `music_on()` stands where the original calls `sys51000`;
    the tune stops with `sound_off()`, during the crash (the original plays none there, and the IRQ would turn
    the fading volume up) and during the F5 pause. The IRQ goes to the KERNAL's for its CIA interrupt, so the
    keyboard scan stays at 60 Hz.
  - The missile can hit the helicopter. The original tests it once a collision pass (lines 53-57), when the
    missile has moved 35-50 pixels since the last test, so it almost never sees it in the 15 pixel high window
    (y 50-70); on a hit its 5 flashes take no frame between the shapes and can't be seen, and the helicopter
    flies on. Now `weapon_update` tests the same window at each 5 pixel step (only for a flying helicopter, not
    the tunnel's headlights). A hit takes the missile and any falling bomb off the screen and stops the
    helicopter; the raster IRQ flashes it for 40 frames, then it's gone until the next country road (or the
    plan's helicopter). The collision pass scores the 2000 and plays one explosion.
  - The missile moves in the raster IRQ, 1.5 pixels a frame (1 and 2 in turn), 3 with turbo, and stops during
    the F5 pause. The original moves it 5 pixels a `weapon_update`, which comes every 9.1 frames on average at
    the game's speed, anywhere from 1 to 70 (mostly 2-4, with long gaps during the collision pass and the
    PRINTs), so about 0.55 pixels a frame and jerky; turbo doubles the steps there too. The missile here is
    about 2.7 times as fast. The hit test goes with it into the IRQ.
  - The enemy cars and the player move in the raster IRQ (`cars_frame`), so at the same speed on every part of
    the road. The original moves them in `frame_update`, which comes every 19.8 frames on average (4 to 48):
    cars 5 pixels down (or up) and -5 to 5 across a step, the player 10 pixels a step with M and Z, and also a
    `weapon_update` step with the joystick. Here the cars move 1 pixel a frame down (5 pixels every 10
    frames, twice the original's average) with x in proportion, in 8.8 fixed point, and the player 2 pixels a
    frame with keys or joystick (the original: 0.5 with the keys, 1.1 with the joystick); turbo doubles both. The cars leave the road at
    y 200 or 160 (car 4 at 80) with `>=`/`<=` where the original tests the exact y. The headlights follow
    the player in the IRQ too. The IRQ moves nothing outside the road (`motion_on`: from `start()` to the
    game's end, off during the bonus), during the F5 pause (`motion_hold`), nor the player during the crash
    slide (`player_hold`; the original reads M and Z then too). The spawns set a car's direction to 0 first
    and last to the new one, so the IRQ never moves a half placed car.
  - The helicopter and its bomb move in the raster IRQ too (`heli_frame`), at the cars' speed (1 pixel a
    frame, doubled with turbo; the original: 5 pixels a `frame_update`). `helicopter_bomb` sets
    `bomb_request` where the original sets `heli_state` to 2, and the IRQ drops the bomb, so only the IRQ
    changes a flying helicopter's state; a hit stops the helicopter and takes its bomb in the IRQ as well. A
    landed bomb (y over 195) goes off the screen at once, where the original leaves it at y 200 until the
    collision pass (line 37) moves it. The original's bug that skips the helicopter while car 4 goes left 5
    is gone.
  - The weapon is in the raster IRQ too (`weapon_frame`): fire from the keys and the joystick, the gun frames
    (4 frames each, 2 with turbo; the original shows one a `weapon_update`, every 9.1 frames on average,
    mostly 2-4), and the smoke following the player while held. The hits on the enemy cars (lines 20-35:
    within 18 pixels of the player in x, y 110-140 for the guns, 175-200 for the smoke) go with it
    (`weapon_hits`): the original tests them once a collision pass, about every 45 frames, so the shorter
    gun fire would mostly miss it. The IRQ shows the explosion and sets `car_shot`; the next collision pass
    scores it and plays the sound (`shots()`, right after line 6), and a shot car
    isn't a crash meanwhile. A car that's already exploding can't be hit again; in the original the guns hit
    it again on the next pass, for another 50 points. A spawn clears the car's `car_shot`. The original's
    frame that ended early while car 4 goes left 5 is gone with `frame_update`.
  - The crashes are tested in the raster IRQ too (`crash_test`): an enemy car whose coloured pixels touch the
    player's (the box of each shape, black outline left out: `shape_box`) and that isn't exploding (the
    original: within 18 pixels in x at y 140-180, up to 4 pixels apart across and 13 along, and whose explosion
    timer is 0 or less), or the bomb, also by its coloured pixels (the original: its sprite x within 10 of the
    player's at y 140-180, off to the left, so a bomb 6 pixels left of the car hit and one over the car's
    right half missed). The original tests once a collision pass, about every 45 frames, so a car could
    drive through the player between two. The IRQ sets `crash_pending`; the main code runs the crash
    (`crash_check`) after each row `play_rows` prints and in the collision pass where the tests were. A
    crash after a row keeps the printer's cursor and colour (`print_save`, `print_restore`) for the next row,
    which goes on from where that one stopped; else the road prints from the crash text down and scrolls. The
    lines of the tests keep their time. No tests during the crash slide (`player_hold`), and `crash_pending`
    is cleared when the cars start moving (start of the game, after the bonus) and when they stop at the
    game's end; a crash only runs while they move.
  - The curves carry the player out smoothly, in the raster IRQ (`curve_drift`, `drift_frame`): 1 pixel a
    frame, left down to x 80 or right up to x 240, not during the crash slide. The original jumps the player
    20 pixels twice a pass of the curve loop (lines 1026/1049 and 1126/1156), about every 45 frames, so
    about 0.45 pixels a frame. Its right push works while x is below 240, so it can reach 259, where BASIC
    stops with `?ILLEGAL QUANTITY` (the C port wrapped it to the left edge); here it stops at 240.
  - The crash is in the raster IRQ (`crash_frame`); `skid` waits for it. The slide goes smoothly left at
    2 pixels a frame (the original: 20 pixels a pass of lines 6000-6001, about 1.2 pixels a frame), with the enemy
    car's shape and the noise for the first 10 pixels of each 20, until x 60. Then 16 steps of 12 frames
    (lines 6002-6006, about 24 frames a step in the original): the car yellow with the noise, volume 15 down to 0, and grey for the last 2 frames
    of each, with the gate off and the envelope at 0, so each step starts a new note. The original jumps 10
    pixels a line and paces the steps with BASIC.
  - An enemy car explodes for 22 frames from the hit, then the raster IRQ takes it off the road
    (`car_boom`, `booms_frame`). The original counts its explosion timer (`j1`-`j4`) down a collision pass
    and takes the car off at 0, so a shot car shows anywhere from 1 to about 90 frames. The timer is gone. The bridge's explosions start the same 22 frames, and a spawn clears them.
  - F1/F3 (turbo), F5 (pause) and F7 (end the game) are read in the raster IRQ (`keys_frame`) while the cars
    move. F5 pauses on a key press and goes on at the next press: no delay loop (line 58), and the main code
    stops at its next row or line (`row_wait` and `pace` wait during the pause) instead of at the collision pass. F7 sets
    `quit_request`, which the collision pass turns into the game's end where the original reads the key, so
    a short press isn't missed.
  - The credit is written to row 23 by the raster IRQ, every frame while the cars move (`print_credit`), so
    it's back right after the road scrolls it; the original writes it in `weapon_update`.
  - `sound_explosion` does a hard restart in the raster IRQ: the gate off and the envelope 0 for 2 frames,
    then the noise (the original turns the gate off and on at once, which the SID may not take as a new
    note), and without the original's volume 0 then 15.
  - The title's logo scrolls in the raster IRQ (`title_on`), at twice the original's average speed (3 pixels a
    pass of line 11070, a pass every 5.8 frames as measured, about 0.5 pixels a frame; here 264/256), smoothly.
  - The bonus animation's moves are in the raster IRQ (`glide`, `anim_frame`), one sprite coordinate at a
    time, all at one speed (`BONUS_SPEED`), in 8.8 fixed point; `bonus_animation` waits for each. The
    siren steps voice 1 to voice 3's sawtooth once a frame for half the time of line 13014 (162 frames),
    where the original takes 501 steps in 324 frames.
  - On the bridge the raster IRQ picks the player's shape every frame (`on_bridge`, `bridge_shape`): the boat
    (sprite 48) over the water, x 76-170, the car on the bank and the bridge's road. The original sets the
    boat once at line 2121, if x is below 180, and keeps it for the whole bridge.
  - The bridge's edge, x 171-199, is tested every frame in the raster IRQ (`bridge_edge`, in `crash_test`)
    from the first test at line 2216 to the end of the bridge, and goes through `crash_pending` like the
    other crashes. The original tests it twice a pass (lines 2216/2240), so a player could cross it between two.
- The title, the instruction pages and the high score table also go on with the joystick's fire button
  (pressed after the page is up, so fire held from the game doesn't skip it); on the title it starts the game,
  as a key other than 'I'. The credits page waits for a key or fire, where the original shows "please wait"
  for 8.4 seconds. The prompts say so: "press fire to continue" for "hit any key to continue" (lines 12034,
  12066, 12089, 12189, 20070) and "please wait" (12417), and "press fire to start game" for "or any other to
  start game" (11021); keys still work.
- The controls page (lines 12041-12066) also shows the keys next to the joystick's directions: SPACE guns,
  '.' missile, 'Z' left, 'M' right, ',' smoke.
- INPUT: DEL rubs out the last character instead of pulling the rest of the screen row left; no cursor keys;
  no "? " prompt, and at most the 8 characters the name keeps can be typed.
- The high score table is in columns: the rank 1-10 right-aligned to column 3, the name from column 5, the
  score right-aligned to column 25. The original prints `{rght}{rght}` name`,,`score (line 20051), so the
  score lands at column 20, or 30 after an 8 letter name.
- The high score and title screens are written straight to screen and colour RAM (`screen_clear`, `text_at`,
  in the colours the PRINTs give) instead of through the printer; the printer's cursor and colour are set after
  them (`print_at`, `print_set_ink`) for the name input and the rendered rows that follow.
- The printer has no logical lines (the game never links two rows).
