#include "road.h"
#include "cars.h"
#include "game.h"
#include "helper.h"
#include "plan.h"
#include "sound.h"
#include "system.h"

// Where each section goes on to: the line it jumps to
enum Next {
	NEXT_COUNTRY,       // 188
	NEXT_COUNTRY_ROAD,  // 200: the country loop, from a curve
	NEXT_CITY,          // 380
	NEXT_TUNNEL,        // 500
	NEXT_LEFT_CURVE,    // 1000
	NEXT_RIGHT_CURVE,   // 1100
	NEXT_BRIDGE,        // 2100
	NEXT_GAME_OVER      // 39
};

#define section_is(n)   (plan[plan_pos] == (n))

static void colours(char back)
{
	vic.color_border = BLACK;
	vic.color_back = back;
}

// Lines 242-245 and the like: new enemy cars for the ones off the road
static void spawn_cars(void)
{
	if (car_direction[0] == 0)
		spawn_car(1);
	if (car_direction[1] == 0)
		spawn_car(2);
	if (car_direction[2] == 0)
		spawn_car(3);
	if (car_direction[3] == 0)
		spawn_car4();
}

// Lines 188-251
static char country(char setup)
{
	if (setup)
	{
		colours(GREY);
		spawn_helicopter();
		headlights_on = 0;
		play_rows(rows_189, 0, 6);
		plan_pos++;
		player_sprite = SPR_PLAYER;
		enemy_sprite = SPR_ENEMY;
		sprite_pointers[0] = player_sprite;
		for (char i = 1; i < 4; i++)
			sprite_pointers[i] = enemy_sprite;
		sprite_pointers[4] = player_sprite;
	}

	for (;;)
	{
		play_rows(rows_200, 0, 15);
		// a sign before the bridge
		music_on();
		if (section_is(3))
		{
			row_wait();
			text_at(10, 2, WHITE, "BRIDGE OUT");
		}
		if (section_is(3))
		{
			row_wait();
			text_at(11, 2, WHITE, "ON LEFT   ");
		}
		if (collide())
			return NEXT_GAME_OVER;

		play_rows(rows_220, 0, 15);
		// line 235 also tests cr, not cr(p): never 1
		distance++;
		if (distance == ROAD_LENGTH && section_is(1))
		{
			distance = 0;
			return NEXT_TUNNEL;
		}
		if (distance == ROAD_LENGTH && section_is(2))
		{
			distance = 0;
			return NEXT_LEFT_CURVE;
		}
		if (distance == ROAD_LENGTH && section_is(3))
		{
			distance = 0;
			return NEXT_BRIDGE;
		}
		if (section_is(3))
		{
			row_wait();
			text_at(10, 2, WHITE, "BRIDGE OUT");
		}
		music_on();
		if (section_is(3))
		{
			row_wait();
			text_at(11, 2, WHITE, "ON LEFT   ");
		}
		if (section_is(6))
			bonus();
		spawn_cars();
		helicopter_bomb(140);
		if (collide())
			return NEXT_GAME_OVER;
	}
}

// The roofs over the houses, and the street lights
static const unsigned roofs_middle[6] = {15, 16, 18, 23, 24, 26};
static const unsigned roofs_sides[6] = {0, 1, 2, 37, 38, 39};
static const unsigned lights_a[5] = {5 * 40 + 21, 7 * 40 + 21, 10 * 40 + 21, 14 * 40 + 21, 19 * 40 + 21};
static const unsigned lights_b[5] = {3 * 40 + 21, 5 * 40 + 21, 8 * 40 + 21, 12 * 40 + 21, 17 * 40 + 21};

static void chars_at(const unsigned *at, char n, char colour, char c)
{
	for (char i = 0; i < n; i++)
		char_at(at[i], colour, c);
}

// Lines 380-499
static char city(void)
{
	colours(GREY);
	headlights_on = 0;
	vic.spr_pos[5].x = 0;
	play_rows(rows_381, 0, 7);
	plan_pos++;
	// the two kinds of street lights take turns
	signed char lights = 1;
	play_rows(rows_391, 0, 8);
	// the three blocks of houses change colour each time
	char c1 = LIGHT_GREY, c2 = BROWN, c3 = RED;

	for (;;)
	{
		music_on();
		row_wait();
		chars_at(roofs_middle, 6, c1, 0xa6);
		play_rows_ink(rows_401, 0, 6, c1);
		if (collide())
			return NEXT_GAME_OVER;

		music_on();
		play_rows_ink(rows_420, 0, 15, c2);
		if (collide())
			return NEXT_GAME_OVER;

		row_wait();
		chars_at(roofs_sides, 6, c3, 0xa6);
		play_rows_ink(rows_451, 0, 21, c3);
		if (lights == 1)
		{
			row_wait();
			chars_at(lights_a, 5, WHITE, 0xdd);
		}
		if (lights == -1)
		{
			row_wait();
			chars_at(lights_b, 5, WHITE, 0xdd);
		}
		if (collide())
			return NEXT_GAME_OVER;

		if (section_is(6))
			bonus();
		if (distance == ROAD_LENGTH && section_is(3))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		lights = -lights;
		distance++;
		if (distance == ROAD_LENGTH && section_is(1))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		if (distance == ROAD_LENGTH && section_is(2))
		{
			distance = 0;
			return NEXT_TUNNEL;
		}
		spawn_cars();
		helicopter_bomb(140);

		// lines 497-499: the colours turn
		char c = c1;
		c1 = c3;
		c3 = c2;
		c2 = c;
	}
}

// Lines 500-850
static char tunnel(void)
{
	// into the tunnel
	play_rows(rows_500, 0, 5);
	play_rows(rows_510, 0, 7);
	music_on();
	play_rows(rows_520, 0, 9);

	// the helicopter's sprite is the headlights now (it stops first, so the IRQ
	// leaves sprites 5 and 6 alone)
	heli_state = 0;
	headlights_on = 1;
	vic.spr_pos[5].y = 140;
	sprite_pointers[5] = SPR_HEADLIGHTS;
	vic.spr_pos[6].x = 0;
	vic.spr_color[5] = YELLOW;
	colours(BLACK);
	plan_pos++;
	play_rows(rows_794, 0, 20);

	for (;;)
	{
		music_on();
		sprite_pointers[5] = SPR_HEADLIGHTS;
		if (collide())
			return NEXT_GAME_OVER;
		play_rows(rows_820, 0, 15);

		distance++;
		if (distance == ROAD_LENGTH && section_is(1))
		{
			distance = 0;
			return NEXT_CITY;
		}
		if (distance == ROAD_LENGTH && (section_is(2) || section_is(3)))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		if (section_is(6))
			bonus();
		music_on();
		sprite_pointers[5] = SPR_HEADLIGHTS;
		spawn_cars();
		vic.spr_pos[5].x = vic.spr_pos[0].x;
		if (collide())
			return NEXT_GAME_OVER;
		// goto800: the tunnel without its first rows
		play_rows(rows_794, 5, 20);
	}
}

// Lines 140-154: the three rows of the curve, scrolled in the right curve
static char curve[3][41];

static void curve_init(void)
{
	static const char rows[3][41] = {
		"    \xdf\xa9 \xdf\xa9     \xdf\xa9  \xdf\xa9     \xdf\xa9      \xdf\xa9  \xdf\xa9 ",
		"    \xce   \xcd     \xce   \xce       \xcd       \xcd  \xce  ",
		"   \xce         \xce             \xcd       \xcd    "};
	for (char i = 0; i < 3; i++)
		for (char j = 0; j < 41; j++)
			curve[i][j] = rows[i][j];
}

// gosub150: the rows 2 characters right
static void curve_scroll(void)
{
	for (char i = 0; i < 3; i++)
	{
		char *s = curve[i];
		char a = s[38], b = s[39];
		for (char j = 39; j >= 2; j--)
			s[j] = s[j - 2];
		s[0] = a;
		s[1] = b;
	}
	for (char i = 0; i < 3; i++)
	{
		row_wait();
		text_at(2 + i, 0, BLUE, curve[i]);
	}
}

// The player is carried out of the curve (lines 1026, 1049, 1126 and 1156) in
// the raster IRQ: curve_drift

// Lines 1000-1060
static char left_curve(void)
{
	colours(GREY);
	curve_init();
	curve_drift = DRIFT_LEFT;
	play_rows(rows_1001, 0, 6);
	plan_pos++;

	for (;;)
	{
		play_rows(rows_1010, 0, 15);
		music_on();
		if (collide())
			return NEXT_GAME_OVER;

		play_rows(rows_1030, 0, 15);
		distance++;
		if (distance == CURVE_LENGTH && section_is(1))
		{
			distance = 0;
			return NEXT_COUNTRY_ROAD;
		}
		if (distance == CURVE_LENGTH && section_is(2))
		{
			distance = 0;
			return NEXT_RIGHT_CURVE;
		}
		if (distance == CURVE_LENGTH && section_is(3))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		if (section_is(6))
			bonus();
		if (section_is(6))
			bonus();
		spawn_cars();
		music_on();
		helicopter_bomb(140);
		if (collide())
			return NEXT_GAME_OVER;
	}
}

// Lines 1100-1160
static char right_curve(void)
{
	colours(GREY);
	curve_init();
	curve_drift = DRIFT_RIGHT;
	play_rows(rows_1101, 0, 6);
	plan_pos++;

	for (;;)
	{
		play_rows(rows_1110, 0, 15);
		music_on();
		if (collide())
			return NEXT_GAME_OVER;

		play_rows(rows_1130, 0, 15);
		distance++;
		if (distance == CURVE_LENGTH && section_is(1))
		{
			distance = 0;
			return NEXT_COUNTRY_ROAD;
		}
		if (distance == CURVE_LENGTH && section_is(2))
		{
			distance = 0;
			return NEXT_LEFT_CURVE;
		}
		if (distance == CURVE_LENGTH && section_is(3))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		if (section_is(6))
			bonus();
		curve_scroll();
		if (section_is(6))
			bonus();
		spawn_cars();
		music_on();
		helicopter_bomb(140);
		if (collide())
			return NEXT_GAME_OVER;
	}
}

// Into the bridge's edge between x 170 and 200: lines 2216 and 2240. The
// raster IRQ tests it every frame (crash_test) from the first of these to the
// bridge's end
static void water(void)
{
	bridge_edge = 1;
}

static void bridge_end(void)
{
	on_bridge = 0;
	bridge_edge = 0;
}

// Lines 2100-2250
static char bridge(void)
{
	play_rows(rows_2100, 0, 5);
	colours(GREY);
	// the cars on the road blow up, for points
	for (char car = 1; car <= 4; car++)
		car_explode(car);
	vic.spr_pos[1].x = 0;
	player_sprite = SPR_BRIDGE_PLAYER;
	enemy_sprite = SPR_BRIDGE_ENEMY;
	// the IRQ gives the player the boat on the water (bridge_shape)
	on_bridge = 1;

	for (;;)
	{
		play_rows(rows_2200, 0, 15);
		collide();
		music_on();
		if (lives == -1)
		{
			bridge_end();
			return NEXT_GAME_OVER;
		}
		water();

		play_rows(rows_2220, 0, 15);
		distance++;
		if (distance == BRIDGE_LENGTH)
		{
			distance = 0;
			bridge_end();
			return NEXT_COUNTRY;
		}
		music_on();
		water();
		// car 1 doesn't come back on the bridge
		if (car_direction[1] == 0)
			spawn_car_bridge(2);
		if (car_direction[2] == 0)
			spawn_car_bridge(3);
		if (car_direction[3] == 0)
			spawn_car4_bridge();
		helicopter_bomb(180);
		if (collide())
			return NEXT_GAME_OVER;
	}
}

// Lines 91-98 and 180: the panel, the cars and the helicopter
static void start(void)
{
	play_rows(rows_91, 0, 2);
	for (char i = 0; i < 21; i++)
		colour_ram[23 * 40 + 5 + i] = YELLOW;
	vic.spr_mcolor0 = BLACK;
	vic.spr_mcolor1 = RED;
	show_lives();

	for (char n = 1; n <= 6; n++)
	{
		switch (n)
		{
		case 1: spawn_player(); break;
		case 2: spawn_car(1); break;
		case 3: spawn_car(2); break;
		case 4: spawn_car(3); break;
		case 5: spawn_car4(); break;
		case 6: spawn_helicopter(); break;
		}
	}
	vic.spr_enable = 0xff;
	crash_pending = 0;
	quit_request = 0;
	// after a game that ended on the bridge (COLLIDE returns at once)
	on_bridge = 0;
	bridge_edge = 0;
	motion_on = 1;
}

void game(void)
{
	start();
	char next = NEXT_COUNTRY;
	for (;;)
	{
		// only the curves carry the player
		curve_drift = DRIFT_NONE;
		switch (next)
		{
		case NEXT_COUNTRY: next = country(1); break;
		case NEXT_COUNTRY_ROAD: next = country(0); break;
		case NEXT_CITY: next = city(); break;
		case NEXT_TUNNEL: next = tunnel(); break;
		case NEXT_LEFT_CURVE: next = left_curve(); break;
		case NEXT_RIGHT_CURVE: next = right_curve(); break;
		case NEXT_BRIDGE: next = bridge(); break;
		default: return;
		}
	}
}
