// SID sounds: the explosion, the tune, the crash and the bonus car's siren
#ifndef SOUND_H
#define SOUND_H

// Noise on voice 1, in the raster IRQ after a hard restart
void sound_explosion(void);

// The tune on voice 2 is played by a raster IRQ, a note every TUNE_FRAMES
// frames, while it is on
void music_init(void);

// The tune goes on (from where it was)
void music_on(void);

// The tune stops after its current note; the note sounds on
void music_off(void);

// The tune goes on for n notes, then the volume goes to 0 (in the raster IRQ)
void music_notes(char n);

// The tune from the top
void tune_restart(void);

// The volume and the tune off
void sound_off(void);

// One step of the crash noise, volume v (from the raster IRQ)
void sound_crash(char volume);

// The crash noise off
void sound_crash_off(void);

// The bonus car's siren, voice 1 following voice 3's sawtooth: the raster IRQ
// takes a step a frame for the frames given, and clears siren_on at the end
void sound_siren_start(void);
void sound_siren(unsigned frames);
extern volatile char siren_on;

// Counts the frames, in the raster IRQ below the playfield
extern volatile char frame_count;

#pragma compile("sound.c")

#endif
