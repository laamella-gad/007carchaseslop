#include "game.h"
#include "system.h"
#include "helper.h"
#include "sound.h"
#include "cars.h"

long score, bonus_points;
signed char lives;
char crashed, player_sprite, enemy_sprite;
unsigned distance;
char plan_pos;
char plan[11];

void play_rows(const Row *rows, char from, char to)
{
	for (char i = from; i < to; i++)
	{
		const Row *r = rows + i;
		char ops = r->ops;
		if (ops & OP_TUNE)
			music_on();
		if (ops & OP_FRAME)
			frame_update();
		if (ops & OP_TURBO)
			turbo_frame();
		if (ops & OP_WEAPON)
			weapon_update();
		print(r->text);
		if (ops & OP_NEWLINE)
			put(PET_RETURN);
		pace(r->cycles);
		// a crash goes on after the row it happens in, not at the next
		// collision pass
		crash_check();
	}
}
