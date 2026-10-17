#include "hiscore.h"
#include "game.h"
#include "sound.h"
#include "system.h"

// sc(1-10) and sc$(1-10); 0 unused
static long scores[11];
static char names[11][9];

static void copy_name(char *d, const char *s)
{
	while ((*d++ = *s++))
		;
}

// The table's columns: the rank right-aligned up to column 3, the name from
// column 5, the score right-aligned up to column 25
#define NAME_COLUMN     5
#define NAME_LENGTH     8
#define SCORE_WIDTH     13

// Written straight to the screen in the colour the printer has (the original
// PRINTs with the KERNAL's colour)
static char ink;

// n right-aligned, ending before offset o
static void number_at(unsigned o, long n)
{
	do
	{
		char_at(--o, ink, '0' + n % 10);
		n /= 10;
	} while (n);
}

// Line 20050/20065: {clr}{down}{rght} top 10 agents :enter your code{down}
static void show_header(void)
{
	ink = print_ink();
	screen_clear(ink);
	text_at(1, 1, ink, " TOP 10 AGENTS :ENTER YOUR CODE");
}

// Lines 20051 and 20066, rows 3-12. The original prints two {rght}, the name
// and the score with two commas between, so the score lands at column 20 or
// 30 by the name's length; here in columns, with the rank in front
#define TABLE_ROW       2

static void show_table(void)
{
	for (char n = 1; n <= 10; n++)
	{
		unsigned o = (TABLE_ROW + n) * 40;
		number_at(o + NAME_COLUMN - 1, n);
		text_at(TABLE_ROW + n, NAME_COLUMN, ink, names[n]);
		number_at(o + NAME_COLUMN + NAME_LENGTH + SCORE_WIDTH, scores[n]);
	}
}

void hiscore(void)
{
	vic.spr_enable = 0;
	sound_off();
	if (!(score > scores[10]))
	{
		pace_restart();
		return;
	}

	// Lines 20002-20011 and 20100: the place below the scores the new one
	// beats, a tie below the old score. The original ENDs on a tie, and its
	// shift (from 9, not 10) loses the 9th place and keeps the 10th
	char x = 10;
	while (x > 1 && score > scores[x - 1])
		x--;
	for (char n = 10; n > x; n--)
	{
		scores[n] = scores[n - 1];
		copy_name(names[n], names[n - 1]);
	}
	names[x][0] = 0;
	scores[x] = score;

	show_header();
	vic.color_back = RED;
	show_table();

	// line 20055: the cursor home, then down to the new entry's row
	while (get_key())
		;
	tune_restart();
	// line 20058: 77 notes of the tune, here while the name is typed (the
	// original plays them first, 10 seconds)
	music_notes(77);

	// the name is typed over the entry's name column, cleared first (the
	// original keeps an old 10th place name there, and INPUT reads its rest);
	// spaces after the name are cut. No "? ": it would cover the rank
	for (char i = NAME_COLUMN; i < NAME_COLUMN + NAME_LENGTH; i++)
		screen[(TABLE_ROW + x) * 40 + i] = ' ';
	print_at(TABLE_ROW + x, NAME_COLUMN);
	char name[NAME_LENGTH + 1];
	input_line(name, NAME_LENGTH);
	char n = 0;
	while (name[n])
		n++;
	while (n && name[n - 1] == ' ')
		n--;
	name[n] = 0;
	copy_name(names[x], name);
	sound_off();

	show_header();
	show_table();
	text_at(19, 7, ink, "PRESS FIRE TO CONTINUE");
	print_at(20, 0);
	wait_key();
	// the lines after go on from here
	pace_restart();
}
