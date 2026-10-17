// SID sounds: the explosion and the tune from the helper, the crash and the bonus
// from BASIC
#ifndef SOUND_H
#define SOUND_H

// sys50900: noise on voice 1, in the raster IRQ after a hard restart
void sound_explosion(void);

// The tune on voice 2 (sys51000 in the original, one note per call) is played
// by a raster IRQ, a note every TUNE_FRAMES frames, while it is on
void music_init(void);

// Where the original calls sys51000: the tune goes on (from where it was)
void music_on(void);

// The tune stops after its current note; the note sounds on
void music_off(void);

// poke51199,2:poke51198,2: the tune from the top
void tune_restart(void);

// poke54296,0, and the tune off
void sound_off(void);

// Line 6003: one step of the crash noise, volume v (from the raster IRQ)
void sound_crash(char volume);

// Line 6006: the crash noise off
void sound_crash_off(void);

// Lines 13011-13014: the bonus car's siren, voice 1 following voice 3's
// sawtooth. The original takes 501 steps; here the raster IRQ takes one a frame
// for the frames given, and clears siren_on at the end
void sound_siren_start(void);
void sound_siren(unsigned frames);
extern volatile char siren_on;

// Counts the frames, in the raster IRQ below the playfield
extern volatile char frame_count;

#pragma compile("sound.c")

#endif
