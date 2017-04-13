#include <arduino.h>

#ifndef MIDICONECT_H
#define MIDICONECT_H

class midiConect {
	private:
	int midiMsg[3];
	
	public:
	midiConect();
	void midiSend();
	void midiSet(int pitch,int velo);
};
#endif