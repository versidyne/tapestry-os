// sound.c -- Initializes and handles onboard system sounds.
//            File Version: 1.2

#include "sound.h"
#include "../drivers/pit.h"
#include "../lib/sound.h"

// System Notes
#define BEEP 2000

//Play sound using built in speaker
void play_sound(u32int nFrequence) {

	u32int Div;
	u8int tmp;

	Div = 1193180 / nFrequence;

	outb(0x43, 0xb6);
	outb(0x42, (u8int) (Div) );
	outb(0x42, (u8int) (Div >> 8));

	tmp = inb(0x61);

	if (tmp != (tmp | 3)) {
		outb(0x61, tmp | 3);
	}

}

//Stop sound from built in speaker
void nosound() {
	
	u8int tmp = (inb(0x61) & 0xFC);
	outb(0x61, tmp);
	
}

//Play note using built in speaker
void play_note(u32int nFrequence, u32int nDuration) {
	
	// Play note
	play_sound(nFrequence);
	
	// Wait for duration
	timer_wait(nDuration);
	
	// Stop sound
	nosound();

}

//Create a beep from built in speaker
void beep() {
	
	play_note(BEEP, HALF);

}

// Attempt to play Twinkle, Twinkle Little Star
void twinkle() {
	
	// Play three beeps prior to playing a song.
	timer_wait(HALF);
	play_note(BEEP, HALF);
	timer_wait(HALF);
	play_note(BEEP, HALF);
	timer_wait(HALF);
	play_note(BEEP, HALF);
	timer_wait(HALF);
	
	// Line 1
	play_note(C4, QUARTER);
	play_note(C4, QUARTER);
	play_note(G4, QUARTER);
	play_note(G4, QUARTER);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, HALF);
	
	play_note(F4, QUARTER);
	play_note(F4, QUARTER);
	play_note(E4, QUARTER);
	play_note(E4, QUARTER);
	
	play_note(D4, QUARTER);
	play_note(D4, QUARTER);
	play_note(C4, HALF);
	
	// Line 2
	play_note(G4, QUARTER);
	play_note(G4, QUARTER);
	play_note(F4, QUARTER);
	play_note(F4, QUARTER);
	
	play_note(E4, QUARTER);
	play_note(E4, QUARTER);
	play_note(D4, HALF);
	
	play_note(G4, QUARTER);
	play_note(G4, QUARTER);
	play_note(F4, QUARTER);
	play_note(F4, QUARTER);
	
	play_note(E4, QUARTER);
	play_note(E4, QUARTER);
	play_note(D4, HALF);
	
	// Line 3
	play_note(C4, QUARTER);
	play_note(C4, QUARTER);
	play_note(G4, QUARTER);
	play_note(G4, QUARTER);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, HALF);
	
	play_note(F4, QUARTER);
	play_note(F4, QUARTER);
	play_note(E4, QUARTER);
	play_note(E4, QUARTER);
	
	play_note(D4, QUARTER);
	play_note(D4, QUARTER);
	play_note(C4, HALF);
	
}

// Attempt to play Mary had a little lamb
void mary() {
	
	// Play three beeps prior to playing a song.
	timer_wait(HALF);
	play_note(BEEP, HALF);
	timer_wait(HALF);
	play_note(BEEP, HALF);
	timer_wait(HALF);
	play_note(BEEP, HALF);
	timer_wait(HALF);
	
	// Line 1
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, HALF);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(A4, HALF);
	
	play_note(B4, QUARTER);
	play_note(DS5, QUARTER);
	play_note(DS5, HALF);
	
	// Line 2
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(G4, WHOLE);
	
	// Line 3
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, HALF);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(A4, HALF);
	
	play_note(B4, QUARTER);
	play_note(DS5, QUARTER);
	play_note(DS5, HALF);
	
	// Line 4
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(G4, HALF);
	play_note(DS5, QUARTER);
	
	// Line 5
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, HALF);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(A4, HALF);
	
	play_note(B4, QUARTER);
	play_note(DS5, QUARTER);
	play_note(DS5, QUARTER);
	play_note(DS5, QUARTER);
	
	// Line 6
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(G4, HALF);
	play_note(DS5, QUARTER);
	
	// Line 7
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, HALF);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(A4, HALF);
	
	play_note(B4, QUARTER);
	play_note(DS5, QUARTER);
	play_note(DS5, QUARTER);
	play_note(DS5, QUARTER);
	
	// Line 8
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	play_note(G4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	play_note(B4, QUARTER);
	
	play_note(A4, QUARTER);
	play_note(A4, QUARTER);
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(G4, WHOLE);
	
}

// Attempt to play the Fur Elise
void felise() {
	
	// Play three beeps prior to playing a song.
	timer_wait(HALF);
	play_note(BEEP, HALF);
	timer_wait(HALF);
	play_note(BEEP, HALF);
	timer_wait(HALF);
	play_note(BEEP, HALF);
	timer_wait(HALF);
	
	// Line 1
	play_note(E5, QUARTER);
	play_note(DS5, QUARTER);
	play_note(E5, QUARTER);
	play_note(DS5, QUARTER);
	
	play_note(E5, QUARTER);
	play_note(B4, QUARTER);
	play_note(D5, QUARTER);
	play_note(C5, QUARTER);
	
	play_note(A4, QUARTER);
	play_note(C4, QUARTER);
	play_note(E4, QUARTER);
	play_note(A4, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(E4, QUARTER);
	play_note(GS4, QUARTER);
	play_note(B4, QUARTER);
	
	play_note(C5, QUARTER);
	
	// Line 2
	play_note(E4, QUARTER);
	play_note(E5, QUARTER);
	play_note(DS5, QUARTER);
	play_note(E5, QUARTER);
	
	play_note(DS5, QUARTER);
	play_note(E5, QUARTER);
	play_note(B4, QUARTER);
	play_note(D5, QUARTER);
	
	play_note(C5, QUARTER);
	play_note(A4, QUARTER);
	play_note(C4, QUARTER);
	play_note(E4, QUARTER);
	
	play_note(A4, QUARTER);
	play_note(B4, QUARTER);
	play_note(E4, QUARTER);
	play_note(C5, QUARTER);
	
	play_note(B4, QUARTER);
	play_note(A4, QUARTER);
	
	// Line 3 (Note 26)
	play_note(B4, QUARTER);
	play_note(C5, QUARTER);
	play_note(D5, QUARTER);
	play_note(E5, QUARTER);
	
	play_note(G4, QUARTER);
	play_note(F5, QUARTER);
	play_note(E5, QUARTER);
	play_note(D5, QUARTER);
	
	//play_note(, QUARTER);
	//play_note(, QUARTER);
	//play_note(, QUARTER);
	//play_note(, QUARTER);
	
}
