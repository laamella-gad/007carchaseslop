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

// gosub5 in line a, then "if ch=-1 then 39", with the time up to line b
#define COLLIDE(a, b)   do { collide(); pace(SUM_##b - SUM_##a + CYCLES_##a); if (lives == -1) return NEXT_GAME_OVER; } while (0)

#define section_is(n)   (plan[plan_pos] == (n))

static void colours(char back)
{
	vic.color_border = BLACK;
	vic.color_back = back;
}

// Lines 242-245 and the like: new enemy cars for the ones off the road
static void spawn_cars(unsigned long c1, unsigned long c2, unsigned long c3, unsigned long c4)
{
	if (car_direction[0] == 0)
		spawn_car(1);
	pace(c1);
	if (car_direction[1] == 0)
		spawn_car(2);
	pace(c2);
	if (car_direction[2] == 0)
		spawn_car(3);
	pace(c3);
	if (car_direction[3] == 0)
		spawn_car4();
	pace(c4);
}

// Lines 188-251
static char country(char setup)
{
	if (setup)
	{
		colours(GREY);
		spawn_helicopter();
		headlights_on = 0;
		LINE(188);
		play_rows(rows_189, 0, 6);
		plan_pos++;
		LINE(195);
		player_sprite = SPR_PLAYER;
		enemy_sprite = SPR_ENEMY;
		sprite_pointers[0] = player_sprite;
		for (char i = 1; i < 4; i++)
			sprite_pointers[i] = enemy_sprite;
		LINE(196);
		sprite_pointers[4] = player_sprite;
		LINE(197);
	}

	for (;;)
	{
		play_rows(rows_200, 0, 15);
		// a sign before the bridge
		music_on();
		if (section_is(3))
		{
			print(t215);
			put(PET_RETURN);
		}
		LINE(215);
		if (section_is(3))
		{
			print(t216);
			put(PET_RETURN);
		}
		LINE(216);
		COLLIDE(217, 217);

		play_rows(rows_220, 0, 15);
		// line 235 also tests cr, not cr(p): never 1
		distance++;
		LINES(235, 238);
		if (distance == 10 && section_is(1))
		{
			distance = 0;
			return NEXT_TUNNEL;
		}
		if (distance == 10 && section_is(2))
		{
			distance = 0;
			return NEXT_LEFT_CURVE;
		}
		if (distance == 10 && section_is(3))
		{
			distance = 0;
			return NEXT_BRIDGE;
		}
		if (section_is(3))
		{
			print(t215);
			put(PET_RETURN);
		}
		LINE(239);
		music_on();
		if (section_is(3))
		{
			print(t216);
			put(PET_RETURN);
		}
		LINE(240);
		if (section_is(6))
			bonus();
		LINE(241);
		spawn_cars(CYCLES_242, CYCLES_243, CYCLES_244, CYCLES_245);
		helicopter_bomb(140, CYCLES_246);
		COLLIDE(250, 251);
	}
}

// Lines 380-499
static char city(void)
{
	colours(GREY);
	headlights_on = 0;
	vic.spr_pos[5].x = 0;
	LINE(380);
	play_rows(rows_381, 0, 7);
	plan_pos++;
	// the two kinds of street lights take turns
	signed char lights = 1;
	LINE(389);
	play_rows(rows_391, 0, 8);
	// the three blocks of houses change colour each time
	char c1 = 155, c2 = 149, c3 = 28;
	LINE(399);

	for (;;)
	{
		music_on();
		put(c1);
		put(PET_RETURN);
		print(t400);
		LINE(400);
		play_rows(rows_401, 0, 6);
		COLLIDE(407, 407);

		put(c2);
		put(PET_RETURN);
		music_on();
		LINE(419);
		play_rows(rows_420, 0, 15);
		COLLIDE(449, 449);

		put(c3);
		put(PET_RETURN);
		print(t450);
		LINE(450);
		play_rows(rows_451, 0, 21);
		if (lights == 1)
		{
			print(t472);
			put(PET_RETURN);
		}
		LINE(472);
		if (lights == -1)
		{
			print(t473);
			put(PET_RETURN);
		}
		LINE(473);
		COLLIDE(480, 480);

		if (section_is(6))
			bonus();
		LINES(485, 489);
		if (distance == 10 && section_is(3))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		lights = -lights;
		distance++;
		if (distance == 10 && section_is(1))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		if (distance == 10 && section_is(2))
		{
			distance = 0;
			return NEXT_TUNNEL;
		}
		spawn_cars(CYCLES_490, CYCLES_491, CYCLES_492, CYCLES_493);
		helicopter_bomb(140, CYCLES_494);

		// lines 497-499: the colours turn
		if (c1 == 155)
		{
			c1 = 28;
			c2 = 155;
			c3 = 149;
			LINE(497);
		}
		else if (c1 == 149)
		{
			c1 = 155;
			c2 = 149;
			c3 = 28;
			LINES(497, 498);
		}
		else
		{
			c1 = 149;
			c2 = 28;
			c3 = 155;
			LINES(497, 499);
		}
	}
}

// Lines 500-850
static char tunnel(void)
{
	// into the tunnel
	play_rows(rows_500, 0, 5);
	LINE(507);
	play_rows(rows_510, 0, 7);
	music_on();
	LINE(518);
	play_rows(rows_520, 0, 9);
	LINE(529);

	// the helicopter's sprite is the headlights now (it stops first, so the IRQ
	// leaves sprites 5 and 6 alone)
	heli_state = 0;
	headlights_on = 1;
	vic.spr_pos[5].y = 140;
	sprite_pointers[5] = SPR_HEADLIGHTS;
	vic.spr_pos[6].x = 0;
	vic.spr_color[5] = YELLOW;
	LINE(780);
	colours(BLACK);
	plan_pos++;
	LINES(790, 793);
	play_rows(rows_794, 0, 20);

	for (;;)
	{
		music_on();
		sprite_pointers[5] = SPR_HEADLIGHTS;
		LINE(815);
		COLLIDE(819, 819);
		play_rows(rows_820, 0, 15);

		distance++;
		LINES(835, 837);
		if (distance == 10 && section_is(1))
		{
			distance = 0;
			return NEXT_CITY;
		}
		if (distance == 10 && (section_is(2) || section_is(3)))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		if (section_is(6))
			bonus();
		music_on();
		sprite_pointers[5] = SPR_HEADLIGHTS;
		LINES(838, 840);
		spawn_cars(CYCLES_842, CYCLES_843, CYCLES_844, CYCLES_845);
		vic.spr_pos[5].x = vic.spr_pos[0].x;
		LINE(846);
		COLLIDE(847, 850);
		// goto800: the tunnel without its first rows
		play_rows(rows_794, 5, 20);
	}
}

// Lines 140-154: the three rows of the curve, scrolled in the right curve
static char curve[3][41];

static void curve_init(void)
{
	static const char *const rows[3] = {t140, t141, t142};
	for (char i = 0; i < 3; i++)
	{
		const char *s = rows[i];
		for (char j = 0; j < 40; j++)
			curve[i][j] = s[j];
		curve[i][40] = 0;
	}
	LINES(140, 144);
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
	LINES(150, 152);
	print(t148);
	for (char i = 0; i < 3; i++)
		print(curve[i]);
	put(PET_RETURN);
	LINES(153, 154);
}

// The player is carried out of the curve (lines 1026, 1049, 1126 and 1156) in
// the raster IRQ: curve_drift

// Lines 1000-1060
static char left_curve(void)
{
	colours(GREY);
	curve_init();
	curve_drift = DRIFT_LEFT;
	LINE(1000);
	play_rows(rows_1001, 0, 6);
	plan_pos++;
	LINE(1007);

	for (;;)
	{
		play_rows(rows_1010, 0, 15);
		music_on();
		LINES(1025, 1026);
		COLLIDE(1027, 1027);

		play_rows(rows_1030, 0, 15);
		distance++;
		LINES(1045, 1047);
		if (distance == 3 && section_is(1))
		{
			distance = 0;
			return NEXT_COUNTRY_ROAD;
		}
		if (distance == 3 && section_is(2))
		{
			distance = 0;
			return NEXT_RIGHT_CURVE;
		}
		if (distance == 3 && section_is(3))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		if (section_is(6))
			bonus();
		LINES(1048, 1049);
		if (section_is(6))
			bonus();
		LINE(1050);
		spawn_cars(CYCLES_1051, CYCLES_1052, CYCLES_1053, CYCLES_1054);
		music_on();
		helicopter_bomb(140, CYCLES_1055);
		COLLIDE(1056, 1060);
	}
}

// Lines 1100-1160
static char right_curve(void)
{
	colours(GREY);
	curve_init();
	curve_drift = DRIFT_RIGHT;
	LINE(1100);
	play_rows(rows_1101, 0, 6);
	plan_pos++;
	LINE(1107);

	for (;;)
	{
		play_rows(rows_1110, 0, 15);
		music_on();
		LINES(1125, 1126);
		COLLIDE(1127, 1127);

		play_rows(rows_1130, 0, 15);
		distance++;
		LINES(1145, 1147);
		if (distance == 3 && section_is(1))
		{
			distance = 0;
			return NEXT_COUNTRY_ROAD;
		}
		if (distance == 3 && section_is(2))
		{
			distance = 0;
			return NEXT_LEFT_CURVE;
		}
		if (distance == 3 && section_is(3))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		if (section_is(6))
			bonus();
		LINE(1148);
		curve_scroll();
		LINE(1149);
		if (section_is(6))
			bonus();
		LINE(1150);
		spawn_cars(CYCLES_1151, CYCLES_1152, CYCLES_1153, CYCLES_1154);
		music_on();
		helicopter_bomb(140, TIME(1155, 1156));
		COLLIDE(1157, 1160);
	}
}

// Into the bridge's edge between x 170 and 200: lines 2216 and 2240. The
// raster IRQ tests it every frame (crash_test) from the first of these on, so
// a player who comes onto the bridge there has the original's time to move
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
	LINE(2110);
	// the cars on the road blow up, for points
	for (char car = 1; car <= 4; car++)
		car_explode(car);
	LINE(2111);
	vic.spr_pos[1].x = 0;
	player_sprite = SPR_BRIDGE_PLAYER;
	enemy_sprite = SPR_BRIDGE_ENEMY;
	LINE(2120);
	// the IRQ gives the player the boat on the water (bridge_shape)
	on_bridge = 1;
	LINE(2121);

	for (;;)
	{
		play_rows(rows_2200, 0, 15);
		collide();
		music_on();
		LINE(2215);
		if (lives == -1)
		{
			bridge_end();
			return NEXT_GAME_OVER;
		}
		water();
		LINE(2216);

		play_rows(rows_2220, 0, 15);
		distance++;
		LINES(2235, 2239);
		if (distance == 30)
		{
			distance = 0;
			bridge_end();
			return NEXT_COUNTRY;
		}
		music_on();
		water();
		LINE(2240);
		// car 1 doesn't come back on the bridge
		if (car_direction[1] == 0)
			spawn_car_bridge(2);
		LINE(2243);
		if (car_direction[2] == 0)
			spawn_car_bridge(3);
		LINE(2244);
		if (car_direction[3] == 0)
			spawn_car4_bridge();
		LINE(2245);
		helicopter_bomb(180, CYCLES_2246);
		COLLIDE(2247, 2250);
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
	LINE(93);
	print(t94);
	print_number(lives);
	put(PET_RETURN);
	LINES(94, 95);

	for (char n = 1; n <= 6; n++)
	{
		LINE(96);
		switch (n)
		{
		case 1: spawn_player(); break;
		case 2: spawn_car(1); break;
		case 3: spawn_car(2); break;
		case 4: spawn_car(3); break;
		case 5: spawn_car4(); break;
		case 6: spawn_helicopter(); break;
		}
		LINE(97);
	}
	LINE(98);
	vic.spr_enable = 0xff;
	crash_pending = 0;
	quit_request = 0;
	// after a game that ended on the bridge (COLLIDE returns at once)
	on_bridge = 0;
	bridge_edge = 0;
	motion_on = 1;
	LINE(180);
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
