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

// sys49155: keys, cars, F1/F3, the car from behind, the helicopter, the weapon
void frame_update(void);

// sys49152: frame_update again when turbo is on
void turbo_frame(void);

// sys49561: the weapon, the headlights, the credit and the joystick
void weapon_update(void);

// sys51900: the title logo 3 pixels left
void title_scroll(void);

// From the raster IRQ, once a frame: the cars, the player, the helicopter and
// its bomb, the weapon, the crashes, and
// the helicopter's explosion flash
__interrupt void cars_frame(void);
__interrupt void missile_frame(void);
__interrupt void heli_flash_frame(void);

#pragma compile("helper.c")

#endif
