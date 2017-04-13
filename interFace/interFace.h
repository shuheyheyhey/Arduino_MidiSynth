#include <arduino.h>
#include <Fluxamasynth.h>
#include "keyBourd.h"

#ifndef INTERFACE_H
#define INTERFACE_H

class interFace{
private:
	int keyRes;
	int keyVelo;
	int sampleKeyPitch;
	int alpNumber;
	int choVolCmp;
	int revVolCmp;
	keyBourd* key;
	Fluxamasynth* synth;	
	
public:
	interFace();
	void initAlpNumber();
	int getKey(int keyNum);
	int getVelocity(int velo);
	int getAlp(int alpNum);
	int setOctave(int octNum);
	void setSoundChange(int soundNum);
	void synthSoundOff();
	void setReverbEffectChange(int reverb,int revVol);
	void setChorusEffectChange(int chorus,int choVol);
	void setAlpegiater(int i,int alp,int velo,int vol);

};
#endif
