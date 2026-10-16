// The game itself: the panel (lines 91-98) and the sections of road (188-2250),
// up to the end of the game
#ifndef ROAD_H
#define ROAD_H

// From goto91 after the title to goto39 when the last life is lost or F7
void game(void);

#pragma compile("road.c")

#endif
