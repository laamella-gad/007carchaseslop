#include "game.h"
#include "system.h"
#include "frame.h"
#include "sound.h"
#include "cars.h"

long score, bonus_points;
signed char lives;
char crashed, player_sprite, enemy_sprite;
unsigned distance;

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

// The screen codes of the characters in the tables
static char screen_codes[128];

void text_init(void)
{
	for (char c = 32; c < 128; c++)
		screen_codes[c] = c >= 'A' && c <= 'Z' ? c - 64 : c;
	for (char i = 0; i < GLYPHS; i++)
		screen_codes[glyphs[i][0]] = glyphs[i][1];
}

static char colour_of(char letter)
{
	switch (letter)
	{
	case 'k': return BLACK;
	case 'w': return WHITE;
	case 'r': return RED;
	case 'c': return CYAN;
	case 'g': return GREEN;
	case 'b': return BLUE;
	case 'y': return YELLOW;
	case 'n': return BROWN;
	case 'd': return DARK_GREY;
	case 'm': return GREY;
	default: return LIGHT_GREY;
	}
}

static void draw_line(const Line *line, char ink)
{
	unsigned o = line->row * 40;
	volatile char *s = screen + o, *c = colour_ram + o;
	const char *chars = line->chars, *runs = line->colours;
	char x = 0;
	while (chars[x])
	{
		while (*runs == ' ')
			runs++;
		char letter = *runs++;
		char n = 0;
		while (*runs >= '0' && *runs <= '9')
			n = n * 10 + *runs++ - '0';
		char end = n ? x + n : 40;
		if (letter == '.')
		{
			x = end;
			continue;
		}
		char colour = letter == '*' ? ink : colour_of(letter);
		while (x < end && chars[x])
		{
			s[x] = screen_codes[chars[x]];
			c[x] = colour;
			x++;
		}
	}
}

void show_rows(const Line *table)
{
	for (; table->row != 0xff; table++)
		draw_line(table, 0);
}

void play_rows_ink(const Line *table, char ink)
{
	for (; table->row != 0xff; table++)
	{
		row_wait();
		draw_line(table, ink);
		// a crash goes on after the row it happens in, not at the next
		// collision pass
		if (crash_pending && motion_on)
			crash_check();
	}
}

void play_rows(const Line *table)
{
	play_rows_ink(table, 0);
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
