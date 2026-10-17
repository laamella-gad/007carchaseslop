#include "system.h"
#include "helper.h"
#include <stdlib.h>

// The KERNAL's text colour and cursor flags
#define KERNAL_COLOUR   0x286
#define KEYS_IN_BUFFER  0xc6
#define CURSOR_OFF      0xcc

static char row, column, ink = 14, reverse;

void system_init(void)
{
	// CIA 2 timer A runs every 256 cycles, timer B counts its underflows
	cia2.ta = 255;
	cia2.tb = 0xffff;
	cia2.cra = 0x11;
	cia2.crb = 0x51;

	ink = PEEK(KERNAL_COLOUR);
	pace_restart();
}

static void scroll(void)
{
	for (unsigned i = 0; i < 960; i++)
	{
		screen[i] = screen[i + 40];
		colour_ram[i] = colour_ram[i + 40];
	}
	for (char i = 0; i < 40; i++)
	{
		screen[960 + i] = ' ';
		colour_ram[960 + i] = ink;
	}
}

static void down(void)
{
	if (row == 24)
		scroll();
	else
		row++;
}

static void clear(void)
{
	for (unsigned i = 0; i < 1000; i++)
	{
		screen[i] = ' ';
		colour_ram[i] = ink;
	}
	row = column = 0;
}

static const char colour_codes[32] = {
	// $00-$1f: $05 white, $1c red, $1e green, $1f blue
	0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 6, 7,
};

static const char colour_codes_high[32] = {
	// $80-$9f: $81 orange, $90 black, $95-$9b brown to light grey, $9c purple,
	// $9e yellow, $9f cyan
	0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15, 16, 5, 0, 8, 4,
};

void put(char c)
{
	char sc;

	if (c < 0x20)
	{
		if (colour_codes[c])
		{
			ink = colour_codes[c] - 1;
			return;
		}
		switch (c)
		{
		case 0x0d:
			column = 0;
			reverse = 0;
			down();
			break;
		case 0x11:
			down();
			break;
		case 0x12:
			reverse = 0x80;
			break;
		case 0x13:
			row = column = 0;
			break;
		case 0x1d:
			if (++column == 40)
			{
				column = 0;
				down();
			}
			break;
		}
		return;
	}
	if (c >= 0x80 && c < 0xa0)
	{
		if (colour_codes_high[c - 0x80])
		{
			ink = colour_codes_high[c - 0x80] - 1;
			return;
		}
		switch (c)
		{
		case 0x8d:
			column = 0;
			reverse = 0;
			down();
			break;
		case 0x91:
			if (row)
				row--;
			break;
		case 0x92:
			reverse = 0;
			break;
		case 0x93:
			clear();
			break;
		case 0x9d:
			if (column)
				column--;
			else if (row)
			{
				column = 39;
				row--;
			}
			break;
		}
		return;
	}

	if (c < 0x40)
		sc = c;
	else if (c < 0x60)
		sc = c - 0x40;
	else if (c < 0x80)
		sc = c - 0x20;
	else if (c < 0xc0)
		sc = c - 0x40;
	else if (c < 0xff)
		sc = c - 0x80;
	else
		sc = 0x5e;

	unsigned o = row * 40 + column;
	screen[o] = sc | reverse;
	colour_ram[o] = ink;
	if (++column == 40)
	{
		column = 0;
		down();
	}
}

void print(const char *s)
{
	while (*s)
		put(*s++);
}

void print_number(long n)
{
	char digits[11], i = 0;

	if (n < 0)
	{
		put('-');
		n = -n;
	}
	else
		put(' ');
	do
	{
		digits[i++] = '0' + n % 10;
		n /= 10;
	} while (n);
	while (i)
		put(digits[--i]);
	put(PET_RIGHT);
}

static char saved_row, saved_column, saved_ink, saved_reverse;

void print_save(void)
{
	saved_row = row;
	saved_column = column;
	saved_ink = ink;
	saved_reverse = reverse;
}

void print_restore(void)
{
	row = saved_row;
	column = saved_column;
	ink = saved_ink;
	reverse = saved_reverse;
}

void print_comma(void)
{
	char n = 10 - column % 10;
	while (n--)
		put(PET_RIGHT);
}

char get_key(void)
{
	return __asm {
		jsr $ffe4
		sta accu
	};
}

// Screen code back to PETSCII, as the screen editor reads it
static char petscii(char sc)
{
	sc &= 0x7f;
	if (sc < 0x20)
		return sc + 0x40;
	if (sc < 0x40)
		return sc;
	if (sc < 0x60)
		return sc + 0x80;
	return sc + 0x40;
}

void input_line(char *s, char max)
{
	print("? ");
	char start = column;
	unsigned line = row * 40;
	for (;;)
	{
		unsigned o = line + column;
		// a blinking cursor, as the KERNAL's
		char under = screen[o];
		char c;
		while (!(c = get_key()))
			screen[o] = (PEEK(0xa2) & 16) ? under ^ 0x80 : under;
		screen[o] = under;

		if (c == PET_RETURN)
			break;
		if (c == 0x14)
		{
			if (column > start)
			{
				put(0x9d);
				put(' ');
				put(0x9d);
			}
		}
		else if (((c >= 0x20 && c < 0x60) || (c >= 0xc1 && c <= 0xda)) && column < 39)
			put(c);
	}

	// As the screen editor: the whole line from where the typing started,
	// with what was already there after the typed text, without the spaces
	// at the end. INPUT skips the spaces in front and stops at ',' or ':'
	char end = 40;
	while (end > start && screen[line + end - 1] == ' ')
		end--;
	while (start < end && screen[line + start] == ' ')
		start++;
	char n = 0;
	while (start < end && n < max)
	{
		char c = petscii(screen[line + start++]);
		if (c == ',' || c == ':')
			break;
		s[n++] = c;
	}
	s[n] = 0;
	put(PET_RETURN);
}

char rnd(char n)
{
	return (unsigned)rand() % n;
}

// Timer B counts down by 1 every 256 cycles
static unsigned ticks(void)
{
	unsigned t;
	do
		t = cia2.tb;
	while (t != cia2.tb);
	return ~t;
}

static unsigned target;
static char rest;

void pace(unsigned long cycles)
{
	// F5 pauses the game (keys_frame) at the next line, until F5 again
	if (motion_hold)
	{
		while (motion_hold)
			;
		pace_restart();
	}

	cycles += rest;
	rest = cycles & 255;
	cycles >>= 8;

	// more than 8 s ahead can't be compared in 16 bits: wait in steps
	while (cycles > 0x4000)
	{
		target += 0x4000;
		cycles -= 0x4000;
		while ((int)(target - ticks()) > 0)
			;
	}
	target += (unsigned)cycles;

	// far behind (half a second, on a slow line): don't rush to catch up
	unsigned now = ticks();
	if ((int)(now - target) > 2000)
		target = now;

	while ((int)(target - ticks()) > 0)
		;
}

void pace_restart(void)
{
	target = ticks();
	rest = 0;
}
