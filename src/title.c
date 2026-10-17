#include "title.h"
#include "game.h"
#include "helper.h"
#include "plan.h"
#include "sound.h"
#include "system.h"

// pokev+21,0:forx=0to15:pokev+x,0:next:pokev+21,255
static void sprites_reset(void)
{
	vic.spr_enable = 0;
	for (char i = 0; i < 8; i++)
		vic.spr_pos[i].x = vic.spr_pos[i].y = 0;
	vic.spr_enable = 0xff;
}

// print"{clr}": the cursor ends on the row below
static void clear(void)
{
	screen_clear(print_ink());
	print_at(1, 0);
}

// geta$:ifa$=""then...
static void wait_key(void)
{
	while (!get_key())
		;
	pace_restart();
}

// Lines 12400-12420: the credits page
static void credits(void)
{
	sound_off();
	sprites_reset();
	LINE(12400);
	show_rows(rows_12401, 0, 9);
	LINE(12420);
}

// Lines 12100-12199: the cars
static void instructions_cars(void)
{
	credits();
	sprites_reset();
	LINE(12200);
	vic.color_border = BLACK;
	vic.color_back = DARK_GREY;
	vic.spr_mcolor0 = BLACK;
	vic.spr_mcolor1 = RED;
	LINE(12201);
	// print"{clr}{blk}{down}{rght}  the aim of this game is to shoot the"
	screen_clear(print_ink());
	text_at(1, 1, BLACK, "  THE AIM OF THIS GAME IS TO SHOOT THE");
	print_at(2, 0);
	print_set_ink(BLACK);
	spend(CYCLES_12100);
	show_rows(rows_12101, 0, 7);

	vic.spr_expand_y = 0;
	vic.spr_expand_x = 0;
	vic.spr_color[0] = RED;
	vic.spr_pos[0].x = 90;
	sprite_pointers[0] = SPR_PLAYER;
	vic.spr_pos[0].y = 130;
	spend(CYCLES_12110);
	sprite_pointers[1] = SPR_HELICOPTER;
	vic.spr_pos[1].x = 90;
	vic.spr_pos[1].y = 155;
	vic.spr_color[1] = LIGHT_GREY;
	spend(CYCLES_12111);
	show_rows(rows_12112, 0, 5);
	wait_key();
	LINE(12199);
}

// Lines 12000-12099
static void instructions(void)
{
	instructions_cars();
	clear();
	sprites_reset();
	spend(CYCLES_12000);
	vic.color_back = DARK_GREY;
	// print"{home}{down}{rght}{blk}            the car."
	text_at(1, 1, BLACK, "            THE CAR.");
	print_set_ink(BLACK);
	vic.spr_expand_x = 1;
	spend(CYCLES_12001);
	// print"            {CBM-T}x9": the line under it
	text_at(2, 0, BLACK, "            \xa3\xa3\xa3\xa3\xa3\xa3\xa3\xa3\xa3");
	print_at(3, 0);
	spend(CYCLES_12002);
	vic.spr_mcolor0 = BLACK;
	vic.spr_mcolor1 = RED;
	spend(CYCLES_12005);

	sprite_pointers[0] = SPR_PLAYER;
	vic.spr_color[0] = LIGHT_GREY;
	vic.spr_expand_y++;
	vic.spr_pos[0].x = 150;
	vic.spr_pos[0].y = 150;
	spend(CYCLES_12010);
	show_rows(rows_12020, 0, 14);
	wait_key();

	vic.spr_pos[0].x = 0;
	vic.spr_pos[0].y = 0;
	vic.spr_expand_x = 0;
	LINE(12040);
	show_rows(rows_12041, 0, 18);
	wait_key();
	show_rows(rows_12070, 0, 13);
	wait_key();
}

void title(void)
{
	char key;
	for (;;)
	{
		clear();
		vic.color_border = BLACK;
		vic.color_back = BLACK;
		vic.spr_multi = 0xff;
		sound_off();
		score = 0;
		spend(CYCLES_11000);
		vic.spr_mcolor0 = RED;
		vic.spr_mcolor1 = LIGHT_GREY;
		spend(CYCLES_11001);
		sprites_reset();
		bonus_points = 0;
		spend(CYCLES_11002);
		show_rows(rows_11010, 0, 12);

		// the 007 logo, double width
		static const char logo[4] = {SPR_LOGO, SPR_LOGO + 1, SPR_LOGO + 1, SPR_LOGO + 2};
		static const char logo_x[4] = {95, 145, 190, 235};
		static const unsigned long logo_cycles[4] = {CYCLES_11030, CYCLES_11031, CYCLES_11032, CYCLES_11033};
		for (char i = 0; i < 4; i++)
		{
			sprite_pointers[i] = logo[i];
			vic.spr_pos[i].x = logo_x[i];
			vic.spr_pos[i].y = 100;
			spend(logo_cycles[i]);
		}
		vic.spr_expand_x = 0xff;
		vic.spr_expand_y = 0;
		spend(CYCLES_11034);
		tune_restart();
		LINE(11067);

		// the logo scrolls and the tune plays until a key
		while (get_key())
			;
		pace_restart();
		music_on();
		// line 11070: the raster IRQ scrolls the logo (sys51900 in the
		// original, 3 pixels a pass of the loop)
		title_on = 1;
		while (!(key = get_key()))
			;
		title_on = 0;
		pace_restart();

		LINE(11071);
		if (key != 'I')
			break;
		instructions();
	}

	sound_off();
	tune_restart();
	LINE(11072);
	sprites_reset();
	LINE(11078);
	// print"{clr}{down}x13{rght}x14{yel}ready"
	screen_clear(print_ink());
	text_at(13, 14, YELLOW, "READY");
	print_at(14, 0);
	print_set_ink(YELLOW);
	LINE(11079);
	vic.spr_expand_x = 0;
	LINE(11080);
	vic.spr_expand_y = 0x80;
	plan_clear_colours();
	plan_new();
	LINE(11100);
}
