#include <CapacitiveSensor.h>
#define CAP_THRESHOLD   900
#define DEBOUNCE        200
//Melody Note
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST  0
#define cap_threshold 1000
int tempo = 85;
int buzzer = 0;
int musicState = 0;
boolean play = false;
//Three capacitive sensors
CapacitiveSensor   cs_9_6 = CapacitiveSensor(9,6);        
CapacitiveSensor   cs_9_12 = CapacitiveSensor(9,12);        
CapacitiveSensor   cs_9_10 = CapacitiveSensor(9,10); 

void setup()                    
{
   cs_9_6.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_9_12.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_9_10.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example

   Serial.begin(9600);
}

void playMusicOne(){
    int melodyOne[] = {
    NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
    NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
    NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
    NOTE_D5,-2,
    NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
    NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
    NOTE_FS5,-1,
    NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
    NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,   
    NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
    NOTE_D5,-2,
    NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
    NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
    NOTE_FS5,-1,
    
  };

  int notes = sizeof(melodyOne) / sizeof(melodyOne[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    if(cs_9_6.capacitiveSensor(30) > CAP_THRESHOLD){
      play = false;
      return;
    }

    // calculates the duration of each note
    divider = melodyOne[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melodyOne[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void playMusicTwo(){

    int melodyTwo[] = {
  
    //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=169
    
    NOTE_AS4,-2,  NOTE_F4,8,  NOTE_F4,8,  NOTE_AS4,8,//1
    NOTE_GS4,16,  NOTE_FS4,16,  NOTE_GS4,-2,
    NOTE_AS4,-2,  NOTE_FS4,8,  NOTE_FS4,8,  NOTE_AS4,8,
    NOTE_A4,16,  NOTE_G4,16,  NOTE_A4,-2,
    REST,1, 
  
    NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//7
    NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
    NOTE_AS5,-2,  NOTE_AS5,8,  NOTE_AS5,8,  NOTE_GS5,8,  NOTE_FS5,16,
    NOTE_GS5,-8,  NOTE_FS5,16,  NOTE_F5,2,  NOTE_F5,4, 
  
    NOTE_DS5,-8, NOTE_F5,16, NOTE_FS5,2, NOTE_F5,8, NOTE_DS5,8, //11
    NOTE_CS5,-8, NOTE_DS5,16, NOTE_F5,2, NOTE_DS5,8, NOTE_CS5,8,
    NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8, 
    NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8,
  
    NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//15
    NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
    NOTE_AS5,-2, NOTE_CS6,4,
    NOTE_C6,4, NOTE_A5,2, NOTE_F5,4,
    NOTE_FS5,-2, NOTE_AS5,4,
    NOTE_A5,4, NOTE_F5,2, NOTE_F5,4,
  
    NOTE_FS5,-2, NOTE_AS5,4,
    NOTE_A5,4, NOTE_F5,2, NOTE_D5,4,
    NOTE_DS5,-2, NOTE_FS5,4,
    NOTE_F5,4, NOTE_CS5,2, NOTE_AS4,4,
    NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8, 
    NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8
    
  };
  
  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes=sizeof(melodyTwo)/sizeof(melodyTwo[0])/2; 
  // this calculates the duration of a whole note in ms (60s/tempo)*4 beats
  int wholenote = (60000 * 4) / tempo;
  
  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    if(play == true && cs_9_6.capacitiveSensor(30) > CAP_THRESHOLD){
      play = false;
      return;
    }

    divider = melodyTwo[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    tone(buzzer, melodyTwo[thisNote], noteDuration*0.9);

    delay(noteDuration);
    
    noTone(buzzer);
  }
}

void playMusicThree(){

    int melodyThree[] = {

    NOTE_FS4,2, NOTE_E4,2,
    NOTE_D4,2, NOTE_CS4,2,
    NOTE_B3,2, NOTE_A3,2,
    NOTE_B3,2, NOTE_CS4,2,
    NOTE_FS4,2, NOTE_E4,2,
    NOTE_D4,2, NOTE_CS4,2,
    NOTE_B3,2, NOTE_A3,2,
    NOTE_B3,2, NOTE_CS4,2,
    NOTE_D4,2, NOTE_CS4,2,
    NOTE_B3,2, NOTE_A3,2,
    NOTE_G3,2, NOTE_FS3,2,
    NOTE_G3,2, NOTE_A3,2,
  
    NOTE_D4,4, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,4, NOTE_FS4,8, NOTE_G4,8, 
    NOTE_A4,4, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, 
    NOTE_FS4,4, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,4, NOTE_FS3,8, NOTE_G3,8,
    NOTE_A3,8, NOTE_G3,8, NOTE_FS3,8, NOTE_G3,8, NOTE_A3,2,
    NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_G3,4, NOTE_FS3,8, NOTE_E3,8, 
    NOTE_FS3,4, NOTE_D3,8, NOTE_E3,8, NOTE_FS3,8, NOTE_G3,8, NOTE_A3,8, NOTE_B3,8,
  
    NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_B3,4, NOTE_CS4,8, NOTE_D4,8,
    NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,2,
    NOTE_A4,4, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,4,
    NOTE_FS4,8, NOTE_G4,8, NOTE_A4,8, NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8,
    NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, NOTE_FS4,4, NOTE_D4,8, NOTE_E4,8,
    NOTE_FS4,8, NOTE_CS4,8, NOTE_A3,8, NOTE_A3,8,
  
    NOTE_CS4,4, NOTE_B3,4, NOTE_D4,8, NOTE_CS4,8, NOTE_B3,4,
    NOTE_A3,8, NOTE_G3,8, NOTE_A3,4, NOTE_D3,8, NOTE_E3,8, NOTE_FS3,8, NOTE_G3,8,
    NOTE_A3,8, NOTE_B3,4, NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_B3,4,
    NOTE_CS4,8, NOTE_D4,8, NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8,
    NOTE_FS4,8, NOTE_G4,8, NOTE_A4,2,  
     
    
  };
  
  int notes = sizeof(melodyThree) / sizeof(melodyThree[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  
  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    if(play == true && cs_9_6.capacitiveSensor(30) > CAP_THRESHOLD){
      play = false;
      return;
    }

    divider = melodyThree[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }

    tone(buzzer, melodyThree[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
  
}

void switchMusic(int playPaulse, int nextMusic, int previousMusic){
  if(nextMusic > CAP_THRESHOLD){
    musicState += 1;
    if(musicState > 3){
      musicState = 1;
    }
  }
  if(previousMusic > CAP_THRESHOLD){
    musicState -= 1;
    if(musicState < 1){
      musicState = 3;
    }
  }

  if(play == false &&  playPaulse > CAP_THRESHOLD){
    play = true;
  }else if(play == true && playPaulse > CAP_THRESHOLD){
    play = false;
  }

  if(musicState == 1 && play == true){
    playMusicOne();
  }else if(musicState ==2 && play == true){
    playMusicTwo();
  }else if(musicState == 3 && play == true){
    playMusicThree();
  }
}
void loop()                    
{
    long playPaulse =  cs_9_6.capacitiveSensor(30);
    long nextMusic =  cs_9_12.capacitiveSensor(30);
    long previousMusic =  cs_9_10.capacitiveSensor(30);

    switchMusic(playPaulse, nextMusic, previousMusic);
    Serial.print(playPaulse);                  
    Serial.print("\n");
    Serial.print(nextMusic); 
    Serial.print("\n");
    Serial.println(previousMusic);
    Serial.print("\n");
    Serial.print(play);
    Serial.print("\n");
    Serial.print(musicState);
    Serial.print("\n");
    delay(DEBOUNCE);                        
}
