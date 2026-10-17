// The cars and the helicopter: where they come on, the collision pass after
// each part of the road, and the crash
#ifndef CARS_H
#define CARS_H

// The cars and the helicopter onto the road
void spawn_player(void);
void spawn_car(char car);           // enemy car 1-3
void spawn_car4(void);              // the car from behind
void spawn_helicopter(void);

// The same on the bridge, where the cars only go straight or left
void spawn_car_bridge(char car);
void spawn_car4_bridge(void);

// A flying helicopter that's past x decides at random whether to drop a bomb
void helicopter_bomb(char x);

// Enemy car 1-4 explodes; points for it
void car_explode(char car);

// The explosions, hits, crashes, F7 and the score; 1 when the game ends
char collide(void);

// A crash the raster IRQ found (crash_test): from the collision pass and after
// each row of the road
void crash_check(void);
// On the bridge: the player skids left and crashes, and loses a life unless it
// just crashed
void crash_skid(void);

#pragma compile("cars.c")

#endif
