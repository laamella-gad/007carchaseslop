// The plan of the road at the bottom right (lines 7000-7500), and the bonus at
// the end of it (7100, 13000)
#ifndef PLAN_H
#define PLAN_H

// d$: the kind of road the plan drawing is at. It goes on from the last plan
enum Road {ROAD_COUNTRY, ROAD_CITY, ROAD_TUNNEL, ROAD_LEFT_CURVE, ROAD_RIGHT_CURVE, ROAD_BRIDGE};
extern char plan_road;

// gosub7000: six random sections, then the bonus, drawn on the screen
void plan_new(void);

// gosub7100: the bonus car animation and points, then a new plan
void bonus(void);

// gosub7500: the plan's colour area black
void plan_clear_colours(void);

#pragma compile("plan.c")

#endif
