#include <arduino.h>
#include <Fluxamasynth.h>
#include "interFace.h"


interFace::interFace(){
	this->synth=new Fluxamasynth();	
	this->key = new keyBourd(48);	//initialize code C
	keyVelo=alpNumber=sampleKeyPitch=keyRes=revVolCmp=choVolCmp=0;
}

void interFace::initAlpNumber(){
	alpNumber=0;
}

int interFace::getKey(int keyNum){
	keyRes=key->kenban(keyNum);	//which key push
	return keyRes; 
}

int interFace::getVelocity(int velo){
	keyVelo=key->analogToVelocity(velo);	//the force use in pussing 
	return keyVelo;
}

int interFace::getAlp(int alpNum){
	//aplpegiater sound program
	int alp1[]={0,7,5,2,4};	
	int alp2[]={0,4,7,4};
	int alp3[]={0,12,5,12};
	int alp4[]={0,5,19};
	int endnum=0;
	switch(alpNum){
		case 0:return 0;
			break;
		case 1:return 0;
			break;
		case 2: 
			alpNumber++;
			if(alpNumber==5) alpNumber=0;
			return alp1[alpNumber];
			break;
		case 3:
			
			alpNumber++;
			if(alpNumber==4) alpNumber=0;
			return alp2[alpNumber];
			break;
		case 4:
			alpNumber++;
			if(alpNumber==4) alpNumber=0;
			return alp3[alpNumber];
			break;
	
		case 5:
			alpNumber++;
			if(alpNumber==3) alpNumber=0;
			return alp4[alpNumber];
			break;
	}
}


int interFace::setOctave(int octNum){
	sampleKeyPitch=key->octaveChange(octNum);	//set pitch
	return sampleKeyPitch;
}
	
void interFace::setSoundChange(int soundNum){
	switch(soundNum){
		case 0:
			synth->programChange(0,0,80);
			delay(5);
			synth->programChange(0,1,81);
			delay(5);
			break;
		case 1: 
			synth->programChange(0,0,12);
			delay(5);
			synth->programChange(127,1,98);
			
			delay(5);
			break;
		case 2: 
			synth->programChange(0,0,38);
			delay(5);
			synth->programChange(127,1,116);
			
			delay(5);
			break;
		case 3: 
			synth->programChange(0,0,87);
			delay(5);
			synth->programChange(0,1,90);
			delay(5);
			break;
		case 4: 
			synth->programChange(0,0,102);
			delay(5);
			synth->programChange(127,1,44);
			delay(5);
			break;
		case 5: 
			synth->programChange(0,0,10);
			delay(5);
			synth->programChange(127,1,7);
			delay(5);
			break;
		}
}

void interFace::synthSoundOff(){
	synth->allNotesOff(0);
	synth->allNotesOff(1);
}

void interFace::setAlpegiater(int i,int alp,int velo,int vol){
	synth->noteOn(0,getKey(i)+getAlp(alp),getVelocity(velo));
	synth->noteOn(1,getKey(i)+getAlp(alp),getVelocity(velo));
	if(alp!=0)	
		delay(vol);
	/*if(alp==0){
		synth->pitchBendRange(0,2);
	 	while (i < vol+300) {
    			synth->pitchBend(0, i);
    			i+= 16;
    			delay(10);
  		}

  		while (i > 0){
    			synth->pitchBend(0, i);
    			i-= 16;
    			delay(10);
 		 }
	}*/
}

void interFace::setReverbEffectChange(int reverb,int revVol){
	if(revVolCmp!=revVol){
		 synth->setReverb(0,reverb,revVol,revVol);
		// synth->setReverb(1,reverb,revVol,revVol);
		 revVolCmp=revVol;
	}
}

void interFace::setChorusEffectChange(int chorus,int choVol){
	if(choVolCmp!=choVol) synth->setChorus(1,chorus,choVol,choVol,choVol);
	choVolCmp=choVol;
}