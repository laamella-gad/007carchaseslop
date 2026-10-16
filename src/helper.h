// The original's machine code helper at $c000: one frame of the cars, the
// helicopter and the weapon. BASIC calls it with SYS between its PRINTs
#ifndef HELPER_H
#define HELPER_H

// Shared with BASIC in the original ($cff0-$cffe)
extern char turbo;              // 53232: 1 after F1, 0 after F3
extern char headlights_on;      // 53233: in the tunnel the headlights follow the player
extern char car_direction[4];   // 53241-53244: 1-5, 0 off the road
extern char heli_state;         // 53245: 1 flying, 2 drop the bomb, 3 bomb falling
extern char weapon_state;       // 53246: 0 free, 1 guns, 2 missile, 3 smoke

#define WEAPON_FREE     0
#define WEAPON_GUNS     1
#define WEAPON_MISSILE  2
#define WEAPON_SMOKE    3

// Set when the missile hits the helicopter; the collision pass scores it
extern char heli_hit;
// Frames left of the helicopter's explosion flash; 0 when none
extern volatile char heli_flash;

// sys49155: keys, cars, F1/F3, the car from behind, the helicopter, the weapon
void frame_update(void);

// sys49152: frame_update again when turbo is on
void turbo_frame(void);

// sys49561: the weapon, the headlights, the credit and the joystick
void weapon_update(void);

// sys51900: the title logo 3 pixels left
void title_scroll(void);

// From the raster IRQ, once a frame: the helicopter's explosion flash
__interrupt void heli_flash_frame(void);

#pragma compile("helper.c")

#endif
