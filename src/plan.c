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
	LINE(7400);
	LINE(7401);
}

void plan_clear_colours(void)
{
	// rows 18-24: also the bonus points above the plan
	for (char y = 18; y < 25; y++)
		for (char x = 30; x < 40; x++)
			colour_ram[x + 40 * y] = BLACK;
	LINE(7500);
}

// The pieces of the plan by direction (dr: 1 up, 2 right, 3 down, 4 left).
// A straight piece keeps the direction, the curves turn it
typedef struct {
	char c, direction;
	signed char dx, dy;
	unsigned long cycles;
} Piece;

static const Piece straight[4] = {
	{93, 1, 0, -1, CYCLES_7027},
	{67, 2, 1, 0, CYCLES_7028},
	{93, 3, 0, 1, CYCLES_7029},
	{67, 4, -1, 0, CYCLES_7030},
};

// after a left curve on the road
static const Piece turn_left[4] = {
	{85, 2, 1, 0, CYCLES_7070},
	{73, 3, 0, 1, CYCLES_7071},
	{75, 4, -1, 0, CYCLES_7072},
	{74, 1, 0, -1, CYCLES_7073},
};

// after a right curve
static const Piece turn_right[4] = {
	{75, 4, -1, 0, CYCLES_7090},
	{75, 1, 0, -1, CYCLES_7091},
	{74, 2, 1, 0, CYCLES_7092},
	{85, 3, 0, 1, CYCLES_7093},
};

// The tests of lines 7016-7021, in order
static const char road_tests[6] = {
	ROAD_COUNTRY, ROAD_BRIDGE, ROAD_LEFT_CURVE, ROAD_RIGHT_CURVE, ROAD_CITY, ROAD_TUNNEL
};
static const unsigned long test_cycles[6] = {
	CYCLES_7016, CYCLES_7017, CYCLES_7018, CYCLES_7019, CYCLES_7020, CYCLES_7021
};

void plan_new(void)
{
	LINE(7000);
	for (char n = 1; n <= 6; n++)
	{
		plan[n] = rnd(3) + 1;
		LINE(7002);
		LINE(7003);
	}
	plan[7] = 6;
	plan_pos = 1;
	print(t7004);
	LINE(7004);

	// the drawing starts at the bottom, going up, with the second section: the
	// plan is one section ahead of the road
	// int, not signed char: oscar64 1.32.271 (-O2) shortens the sign extension
	// of a signed char to int after placing its branch, which then jumps into
	// the middle of an instruction
	int x = 30, y = 24;
	char n = 1, direction = 1;
	LINE(7005);
	plan_clear();
	for (char z1 = 30; z1 < 40; z1++)
		for (char z2 = 20; z2 < 25; z2++)
			colour_ram[z1 + 40 * z2] = BLACK;
	LINE(7011);

	for (;;)
	{
		n++;
		LINE(7015);
		if (plan[n] == 6)
		{
			LINE(7300);
			return;
		}

		char i = 0;
		while (road_tests[i] != plan_road)
			pace(test_cycles[i++]);
		pace(test_cycles[i]);

		char next = plan[n];
		const Piece *pieces = straight;
		switch (plan_road)
		{
		case ROAD_COUNTRY:
			LINE(7040);
			LINE(7041);
			LINE(7042);
			plan_road = next == 1 ? ROAD_TUNNEL : next == 2 ? ROAD_LEFT_CURVE : ROAD_BRIDGE;
			LINE(7045);
			LINE(7046);
			break;
		case ROAD_BRIDGE:
			// the bridge is drawn as a piece of its own: the next section is
			// the same plan entry again
			n--;
			plan_road = ROAD_COUNTRY;
			LINE(7060);
			break;
		case ROAD_LEFT_CURVE:
			LINE(7065);
			LINE(7066);
			LINE(7067);
			plan_road = next == 2 ? ROAD_RIGHT_CURVE : ROAD_COUNTRY;
			LINE(7075);
			LINE(7076);
			pieces = turn_left;
			break;
		case ROAD_RIGHT_CURVE:
			LINE(7085);
			LINE(7086);
			LINE(7087);
			plan_road = next == 2 ? ROAD_LEFT_CURVE : ROAD_COUNTRY;
			LINE(7095);
			LINE(7096);
			pieces = turn_right;
			break;
		case ROAD_CITY:
			LINE(7035);
			LINE(7036);
			plan_road = next == 2 ? ROAD_TUNNEL : ROAD_COUNTRY;
			LINE(7037);
			break;
		case ROAD_TUNNEL:
			LINE(7022);
			LINE(7023);
			LINE(7024);
			plan_road = next == 1 ? ROAD_CITY : ROAD_COUNTRY;
			LINE(7025);
			LINE(7026);
			break;
		}

		const Piece *p = pieces + direction - 1;
		int o = x + 40 * y;
		if (o >= 0 && o < 1000)
			screen[o] = p->c;
		direction = p->direction;
		x += p->dx;
		y += p->dy;
		pace(p->cycles);
	}
}

// One sprite coordinate to a value in the raster IRQ, smoothly, at twice the
// speed the original's loop of steps took; then on with the time from here
static void glide_wait(volatile char *reg, char to, char px, unsigned long cycles)
{
	glide(reg, to, PX_SPEED(2 * px, cycles));
	while (glide_on)
		;
	pace_restart();
}

// Lines 13000-13099: the bonus car drives round the player's car with a siren.
// The moves and the siren are in the raster IRQ, a step a frame; the original
// steps them from BASIC, unevenly
static void bonus_animation(void)
{
	// all but the player off the screen
	for (char i = 1; i < 8; i++)
		vic.spr_pos[i].x = 0;
	sid.fmodevol = 15;
	vic.spr_pos[1].y = 0;
	LINE(13000);
	for (char i = 0; i < 4; i++)
		car_direction[i] = 0;
	char x = vic.spr_pos[0].x;
	LINE(13001);
	sound_off();
	tune_restart();
	LINE(13002);

	// the player to the left, a pixel for each x from 80 up to the player's
	// (to 79, or 1 left from below 80), the bonus car on in the middle. The
	// time wasn't measured per step: about 2750 cycles each
	sprite_pointers[1] = SPR_BONUS_CAR;
	vic.spr_color[1] = WHITE;
	// (stops at 0, where the original stops with ?ILLEGAL QUANTITY)
	char to = x >= 80 ? 79 : x ? x - 1 : 0;
	glide_wait(&vic.spr_pos[0].x, to, 1, 2750);
	vic.spr_pos[1].x = 180;
	pace(30000);
	LINE(13011);

	sound_siren_start();
	LINE(13012);
	LINE(13013);
	// half the time of the original
	sound_siren((unsigned)(CYCLES_13014 / FRAME_CYCLES / 2));
	while (siren_on)
		;
	pace_restart();
	sound_off();

	// down, right, up and back round the player
	vic.spr_pos[1].y = 200;
	glide_wait(&vic.spr_pos[1].y, 130, 71, CYCLES_13015);
	glide_wait(&vic.spr_pos[0].x, 180, 101, CYCLES_13016);
	glide_wait(&vic.spr_pos[0].y, 140, 21, CYCLES_13017);
	LINE(13018);
	glide_wait(&vic.spr_pos[0].y, 160, 21, CYCLES_13021);
	glide_wait(&vic.spr_pos[0].x, 80, 101, CYCLES_13022);
	glide_wait(&vic.spr_pos[1].y, 200, 71, CYCLES_13029);
	vic.spr_pos[1].x = 0;
	LINE(13030);
	LINE(13099);
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
	LINE(7100);

	// the points go to the score in 20 steps
	for (char i = 0; i < 20; i++)
	{
		LINE(7101);
		score += bonus_points / 20;
		print(t11);
		print_number(score);
		put(PET_RETURN);
		LINE(7102);
		LINE(7103);
	}
	LINE(7104);
	plan_new();
	crash_pending = 0;
	motion_on = 1;
}
