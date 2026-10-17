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

// Lines 12400-12420: the credits page
static void credits(void)
{
	sound_off();
	sprites_reset();
	show_rows(rows_12401, 0, 9);
	// line 12420: forx=0to7000:next, 8.4 seconds of "please wait"; here
	// "press fire to continue", and a wait for a key or fire
	wait_key();
}

// Lines 12100-12199: the cars
static void instructions_cars(void)
{
	credits();
	sprites_reset();
	vic.color_border = BLACK;
	vic.color_back = DARK_GREY;
	vic.spr_mcolor0 = BLACK;
	vic.spr_mcolor1 = RED;
	// print"{clr}{blk}{down}{rght}  the aim of this game is to shoot the"
	screen_clear(BLACK);
	text_at(1, 1, BLACK, "  THE AIM OF THIS GAME IS TO SHOOT THE");
	show_rows(rows_12101, 0, 7);

	vic.spr_expand_y = 0;
	vic.spr_expand_x = 0;
	vic.spr_color[0] = RED;
	vic.spr_pos[0].x = 90;
	sprite_pointers[0] = SPR_PLAYER;
	vic.spr_pos[0].y = 130;
	sprite_pointers[1] = SPR_HELICOPTER;
	vic.spr_pos[1].x = 90;
	vic.spr_pos[1].y = 155;
	vic.spr_color[1] = LIGHT_GREY;
	show_rows(rows_12112, 0, 5);
	wait_key();
}

// Lines 12000-12099
static void instructions(void)
{
	instructions_cars();
	screen_clear(BLACK);
	sprites_reset();
	vic.color_back = DARK_GREY;
	// print"{home}{down}{rght}{blk}            the car."
	text_at(1, 1, BLACK, "            THE CAR.");
	vic.spr_expand_x = 1;
	// print"            {CBM-T}x9": the line under it
	text_at(2, 0, BLACK, "            \xa3\xa3\xa3\xa3\xa3\xa3\xa3\xa3\xa3");
	vic.spr_mcolor0 = BLACK;
	vic.spr_mcolor1 = RED;

	sprite_pointers[0] = SPR_PLAYER;
	vic.spr_color[0] = LIGHT_GREY;
	vic.spr_expand_y++;
	vic.spr_pos[0].x = 150;
	vic.spr_pos[0].y = 150;
	show_rows(rows_12020, 0, 14);
	wait_key();

	vic.spr_pos[0].x = 0;
	vic.spr_pos[0].y = 0;
	vic.spr_expand_x = 0;
	show_rows(rows_12041, 0, 18);
	// the keys next to the joystick's directions (not in the original)
	text_at(6, 32, CYAN, "KEYS");
	text_at(8, 32, BLACK, "SPACE");
	text_at(10, 32, BLACK, "'.'");
	text_at(13, 9, BLACK, "'Z'");
	text_at(13, 32, BLACK, "'M'");
	text_at(16, 32, BLACK, "','");
	wait_key();
	show_rows(rows_12070, 0, 13);
	wait_key();
}

void title(void)
{
	char key;
	for (;;)
	{
		screen_clear(WHITE);
		vic.color_border = BLACK;
		vic.color_back = BLACK;
		vic.spr_multi = 0xff;
		sound_off();
		score = 0;
		vic.spr_mcolor0 = RED;
		vic.spr_mcolor1 = LIGHT_GREY;
		sprites_reset();
		bonus_points = 0;
		show_rows(rows_11010, 0, 12);

		// the 007 logo, double width
		static const char logo[4] = {SPR_LOGO, SPR_LOGO + 1, SPR_LOGO + 1, SPR_LOGO + 2};
		static const char logo_x[4] = {95, 145, 190, 235};
		for (char i = 0; i < 4; i++)
		{
			sprite_pointers[i] = logo[i];
			vic.spr_pos[i].x = logo_x[i];
			vic.spr_pos[i].y = 100;
		}
		vic.spr_expand_x = 0xff;
		vic.spr_expand_y = 0;
		tune_restart();

		// the logo scrolls and the tune plays until a key or fire (which
		// starts the game, as space)
		while (get_key())
			;
		music_on();
		// line 11070: the raster IRQ scrolls the logo (sys51900 in the
		// original, 3 pixels a pass of the loop)
		title_on = 1;
		key = wait_key();
		title_on = 0;

		if (key != 'I')
			break;
		instructions();
	}

	sound_off();
	tune_restart();
	sprites_reset();
	// print"{clr}{down}x13{rght}x14{yel}ready"
	screen_clear(YELLOW);
	text_at(13, 14, YELLOW, "READY");
	vic.spr_expand_x = 0;
	vic.spr_expand_y = 0x80;
	plan_clear_colours();
	plan_new();
}
