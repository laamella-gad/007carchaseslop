// 007 Car Chase, (c) Coplin Software, rewritten in C for oscar64
#include "system.h"
#include "helper.h"
#include "sound.h"
#include "game.h"
#include "plan.h"
#include "road.h"
#include "title.h"
#include "hiscore.h"

// VIC bank 0 as in the original: the screen at $0400, the sprites at blocks
// 40-59 ($0a00-$0eff), the ROM character set. Code and data go after them, up to
// the BASIC ROM
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
	system_init();
	music_init();

	// lines 2-4
	vic.color_border = BLACK;
	vic.color_back = BLACK;
	vic.spr_enable = 0;
	turbo = 0;
	print(t2);
	put(PET_RETURN);
	vic.spr_multi = 0xff;
	vic.spr_mcolor0 = BLACK;
	vic.spr_mcolor1 = RED;

	for (;;)
	{
		// lines 39-44, also after each game
		weapon_state = WEAPON_FREE;
		lives = 3;
		player_sprite = SPR_PLAYER;
		enemy_sprite = SPR_ENEMY;
		distance = 0;
		LINE(39);
		vic.spr_color[7] = YELLOW;
		vic.spr_expand_y = 0x80;
		LINE(40);
		sprite_pointers[6] = SPR_BOMB;
		LINE(41);
		// the credit row
		for (char i = 0; i < 21; i++)
			colour_ram[23 * 40 + 5 + i] = YELLOW;
		LINE(42);
		plan_road = ROAD_COUNTRY;
		hiscore();
		LINE(43);

		title();
		game();
	}
	return 0;
}
