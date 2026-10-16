#include "helper.h"
#include "system.h"

char turbo, headlights_on;
volatile char heli_state, bomb_request;
volatile char weapon_state;
volatile char heli_hit, heli_flash;
volatile char motion_hold, motion_on, player_hold;
volatile char car_direction[4];
volatile char car_shot[4];
volatile char crash_pending;

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

// The missile's speed in half pixels a frame, doubled with turbo. The original
// moves it 5 pixels a frame_update, on average every 3.6 frames (1 to 10) at
// the game's speed: about 1.4 pixels a frame
#define MISSILE_SPEED       3

// The cars' speed in 1/256 pixels a frame for each 5 pixels the original moves
// them a frame_update, which comes every 19.8 frames on average at the game's
// speed (4 to 48): 5 pixels every 20 frames, here twice that. Doubled with turbo
#define CAR_SPEED           128

// The player's speed in pixels a frame, doubled with turbo. The original moves
// it 10 pixels a call: with the keys a frame_update (0.5 pixels a frame), with
// the joystick a weapon_update, every 9.1 frames on average (1.1 a frame).
// Here 2
#define PLAYER_SPEED        2

// Frames each gun frame shows, halved with turbo. The original shows one a
// weapon_update: every 9.1 frames on average, mostly 2-4
#define GUN_FRAMES          4

// The player stops at the kerbs. The original stops only at exactly these x,
// so from an x past a kerb (after the crash slide) the car walks off the road
#define KERB_LEFT   0x50
#define KERB_RIGHT  0xfa

// The player is sprite 0, the enemy cars 1-3, the car from behind 4, the
// helicopter (or the headlights) 5, the bomb 6, the weapon 7

static void player_right(char step)
{
	// the original jumps to crash_reset here, which does nothing unless x is $b4
	char x = vic.spr_pos[0].x;
	if (x < KERB_RIGHT)
		vic.spr_pos[0].x = x < KERB_RIGHT - step ? x + step : KERB_RIGHT;
}

static void player_left(char step)
{
	char x = vic.spr_pos[0].x;
	if (x > KERB_LEFT)
		vic.spr_pos[0].x = x > KERB_LEFT + step ? x - step : KERB_LEFT;
}

static char gun_frames;

static void fire_guns(void)
{
	if (weapon_state == WEAPON_FREE)
	{
		gun_frames = 0;
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
		// the state last: from then on the IRQ moves it
		vic.spr_pos[7].x = vic.spr_pos[0].x;
		vic.spr_pos[7].y = GUNS_Y;
		sprite_pointers[7] = SPR_MISSILE;
		weapon_state = WEAPON_MISSILE;
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

// x speeds of the enemy cars 1-3 by direction, for the original's x steps
// -5 -3 -2 2 3 5 against a y step of 5; car 1 has its own order
#define DX(n)   ((n) * CAR_SPEED / 5)
static const int car1_vx[6] = {0, DX(-2), 0, DX(2), DX(5), DX(-5)};
static const int car_vx[6] = {0, DX(-5), DX(-3), 0, DX(3), DX(5)};
// car 4 comes from behind
static const int car4_vx[6] = {0, DX(5), DX(3), 0, DX(-3), DX(-5)};

// The fractions of a pixel of the enemy cars 1-4, and the direction they're
// for (a new one starts them at half a pixel)
static char car_fx[5], car_fy[5], car_dir[5];

// An enemy car one frame on; at y end (car 4: back up at y 80) it's off the road
static char car_move(char car, int vx, int vy)
{
	char d = car_direction[car - 1];
	if (d != car_dir[car])
	{
		car_dir[car] = d;
		car_fx[car] = car_fy[car] = 128;
	}
	if (!d)
		return 0;
	if (turbo)
	{
		vx *= 2;
		vy *= 2;
	}
	// offset by 2 pixels to stay positive
	unsigned sx = car_fx[car] + vx + 512, sy = car_fy[car] + vy + 512;
	car_fx[car] = sx & 255;
	car_fy[car] = sy & 255;
	vic.spr_pos[car].x += (char)(sx >> 8) - 2;
	char y = vic.spr_pos[car].y + (char)(sy >> 8) - 2;
	vic.spr_pos[car].y = y;
	return y;
}

// An enemy car 1-3 down; off the road at y 200, or 160 when it goes right 5
static void car_down(char car, int vx)
{
	char y = car_move(car, vx, CAR_SPEED);
	if (y >= (vx == DX(5) ? 160 : 200))
		car_direction[car - 1] = 0;
}

static void player_frame(void)
{
	char step = turbo ? 2 * PLAYER_SPEED : PLAYER_SPEED;
	char k = last_key(), j = cia1.pra;
	if (k == KEY_M || j == JOY_RIGHT)
		player_right(step);
	else if (k == KEY_Z || j == JOY_LEFT)
		player_left(step);
}

// The helicopter flies right; on a request it stops and drops the bomb, which
// falls down and right to y 195, then it flies on. The original moves both 5
// pixels a frame_update; here at the cars' speed
static void heli_frame(unsigned step_speed)
{
	static char heli_fx, bomb_f;
	unsigned s;
	if (heli_state == 1)
	{
		if (bomb_request)
		{
			// drop the bomb from the helicopter
			vic.spr_pos[6].x = vic.spr_pos[5].x;
			vic.spr_pos[6].y = vic.spr_pos[5].y;
			bomb_f = 128;
			heli_state = 3;
		}
		else
		{
			s = heli_fx + step_speed;
			heli_fx = s & 255;
			vic.spr_pos[5].x += (char)(s >> 8);
		}
	}
	bomb_request = 0;
	if (heli_state == 3)
	{
		s = bomb_f + step_speed;
		bomb_f = s & 255;
		char d = s >> 8;
		vic.spr_pos[6].x += d;
		char y = vic.spr_pos[6].y + d;
		// landed: off the screen (the original leaves it at y 200 until the
		// collision pass moves it to 0)
		if (y > 195)
		{
			y = 0;
			heli_state = 1;
		}
		vic.spr_pos[6].y = y;
	}
}

// The guns or the smoke against the enemy cars, from line 6-35 of the
// original's collision pass: a car within 18 pixels of the player in x, at y
// 110-140 for the guns or 175-200 for the smoke. The original tests once a
// pass, every 45 frames or so, and may hit an exploding car again
static void weapon_hits(void)
{
	char state = weapon_state;
	if (state != WEAPON_GUNS && state != WEAPON_SMOKE)
		return;
	char low = state == WEAPON_GUNS ? 110 : 175, high = state == WEAPON_GUNS ? 140 : 200;
	int x = vic.spr_pos[0].x;
	for (char car = 1; car <= 4; car++)
	{
		if (car_shot[car - 1] || sprite_pointers[car] == SPR_EXPLOSION)
			continue;
		int cx = vic.spr_pos[car].x;
		char y = vic.spr_pos[car].y;
		if (cx > x - 18 && cx < x + 18 && y > low && y < high)
		{
			sprite_pointers[car] = SPR_EXPLOSION;
			vic.spr_color[car] = YELLOW;
			car_shot[car - 1] = 1;
		}
	}
}

// The weapon: fire from the keys and the joystick, the gun frames, the smoke
// following the player while held, and the hits
static void weapon_frame(void)
{
	char k = last_key(), j = cia1.pra;
	if (k == KEY_SPACE || j == JOY_FIRE)
		fire_guns();
	if (k == KEY_PERIOD || j == JOY_UP)
		fire_missile();
	if (k == KEY_COMMA || j == JOY_DOWN)
		fire_smoke();

	if (weapon_state == WEAPON_GUNS && ++gun_frames >= (turbo ? GUN_FRAMES / 2 : GUN_FRAMES))
	{
		// the next gun frame, up to the empty one
		gun_frames = 0;
		if (sprite_pointers[7] == SPR_GUNS_END)
			weapon_state = WEAPON_FREE;
		else
			sprite_pointers[7]++;
	}
	if (weapon_state == WEAPON_SMOKE)
	{
		// the smoke stays while the joystick is held down, or the ',' key (the
		// original tests only the joystick, so smoke from the key ends on the
		// next frame)
		vic.spr_pos[7].x = vic.spr_pos[0].x;
		if (j != JOY_DOWN && k != KEY_COMMA)
		{
			vic.spr_pos[7].x = 0;
			weapon_state = WEAPON_FREE;
		}
	}
	weapon_hits();
}

// An enemy car or the bomb against the player, from lines 20-38 of the
// original's collision pass: a car within 18 pixels in x and at y 140-180 that
// isn't exploding, or the bomb within 10 pixels at y 140-180. The original tests
// once a pass, so a car could drive through the player between two
static void crash_test(void)
{
	if (player_hold || crash_pending)
		return;
	int x = vic.spr_pos[0].x;
	for (char car = 1; car <= 4; car++)
	{
		if (car_shot[car - 1] || sprite_pointers[car] == SPR_EXPLOSION)
			continue;
		int cx = vic.spr_pos[car].x;
		char y = vic.spr_pos[car].y;
		if (cx > x - 18 && cx < x + 18 && y > 140 && y < 180)
		{
			crash_pending = 1;
			return;
		}
	}
	int bx = vic.spr_pos[6].x;
	char by = vic.spr_pos[6].y;
	if (bx > 0 && bx > x - 10 && bx < x + 10 && by > 140 && by < 180)
		crash_pending = 1;
}

// The original moves the cars and the player in frame_update (and the joystick
// in weapon_update), so at the speed of the BASIC that calls them
__interrupt void cars_frame(void)
{
	if (!motion_on || motion_hold)
		return;
	if (!player_hold)
		player_frame();
	if (headlights_on == 1)
		vic.spr_pos[5].x = vic.spr_pos[0].x;

	car_down(1, car1_vx[car_direction[0]]);
	car_down(2, car_vx[car_direction[1]]);
	car_down(3, car_vx[car_direction[2]]);
	if (car_direction[3])
	{
		char y = car_move(4, car4_vx[car_direction[3]], -CAR_SPEED);
		if (y <= 80)
			car_direction[3] = 0;
	}
	heli_frame(turbo ? 2 * CAR_SPEED : CAR_SPEED);
	weapon_frame();
	crash_test();
}

static void turbo_keys(void)
{
	if (last_key() == KEY_F1)
		turbo = 1;
	if (last_key() == KEY_F3)
		turbo = 0;
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


// The missile against the helicopter at each step. The original tests only
// once a collision pass, when the missile has moved 35-50 pixels since the last
// one, so it almost never finds it in the 15 pixel high window
static void missile_hit(char y)
{
	if (!(y > 50 && y < 70))
		return;
	// not the headlights in the tunnel, nor a helicopter that's exploding
	if (heli_state < 1 || heli_state > 3 || heli_flash || sprite_pointers[5] != SPR_HELICOPTER)
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

__interrupt void missile_frame(void)
{
	static char half;
	if (weapon_state != WEAPON_MISSILE || motion_hold)
		return;
	half += turbo ? 2 * MISSILE_SPEED : MISSILE_SPEED;
	char step = half >> 1;
	half &= 1;

	char y = vic.spr_pos[7].y;
	if (y <= step)
	{
		vic.spr_pos[7].y = 0;
		weapon_state = WEAPON_FREE;
		return;
	}
	y -= step;
	vic.spr_pos[7].y = y;
	missile_hit(y);
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

// The weapon (fire, guns, smoke) and the joystick are in the raster IRQ
// (weapon_frame, player_frame), the missile too (missile_frame)
void weapon_update(void)
{
	// frame_extras in the original; the headlights follow the player in the IRQ
	// crash_reset_check: crash_reset_on is never set
	print_credit();
}

// The keys, the cars, the helicopter and the weapon are in the raster IRQ
// (cars_frame). The original's bug, a frame that ends early while the car from
// behind goes left 5, skipped the helicopter and the weapon
void frame_update(void)
{
	turbo_keys();
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
