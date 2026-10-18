#include "plan.h"
#include "game.h"
#include "frame.h"
#include "sound.h"
#include "system.h"

char plan[PLAN_SIZE], plan_length, plan_pos;

void plan_clear_colours(void)
{
	// rows 18-24: also the bonus points above the plan
	for (char y = 18; y < 25; y++)
		for (char x = 30; x < 40; x++)
			colour_ram[x + 40 * y] = BLACK;
}

// The pieces of the plan by direction: up, right, down, left. A straight piece
// keeps the direction, the curves turn it
enum {UP, RIGHT, DOWN, LEFT};

typedef struct {
	char c, direction;
	signed char dx, dy;
} Piece;

static const Piece straight[4] = {
	{93, UP, 0, -1},
	{67, RIGHT, 1, 0},
	{93, DOWN, 0, 1},
	{67, LEFT, -1, 0},
};

// after a left curve on the road
static const Piece turn_left[4] = {
	{85, RIGHT, 1, 0},
	{73, DOWN, 0, 1},
	{75, LEFT, -1, 0},
	{74, UP, 0, -1},
};

// after a right curve
static const Piece turn_right[4] = {
	{75, LEFT, -1, 0},
	{75, UP, 0, -1},
	{74, RIGHT, 1, 0},
	{85, DOWN, 0, 1},
};

// The sections a section can go on to, picked at random. A bridge always goes
// on to the country
static const char roads_after[5][3] = {
	{ROAD_TUNNEL, ROAD_LEFT_CURVE, ROAD_BRIDGE},        // country
	{ROAD_COUNTRY, ROAD_TUNNEL, ROAD_COUNTRY},          // city
	{ROAD_CITY, ROAD_COUNTRY, ROAD_COUNTRY},            // tunnel
	{ROAD_COUNTRY, ROAD_RIGHT_CURVE, ROAD_COUNTRY},     // left curve
	{ROAD_COUNTRY, ROAD_LEFT_CURVE, ROAD_COUNTRY},      // right curve
};

// Five random steps from the section the road is in
#define PLAN_STEPS 5

void plan_new(char from)
{
	char n = 0;
	plan[0] = from;
	for (char i = 0; i < PLAN_STEPS; i++)
	{
		if (plan[n] == ROAD_BRIDGE)
		{
			plan[n + 1] = ROAD_COUNTRY;
			n++;
		}
		plan[n + 1] = roads_after[plan[n]][rnd(3)];
		n++;
	}
	if (plan[n] == ROAD_BRIDGE)
	{
		plan[n + 1] = ROAD_COUNTRY;
		n++;
	}
	plan_length = n + 1;
	plan_pos = 0;

	// the area, columns 30-39 of rows 20-24, cleared to black
	for (char y = 20; y < 25; y++)
		for (char x = 30; x < 40; x++)
		{
			screen[x + 40 * y] = ' ';
			colour_ram[x + 40 * y] = BLACK;
		}

	// drawn from the bottom, going up, a piece for each section but the last.
	// int, not signed char: oscar64 1.32.271 (-O2) shortens the sign extension
	// of a signed char to int after placing its branch, which then jumps into
	// the middle of an instruction
	int x = 30, y = 24;
	char direction = UP;

	for (char i = 0; i + 1 < plan_length; i++)
	{
		const Piece *pieces = straight;
		if (plan[i] == ROAD_LEFT_CURVE)
			pieces = turn_left;
		else if (plan[i] == ROAD_RIGHT_CURVE)
			pieces = turn_right;

		const Piece *p = pieces + direction;
		int o = x + 40 * y;
		if (o >= 0 && o < 1000)
			screen[o] = p->c;
		direction = p->direction;
		x += p->dx;
		y += p->dy;
	}
}

char plan_next(void)
{
	return plan_pos + 1 < plan_length ? plan[plan_pos + 1] : ROAD_NONE;
}

// The speed of all the bonus animation's moves, in 1/256 pixels a frame: 2
// pixels a frame
#define BONUS_SPEED	512

// One sprite coordinate to a value in the raster IRQ, smoothly
static void glide_wait(volatile char *reg, char to)
{
	glide(reg, to, BONUS_SPEED);
	while (glide_on)
		;
}

// n frames of the raster IRQ (counted up: oscar64 before cf1b548 drops the
// exit test of a count down loop with a constant start, issue #425)
static void wait_frames(char n)
{
	for (char i = 0; i < n; i++)
	{
		char f = frame_count;
		while (frame_count == f)
			;
	}
}

// The bonus car drives round the player's car with a siren. The moves and the
// siren are in the raster IRQ, a step a frame
static void bonus_animation(void)
{
	// all but the player off the screen
	for (char i = 1; i < 8; i++)
		vic.spr_pos[i].x = 0;
	sid.fmodevol = 15;
	vic.spr_pos[1].y = 0;
	for (char i = 0; i < 4; i++)
		car_direction[i] = 0;
	char x = vic.spr_pos[0].x;
	sound_off();
	tune_restart();

	// the player to the left (to 79, or 1 left from below 80), the bonus car on
	// in the middle
	sprite_pointers[1] = SPR_BONUS_CAR;
	vic.spr_color[1] = WHITE;
	char to = x >= 80 ? 79 : x ? x - 1 : 0;
	glide_wait(&vic.spr_pos[0].x, to);
	vic.spr_pos[1].x = 180;

	sound_siren_start();
	sound_siren(162);
	while (siren_on)
		;
	sound_off();

	// down, right, up and back round the player
	vic.spr_pos[1].y = 200;
	glide_wait(&vic.spr_pos[1].y, 130);
	glide_wait(&vic.spr_pos[0].x, 180);
	glide_wait(&vic.spr_pos[0].y, 140);
	wait_frames(29);
	glide_wait(&vic.spr_pos[0].y, 160);
	glide_wait(&vic.spr_pos[0].x, 80);
	glide_wait(&vic.spr_pos[1].y, 200);
	vic.spr_pos[1].x = 0;
}

void bonus(void)
{
	// the cars and the player stay still for the animation
	motion_on = 0;
	bonus_animation();
	bonus_points += 1000;
	text_at(8, 14, WHITE, "BONUS");
	number_at(8, 20, WHITE, bonus_points);

	// the points go to the score in 20 steps, 2 frames each
	for (char i = 0; i < 20; i++)
	{
		wait_frames(2);
		score += bonus_points / 20;
		show_score();
	}
	plan_new(plan[plan_pos]);
	crash_pending = 0;
	motion_on = 1;
}
