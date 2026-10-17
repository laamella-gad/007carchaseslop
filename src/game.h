// The game's BASIC variables, and playing back the rows of text that draw the road
#ifndef GAME_H
#define GAME_H

#include "text.h"

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

// Plays a table of src/text.c, a row a frame, starting the tune where a row
// says so; ink for the spans marked INK (the city's houses). play_rows is a
// macro: as an inlined function oscar64 gave it a stack frame at each call that
// didn't balance, and the software stack crept into $a000
void play_rows_ink(const char *table, char ink);
#define play_rows(table) play_rows_ink(table, 0)

// A table at once, for a screen shown whole (title, instructions): no tune, no
// waits
void show_rows(const char *table);

// The panel: the TRACK and PLAN labels, the score, and the cars left
void show_labels(void);
void show_score(void);
void show_lives(void);

#pragma compile("game.c")

#endif
