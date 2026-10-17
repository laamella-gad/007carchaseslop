// The plan of the road at the bottom right, and the bonus at the end of it
#ifndef PLAN_H
#define PLAN_H

enum Road {ROAD_COUNTRY, ROAD_CITY, ROAD_TUNNEL, ROAD_LEFT_CURVE, ROAD_RIGHT_CURVE, ROAD_BRIDGE};

// The track: plan[0] is the section the road is in, the road goes through the
// others in turn, and the bonus comes in the last one, which is the first of the
// next plan. The plan drawn at the bottom right is all but the last
#define PLAN_SIZE 12
extern char plan[PLAN_SIZE];
extern char plan_length;
extern char plan_pos;

// A new plan from the given section, drawn on the screen
void plan_new(char from);

// The section after the one the road is in, ROAD_NONE in the last
#define ROAD_NONE 0xff
char plan_next(void);

// The bonus car animation and points, then a new plan
void bonus(void);

// The plan's colour area black
void plan_clear_colours(void);

#pragma compile("plan.c")

#endif
