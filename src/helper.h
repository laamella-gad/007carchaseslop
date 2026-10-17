// The original's machine code helper at $c000: one frame of the cars, the
// helicopter and the weapon. BASIC calls it with SYS between its PRINTs
#ifndef HELPER_H
#define HELPER_H

// Shared with BASIC in the original ($cff0-$cffe)
extern char turbo;              // 53232: 1 after F1, 0 after F3
extern char headlights_on;      // 53233: in the tunnel the headlights follow the player
extern volatile char car_direction[4]; // 53241-53244: 1-5, 0 off the road
extern volatile char heli_state; // 53245: 1 flying, 2 drop the bomb, 3 bomb falling
extern volatile char weapon_state; // 53246: 0 free, 1 guns, 2 missile, 3 smoke

#define WEAPON_FREE     0
#define WEAPON_GUNS     1
#define WEAPON_MISSILE  2
#define WEAPON_SMOKE    3

// Set when the missile hits the helicopter; the collision pass scores it
extern volatile char heli_hit;
// Frames left of the helicopter's explosion flash; 0 when none
extern volatile char heli_flash;
// Set by the IRQ for an enemy car 1-4 the guns or the smoke hit; it shows the
// explosion, the collision pass scores it
extern volatile char car_shot[4];
// Set by the IRQ when an enemy car or the bomb hits the player; the main code
// runs the crash (crash_check)
extern volatile char crash_pending;
// In a curve the player is carried out of it, left or right, in the IRQ
extern volatile char curve_drift;
#define DRIFT_NONE      0
#define DRIFT_LEFT      1
#define DRIFT_RIGHT     2
// Set by the main code for a flying helicopter to drop its bomb; the IRQ does it
extern volatile char bomb_request;
// Set during the F5 pause: the cars, the player and the missile stop
extern volatile char motion_hold;
// Set while a game is on the road: the IRQ moves the cars, the player and the
// helicopter
extern volatile char motion_on;
// Set during the crash slide: the player can't steer
extern volatile char player_hold;
// On the bridge (lines 2100-2250): the player is a boat on the water and a car
// on the bank and the road (in the IRQ). With bridge_edge set too, the IRQ
// tests the bridge's edge (x 171-199) for a crash every frame
extern volatile char on_bridge, bridge_edge;

// Set by the IRQ on F7; the collision pass ends the game
extern volatile char quit_request;

// The crash in the raster IRQ (crash_frame): the slide, then the explosion.
// Back to CRASH_NONE at the end
extern volatile char crash_anim;
#define CRASH_NONE      0
#define CRASH_SLIDE     1
#define CRASH_BOOM      2

// Frames an enemy car explodes, from the hit, before it goes off the road; 0
// when it doesn't. Set by the IRQ and car_explode, counted down in the IRQ
extern volatile char car_boom[4];
#define CAR_BOOM_FRAMES 22

// Set while the title's logo scrolls (in the raster IRQ)
extern volatile char title_on;

// One sprite coordinate to a value at a speed, in the raster IRQ; glide_on is
// cleared when it's there
extern volatile char glide_on;
void glide(volatile char *reg, char to, unsigned speed);

// A PAL frame
#define FRAME_CYCLES    19656ul
// A speed in 1/256 pixels a frame for px pixels in the given cycles
#define PX_SPEED(px, cycles)    ((unsigned)((px) * 256ul * FRAME_CYCLES / (cycles)))

// From the raster IRQ, once a frame: F1, F3, F5 and F7, the cars, the player,
// the helicopter and its bomb, the weapon, the crashes, the credit, the
// helicopter's explosion flash, the title's logo and the bonus animation
__interrupt void keys_frame(void);
__interrupt void cars_frame(void);
__interrupt void missile_frame(void);
__interrupt void heli_flash_frame(void);
__interrupt void anim_frame(void);

#pragma compile("helper.c")

#endif
