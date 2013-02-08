// sound.h -- Defines the all onboard sound-related functions.
//            File Version: 1.2

#ifndef SOUND_H
#define SOUND_H

#include "../core/common.h"

//Play sound using built in speaker
void play_sound(u32int nFrequence);

//Stop sound from built in speaker
void nosound();

//Play note using built in speaker
void play_note(u32int nFrequence, u32int nDuration);

//Create a beep from built in speaker
void beep();

// Attempt to play Twinkle, Twinkle Little Star
void twinkle();

// Attempt to play Mary had a little lamb
void mary();

// Attempt to play the Fur Elise
void felise();

#endif
