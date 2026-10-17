#include "game.h"
#include "system.h"
#include "helper.h"
#include "sound.h"
#include "cars.h"

long score, bonus_points;
signed char lives;
char crashed, player_sprite, enemy_sprite;
unsigned distance;
char plan_pos;
char plan[11];

static char row_frame;

void row_wait(void)
{
	// F5 pauses the game (keys_frame) at the next row, until F5 again
	while (motion_hold)
		;
	// the next frame after the last row's, from the raster IRQ below the
	// playfield; a row that comes late goes at once
	while (frame_count == row_frame)
		;
	row_frame = frame_count;
	// the measured lines that come after go on from here
	pace_restart();
}

void play_rows(const Row *rows, char from, char to)
{
	for (char i = from; i < to; i++)
	{
		const Row *r = rows + i;
		if (r->tune)
			music_on();
		row_wait();
		print_cells(r->cells);
		// a crash goes on after the row it happens in, not at the next
		// collision pass. Its prints move the cursor, and the next row goes
		// on from this one
		if (crash_pending && motion_on)
		{
			print_save();
			crash_check();
			print_restore();
		}
	}
}
