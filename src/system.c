#include "system.h"
#include "helper.h"
#include <stdlib.h>

void screen_clear(char colour)
{
	for (unsigned i = 0; i < 1000; i++)
	{
		screen[i] = ' ';
		colour_ram[i] = colour;
	}
}

void char_at(unsigned o, char colour, char c)
{
	// PETSCII to screen code: letters to 1-26, digits, space and
	// punctuation as they are, the shifted and graphics characters
	if (c >= 0xc0)
		c -= 0x80;
	else if (c >= 0xa0)
		c -= 0x40;
	else if (c >= 0x40)
		c -= 0x40;
	screen[o] = c;
	colour_ram[o] = colour;
}

void text_at(char row, char column, char colour, const char *s)
{
	unsigned o = row * 40 + column;
	while (*s)
		char_at(o++, colour, *s++);
}

void number_at(char row, char column, char colour, long n)
{
	char digits[10], i = 0;
	do
	{
		digits[i++] = '0' + n % 10;
		n /= 10;
	} while (n);
	unsigned o = row * 40 + column;
	while (i)
		char_at(o++, colour, digits[--i]);
}

// The cells: spans of [offset high, offset low, colour, length, screen codes],
// or [0xfe, colour] (the screen cleared) or [0xfd, colour] (rows 0-19
// cleared), until 0xff. CELL_INK as the colour takes the colour given
#define CELL_INK        0x40

void print_cells(const char *p, char ink)
{
	char hi;
	while ((hi = p[0]) != 0xff)
	{
		if (hi >= 0xfd)
		{
			unsigned n = hi == 0xfe ? 1000 : 800;
			for (unsigned i = 0; i < n; i++)
			{
				screen[i] = ' ';
				colour_ram[i] = p[1];
			}
			p += 2;
			continue;
		}
		char colour = p[2] == CELL_INK ? ink : p[2];
		unsigned o = (unsigned)hi << 8 | p[1];
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
}

char get_key(void)
{
	return __asm {
		jsr $ffe4
		sta accu
	};
}

void input_line(char row, char column, char colour, char *s, char max)
{
	unsigned line = row * 40 + column;
	char n = 0;
	for (;;)
	{
		// a blinking cursor
		unsigned o = line + n;
		char under = screen[o];
		char c;
		while (!(c = get_key()))
			screen[o] = (PEEK(0xa2) & 16) ? under ^ 0x80 : under;
		screen[o] = under;

		if (c == PET_RETURN)
			break;
		if (c == PET_DEL)
		{
			if (n)
				char_at(line + --n, colour, ' ');
		}
		else if (((c >= 0x20 && c < 0x60) || (c >= 0xc1 && c <= 0xda)) && n < max)
		{
			char_at(line + n, colour, c);
			s[n++] = c;
		}
	}
	s[n] = 0;
}

char wait_key(void)
{
	while (joystick_fire())
		;
	for (;;)
	{
		char key = get_key();
		if (key)
			return key;
		if (joystick_fire())
			return ' ';
	}
}

char rnd(char n)
{
	return (unsigned)rand() % n;
}
