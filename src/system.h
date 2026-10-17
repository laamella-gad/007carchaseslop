// The C64 as the game uses it: screen, sprites, text, keys
#ifndef SYSTEM_H
#define SYSTEM_H

#include <c64/vic.h>
#include <c64/sid.h>
#include <c64/cia.h>

// VIC bank 0: the screen at $0400, the ROM character set
#define screen          ((volatile char *)0x0400)
#define colour_ram      ((volatile char *)0xd800)
#define sprite_pointers ((volatile char *)0x07f8)

// Sprite blocks, at $0a00-$0eff
#define SPR_GUNS            40      // 40-45: the gun fire, 44 and 45 empty
#define SPR_GUNS_END        45
#define SPR_MISSILE         46
#define SPR_SMOKE           47
#define SPR_BRIDGE_PLAYER   48
#define SPR_BRIDGE_ENEMY    49
#define SPR_HEADLIGHTS      50
#define SPR_BONUS_CAR       51
#define SPR_LOGO            52      // 52-54: "0", "0", "7"... the title logo
#define SPR_PLAYER          55
#define SPR_ENEMY           56
#define SPR_HELICOPTER      57
#define SPR_EXPLOSION       58
#define SPR_BOMB            59

// Key matrix codes of the key held down, in the KERNAL's LSTX
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

inline char last_key(void) { return *(volatile char *)0xc5; }

// Colours
#define BLACK       0
#define WHITE       1
#define RED         2
#define CYAN        3
#define GREEN       5
#define BLUE        6
#define YELLOW      7
#define BROWN       9
#define DARK_GREY   11
#define GREY        12
#define LIGHT_GREY  15

// PETSCII key codes
#define PET_RETURN  13
#define PET_DEL     0x14

// Written straight to the screen and colour RAM: the screen cleared to spaces,
// a PETSCII character at offset o, PETSCII text, a number
void screen_clear(char colour);
void char_at(unsigned o, char colour, char c);
void text_at(char row, char column, char colour, const char *s);
void number_at(char row, char column, char colour, long n);

// The next key in the keyboard buffer (GETIN), 0 if none
char get_key(void);

// A line typed at row, column, up to RETURN, at most max characters; DEL
// rubs out the last one
void input_line(char row, char column, char colour, char *s, char max);

// Waits for a key, or the joystick's fire button pressed
// after the wait starts (fire held from before doesn't count). The key, or ' '
// for fire
char wait_key(void);

// 0 to n-1
char rnd(char n);

#pragma compile("system.c")

#endif
