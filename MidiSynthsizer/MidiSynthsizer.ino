#include <Bounce.h>
#include <Fluxamasynth.h>
#include <NewSoftSerial.h>
#include <PgmChange.h>
#include <interFace.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5,6,7,8,9,10,11); //LCD

interFace inter;
 
//PinNumberSetting
int kenbanPin[12]={0,1,2,3,4,5,6,7,8,9,10,11};  //keyboard
int octavePin[2]={33,35};                       //change octave
int alpegiaterChoicePin[6]={37,36,39,38,41,40};  //kind of alpegiater
int reverbChoicePin[6]={43,42,45,44,47,46};      //kind of effect1
int chorusChoicePin[6]={49,48,51,50,53,52};      //kind of effect2
int programPin=2;                  //change sound
int alpegiaterBPM=13;              //alpegiater speed
int reverbVolume=14;              //effect1 depth
int chorusVolume=12;              //effect2 depth

//statusPin
int octPinStatus[]={0};
int keyStatus[]={0};
int programStatus={0};
int synthNum=0;
int velocity=0;
int volume=0;

//function bounce
Bounce octPin[] = {Bounce(octavePin[0],20),  
                   Bounce(octavePin[1],20)};
                   
Bounce programInter=Bounce(programPin,20);
              
 //setup             
void setup(){
 lcd.begin(16,2);  //lcd display position
 lcd.print("Hello!!");
 lcd.setCursor(0,1);  //lcd display position
 lcd.print("Choice sound!!");
 //set pin
  for(int i=0;i<2;i++){
    pinMode(octavePin[i],INPUT_PULLUP);
  }
  for(int i=0;i<6;i++){
    pinMode(alpegiaterChoicePin[i],INPUT_PULLUP);
    pinMode(reverbChoicePin[i],INPUT_PULLUP);
    pinMode(chorusChoicePin[i],INPUT_PULLUP);
  }
  pinMode(programPin,INPUT_PULLUP);
  //midi baudrate
  Serial.begin(31250);
}

void loop(){
    //keybourd section
    for(int i=0;i<12;i++){
      velocity=analogRead(i);  //the force use in pussing keyboard
      if(velocity<100){
        inter.synthSoundOff();
      }
      if(velocity>100){
       for(int alp=0;alp<6;alp++){  //choice a kind of alpegiater
         if (digitalRead(alpegiaterChoicePin[alp])== LOW){
            volume=analogRead(alpegiaterBPM)/2;  //set apegiater speed
      	    inter.setAlpegiater(i,alp,velocity,volume); 
            if(alp==0) while(analogRead(i)>100);      //no alpegio
         }
       }
       //reverb change section
      for(int reverb=0;reverb<6;reverb++){  //choice a kind of effect
        if (digitalRead(reverbChoicePin[reverb])== LOW){ //pullup
          //LCD display section
          switch(reverb){
            case 0:
                   lcd.setCursor(8, 1); 
                   lcd.print(" ROOM  ");
                   break;
            case 1:
                   lcd.setCursor(8, 1); 
                   lcd.print(" HALL1 ");
                   break;
            case 2:
                   lcd.setCursor(8, 1); 
                   lcd.print(" HALL2");
                   break;
            case 3:
                   lcd.setCursor(8, 1); 
                   lcd.print(" Plate ");
                   break;
            case 4:
                   lcd.setCursor(8, 1); 
                   lcd.print(" Delay ");
                   break;
            case 5:
                   lcd.setCursor(8, 1); 
                   lcd.print(" PanDel");
                   break;
            }
          inter.setReverbEffectChange(reverb+2,analogRead(reverbVolume)/8);
        }
      }
      //chorus change section
      for(int chorus=0;chorus<6;chorus++){  //choice a kind of effect
        if (digitalRead(chorusChoicePin[chorus])== LOW){
          //LCD display section
           switch(chorus){
            case 0:
                   lcd.setCursor(0, 1); 
                   lcd.print("Chorus1 ");
                   break;
            case 1:
                   lcd.setCursor(0, 1); 
                   lcd.print("Chorus2 ");
                   break;
            case 2:
                   lcd.setCursor(0, 1); 
                   lcd.print("Feedback");
                   break;
            case 3:
                   lcd.setCursor(0, 1); 
                   lcd.print("Flanger ");
                   break;
            case 4:
                   lcd.setCursor(0, 1); 
                   lcd.print("ShortDel");
                   break;
            case 5:
                   lcd.setCursor(0, 1); 
                   lcd.print("FeedDel ");
                   break;
          }
        inter.setChorusEffectChange(chorus+2,analogRead(chorusVolume)/8);
        }
      }
    }
    }
    
     //octave change section
     for(int oct=0;oct<2;oct++){
      octPin[oct].update();
      if ((octPin[oct].read() == HIGH)&&(octPinStatus[oct] == 0)) { 
        octPinStatus[oct] = 1;
      }
      if((octPin[oct].read() == LOW)&&(octPinStatus[oct] == 1)) { 
        delay(20);
        inter.setOctave(oct);
        octPinStatus[oct] = 0;
        
     }
  }
  //program change section
  programInter.update();
  if((programInter.read() == HIGH) && programStatus==0){
     programStatus=1;
  }
  if((programInter.read() == LOW) && programStatus==1){
    delay(20);
  inter.setSoundChange(synthNum);
  programStatus=0;
  //LCD display section
  switch(synthNum){
    case 0:
          lcd.setCursor(0, 0); 
          lcd.print("Sound:Piano   ");
          break;
     case 1:
           lcd.setCursor(0, 0); 
          lcd.print("Sound:Marinba   ");
          break;
     case 2:
           lcd.setCursor(0, 0); 
          lcd.print("Sound:Game     ");
          break;
     case 3:
            lcd.setCursor(0, 0); 
          lcd.print("Sound:Bass     ");
          break;
     case 4:
            lcd.setCursor(0, 0); 
          lcd.print("Sound:synth     ");
          break;
     case 5:
            lcd.setCursor(0, 0); 
          lcd.print("Sound:star     ");
          break;
  }
  synthNum++;
  if(synthNum==6) synthNum=0;
  }
}
  
