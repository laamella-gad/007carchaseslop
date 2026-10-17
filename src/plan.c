#include "plan.h"
#include "game.h"
#include "helper.h"
#include "sound.h"
#include "system.h"

char plan_road;

// Lines 7400-7401: spaces over the plan area, columns 30-39 of rows 20-24
static void plan_clear(void)
{
	for (char y = 20; y < 25; y++)
		for (char x = 30; x < 40; x++)
			screen[x + 40 * y] = ' ';
}

void plan_clear_colours(void)
{
	// rows 18-24: also the bonus points above the plan
	for (char y = 18; y < 25; y++)
		for (char x = 30; x < 40; x++)
			colour_ram[x + 40 * y] = BLACK;
}

// The pieces of the plan by direction (dr: 1 up, 2 right, 3 down, 4 left).
// A straight piece keeps the direction, the curves turn it
typedef struct {
	char c, direction;
	signed char dx, dy;
} Piece;

static const Piece straight[4] = {
	{93, 1, 0, -1},
	{67, 2, 1, 0},
	{93, 3, 0, 1},
	{67, 4, -1, 0},
};

// after a left curve on the road
static const Piece turn_left[4] = {
	{85, 2, 1, 0},
	{73, 3, 0, 1},
	{75, 4, -1, 0},
	{74, 1, 0, -1},
};

// after a right curve
static const Piece turn_right[4] = {
	{75, 4, -1, 0},
	{75, 1, 0, -1},
	{74, 2, 1, 0},
	{85, 3, 0, 1},
};

void plan_new(void)
{
	for (char n = 1; n <= 6; n++)
	{
		plan[n] = rnd(3) + 1;
	}
	plan[7] = 6;
	plan_pos = 1;
	print(t7004);

	// the drawing starts at the bottom, going up, with the second section: the
	// plan is one section ahead of the road
	// int, not signed char: oscar64 1.32.271 (-O2) shortens the sign extension
	// of a signed char to int after placing its branch, which then jumps into
	// the middle of an instruction
	int x = 30, y = 24;
	char n = 1, direction = 1;
	plan_clear();
	for (char z1 = 30; z1 < 40; z1++)
		for (char z2 = 20; z2 < 25; z2++)
			colour_ram[z1 + 40 * z2] = BLACK;

	for (;;)
	{
		n++;
		if (plan[n] == 6)
			return;

		char next = plan[n];
		const Piece *pieces = straight;
		switch (plan_road)
		{
		case ROAD_COUNTRY:
			plan_road = next == 1 ? ROAD_TUNNEL : next == 2 ? ROAD_LEFT_CURVE : ROAD_BRIDGE;
			break;
		case ROAD_BRIDGE:
			// the bridge is drawn as a piece of its own: the next section is
			// the same plan entry again
			n--;
			plan_road = ROAD_COUNTRY;
			break;
		case ROAD_LEFT_CURVE:
			plan_road = next == 2 ? ROAD_RIGHT_CURVE : ROAD_COUNTRY;
			pieces = turn_left;
			break;
		case ROAD_RIGHT_CURVE:
			plan_road = next == 2 ? ROAD_LEFT_CURVE : ROAD_COUNTRY;
			pieces = turn_right;
			break;
		case ROAD_CITY:
			plan_road = next == 2 ? ROAD_TUNNEL : ROAD_COUNTRY;
			break;
		case ROAD_TUNNEL:
			plan_road = next == 1 ? ROAD_CITY : ROAD_COUNTRY;
			break;
		}

		const Piece *p = pieces + direction - 1;
		int o = x + 40 * y;
		if (o >= 0 && o < 1000)
			screen[o] = p->c;
		direction = p->direction;
		x += p->dx;
		y += p->dy;
	}
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

// n frames of the raster IRQ (counted up: oscar64 1.32.273 drops the exit test
// of a count down loop with a constant start)
static void wait_frames(char n)
{
	for (char i = 0; i < n; i++)
	{
		char f = frame_count;
		while (frame_count == f)
			;
	}
}

// Lines 13000-13099: the bonus car drives round the player's car with a siren.
// The moves and the siren are in the raster IRQ, a step a frame; the original
// steps them from BASIC, unevenly, at 1-7 pixels a frame (the pixels and frames of
// its measured loops are in the comments). The pause and the siren take half
// the original's time
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

	// the player to the left, a pixel for each x from 80 up to the player's
	// (to 79, or 1 left from below 80), the bonus car on in the middle. Line
	// 13010 wasn't measured per step: about 2750 cycles each, 7 pixels a frame
	sprite_pointers[1] = SPR_BONUS_CAR;
	vic.spr_color[1] = WHITE;
	// (stops at 0, where the original stops with ?ILLEGAL QUANTITY)
	char to = x >= 80 ? 79 : x ? x - 1 : 0;
	glide_wait(&vic.spr_pos[0].x, to);
	vic.spr_pos[1].x = 180;

	sound_siren_start();
	// line 13014: 324 frames
	sound_siren(162);
	while (siren_on)
		;
	sound_off();

	// down, right, up and back round the player
	vic.spr_pos[1].y = 200;
	glide_wait(&vic.spr_pos[1].y, 130);	// 13015: 71 pixels, 98 frames
	glide_wait(&vic.spr_pos[0].x, 180);	// 13016: 101, 108
	glide_wait(&vic.spr_pos[0].y, 140);	// 13017: 21, 25
	wait_frames(29);			// 13018: 58 frames
	glide_wait(&vic.spr_pos[0].y, 160);	// 13021: 21, 7
	glide_wait(&vic.spr_pos[0].x, 80);	// 13022: 101, 108
	glide_wait(&vic.spr_pos[1].y, 200);	// 13029: 71, 100
	vic.spr_pos[1].x = 0;
}

void bonus(void)
{
	// the cars and the player stay still for the animation
	motion_on = 0;
	bonus_animation();
	bonus_points += 1000;
	print(t7100);
	print_number(bonus_points);
	put(PET_RETURN);

	// the points go to the score in 20 steps, 2 frames each (the original's
	// lines 7101-7103 take 3.5)
	for (char i = 0; i < 20; i++)
	{
		wait_frames(2);
		score += bonus_points / 20;
		print(t11);
		print_number(score);
		put(PET_RETURN);
	}
	plan_new();
	crash_pending = 0;
	motion_on = 1;
}
