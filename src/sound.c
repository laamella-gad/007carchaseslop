#include "sound.h"
#include "system.h"

// The tune: 76 notes of (freq hi, freq lo, SR)
static const char tune_notes[228] = {
	#embed "tune_notes.bin"
};

#define TUNE_END    228
#define TUNE_LOOP   93      // note 31

// The offset of the next note; passes through the tune, from 2
static char tune_pos, tune_loops = 2;

void sound_explosion(void)
{
	sid.fmodevol = 0;
	sid.voices[0].ctrl = 0;
	sid.voices[0].attdec = 0;
	sid.fmodevol = 15;
	sid.voices[0].ctrl = SID_CTRL_NOISE | SID_CTRL_GATE;
	sid.voices[0].attdec = 0x88;
	sid.voices[0].freq = 0x28c8;
}

void tune_play(void)
{
	sid.voices[1].attdec = 0;
	sid.voices[1].ctrl = 0;
	sid.fmodevol = 15;
	sid.voices[1].attdec = 0x09;
	sid.voices[1].ctrl = SID_CTRL_RECT | SID_CTRL_GATE;
	sid.voices[1].pwm = 0x00ff;

	// The original starts at the second note and plays two notes from past the
	// end of the table; this plays the 76 notes of the table
	char x = tune_pos;
	sid.voices[1].freq = (tune_notes[x] << 8) | tune_notes[x + 1];
	sid.voices[1].susrel = tune_notes[x + 2];
	tune_pos = x + 3;

	// at the end: back to note 31, and after 3 times from the top
	if (tune_pos == TUNE_END)
	{
		tune_pos = TUNE_LOOP;
		if (++tune_loops == 5)
		{
			tune_pos = 0;
			tune_loops = 2;
		}
	}
}

void tune_restart(void)
{
	tune_pos = 0;
	tune_loops = 2;
}

void sound_off(void)
{
	sid.fmodevol = 0;
}

void sound_crash(char volume)
{
	sid.fmodevol = volume;
	sid.voices[0].ctrl = SID_CTRL_NOISE | SID_CTRL_GATE;
	sid.voices[0].attdec = 15;
	sid.voices[0].freq = 0x28c8;
}

void sound_crash_off(void)
{
	sid.fmodevol = 0;
	sid.voices[0].ctrl = 0;
}

void sound_siren_start(void)
{
	for (char i = 0; i < 24; i++)
		POKE(0xd400 + i, 0);
	sid.voices[2].freq = 50;
	sid.voices[0].attdec = 255;
	// volume 15, voice 3 off
	sid.fmodevol = 143;
	sid.voices[0].ctrl = SID_CTRL_TRI | SID_CTRL_GATE;
	sid.voices[2].ctrl = SID_CTRL_SAW | SID_CTRL_GATE;
}

void sound_siren_step(void)
{
	POKE(0xd401, PEEK(0xd41b));
}
