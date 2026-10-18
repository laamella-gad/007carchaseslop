// The game's state, and playing back the rows of text that draw the road
#ifndef GAME_H
#define GAME_H

#include "text.h"

extern long score;
extern long bonus_points;       // 1000 more for each bonus
extern signed char lives;       // -1 ends the game (no lives left, or F7)
extern char crashed;            // 1 after a crash, until the end of the collision pass
extern char player_sprite;      // the player's car, also used for the car from behind
extern char enemy_sprite;
extern unsigned distance;       // passes of the section so far

// The passes a section lasts
#define ROAD_LENGTH     15      // country, city, tunnel
#define CURVE_LENGTH    5
#define BRIDGE_LENGTH   45

// Waits for the next row of the road: a row a frame
void row_wait(void);

// Plays a table of src/text.c, a line a frame; ink for the colour * (the city's
// houses)
void play_rows_ink(const Line *table, char ink);
void play_rows(const Line *table);

// A table at once, for a screen shown whole (title, instructions)
void show_rows(const Line *table);

// Once at the start, before the tables are drawn
void text_init(void);

// The panel: the TRACK and PLAN labels, the score, and the cars left
void show_labels(void);
void show_score(void);
void show_lives(void);

#pragma compile("game.c")

#endif
