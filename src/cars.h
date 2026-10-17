// The cars and the helicopter from BASIC: where they come on, the collision pass
// after each part of the road, and the crash
#ifndef CARS_H
#define CARS_H

// Lines 100-115: the cars and the helicopter onto the road
void spawn_player(void);            // 100
void spawn_car(char car);           // 101-103: enemy car 1-3
void spawn_car4(void);              // 105-111: the car from behind
void spawn_helicopter(void);        // 115

// Lines 122-131: the same on the bridge, where the cars only go straight or left
void spawn_car_bridge(char car);    // 122-123
void spawn_car4_bridge(void);       // 125-131

// Line 246 and the like: a flying helicopter that's past x decides at random
// whether to drop a bomb
void helicopter_bomb(char x);

// Lines 12-19 (gosub12-15): enemy car 1-4 explodes; points for it
void car_explode(char car);

// Lines 5-60 (gosub5): the explosions, hits, crashes, F7, F5 and the score;
// 1 when the game ends
char collide(void);

// A crash the raster IRQ found (crash_test): from the collision pass and after
// each row of the road
void crash_check(void);
// Line 6000 (gosub6000 on the bridge): the player skids left and crashes, and
// loses a life unless it just crashed
void crash_skid(void);

#pragma compile("cars.c")

#endif
