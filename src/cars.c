#include "cars.h"
#include "game.h"
#include "helper.h"
#include "sound.h"
#include "system.h"

void spawn_player(void)
{
	vic.spr_pos[0].x = 180;
	vic.spr_pos[0].y = 160;
	sprite_pointers[0] = player_sprite;
	vic.spr_color[0] = LIGHT_GREY;
}

static const char car_colours[3] = {RED, CYAN, GREEN};

// The direction goes to 0 first and is set last, so the IRQ doesn't move a car
// that's half placed; a hit on the car before goes too

void spawn_car(char car)
{
	car_direction[car - 1] = 0;
	car_shot[car - 1] = 0;
	car_boom[car - 1] = 0;
	vic.spr_pos[car].x = 180;
	vic.spr_pos[car].y = 80;
	sprite_pointers[car] = enemy_sprite;
	car_direction[car - 1] = rnd(5) + 1;
	vic.spr_color[car] = car_colours[car - 1];
}

// Where the car from behind comes on, by direction
static const char car4_x[5] = {60, 108, 180, 252, 255};
static const char car4_y[5] = {200, 200, 200, 200, 160};

static void car4_on(char direction)
{
	vic.spr_pos[4].x = car4_x[direction - 1];
	vic.spr_pos[4].y = car4_y[direction - 1];
	car_direction[3] = direction;
}

void spawn_car4(void)
{
	char direction = rnd(5) + 1;
	car_direction[3] = 0;
	car_shot[3] = 0;
	car_boom[3] = 0;
	sprite_pointers[4] = player_sprite;
	vic.spr_color[4] = rnd(10);
	car4_on(direction);
}

void spawn_helicopter(void)
{
	// the state last, so the IRQ doesn't move a half placed helicopter
	heli_state = 0;
	vic.spr_color[5] = LIGHT_GREY;
	sprite_pointers[5] = SPR_HELICOPTER;
	vic.spr_pos[5].x = 80;
	vic.spr_pos[5].y = 55;
	heli_flash = 0;
	heli_hit = 0;
	bomb_request = 0;
	heli_state = 1;
}


void spawn_car_bridge(char car)
{
	// no colour: the car is still yellow from its explosion
	car_direction[car - 1] = 0;
	car_shot[car - 1] = 0;
	car_boom[car - 1] = 0;
	vic.spr_pos[car].x = 180;
	vic.spr_pos[car].y = 80;
	sprite_pointers[car] = enemy_sprite;
	car_direction[car - 1] = rnd(2) + 1;
}

void spawn_car4_bridge(void)
{
	char direction = rnd(2) + 1;
	car_direction[3] = 0;
	car_shot[3] = 0;
	car_boom[3] = 0;
	sprite_pointers[4] = player_sprite;
	vic.spr_color[4] = rnd(10);
	car4_on(direction);
}

void helicopter_bomb(char x)
{
	// the IRQ drops the bomb (the original sets heli_state to 2 here)
	if (heli_state == 1 && vic.spr_pos[5].x < x && rnd(2))
		bomb_request = 1;
}

// Lines 6000-6099
static void skid(void)
{
	// no tune during the crash (the original plays none), so it doesn't turn
	// the fading volume up again
	music_off();

	// Lines 6000-6006 in the raster IRQ (crash_frame), smoothly: back and forth
	// between the enemy car and the player's, 20 pixels left each time, until
	// the left side of the road, then the player's car explodes, flashing
	// yellow, with the noise fading out. The original jumps 10 pixels a line,
	// and stops with ?ILLEGAL QUANTITY when x goes below 0; here it stops at 0
	crash_anim = CRASH_SLIDE;
	while (crash_anim)
		;

	turbo = 0;
	if (crashed == 1)
		return;

	lives--;
	crashed = 1;
	if (lives < 0)
	{
		lives = -1;
		return;
	}

	show_lives();
	show_labels();
}

// The player can't steer during the slide (the original reads the keys in
// frame_update then too)
void crash_skid(void)
{
	player_hold = 1;
	skid();
	player_hold = 0;
}

// Line 5999
static void crash(void)
{
	if (crashed == 1)
		return;
	crash_skid();
}

// Only while the cars move: the crash runs in the raster IRQ then
void crash_check(void)
{
	if (crash_pending && motion_on)
	{
		crash_pending = 0;
		crash();
	}
}

// Lines 12-19: an enemy car hit by the guns or the smoke

void car_explode(char car)
{
	sprite_pointers[car] = SPR_EXPLOSION;
	// a car the weapon hit has its time from the hit
	if (!car_boom[car - 1])
		car_boom[car - 1] = CAR_BOOM_FRAMES;
	vic.spr_color[car] = YELLOW;
	sound_explosion();
	score += (turbo + 1) * 50;
}

// The cars the guns or the smoke hit since the last pass explode for points
static void shots(void)
{
	for (char car = 1; car <= 4; car++)
		if (car_shot[car - 1])
		{
			car_explode(car);
			car_shot[car - 1] = 0;
		}
}

// Lines 51-57: F7, F5, and the missile hitting the helicopter. F5 pauses in
// the raster IRQ (keys_frame, lines 58-60), F7 is read there too
static void keys_and_helicopter(void)
{
	if (quit_request)
		lives = -1;

	// The missile tests itself at each step (weapon_update); the original tests
	// it here and the helicopter flashes too fast to see and flies on. Now
	// the raster IRQ flashes it and it's gone until the next country road
	if (!heli_hit)
		return;
	heli_hit = 0;
	sound_explosion();
	score += 2000;
}

// The tests of the pass are in the raster IRQ: the guns and the smoke hit
// there (weapon_hits), the crashes too (crash_test), and it takes the
// explosions off (booms_frame). What's left takes no time. 1 at the game's end
char collide(void)
{
	shots();
	crash_check();
	keys_and_helicopter();
	crashed = 0;
	show_score();
	return lives == -1;
}
