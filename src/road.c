#include "road.h"
#include "cars.h"
#include "game.h"
#include "frame.h"
#include "plan.h"
#include "sound.h"
#include "system.h"

// One more pass of a section: 1 when it has lasted length passes
static char section_done(unsigned length)
{
	if (++distance < length)
		return 0;
	distance = 0;
	return 1;
}

static void bonus_check(void)
{
	if (plan_pos + 1 == plan_length)
		bonus();
}

// Rows 0-19 cleared, the panel below stays
static void road_clear(char colour)
{
	for (unsigned i = 0; i < 20 * 40; i++)
	{
		screen[i] = ' ';
		colour_ram[i] = colour;
	}
}

static void colours(char back)
{
	vic.color_border = BLACK;
	vic.color_back = back;
}

// New enemy cars for the ones off the road
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

// "BRIDGE OUT ON LEFT" before the bridge, a row a frame
static void bridge_sign(void)
{
	if (plan_next() != ROAD_BRIDGE)
		return;
	row_wait();
	text_at(10, 2, WHITE, "BRIDGE OUT");
	row_wait();
	text_at(11, 2, WHITE, "ON LEFT   ");
}

// Each section returns 1 when the game is over, 0 at its end
static char country(void)
{
	colours(GREY);
	spawn_helicopter();
	headlights_on = 0;
	play_rows(country_start);
	player_sprite = SPR_PLAYER;
	enemy_sprite = SPR_ENEMY;
	sprite_pointers[0] = player_sprite;
	for (char i = 1; i < 4; i++)
		sprite_pointers[i] = enemy_sprite;
	sprite_pointers[4] = player_sprite;

	for (;;)
	{
		play_rows(country_a);
		music_on();
		bridge_sign();
		if (collide())
			return 1;

		play_rows(country_b);
		if (section_done(ROAD_LENGTH))
			return 0;
		bridge_sign();
		music_on();
		bonus_check();
		spawn_cars();
		helicopter_bomb(140);
		if (collide())
			return 1;
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

static char city(void)
{
	colours(GREY);
	headlights_on = 0;
	vic.spr_pos[5].x = 0;
	road_clear(WHITE);
	play_rows(city_top);
	play_rows(city_sides);
	// the two kinds of street lights take turns, and the three blocks of
	// houses change colour each time
	char lights = 0;
	char c1 = LIGHT_GREY, c2 = BROWN, c3 = RED;

	for (;;)
	{
		music_on();
		row_wait();
		chars_at(roofs_middle, 6, c1, 0xa6);
		play_rows_ink(city_a, c1);
		if (collide())
			return 1;

		music_on();
		play_rows_ink(city_b, c2);
		if (collide())
			return 1;

		row_wait();
		chars_at(roofs_sides, 6, c3, 0xa6);
		play_rows_ink(city_c, c3);
		row_wait();
		chars_at(lights_a, 5, WHITE, ' ');
		row_wait();
		chars_at(lights_b, 5, WHITE, ' ');
		row_wait();
		chars_at(lights ? lights_b : lights_a, 5, WHITE, 0xdd);
		if (collide())
			return 1;

		bonus_check();
		lights = !lights;
		if (section_done(ROAD_LENGTH))
			return 0;
		spawn_cars();
		helicopter_bomb(140);

		char c = c1;
		c1 = c3;
		c3 = c2;
		c2 = c;
	}
}

static char tunnel(void)
{
	// into the tunnel
	play_rows(tunnel_in);
	music_on();
	play_rows(tunnel_mouth);

	// the helicopter's sprite is the headlights now (it stops first, so the IRQ
	// leaves sprites 5 and 6 alone)
	heli_state = HELI_OFF;
	headlights_on = 1;
	vic.spr_pos[5].y = 140;
	sprite_pointers[5] = SPR_HEADLIGHTS;
	vic.spr_pos[6].x = 0;
	vic.spr_color[5] = YELLOW;
	colours(BLACK);
	road_clear(LIGHT_GREY);
	play_rows(tunnel_start);
	play_rows(tunnel_a);

	for (;;)
	{
		music_on();
		sprite_pointers[5] = SPR_HEADLIGHTS;
		if (collide())
			return 1;
		play_rows(tunnel_b);

		if (section_done(ROAD_LENGTH))
			return 0;
		bonus_check();
		music_on();
		sprite_pointers[5] = SPR_HEADLIGHTS;
		spawn_cars();
		vic.spr_pos[5].x = vic.spr_pos[0].x;
		if (collide())
			return 1;
		play_rows(tunnel_a);
	}
}

// The three rows of the curve, scrolled in the right curve
static char curve_rows[3][41];

static void curve_init(void)
{
	static const char rows[3][41] = {
		"    \xdf\xa9 \xdf\xa9     \xdf\xa9  \xdf\xa9     \xdf\xa9      \xdf\xa9  \xdf\xa9 ",
		"    \xce   \xcd     \xce   \xce       \xcd       \xcd  \xce  ",
		"   \xce         \xce             \xcd       \xcd    "};
	for (char i = 0; i < 3; i++)
		for (char j = 0; j < 41; j++)
			curve_rows[i][j] = rows[i][j];
}

// The rows 2 characters right
static void curve_scroll(void)
{
	for (char i = 0; i < 3; i++)
	{
		char *s = curve_rows[i];
		char a = s[38], b = s[39];
		for (char j = 39; j >= 2; j--)
			s[j] = s[j - 2];
		s[0] = a;
		s[1] = b;
	}
	for (char i = 0; i < 3; i++)
	{
		row_wait();
		text_at(2 + i, 0, BLUE, curve_rows[i]);
	}
}

// The player is carried out of the curve in the raster IRQ: curve_drift
static char curve(char left)
{
	colours(GREY);
	curve_init();
	curve_drift = left ? DRIFT_LEFT : DRIFT_RIGHT;
	play_rows(left ? left_curve_start : right_curve_start);

	for (;;)
	{
		play_rows(left ? left_curve_a : right_curve_a);
		music_on();
		if (collide())
			return 1;

		play_rows(left ? left_curve_b : right_curve_b);
		if (section_done(CURVE_LENGTH))
			return 0;
		bonus_check();
		if (!left)
			curve_scroll();
		spawn_cars();
		music_on();
		helicopter_bomb(140);
		if (collide())
			return 1;
	}
}

// Into the bridge's edge between x 170 and 200. The
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

static char bridge(void)
{
	play_rows(bridge_start);
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
		play_rows(bridge_a);
		collide();
		music_on();
		if (lives == -1)
		{
			bridge_end();
			return 1;
		}
		water();

		play_rows(bridge_b);
		if (section_done(BRIDGE_LENGTH))
		{
			bridge_end();
			return 0;
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
			return 1;
	}
}

// The panel, the cars and the helicopter
static void start(void)
{
	show_labels();
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

static char section(char road)
{
	// only the curves carry the player
	curve_drift = DRIFT_NONE;
	switch (road)
	{
	case ROAD_COUNTRY: return country();
	case ROAD_CITY: return city();
	case ROAD_TUNNEL: return tunnel();
	case ROAD_LEFT_CURVE: return curve(1);
	case ROAD_RIGHT_CURVE: return curve(0);
	default: return bridge();
	}
}

void game(void)
{
	start();
	while (!section(plan[plan_pos]))
		plan_pos++;
}
