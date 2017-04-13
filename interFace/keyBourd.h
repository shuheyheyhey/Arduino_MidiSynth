#include <arduino.h>
#include "midiConect.h"

#ifndef KEYBOURD_H
#define KEYBOURD_H

class keyBourd {
	private:
	int keyOutput; //output key picth
	int keyVelocity; //output key velocity
	int midiPitch;
	int midiVelo;
	
	public:
	keyBourd(int n); //constracter
	int octaveChange(int oct);
	int kenban(int keyNumber);
	int analogToVelocity(int anaRead);
	midiConect* midi;
};	
#endif 