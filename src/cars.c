#include "cars.h"
#include "game.h"
#include "helper.h"
#include "sound.h"
#include "system.h"

// j1-j4: set to 1 when an enemy car explodes, counted down each collision pass.
// At 0 the explosion is taken off the road; the car can't crash into the player
// while it is 1 or more. Stops at -100 (a BASIC float never wraps)
static signed char explosion_timer[4];

void spawn_player(void)
{
	vic.spr_pos[0].x = 180;
	vic.spr_pos[0].y = 160;
	sprite_pointers[0] = player_sprite;
	vic.spr_color[0] = LIGHT_GREY;
	LINE(100);
}

static const char car_colours[3] = {RED, CYAN, GREEN};
static const unsigned long spawn_cycles[3] = {CYCLES_101, CYCLES_102, CYCLES_103};

void spawn_car(char car)
{
	vic.spr_pos[car].x = 180;
	vic.spr_pos[car].y = 80;
	sprite_pointers[car] = enemy_sprite;
	car_direction[car - 1] = rnd(5) + 1;
	vic.spr_color[car] = car_colours[car - 1];
	pace(spawn_cycles[car - 1]);
}

// Where the car from behind comes on, by direction
static const char car4_x[5] = {60, 108, 180, 252, 255};
static const char car4_y[5] = {200, 200, 200, 200, 160};
static const unsigned long car4_cycles[5] = {CYCLES_107, CYCLES_108, CYCLES_109, CYCLES_110, CYCLES_111};

static void car4_on(char direction)
{
	vic.spr_pos[4].x = car4_x[direction - 1];
	vic.spr_pos[4].y = car4_y[direction - 1];
	pace(car4_cycles[direction - 1]);
}

void spawn_car4(void)
{
	char direction = rnd(5) + 1;
	sprite_pointers[4] = player_sprite;
	car_direction[3] = direction;
	vic.spr_color[4] = rnd(10);
	LINE(105);
	LINE(106);
	car4_on(direction);
}

void spawn_helicopter(void)
{
	vic.spr_color[5] = LIGHT_GREY;
	sprite_pointers[5] = SPR_HELICOPTER;
	vic.spr_pos[5].x = 80;
	vic.spr_pos[5].y = 55;
	heli_state = 1;
	LINE(115);
}

static const unsigned long bridge_cycles[2] = {CYCLES_122, CYCLES_123};

void spawn_car_bridge(char car)
{
	// no colour: the car is still yellow from its explosion
	vic.spr_pos[car].x = 180;
	vic.spr_pos[car].y = 80;
	sprite_pointers[car] = enemy_sprite;
	car_direction[car - 1] = rnd(2) + 1;
	pace(bridge_cycles[car - 2]);
}

void spawn_car4_bridge(void)
{
	char direction = rnd(2) + 1;
	sprite_pointers[4] = player_sprite;
	car_direction[3] = direction;
	vic.spr_color[4] = rnd(10);
	LINE(125);
	LINE(126);
	car4_on(direction);
}

void helicopter_bomb(char x, unsigned long cycles)
{
	if (heli_state == 1 && vic.spr_pos[5].x < x)
		heli_state = rnd(2) + 1;
	pace(cycles);
}

// Lines 6000-6099
void crash_skid(void)
{
	// no tune during the crash (the original plays none), so it doesn't turn
	// the fading volume up again
	music_off();

	// Back and forth between the enemy car and the player's, 20 pixels left
	// each time, until the left side of the road. The original stops with
	// ?ILLEGAL QUANTITY when x goes below 0; here it stops at 0
	for (;;)
	{
		int x = vic.spr_pos[0].x - 10;
		vic.spr_pos[0].x = x < 0 ? 0 : x;
		sprite_pointers[0] = SPR_ENEMY;
		LINE(6000);
		frame_update();

		sound_explosion();
		x = vic.spr_pos[0].x - 10;
		vic.spr_pos[0].x = x < 0 ? 0 : x;
		sprite_pointers[0] = player_sprite;
		LINE(6001);
		if (vic.spr_pos[0].x <= 60)
			break;
	}

	// The player's car explodes, flashing yellow, with the noise fading out
	sprite_pointers[0] = SPR_EXPLOSION;
	for (signed char v = 15; v >= 0; v--)
	{
		LINE(6002);
		sound_crash(v);
		vic.spr_color[0] = YELLOW;
		LINE(6003);
		LINE(6004);
		frame_update();
		vic.spr_color[0] = LIGHT_GREY;
		sound_crash_off();
		LINE(6006);
	}

	sprite_pointers[0] = player_sprite;
	turbo = 0;
	LINE(6007);
	if (crashed == 1)
		return;

	lives--;
	crashed = 1;
	LINE(6008);
	if (lives < 0)
	{
		lives = -1;
		return;
	}

	print(t94);
	print_number(lives);
	put(PET_RETURN);
	LINE(6010);
	play_rows(rows_6011, 0, 2);
	LINE(6099);
}

// Line 5999
static void crash(void)
{
	LINE(5999);
	if (crashed == 1)
		return;
	crash_skid();
}

// Lines 12-19: an enemy car hit by the guns or the smoke
static const unsigned long hit_cycles[4] = {CYCLES_12, CYCLES_13, CYCLES_14, CYCLES_15};

void car_explode(char car)
{
	sprite_pointers[car] = SPR_EXPLOSION;
	explosion_timer[car - 1] = 1;
	vic.spr_color[car] = YELLOW;
	pace(hit_cycles[car - 1]);
	sound_explosion();
	score += (turbo + 1) * 50;
	LINE(18);
	LINE(19);
}

// Lines 20-35 (gosub20, 24, 28, 32): an enemy car level with the player
static const unsigned long car_cycles[4][4] = {
	{CYCLES_20, CYCLES_21, CYCLES_22, CYCLES_23},
	{CYCLES_24, CYCLES_25, CYCLES_26, CYCLES_27},
	{CYCLES_28, CYCLES_29, CYCLES_30, CYCLES_31},
	{CYCLES_32, CYCLES_33, CYCLES_34, CYCLES_35},
};

static void car_check(char car)
{
	const unsigned long *c = car_cycles[car - 1];
	char y = vic.spr_pos[car].y;

	pace(c[0]);
	if (y > 110 && y < 140 && weapon_state == WEAPON_GUNS)
	{
		car_explode(car);
		return;
	}
	pace(c[1]);
	if (y > 175 && y < 200 && weapon_state == WEAPON_SMOKE)
	{
		car_explode(car);
		return;
	}
	pace(c[2]);
	if (y > 140 && y < 180 && explosion_timer[car - 1] <= 0)
	{
		crash();
		return;
	}
	pace(c[3]);
}

// Lines 45-49: explosions off the road after one collision pass
static const unsigned long clear_cycles[4] = {CYCLES_45, CYCLES_46, CYCLES_47, CYCLES_48};

static void explosions_end(void)
{
	for (char car = 1; car <= 4; car++)
	{
		if (explosion_timer[car - 1] == 0 && sprite_pointers[car] == SPR_EXPLOSION)
		{
			car_direction[car - 1] = 0;
			vic.spr_pos[car].x = 0;
		}
		pace(clear_cycles[car - 1]);
	}
	LINE(49);
}

// Lines 36-38: the helicopter's bomb
// (x and the player's position are from line 5)
static void bomb_check(char x, int left, int right)
{
	char y = vic.spr_pos[6].y;

	LINE(36);
	if (x > left && x < right && y > 140 && y < 180)
	{
		crash();
		return;
	}
	if (y > 195)
		vic.spr_pos[6].y = 0;
	LINE(37);
	LINE(38);
}

// Lines 58-60: F5 pauses until F5 again
static void pause(void)
{
	// line 58: a delay so that the F5 that paused doesn't end the pause.
	// Not measured (the timing run never pauses): about 1350 cycles a loop
	music_off();
	pace(1001 * 1350ul);
	while (last_key() != KEY_F5)
		;
	pace_restart();
}

// Lines 51-57: F7, F5, and the missile hitting the helicopter
static void keys_and_helicopter(void)
{
	if (last_key() == KEY_F7)
		lives = -1;
	LINE(51);
	if (last_key() == KEY_F5)
		pause();
	LINE(52);

	char y = vic.spr_pos[7].y;
	LINE(53);
	if (!(y > 50 && y < 70))
	{
		LINE(54);
		return;
	}
	int x = vic.spr_pos[7].x, heli = vic.spr_pos[5].x;
	LINE(55);
	if (!(x > heli - 15 && x < heli + 15))
	{
		LINE(56);
		return;
	}
	// the helicopter flashes 5 times; it flies on
	for (char n = 0; n < 5; n++)
	{
		sprite_pointers[5] = SPR_EXPLOSION;
		sound_explosion();
		sprite_pointers[5] = SPR_HELICOPTER;
		pace(CYCLES_57 / 5);
	}
	score += 2000;
}

void collide(void)
{
	int x = vic.spr_pos[0].x;
	int left = x - 18, right = x + 18;
	char bomb_x = vic.spr_pos[6].x;
	LINE(5);

	for (char i = 0; i < 4; i++)
		if (explosion_timer[i] > -100)
			explosion_timer[i]--;
	explosions_end();
	LINE(6);

	// lines 6-9: each enemy car level with the player
	static const unsigned long level_cycles[3] = {CYCLES_7, CYCLES_8, CYCLES_9};
	for (char car = 1; car <= 4; car++)
	{
		int cx = vic.spr_pos[car].x;
		if (cx > left && cx < right)
			car_check(car);
		if (car < 4)
			pace(level_cycles[car - 1]);
	}

	LINE(10);
	if (bomb_x > 0)
		bomb_check(bomb_x, x - 10, x + 10);

	keys_and_helicopter();
	crashed = 0;
	print(t11);
	print_number(score);
	put(PET_RETURN);
	LINE(11);
}
