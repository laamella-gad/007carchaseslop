#include "system.h"
#include "frame.h"
#include <stdlib.h>

// The KERNAL's jiffy clock, low byte
#define jiffy_clock (*(volatile char *)0xa2)

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
			screen[o] = (jiffy_clock & 16) ? under ^ 0x80 : under;
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
