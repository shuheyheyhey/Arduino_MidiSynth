#include <arduino.h>
#include "keyBourd.h"

keyBourd::keyBourd(int n){ //key init contractor
	this->midi=new midiConect();
	keyOutput=n;
	keyVelocity=0;
	midiPitch=60;
	midiVelo=0;
}

int keyBourd::octaveChange(int oct){ //octave change function
	if(oct==0){
		 keyOutput+=12;
		 midiPitch+=12;
	}else if(oct==1){
		 keyOutput-=12;
		 midiPitch-=12;
	}
	if(keyOutput>120){
		keyOutput=120;
	}
	if(keyOutput<0){
		keyOutput=0;
	}
	return keyOutput;
}

	
int keyBourd::kenban(int keyNumber){ //To push kenban change pitch of tone 
	int keyResponce;
	switch(keyNumber){
		case 0:keyResponce=keyOutput;
		       midi->midiSet(midiPitch,midiVelo);
			break;
		case 1:keyResponce=keyOutput+1;
		       midi->midiSet(midiPitch+1,midiVelo);
			break;
		case 2:keyResponce=keyOutput+2;
		       midi->midiSet(midiPitch+2,midiVelo);
			break;
		case 3:keyResponce=keyOutput+3;
			midi->midiSet(midiPitch+3,midiVelo);
			break;
		case 4:keyResponce=keyOutput+4;
			midi->midiSet(midiPitch+4,midiVelo);
			break;
		case 5:keyResponce=keyOutput+5;
			midi->midiSet(midiPitch+5,midiVelo);
			break;
		case 6:keyResponce=keyOutput+6;
			midi->midiSet(midiPitch+6,midiVelo);
			break;
		case 7:keyResponce=keyOutput+7;
			midi->midiSet(midiPitch+7,midiVelo);
			break;
		case 8:keyResponce=keyOutput+8;
			midi->midiSet(midiPitch+8,midiVelo);
			break;
		case 9:keyResponce=keyOutput+9;
			midi->midiSet(midiPitch+9,midiVelo);
			break;
		case 10:keyResponce=keyOutput+10;
			midi->midiSet(midiPitch+10,midiVelo);
			break;
		case 11:keyResponce=keyOutput+11;
			midi->midiSet(midiPitch+11,midiVelo);
			break;
			
		default:break;
	}
	return keyResponce;
}

int keyBourd::analogToVelocity(int anaRead){ //change from press sensor to velocity 
	keyVelocity=anaRead/7;
	midiVelo=keyVelocity;
	return keyVelocity;
}

	