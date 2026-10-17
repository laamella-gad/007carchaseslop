// The game's BASIC variables, and playing back the rows of text that draw the road
#ifndef GAME_H
#define GAME_H

#include "text.h"

// The time of BASIC line n in the original
#define LINE(n)     pace(CYCLES_##n)

// The time of lines a to b, all the lines in between in the listing (each
// pastes on its own: oscar64 can't paste in a macro inside a macro)
#define TIME(a, b)  (SUM_##b - SUM_##a + CYCLES_##a)
#define LINES(a, b) pace(SUM_##b - SUM_##a + CYCLES_##a)
#define SPEND(a, b) spend(SUM_##b - SUM_##a + CYCLES_##a)

extern long score;              // sc
extern long bonus_points;       // bp: 1000 more for each bonus
extern signed char lives;       // ch: -1 ends the game (no lives left, or F7)
extern char crashed;            // te: 1 after a crash, until the end of the collision pass
extern char player_sprite;      // p1: the player's car, also used for the car from behind
extern char enemy_sprite;       // p2
extern unsigned distance;       // d: road drawn in this section

// The passes of d a section lasts, 1.5 times the original's (10, 3 and 30;
// a curve 5 for 4.5)
#define ROAD_LENGTH     15      // country, city, tunnel
#define CURVE_LENGTH    5
#define BRIDGE_LENGTH   45
extern char plan_pos;           // p: the section of the plan the road is in
extern char plan[11];           // cr(1-7): 1-3 where the road goes next, 6 the bonus

// Waits for the next row of the road: a row a frame
void row_wait(void);

// Plays rows from to to-1 of a table from tools/bas2c.py: the tune if the line
// plays it, then its PRINT, a row a frame
void play_rows(const Row *rows, char from, char to);

#pragma compile("game.c")

#endif
