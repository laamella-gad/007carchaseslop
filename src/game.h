// The game's BASIC variables, and playing back the rows of text that draw the road
#ifndef GAME_H
#define GAME_H

#include "text.h"

// The time of BASIC line n in the original
#define LINE(n)     pace(CYCLES_##n)

extern long score;              // sc
extern long bonus_points;       // bp: 1000 more for each bonus
extern signed char lives;       // ch: -1 ends the game (no lives left, or F7)
extern char crashed;            // te: 1 after a crash, until the end of the collision pass
extern char player_sprite;      // p1: the player's car, also used for the car from behind
extern char enemy_sprite;       // p2
extern unsigned distance;       // d: road drawn in this section
extern char plan_pos;           // p: the section of the plan the road is in
extern char plan[11];           // cr(1-7): 1-3 where the road goes next, 6 the bonus

// Plays rows from to to-1 of a table from tools/bas2c.py: the helper calls of
// each line, its PRINT, and the line's time
void play_rows(const Row *rows, char from, char to);

#pragma compile("game.c")

#endif
