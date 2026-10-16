// SID sounds: the explosion and the tune from the helper, the crash and the bonus
// from BASIC
#ifndef SOUND_H
#define SOUND_H

// sys50900: noise on voice 1
void sound_explosion(void);

// sys51000: the next note of the tune on voice 2
void tune_play(void);

// poke51199,2:poke51198,2: the tune from the top
void tune_restart(void);

// poke54296,0
void sound_off(void);

// Line 6003: one step of the crash noise, volume v
void sound_crash(char volume);

// Line 6006: the crash noise off
void sound_crash_off(void);

// Lines 13011-13014: the bonus car's siren, 501 steps of voice 1 following
// voice 3's sawtooth
void sound_siren_start(void);
void sound_siren_step(void);

#pragma compile("sound.c")

#endif
