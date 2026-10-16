#include "helper.h"
#include "system.h"

char turbo, headlights_on, heli_state, weapon_state;
char heli_hit;
volatile char heli_flash;
char car_direction[4];

// Joystick in port 2 as $dc00 reads it after the KERNAL's key scan; only one
// direction or fire at a time counts
#define JOY_FIRE    0x6f
#define JOY_UP      0x7e
#define JOY_DOWN    0x7d
#define JOY_LEFT    0x7b
#define JOY_RIGHT   0x77

#define GUNS_Y      120     // line 40 pokes it into fire_guns and fire_missile
#define SMOKE_Y     180

// The helicopter's explosion: frames of the flash, explosion and helicopter
// shapes switching every 4
#define HELI_FLASH_FRAMES   40

// The player stops at the kerbs. The original stops only at exactly these x,
// so from an x past a kerb (after the crash slide) the car walks off the road
#define KERB_LEFT   0x50
#define KERB_RIGHT  0xfa

// The player is sprite 0, the enemy cars 1-3, the car from behind 4, the
// helicopter (or the headlights) 5, the bomb 6, the weapon 7

static void player_right(void)
{
	// the original jumps to crash_reset here, which does nothing unless x is $b4
	char x = vic.spr_pos[0].x;
	if (x < KERB_RIGHT)
		vic.spr_pos[0].x = x < KERB_RIGHT - 10 ? x + 10 : KERB_RIGHT;
}

static void player_left(void)
{
	char x = vic.spr_pos[0].x;
	if (x > KERB_LEFT)
		vic.spr_pos[0].x = x > KERB_LEFT + 10 ? x - 10 : KERB_LEFT;
}

static void fire_guns(void)
{
	if (weapon_state == WEAPON_FREE)
	{
		sprite_pointers[7] = SPR_GUNS;
		vic.spr_pos[7].x = vic.spr_pos[0].x;
		vic.spr_pos[7].y = GUNS_Y;
		weapon_state = WEAPON_GUNS;
	}
}

static void fire_missile(void)
{
	if (weapon_state == WEAPON_FREE)
	{
		weapon_state = WEAPON_MISSILE;
		vic.spr_pos[7].x = vic.spr_pos[0].x;
		vic.spr_pos[7].y = GUNS_Y;
		sprite_pointers[7] = SPR_MISSILE;
	}
}

static void fire_smoke(void)
{
	if (weapon_state == WEAPON_FREE)
	{
		sprite_pointers[7] = SPR_SMOKE;
		vic.spr_pos[7].x = vic.spr_pos[0].x;
		vic.spr_pos[7].y = SMOKE_Y;
		weapon_state = WEAPON_SMOKE;
	}
}

// x steps of the enemy cars 1-3 by direction; car 1 has its own order
static const signed char car1_dx[6] = {0, -2, 0, 2, 5, -5};
static const signed char car_dx[6] = {0, -5, -3, 0, 3, 5};
// car 4 comes from behind
static const signed char car4_dx[6] = {0, 5, 3, 0, -3, -5};

// An enemy car down 5 pixels; off the road at y 200, or 160 when it goes right 5
static void car_down(char car, signed char dx)
{
	vic.spr_pos[car].x += dx;
	vic.spr_pos[car].y += 5;
	if (vic.spr_pos[car].y == (dx == 5 ? 160 : 200))
		car_direction[car - 1] = 0;
}

static void turbo_keys(void)
{
	if (last_key() == KEY_F1)
		turbo = 1;
	if (last_key() == KEY_F3)
		turbo = 0;
}

static void headlights_follow(void)
{
	if (headlights_on == 1)
		vic.spr_pos[5].x = vic.spr_pos[0].x;
}

static void print_credit(void)
{
	// "(c) coplin software" in screen codes on row 23, every frame
	static const char credit[] = {
		0x28, 0x03, 0x29, 0x00, 0x03, 0x0f, 0x10, 0x0c, 0x09, 0x0e,
		0x00, 0x13, 0x0f, 0x06, 0x14, 0x17, 0x01, 0x12, 0x05,
	};
	for (char i = 0; i < sizeof(credit); i++)
		if (credit[i])
			screen[23 * 40 + 5 + i] = credit[i];
}

static void joystick_controls(void)
{
	if (cia1.pra == JOY_FIRE)
		fire_guns();
	if (cia1.pra == JOY_UP)
		fire_missile();
	if (cia1.pra == JOY_DOWN)
		fire_smoke();
	if (cia1.pra == JOY_LEFT)
		player_left();
	if (cia1.pra == JOY_RIGHT)
		player_right();
}

// The missile against the helicopter at each 5 pixel step. The original tests
// only once a collision pass, when the missile has moved 35-50 pixels since the
// last one, so it almost never finds it in the 15 pixel high window
static void missile_hit(void)
{
	char y = vic.spr_pos[7].y;
	if (!(y > 50 && y < 70))
		return;
	// not the headlights in the tunnel, nor a helicopter that's exploding
	if (heli_state < 1 || heli_state > 3 || sprite_pointers[5] != SPR_HELICOPTER)
		return;
	int x = vic.spr_pos[7].x, heli = vic.spr_pos[5].x;
	if (!(x > heli - 15 && x < heli + 15))
		return;

	// the missile is gone, the helicopter stops and explodes, its bomb with it
	vic.spr_pos[7].x = 0;
	vic.spr_pos[7].y = 0;
	weapon_state = WEAPON_FREE;
	heli_state = 0;
	vic.spr_pos[6].x = 0;
	vic.spr_pos[6].y = 0;
	heli_hit = 1;
	heli_flash = HELI_FLASH_FRAMES;
}

__interrupt void heli_flash_frame(void)
{
	if (!heli_flash)
		return;
	// the tunnel's headlights take over sprite 5
	if (headlights_on)
	{
		heli_flash = 0;
		return;
	}
	heli_flash--;
	if (heli_flash)
		sprite_pointers[5] = heli_flash & 4 ? SPR_EXPLOSION : SPR_HELICOPTER;
	else
	{
		// off the screen until the next country road
		vic.spr_pos[5].x = 0;
		sprite_pointers[5] = SPR_HELICOPTER;
	}
}

void weapon_update(void)
{
	if (weapon_state == WEAPON_GUNS)
	{
		// the next gun frame, up to the empty one
		if (sprite_pointers[7] == SPR_GUNS_END)
			weapon_state = WEAPON_FREE;
		else
			sprite_pointers[7]++;
	}
	if (weapon_state == WEAPON_MISSILE)
	{
		vic.spr_pos[7].y -= 5;
		if (vic.spr_pos[7].y == 0)
			weapon_state = WEAPON_FREE;
		else
			missile_hit();
	}
	if (weapon_state == WEAPON_SMOKE)
	{
		// the smoke stays while the joystick is held down, or the ',' key (the
		// original tests only the joystick, so smoke from the key ends on the
		// next frame)
		vic.spr_pos[7].x = vic.spr_pos[0].x;
		if (cia1.pra != JOY_DOWN && last_key() != KEY_COMMA)
		{
			vic.spr_pos[7].x = 0;
			weapon_state = WEAPON_FREE;
		}
	}
	if (weapon_state == 4 || weapon_state == 5)
		return;

	// frame_extras in the original
	headlights_follow();
	// crash_reset_check: crash_reset_on is never set
	print_credit();
	joystick_controls();
}

void frame_update(void)
{
	char k = last_key();
	if (k == KEY_M)
		player_right();
	if (k == KEY_Z)
		player_left();
	if (k == KEY_SPACE)
		fire_guns();
	if (k == KEY_PERIOD)
		fire_missile();
	if (k == KEY_COMMA)
		fire_smoke();

	if (car_direction[0])
		car_down(1, car1_dx[car_direction[0]]);
	if (car_direction[1])
		car_down(2, car_dx[car_direction[1]]);
	if (car_direction[2])
		car_down(3, car_dx[car_direction[2]]);

	turbo_keys();

	if (car_direction[3])
	{
		vic.spr_pos[4].x += car4_dx[car_direction[3]];
		vic.spr_pos[4].y -= 5;
		if (vic.spr_pos[4].y == 80)
			car_direction[3] = 0;
	}
	// a bug: while the car from behind goes left 5, the frame ends here, without
	// the helicopter and the weapon
	if (car_direction[3] == 5)
		return;

	if (heli_state == 1)
		vic.spr_pos[5].x += 5;
	if (heli_state == 2)
	{
		// drop the bomb from the helicopter
		vic.spr_pos[6].x = vic.spr_pos[5].x;
		vic.spr_pos[6].y = vic.spr_pos[5].y;
		heli_state = 3;
	}
	if (heli_state == 3)
	{
		vic.spr_pos[6].x += 5;
		vic.spr_pos[6].y += 5;
		if (vic.spr_pos[6].y == 200)
			heli_state = 1;
	}
	if (heli_state == 4 || heli_state == 5)
		return;

	weapon_update();
}

void turbo_frame(void)
{
	if (turbo == 1)
		frame_update();
}

void title_scroll(void)
{
	for (char i = 0; i < 4; i++)
		vic.spr_pos[i].x -= 3;
}
