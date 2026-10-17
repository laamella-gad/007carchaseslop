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

static void put_at(unsigned o, char c)
{
	// PETSCII to screen code, as the printer: letters to 1-26, digits, space
	// and punctuation as they are, the shifted characters a name can have
	if (c >= 0xc0)
		c -= 0x80;
	else if (c >= 0xa0)
		c -= 0x40;
	else if (c >= 0x40)
		c -= 0x40;
	screen[o] = c;
	colour_ram[o] = ink;
}

static void text_at(char row, char column, const char *s)
{
	unsigned o = row * 40 + column;
	while (*s)
		put_at(o++, *s++);
}

// n right-aligned, ending before offset o
static void number_at(unsigned o, long n)
{
	do
	{
		put_at(--o, '0' + n % 10);
		n /= 10;
	} while (n);
}

// Line 20050/20065: {clr}{down}{rght} top 10 agents :enter your code{down}
static void show_header(void)
{
	ink = print_ink();
	for (unsigned i = 0; i < 1000; i++)
	{
		screen[i] = ' ';
		colour_ram[i] = ink;
	}
	text_at(1, 1, " TOP 10 AGENTS :ENTER YOUR CODE");
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
		text_at(TABLE_ROW + n, NAME_COLUMN, names[n]);
		number_at(o + NAME_COLUMN + NAME_LENGTH + SCORE_WIDTH, scores[n]);
		pace(CYCLES_20051 / 10);
	}
}

void hiscore(void)
{
	vic.spr_enable = 0;
	sound_off();
	LINE(20000);
	if (!(score > scores[10]))
	{
		LINE(20001);
		return;
	}

	// Lines 20002-20011 and 20100: the place below the scores the new one
	// beats, a tie below the old score. The original ENDs on a tie, and its
	// shift (from 9, not 10) loses the 9th place and keeps the 10th
	static const unsigned long cycles[10] = {
		CYCLES_20002, CYCLES_20003, CYCLES_20004, CYCLES_20005, CYCLES_20006,
		CYCLES_20007, CYCLES_20008, CYCLES_20009, CYCLES_20010, CYCLES_20011,
	};
	char x = 10;
	pace(cycles[0]);
	while (x > 1 && score > scores[x - 1])
	{
		x--;
		pace(cycles[10 - x]);
	}
	for (char n = 10; n > x; n--)
	{
		scores[n] = scores[n - 1];
		copy_name(names[n], names[n - 1]);
	}
	names[x][0] = 0;
	scores[x] = score;
	LINE(20100);

	show_header();
	vic.color_back = RED;
	LINE(20050);
	show_table();

	// line 20055: the cursor home, then down to the new entry's row
	LINE(20055);
	while (get_key())
		;
	pace_restart();
	tune_restart();
	LINE(20057);
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
	pace_restart();
	LINE(20060);

	show_header();
	LINE(20065);
	show_table();
	text_at(19, 7, "HIT ANY KEY TO CONTINUE");
	print_at(20, 0);
	LINE(20070);
	while (!get_key())
		;
	pace_restart();
	LINE(20080);
}
