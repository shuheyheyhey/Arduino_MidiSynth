#include <arduino.h>
#include "midiConect.h"

midiConect::midiConect(){
	midiMsg[0]=0x90;
	midiMsg[1]=0;
	midiMsg[2]=0;
}

void midiConect::midiSend(){
	int i;
	Serial.write(176);
	Serial.write(66);
	Serial.write(100);
	
	for(i=0;i<3;i++){
		Serial.write(midiMsg[i]);
	}
}

void midiConect::midiSet(int pitch,int velo){
	midiMsg[1]=pitch;
	midiMsg[2]=velo;
	midiSend();
}