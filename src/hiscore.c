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

// Lines 20051 and 20066
static void show_table(void)
{
	for (char n = 1; n <= 10; n++)
	{
		print(t20051);
		print(names[n]);
		print_comma();
		print_comma();
		print_number(scores[n]);
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
	// line 20058: 77 notes of the tune
	music_on();
	pace(CYCLES_20058);
	sound_off();

	// the name is typed over the entry's name column, cleared first (the
	// original keeps an old 10th place name there, and INPUT reads its rest);
	// spaces after the name are cut
	for (char i = 2; i < 10; i++)
		screen[(2 + x) * 40 + i] = ' ';
	char name[9];
	input_line(name, 8);
	char n = 0;
	while (name[n])
		n++;
	while (n && name[n - 1] == ' ')
		n--;
	name[n] = 0;
	copy_name(names[x], name);
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
