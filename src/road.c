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

// gosub5 at line n, then "if ch=-1 then 39"
#define COLLIDE(n)  do { collide(); pace(CYCLES_##n); if (lives == -1) return NEXT_GAME_OVER; } while (0)

#define section_is(n)   (plan[plan_pos] == (n))

static void colours(char back)
{
	vic.color_border = BLACK;
	vic.color_back = back;
}

// Lines 242-245 and the like: new enemy cars for the ones off the road. The
// weapon moves between the third and the fourth
static void spawn_cars(unsigned long c1, unsigned long c2, unsigned long c3, unsigned long c4, char weapon)
{
	if (car_direction[0] == 0)
		spawn_car(1);
	pace(c1);
	if (car_direction[1] == 0)
		spawn_car(2);
	pace(c2);
	if (weapon)
		weapon_update();
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
		heli_state = 1;
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
		frame_update();
		if (section_is(3))
		{
			print(t215);
			put(PET_RETURN);
		}
		LINE(215);
		turbo_frame();
		if (section_is(3))
		{
			print(t216);
			put(PET_RETURN);
		}
		LINE(216);
		weapon_update();
		COLLIDE(217);

		play_rows(rows_220, 0, 15);
		weapon_update();
		// line 235 also tests cr, not cr(p): never 1
		distance++;
		LINE(235);
		LINE(236);
		if (distance == 10 && section_is(1))
		{
			distance = 0;
			return NEXT_TUNNEL;
		}
		LINE(237);
		if (distance == 10 && section_is(2))
		{
			distance = 0;
			return NEXT_LEFT_CURVE;
		}
		weapon_update();
		LINE(238);
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
		frame_update();
		if (section_is(3))
		{
			print(t216);
			put(PET_RETURN);
		}
		LINE(240);
		if (section_is(6))
			bonus();
		LINE(241);
		spawn_cars(CYCLES_242, CYCLES_243, CYCLES_244, CYCLES_245, 1);
		helicopter_bomb(140, CYCLES_246);
		weapon_update();
		COLLIDE(250);
		LINE(251);
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
		COLLIDE(407);

		weapon_update();
		put(c2);
		put(PET_RETURN);
		music_on();
		LINE(419);
		play_rows(rows_420, 0, 15);
		COLLIDE(449);

		frame_update();
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
		weapon_update();
		if (lights == -1)
		{
			print(t473);
			put(PET_RETURN);
		}
		LINE(473);
		COLLIDE(480);

		if (section_is(6))
			bonus();
		LINE(485);
		weapon_update();
		LINE(486);
		if (distance == 10 && section_is(3))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		lights = -lights;
		LINE(487);
		distance++;
		LINE(488);
		if (distance == 10 && section_is(1))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		LINE(489);
		if (distance == 10 && section_is(2))
		{
			distance = 0;
			return NEXT_TUNNEL;
		}
		if (car_direction[0] == 0)
			spawn_car(1);
		LINE(490);
		weapon_update();
		if (car_direction[1] == 0)
			spawn_car(2);
		LINE(491);
		if (car_direction[2] == 0)
			spawn_car(3);
		LINE(492);
		if (car_direction[3] == 0)
			spawn_car4();
		LINE(493);
		helicopter_bomb(140, CYCLES_494);

		weapon_update();
		LINE(497);
		if (c1 == 155)
		{
			c1 = 28;
			c2 = 155;
			c3 = 149;
		}
		else
		{
			LINE(498);
			if (c1 == 149)
			{
				c1 = 155;
				c2 = 149;
				c3 = 28;
			}
			else
			{
				LINE(499);
				c1 = 149;
				c2 = 28;
				c3 = 155;
			}
		}
	}
}

// Lines 500-850
static char tunnel(void)
{
	// into the tunnel
	play_rows(rows_500, 0, 5);
	frame_update();
	LINE(507);
	play_rows(rows_510, 0, 7);
	music_on();
	frame_update();
	LINE(518);
	play_rows(rows_520, 0, 9);
	frame_update();
	LINE(529);

	// the helicopter's sprite is the headlights now
	headlights_on = 1;
	vic.spr_pos[5].y = 140;
	sprite_pointers[5] = SPR_HEADLIGHTS;
	heli_state = 0;
	vic.spr_pos[6].x = 0;
	vic.spr_color[5] = YELLOW;
	LINE(780);
	colours(BLACK);
	LINE(790);
	plan_pos++;
	LINE(793);
	play_rows(rows_794, 0, 20);

	for (;;)
	{
		weapon_update();
		music_on();
		sprite_pointers[5] = SPR_HEADLIGHTS;
		LINE(815);
		COLLIDE(819);
		play_rows(rows_820, 0, 15);

		weapon_update();
		distance++;
		LINE(835);
		if (distance == 10 && section_is(1))
		{
			distance = 0;
			return NEXT_CITY;
		}
		LINE(836);
		if (distance == 10 && section_is(2))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		LINE(837);
		if (distance == 10 && section_is(3))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		weapon_update();
		if (section_is(6))
			bonus();
		LINE(838);
		music_on();
		sprite_pointers[5] = SPR_HEADLIGHTS;
		LINE(840);
		frame_update();
		spawn_cars(CYCLES_842, CYCLES_843, CYCLES_844, CYCLES_845, 1);
		vic.spr_pos[5].x = vic.spr_pos[0].x;
		LINE(846);
		COLLIDE(847);
		LINE(850);
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
		pace(i == 0 ? CYCLES_140 : i == 1 ? CYCLES_141 : CYCLES_142);
	}
	LINE(144);
}

// gosub150: the rows 2 characters right
static void curve_scroll(void)
{
	static const unsigned long cycles[3] = {CYCLES_150, CYCLES_151, CYCLES_152};
	for (char i = 0; i < 3; i++)
	{
		char *s = curve[i];
		char a = s[38], b = s[39];
		for (char j = 39; j >= 2; j--)
			s[j] = s[j - 2];
		s[0] = a;
		s[1] = b;
		pace(cycles[i]);
	}
	print(t148);
	for (char i = 0; i < 3; i++)
		print(curve[i]);
	put(PET_RETURN);
	LINE(153);
	LINE(154);
}

// The player is carried out of the curve: lines 1026 and 1049
static void carried_left(void)
{
	int x = vic.spr_pos[0].x - 20;
	vic.spr_pos[0].x = x < 80 ? 80 : x;
}

// lines 1126 and 1156
static void carried_right(void)
{
	if (vic.spr_pos[0].x < 240)
		vic.spr_pos[0].x += 20;
}

// Lines 1000-1060
static char left_curve(void)
{
	colours(GREY);
	curve_init();
	LINE(1000);
	play_rows(rows_1001, 0, 6);
	plan_pos++;
	LINE(1007);

	for (;;)
	{
		play_rows(rows_1010, 0, 15);
		music_on();
		LINE(1025);
		carried_left();
		LINE(1026);
		weapon_update();
		COLLIDE(1027);

		play_rows(rows_1030, 0, 15);
		turbo_frame();
		distance++;
		LINE(1045);
		if (distance == 3 && section_is(1))
		{
			distance = 0;
			return NEXT_COUNTRY_ROAD;
		}
		LINE(1046);
		if (distance == 3 && section_is(2))
		{
			distance = 0;
			return NEXT_RIGHT_CURVE;
		}
		LINE(1047);
		if (distance == 3 && section_is(3))
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		if (section_is(6))
			bonus();
		LINE(1048);
		weapon_update();
		carried_left();
		LINE(1049);
		if (section_is(6))
			bonus();
		LINE(1050);
		frame_update();
		spawn_cars(CYCLES_1051, CYCLES_1052, CYCLES_1053, CYCLES_1054, 1);
		music_on();
		helicopter_bomb(140, CYCLES_1055);
		COLLIDE(1056);
		LINE(1060);
	}
}

// Lines 1100-1160
static char right_curve(void)
{
	colours(GREY);
	curve_init();
	LINE(1100);
	play_rows(rows_1101, 0, 6);
	plan_pos++;
	LINE(1107);

	for (;;)
	{
		play_rows(rows_1110, 0, 15);
		music_on();
		LINE(1125);
		carried_right();
		LINE(1126);
		COLLIDE(1127);

		play_rows(rows_1130, 0, 15);
		distance++;
		LINE(1145);
		if (distance == 3 && section_is(1))
		{
			distance = 0;
			return NEXT_COUNTRY_ROAD;
		}
		LINE(1146);
		if (distance == 3 && section_is(2))
		{
			distance = 0;
			return NEXT_LEFT_CURVE;
		}
		LINE(1147);
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
		frame_update();
		spawn_cars(CYCLES_1151, CYCLES_1152, CYCLES_1153, CYCLES_1154, 0);
		music_on();
		helicopter_bomb(140, CYCLES_1155);
		carried_right();
		LINE(1156);
		COLLIDE(1157);
		LINE(1160);
	}
}

// Into the water between x 170 and 200: lines 2216 and 2240
static void water(void)
{
	char x = vic.spr_pos[0].x;
	if (x > 170 && x < 200)
		crash_skid();
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
	if (vic.spr_pos[0].x < 180)
		sprite_pointers[0] = player_sprite;
	LINE(2121);

	for (;;)
	{
		play_rows(rows_2200, 0, 15);
		weapon_update();
		collide();
		music_on();
		LINE(2215);
		if (lives == -1)
			return NEXT_GAME_OVER;
		water();
		LINE(2216);

		play_rows(rows_2220, 0, 15);
		distance++;
		LINE(2235);
		if (distance == 30)
		{
			distance = 0;
			return NEXT_COUNTRY;
		}
		music_on();
		LINE(2239);
		water();
		LINE(2240);
		// car 1 doesn't come back on the bridge
		if (car_direction[1] == 0)
			spawn_car_bridge(2);
		LINE(2243);
		weapon_update();
		if (car_direction[2] == 0)
			spawn_car_bridge(3);
		LINE(2244);
		if (car_direction[3] == 0)
			spawn_car4_bridge();
		LINE(2245);
		helicopter_bomb(180, CYCLES_2246);
		weapon_update();
		COLLIDE(2247);
		LINE(2250);
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
	LINE(94);

	LINE(95);
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
	LINE(180);
}

void game(void)
{
	start();
	char next = NEXT_COUNTRY;
	for (;;)
	{
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
