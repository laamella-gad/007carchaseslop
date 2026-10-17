#include "helper.h"
#include "game.h"
#include "sound.h"
#include "system.h"

char turbo, headlights_on;
volatile char heli_state, bomb_request;
volatile char weapon_state;
volatile char heli_hit, heli_flash;
volatile char motion_hold, motion_on, player_hold;
volatile char car_direction[4];
volatile char car_shot[4];
volatile char crash_pending, curve_drift;
volatile char quit_request, crash_anim, title_on, glide_on;
volatile char on_bridge, bridge_edge;
volatile char car_boom[4];

// Joystick in port 2: the bits of $dc00 that go low. The original compares
// $dc00 with one value each, so only one direction or fire at a time counts:
// no diagonals, no fire while steering
#define JOY_UP      0x01
#define JOY_DOWN    0x02
#define JOY_LEFT    0x04
#define JOY_RIGHT   0x08
#define JOY_FIRE    0x10

static char joystick(void)
{
	return ~cia1.pra & 0x1f;
}

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

// The curves carry the player out, in 1/256 pixels a frame. The original moves
// it 20 pixels twice a pass of the curve loop, about every 45 frames
#define DRIFT_SPEED         256

// Frames each gun frame shows, halved with turbo. The original shows one a
// weapon_update: every 9.1 frames on average, mostly 2-4
#define GUN_FRAMES          4

// The bridge's water, by the player's x: the left bank below WATER_LEFT, the
// edge of the broken bridge from EDGE_LEFT to EDGE_RIGHT, the road right of it
#define WATER_LEFT  76
#define EDGE_LEFT   171
#define EDGE_RIGHT  199

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
	char k = last_key(), j = joystick();
	if (k == KEY_M || (j & JOY_RIGHT))
		player_right(step);
	else if (k == KEY_Z || (j & JOY_LEFT))
		player_left(step);
}

// Carried out of the curve: left down to x 80, right up to x 240. The original
// jumps 20 pixels: left not below 80, right while below 240, so up to 259, where
// BASIC stops with ?ILLEGAL QUANTITY (in a byte it wraps to the left edge)
static void drift_frame(void)
{
	static char drift_f;
	unsigned s = drift_f + DRIFT_SPEED;
	drift_f = s & 255;
	char d = s >> 8, x = vic.spr_pos[0].x;
	if (curve_drift == DRIFT_LEFT && x > 80)
		vic.spr_pos[0].x = x > 80 + d ? x - d : 80;
	else if (curve_drift == DRIFT_RIGHT && x < 240)
		vic.spr_pos[0].x = x < 240 - d ? x + d : 240;
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
			car_boom[car - 1] = CAR_BOOM_FRAMES;
			car_shot[car - 1] = 1;
		}
	}
}

// The weapon: fire from the keys and the joystick, the gun frames, the smoke
// following the player while held, and the hits
static void weapon_frame(void)
{
	char k = last_key(), j = joystick();
	if (k == KEY_SPACE || (j & JOY_FIRE))
		fire_guns();
	if (k == KEY_PERIOD || (j & JOY_UP))
		fire_missile();
	if (k == KEY_COMMA || (j & JOY_DOWN))
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
		if (!(j & JOY_DOWN) && k != KEY_COMMA)
		{
			vic.spr_pos[7].x = 0;
			weapon_state = WEAPON_FREE;
		}
	}
	weapon_hits();
}

// The coloured pixels of the cars' shapes in the sprite: x from left to right,
// y from top to bottom. The black outline (multicolour 1) doesn't show on the
// black road
typedef struct
{
	char left, right, top, bottom;
} Box;

static const Box box_player = {4, 19, 1, 15};      // SPR_PLAYER, also car 4
static const Box box_enemy = {6, 17, 0, 13};       // SPR_ENEMY
static const Box box_boat = {2, 21, 1, 15};        // SPR_BRIDGE_PLAYER
static const Box box_boat_enemy = {8, 17, 4, 19};  // SPR_BRIDGE_ENEMY
static const Box box_bomb = {0, 7, 9, 13};          // SPR_BOMB

static const Box *shape_box(char shape)
{
	switch (shape)
	{
	case SPR_ENEMY: return &box_enemy;
	case SPR_BRIDGE_PLAYER: return &box_boat;
	case SPR_BRIDGE_ENEMY: return &box_boat_enemy;
	case SPR_BOMB: return &box_bomb;
	default: return &box_player;
	}
}

// An enemy car or the bomb against the player, from lines 20-38 of the
// original's collision pass: a car that isn't exploding or the bomb, whose
// coloured pixels touch the player's. The original takes a car within 18
// pixels in x at y 140-180, a box larger than the cars (up to 4 pixels apart
// across, 13 along), and the bomb's sprite x within 10 of the player's at y
// 140-180, which is off to the left: it hits a bomb 6 pixels left of the car
// and misses one over the car's right half. It tests once a pass, so a car
// could also drive through the player between two
static char touches(char sprite, int x, int y, const Box *p)
{
	const Box *e = shape_box(sprite_pointers[sprite]);
	int cx = vic.spr_pos[sprite].x;
	int cy = vic.spr_pos[sprite].y;
	return cx + e->left <= x + p->right && cx + e->right >= x + p->left &&
		cy + e->top <= y + p->bottom && cy + e->bottom >= y + p->top;
}

static void crash_test(void)
{
	if (player_hold || crash_pending)
		return;
	int x = vic.spr_pos[0].x;
	int y0 = vic.spr_pos[0].y;
	const Box *p = shape_box(sprite_pointers[0]);
	for (char car = 1; car <= 4; car++)
	{
		if (car_shot[car - 1] || sprite_pointers[car] == SPR_EXPLOSION)
			continue;
		if (touches(car, x, y0, p))
		{
			crash_pending = 1;
			return;
		}
	}
	// the bomb at x 0 is off the screen
	if (vic.spr_pos[6].x && touches(6, x, y0, p))
		crash_pending = 1;
	// lines 2216 and 2240: into the bridge's edge. The original tests twice a
	// pass of the bridge loop, so the player could get across between two
	if (bridge_edge && x > EDGE_LEFT - 1 && x < EDGE_RIGHT + 1)
		crash_pending = 1;
}

// The player's shape on the bridge: the boat on the water, the car on the left
// bank (where the crash slide ends) and on the road right of the edge. The
// original sets the boat once, at line 2121, when x is below 180
static void bridge_shape(void)
{
	char x = vic.spr_pos[0].x;
	sprite_pointers[0] = x >= WATER_LEFT && x < EDGE_LEFT ? SPR_BRIDGE_PLAYER : SPR_PLAYER;
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

// An exploding enemy car goes off the road when its time is up. The original
// takes it off at the next collision pass but one after the hit, so it shows
// for 1 to 90 frames
static void booms_frame(void)
{
	for (char car = 1; car <= 4; car++)
		if (car_boom[car - 1] && !--car_boom[car - 1])
		{
			car_direction[car - 1] = 0;
			vic.spr_pos[car].x = 0;
		}
}

// The crash slide: the player's car 20 pixels left at a time, the enemy car's
// shape for the first 10 with the explosion's noise, until x 60. 2 pixels a
// frame, in 1/256 pixels; the original: 20 pixels a pass of lines 6000-6001,
// about 1.2 a frame
#define SLIDE_SPEED     512
// Then the car explodes: 16 steps of the noise, from volume 15 down to 0. The
// car is yellow during the noise and grey for the 2 frames between. A step of
// lines 6002-6006 takes about 24 frames, here half that
#define BOOM_STEP_FRAMES    12
#define BOOM_GAP_FRAMES     2

static void crash_frame(void)
{
	static char slide_f, slide_px, boom_frame;
	static signed char boom_volume;
	if (crash_anim == CRASH_SLIDE)
	{
		if (!slide_px && !slide_f)
		{
			// a pass starts: the enemy car's shape and the noise
			sprite_pointers[0] = SPR_ENEMY;
			sound_explosion();
		}
		unsigned s = slide_f + SLIDE_SPEED;
		slide_f = s & 255;
		char d = s >> 8, x = vic.spr_pos[0].x;
		vic.spr_pos[0].x = x > d ? x - d : 0;
		slide_px += d;
		if (slide_px >= 10)
			sprite_pointers[0] = player_sprite;
		if (slide_px >= 20)
		{
			slide_px = 0;
			slide_f = 0;
			if (vic.spr_pos[0].x <= 60)
			{
				sprite_pointers[0] = SPR_EXPLOSION;
				boom_volume = 15;
				boom_frame = 0;
				crash_anim = CRASH_BOOM;
			}
		}
	}
	else if (crash_anim == CRASH_BOOM)
	{
		if (boom_frame == 0)
		{
			sound_crash(boom_volume);
			vic.spr_color[0] = YELLOW;
		}
		else if (boom_frame == BOOM_STEP_FRAMES - BOOM_GAP_FRAMES)
		{
			vic.spr_color[0] = LIGHT_GREY;
			sound_crash_off();
		}
		if (++boom_frame == BOOM_STEP_FRAMES)
		{
			boom_frame = 0;
			if (--boom_volume < 0)
			{
				sprite_pointers[0] = player_sprite;
				crash_anim = CRASH_NONE;
			}
		}
	}
}

// The original moves the cars and the player in frame_update (and the joystick
// in weapon_update), so at the speed of the BASIC that calls them
__interrupt void cars_frame(void)
{
	if (!motion_on || motion_hold)
		return;
	print_credit();
	if (crash_anim)
		crash_frame();
	booms_frame();
	if (!player_hold)
	{
		player_frame();
		if (curve_drift)
			drift_frame();
		if (on_bridge && !crash_anim)
			bridge_shape();
	}
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

// F1 and F3 turbo on and off, F5 pauses and goes on (on a key press, so the
// F5 that pauses doesn't end the pause), F7 ends the game at the next
// collision pass. The original reads F1 and F3 in frame_update and F5 and F7
// in the collision pass, so a short press could be missed
__interrupt void keys_frame(void)
{
	static char key_before;
	char k = last_key();
	if (!motion_on && !motion_hold)
	{
		key_before = k;
		return;
	}
	if (k != key_before)
	{
		key_before = k;
		if (k == KEY_F5)
		{
			if (motion_hold)
				motion_hold = 0;
			else
			{
				motion_hold = 1;
				music_off();
			}
		}
		else if (k == KEY_F7 && !motion_hold)
			quit_request = 1;
	}
	if (!motion_hold)
	{
		if (k == KEY_F1)
			turbo = 1;
		if (k == KEY_F3)
			turbo = 0;
	}
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
	if (!heli_flash || motion_hold)
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

// The title's logo: 3 pixels left a pass of the title loop (sys51900 in line
// 11070); 178 waits of the loop had 669 passes. Here twice that
#define TITLE_SPEED     PX_SPEED(6, CYCLES_11070 * 178 / 669)

static volatile char *glide_reg;
static char glide_to, glide_f;
static unsigned glide_speed;

void glide(volatile char *reg, char to, unsigned speed)
{
	glide_on = 0;
	glide_reg = reg;
	glide_to = to;
	glide_speed = speed;
	glide_f = 0;
	glide_on = 1;
}

__interrupt void anim_frame(void)
{
	static char title_f;
	if (title_on)
	{
		unsigned s = title_f + TITLE_SPEED;
		title_f = s & 255;
		char d = s >> 8;
		for (char i = 0; i < 4; i++)
			vic.spr_pos[i].x -= d;
	}
	if (glide_on)
	{
		unsigned s = glide_f + glide_speed;
		glide_f = s & 255;
		char d = s >> 8, v = *glide_reg, to = glide_to;
		if (v < to)
			v = to - v > d ? v + d : to;
		else
			v = v - to > d ? v - d : to;
		*glide_reg = v;
		if (v == to)
			glide_on = 0;
	}
}
