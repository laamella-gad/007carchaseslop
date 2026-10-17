#include "title.h"
#include "game.h"
#include "frame.h"
#include "plan.h"
#include "sound.h"
#include "system.h"

// All sprites to 0, 0
static void sprites_reset(void)
{
	vic.spr_enable = 0;
	for (char i = 0; i < 8; i++)
		vic.spr_pos[i].x = vic.spr_pos[i].y = 0;
	vic.spr_enable = 0xff;
}

// The credits page
static void credits(void)
{
	sound_off();
	sprites_reset();
	screen_clear(RED);
	show_rows(credits_page);
	wait_key();
}

// The aim of the game, with the cars
static void instructions_cars(void)
{
	credits();
	sprites_reset();
	vic.color_border = BLACK;
	vic.color_back = DARK_GREY;
	vic.spr_mcolor0 = BLACK;
	vic.spr_mcolor1 = RED;
	screen_clear(BLACK);
	text_at(1, 1, BLACK, "  THE AIM OF THIS GAME IS TO SHOOT THE");
	show_rows(aim_page);

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
	show_rows(plan_page);
	wait_key();
}

// The instruction pages
static void instructions(void)
{
	instructions_cars();
	screen_clear(BLACK);
	sprites_reset();
	vic.color_back = DARK_GREY;
	text_at(1, 1, BLACK, "            THE CAR.");
	vic.spr_expand_x = 1;
	// the line under it
	text_at(2, 0, BLACK, "            \xa3\xa3\xa3\xa3\xa3\xa3\xa3\xa3\xa3");
	vic.spr_mcolor0 = BLACK;
	vic.spr_mcolor1 = RED;

	sprite_pointers[0] = SPR_PLAYER;
	vic.spr_color[0] = LIGHT_GREY;
	vic.spr_expand_y++;
	vic.spr_pos[0].x = 150;
	vic.spr_pos[0].y = 150;
	show_rows(car_page);
	wait_key();

	vic.spr_pos[0].x = 0;
	vic.spr_pos[0].y = 0;
	vic.spr_expand_x = 0;
	screen_clear(BLACK);
	show_rows(controls_page);
	// the keys next to the joystick's directions
	text_at(6, 32, CYAN, "KEYS");
	text_at(8, 32, BLACK, "SPACE");
	text_at(10, 32, BLACK, "'.'");
	text_at(13, 9, BLACK, "'Z'");
	text_at(13, 32, BLACK, "'M'");
	text_at(16, 32, BLACK, "','");
	wait_key();
	screen_clear(CYAN);
	show_rows(keys_page);
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
		show_rows(title_page);

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
		// the raster IRQ scrolls the logo
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
	screen_clear(YELLOW);
	text_at(13, 14, YELLOW, "READY");
	vic.spr_expand_x = 0;
	vic.spr_expand_y = 0x80;
	plan_clear_colours();
	plan_new(ROAD_COUNTRY);
}
