#include "sound.h"
#include "system.h"
#include "frame.h"

// The tune: 76 notes of (freq hi, freq lo, SR)
static const char tune_notes[228] = {
	#embed "tune_notes.bin"
};

#define TUNE_END    228
#define TUNE_LOOP   93      // note 31

// The offset of the next note; passes through the tune, from 2
static char tune_pos, tune_loops = 2;

// Frames a note
#define TUNE_FRAMES 12
// Below the screen
#define MUSIC_LINE  251

static volatile char music_playing;
static char music_frames;
// Notes left to play, 0 for no end; then the volume goes off when the last
// note's time is up
static volatile char notes_left, sound_end;

// The explosion starts with a hard restart in the raster IRQ: the gate off and
// the envelope 0 for 2 frames, then the noise, so the SID takes it as a new note
static volatile char explosion_frames;

void sound_explosion(void)
{
	explosion_frames = 3;
}

volatile char siren_on;
static unsigned siren_frames;

void sound_siren(unsigned frames)
{
	siren_frames = frames;
	siren_on = 1;
}

static __interrupt void sound_frame(void)
{
	if (explosion_frames)
	{
		if (explosion_frames == 3)
		{
			sid.voices[0].ctrl = 0;
			sid.voices[0].attdec = 0;
			sid.voices[0].susrel = 0;
		}
		else if (explosion_frames == 1)
		{
			sid.fmodevol = 15;
			sid.voices[0].attdec = 0x88;
			sid.voices[0].freq = 0x28c8;
			sid.voices[0].ctrl = SID_CTRL_NOISE | SID_CTRL_GATE;
		}
		explosion_frames--;
	}
	// voice 1 follows voice 3's sawtooth, a step a frame
	if (siren_on)
	{
		((volatile char *)&sid.voices[0].freq)[1] = sid.random;
		if (!--siren_frames)
			siren_on = 0;
	}
}

volatile char frame_count;

// Each frame, from the raster IRQ
static __interrupt void music_frame(void)
{
	frame_count++;
	if (sound_end && !music_playing && !--music_frames)
	{
		sound_end = 0;
		sid.fmodevol = 0;
	}
	if (!music_playing || --music_frames)
		return;
	music_frames = TUNE_FRAMES;

	sid.voices[1].attdec = 0;
	sid.voices[1].ctrl = 0;
	sid.fmodevol = 15;
	sid.voices[1].attdec = 0x09;
	sid.voices[1].ctrl = SID_CTRL_RECT | SID_CTRL_GATE;
	sid.voices[1].pwm = 0x00ff;

	char x = tune_pos;
	sid.voices[1].freq = (tune_notes[x] << 8) | tune_notes[x + 1];
	sid.voices[1].susrel = tune_notes[x + 2];
	tune_pos = x + 3;

	// the last of the notes: the volume off after it
	if (notes_left && !--notes_left)
	{
		music_playing = 0;
		music_frames = TUNE_FRAMES;
		sound_end = 1;
	}

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

// The raster IRQ plays the tune and the sounds, reads the F keys, moves the
// cars, the player and the missile, flashes the hit helicopter and runs the
// title's and the bonus's animations; the KERNAL's 60 Hz CIA IRQ still scans
// the keyboard
__asm music_irq
{
	lda $d019
	and #$01
	beq music_kernal
	sta $d019
	jsr music_frame
	jsr sound_frame
	jsr keys_frame
	jsr cars_frame
	jsr missile_frame
	jsr heli_flash_frame
	jsr anim_frame
	jmp $ea81
music_kernal:
	jmp $ea31
}

void music_init(void)
{
	__asm { sei }
	*(void **)0x0314 = music_irq;
	vic.raster = MUSIC_LINE;
	vic.ctrl1 &= 0x7f;
	vic.intr_ctrl = 0xff;
	vic.intr_enable = 1;
	__asm { cli }
}

void music_on(void)
{
	// the first note on the next frame
	sound_end = 0;
	if (!music_playing)
	{
		music_frames = 1;
		music_playing = 1;
	}
}

void music_off(void)
{
	music_playing = 0;
	notes_left = 0;
	sound_end = 0;
}

void music_notes(char n)
{
	music_off();
	notes_left = n;
	music_on();
}

void tune_restart(void)
{
	tune_pos = 0;
	tune_loops = 2;
}

void sound_off(void)
{
	music_off();
	sid.fmodevol = 0;
}

void sound_crash(char volume)
{
	explosion_frames = 0;
	sid.fmodevol = volume;
	sid.voices[0].ctrl = SID_CTRL_NOISE | SID_CTRL_GATE;
	sid.voices[0].attdec = 15;
	sid.voices[0].freq = 0x28c8;
}

void sound_crash_off(void)
{
	// the envelope to 0 too, so the next step starts a new note
	sid.fmodevol = 0;
	sid.voices[0].ctrl = 0;
	sid.voices[0].attdec = 0;
	sid.voices[0].susrel = 0;
}

void sound_siren_start(void)
{
	for (char i = 0; i < 24; i++)
		((volatile char *)&sid)[i] = 0;
	sid.voices[2].freq = 50;
	sid.voices[0].attdec = 255;
	// volume 15, voice 3 off
	sid.fmodevol = 143;
	sid.voices[0].ctrl = SID_CTRL_TRI | SID_CTRL_GATE;
	sid.voices[2].ctrl = SID_CTRL_SAW | SID_CTRL_GATE;
}


