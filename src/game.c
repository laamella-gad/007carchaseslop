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
}

void show_rows(const Row *rows, char from, char to)
{
	for (char i = from; i < to; i++)
		print_cells(rows[i].cells, 0);
}

void play_rows_ink(const Row *rows, char from, char to, char ink)
{
	for (char i = from; i < to; i++)
	{
		const Row *r = rows + i;
		if (r->tune)
			music_on();
		row_wait();
		print_cells(r->cells, ink);
		// a crash goes on after the row it happens in, not at the next
		// collision pass
		if (crash_pending && motion_on)
			crash_check();
	}
}

void show_score(void)
{
	text_at(22, 8, WHITE, "SCORE");
	number_at(22, 14, WHITE, score);
}

void show_lives(void)
{
	text_at(21, 8, WHITE, "CARS");
	number_at(21, 13, WHITE, lives);
}
