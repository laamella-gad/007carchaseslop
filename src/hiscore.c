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

// n right-aligned in width characters
static void print_right(long n, char width)
{
	char digits[11], i = 0;
	do
	{
		digits[i++] = '0' + n % 10;
		n /= 10;
	} while (n);
	while (width > i)
	{
		put(' ');
		width--;
	}
	while (i)
		put(digits[--i]);
}

// Lines 20051 and 20066. The original prints two {rght}, the name and the
// score with two commas between, so the score lands at column 20 or 30 by the
// name's length; here in columns, with the rank in front
static void show_table(void)
{
	for (char n = 1; n <= 10; n++)
	{
		print_right(n, NAME_COLUMN - 1);
		put(' ');
		char i = 0;
		while (names[n][i])
			put(names[n][i++]);
		while (i++ < NAME_LENGTH)
			put(' ');
		print_right(scores[n], SCORE_WIDTH);
		put(PET_RETURN);
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

	print(t20050);
	put(PET_RETURN);
	vic.color_back = RED;
	LINE(20050);
	show_table();

	// the cursor home, then down to the new entry's row
	print(t20055);
	put(PET_RETURN);
	for (char n = 0; n < x; n++)
		print(t20055_2);
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
		screen[(2 + x) * 40 + i] = ' ';
	for (char i = 0; i < NAME_COLUMN; i++)
		put(PET_RIGHT);
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

	print(t20050);
	put(PET_RETURN);
	LINE(20065);
	show_table();
	print(t20070);
	put(PET_RETURN);
	LINE(20070);
	while (!get_key())
		;
	pace_restart();
	LINE(20080);
}
