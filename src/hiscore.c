#include "hiscore.h"
#include "game.h"
#include "sound.h"
#include "system.h"

#define PLACES  10

static long scores[PLACES];
static char names[PLACES][9];

static void copy_name(char *d, const char *s)
{
	while ((*d++ = *s++))
		;
}

// The table's columns: the rank right-aligned up to column 3, the name from
// column 5, the score right-aligned up to column 25, on rows 3-12
#define NAME_COLUMN     5
#define NAME_LENGTH     8
#define SCORE_WIDTH     13
#define FIRST_ROW       3

#define INK WHITE

// n right-aligned, ending before offset o
static void number_right(unsigned o, long n)
{
	do
	{
		char_at(--o, INK, '0' + n % 10);
		n /= 10;
	} while (n);
}

static void show_header(void)
{
	screen_clear(INK);
	text_at(1, 1, INK, " TOP 10 AGENTS :ENTER YOUR CODE");
}

static void show_table(void)
{
	for (char i = 0; i < PLACES; i++)
	{
		unsigned o = (FIRST_ROW + i) * 40;
		number_right(o + NAME_COLUMN - 1, i + 1);
		text_at(FIRST_ROW + i, NAME_COLUMN, INK, names[i]);
		number_right(o + NAME_COLUMN + NAME_LENGTH + SCORE_WIDTH, scores[i]);
	}
}

void hiscore(void)
{
	vic.spr_enable = 0;
	sound_off();
	if (!(score > scores[PLACES - 1]))
		return;

	// the place below the scores the new one beats, a tie below the old score
	char x = PLACES - 1;
	while (x > 0 && score > scores[x - 1])
		x--;
	for (char i = PLACES - 1; i > x; i--)
	{
		scores[i] = scores[i - 1];
		copy_name(names[i], names[i - 1]);
	}
	names[x][0] = 0;
	scores[x] = score;

	show_header();
	vic.color_back = RED;
	show_table();

	while (get_key())
		;
	tune_restart();
	music_notes(77);

	// the name is typed over the entry's name column, cleared first; spaces
	// after the name are cut
	char row = FIRST_ROW + x;
	for (char i = NAME_COLUMN; i < NAME_COLUMN + NAME_LENGTH; i++)
		screen[row * 40 + i] = ' ';
	char name[NAME_LENGTH + 1];
	input_line(row, NAME_COLUMN, INK, name, NAME_LENGTH);
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
	text_at(19, 7, INK, "PRESS FIRE TO CONTINUE");
	wait_key();
}
