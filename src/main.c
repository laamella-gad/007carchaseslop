// 007 Car Chase, (c) Coplin Software, rewritten in C for oscar64
#include "system.h"
#include "frame.h"
#include "sound.h"
#include "game.h"
#include "plan.h"
#include "road.h"
#include "title.h"
#include "hiscore.h"

// VIC bank 0: the screen at $0400, the sprites at blocks 40-59 ($0a00-$0eff),
// the ROM character set. Code and data go after them, up to $a000
#pragma region(main, 0x0f00, 0xa000, , , {code, data, bss, heap, stack})
#pragma stacksize(1024)
#pragma heapsize(0)

#pragma section(sprites, 0)
#pragma region(sprites, 0x0a00, 0x0f00, , , {sprites})

#pragma data(sprites)
__export const char sprite_data[] = {
	#embed "sprites_40_54.bin"
	#embed "sprites_13_15.bin"
	#embed "sprites_33_34.bin"
};
#pragma data(data)

int main(void)
{
	music_init();

	vic.color_border = BLACK;
	vic.color_back = BLACK;
	vic.spr_enable = 0;
	turbo = 0;
	text_init();
	screen_clear(WHITE);
	vic.spr_multi = 0xff;
	vic.spr_mcolor0 = BLACK;
	vic.spr_mcolor1 = RED;

	for (;;)
	{
		// each game
		weapon_state = WEAPON_FREE;
		lives = 3;
		player_sprite = SPR_PLAYER;
		enemy_sprite = SPR_ENEMY;
		distance = 0;
		vic.spr_color[7] = YELLOW;
		vic.spr_expand_y = 0x80;
		sprite_pointers[6] = SPR_BOMB;
		// the credit row
		for (char i = 0; i < 21; i++)
			colour_ram[23 * 40 + 5 + i] = YELLOW;
		hiscore();

		title();
		game();
		motion_on = 0;
		crash_pending = 0;
	}
	return 0;
}
