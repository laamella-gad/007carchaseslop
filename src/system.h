// The C64 as the game uses it: screen, sprites, a PETSCII printer, keys and pacing
#ifndef SYSTEM_H
#define SYSTEM_H

#include <c64/vic.h>
#include <c64/sid.h>
#include <c64/cia.h>

#define PEEK(a)         (*(volatile char *)(a))
#define POKE(a, v)      (*(volatile char *)(a) = (v))

// VIC bank 0 as in the original: the screen at $0400, the ROM character set
#define screen          ((volatile char *)0x0400)
#define colour_ram      ((volatile char *)0xd800)
#define sprite_pointers ((volatile char *)0x07f8)

// Sprite blocks. 40-54 are where the original has them ($0a00-$0dbf); the five
// it keeps at $0340 and $0840 follow at 55-59
#define SPR_GUNS            40      // 40-45: the gun fire, 44 and 45 empty
#define SPR_GUNS_END        45
#define SPR_MISSILE         46
#define SPR_SMOKE           47
#define SPR_BRIDGE_PLAYER   48
#define SPR_BRIDGE_ENEMY    49
#define SPR_HEADLIGHTS      50
#define SPR_BONUS_CAR       51
#define SPR_LOGO            52      // 52-54: "0", "0", "7"... the title logo
#define SPR_PLAYER          55      // 13 in the original
#define SPR_ENEMY           56      // 14
#define SPR_HELICOPTER      57      // 15
#define SPR_EXPLOSION       58      // 33
#define SPR_BOMB            59      // 34

// Key matrix codes in LSTX ($c5, BASIC's peek(197))
#define KEY_NONE    64
#define KEY_F7      3
#define KEY_F1      4
#define KEY_F3      5
#define KEY_F5      6
#define KEY_Z       0x0c
#define KEY_M       0x24
#define KEY_PERIOD  0x2c
#define KEY_COMMA   0x2f
#define KEY_SPACE   0x3c

inline char last_key(void) { return PEEK(0xc5); }

// Colours
#define BLACK       0
#define WHITE       1
#define RED         2
#define CYAN        3
#define GREEN       5
#define BLUE        6
#define YELLOW      7
#define DARK_GREY   11
#define GREY        12
#define LIGHT_GREY  15

// PETSCII control codes
#define PET_RETURN  13
#define PET_RIGHT   29

// Sets up the pacing timer and the printer
void system_init(void);

// Prints PETSCII like the KERNAL: colour codes, reverse, cursor moves, home, clear,
// return, and scrolling when the cursor goes past the bottom right. No logical
// lines (tools/c64time.c checks that it draws what the KERNAL draws in this game)
void put(char c);
void print(const char *s);

// BASIC's print of a number: a space or '-', the digits, then a cursor right
void print_number(long n);

// BASIC's ',' in print: on to the next 10 column zone
void print_comma(void);

// The cursor, colour and reverse, kept and put back around a print that comes
// between two rows that go on from each other
void print_save(void);
void print_restore(void);

// A PRINT rendered by tools/bas2c.py, written straight to the screen and colour
// RAM: spans of cells, then the cursor, colour and reverse after the PRINT
void print_cells(const char *cells);

// The next key in the keyboard buffer (GETIN), 0 if none
char get_key(void);

// BASIC's input: "? ", then a line typed at the cursor, up to RETURN. Like the
// screen editor it reads back the whole screen line, so what was on it after the
// typed text is part of the input. At most max characters
void input_line(char *s, char max);

// 0 to n-1
char rnd(char n);

// The original's speed: pace(c) waits until c cycles have passed since the last
// pace. The time comes from the measured BASIC lines (tools/c64time.c), so the
// work in between can take any time shorter than that
void pace(unsigned long cycles);

// Adds cycles to the time the next pace waits for, without waiting: for lines
// that show nothing, so their time goes before the next thing that shows
void spend(unsigned long cycles);

// Starts pacing from now, after waiting for a key
void pace_restart(void);

#pragma compile("system.c")

#endif
