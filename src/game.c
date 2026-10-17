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

// One row of a table to the screen; the start of the next row
static const char *draw_row(const char *p, char ink)
{
	char row;
	while ((row = p[0]) != ROW_END)
	{
		if (row == CLEAR || row == CLEAR_ROAD)
		{
			unsigned n = row == CLEAR ? 1000 : 800;
			for (unsigned i = 0; i < n; i++)
			{
				screen[i] = ' ';
				colour_ram[i] = p[1];
			}
			p += 2;
			continue;
		}
		char colour = p[2] == INK ? ink : p[2];
		unsigned o = row * 40 + p[1];
		volatile char *s = screen + o, *c = colour_ram + o;
		char n = p[3];
		p += 4;
		for (char i = 0; i < n; i++)
		{
			s[i] = p[i];
			c[i] = colour;
		}
		p += n;
	}
	return p + 1;
}

void show_rows(const char *table)
{
	while (*table != TABLE_END)
	{
		if (*table == TUNE)
			table++;
		table = draw_row(table, 0);
	}
}

void play_rows_ink(const char *table, char ink)
{
	while (*table != TABLE_END)
	{
		if (*table == TUNE)
		{
			music_on();
			table++;
		}
		row_wait();
		table = draw_row(table, ink);
		// a crash goes on after the row it happens in, not at the next
		// collision pass
		if (crash_pending && motion_on)
			crash_check();
	}
}

void show_labels(void)
{
	text_at(21, 21, BLACK, "TRACK");
	text_at(22, 21, BLACK, "PLAN");
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
