#include <MIDI.h>

/*
 * ARDUINO MIDI SOLENOID DRUMKIT
 * By: Jonathan Kayne, 2019
 * For use at Pluralsight Live 2019
 * 
 * This program uses an Arduino Mega with a custom Shield
 * to drive 14 solenoids as drums.
 * This is based off the Adafruit version, but does not
 * have the same limitations due the use of a non-blocking delay.
 */

 //Pins
 #define SOLENOID_1 2
 #define SOLENOID_2 3
 #define SOLENOID_3 4
 #define SOLENOID_4 5
 #define SOLENOID_5 6
 #define SOLENOID_6 7
 #define SOLENOID_7 8
 #define SOLENOID_8 9
 #define SOLENOID_9 10
 #define SOLENOID_10 11
 #define SOLENOID_11 12
 #define SOLENOID_12 13
 #define SOLENOID_13 14
 #define SOLENOID_14 15

 #define NUM_SOLENOIDS 14

 //The delay value in milliseconds for the on time
 #define HIT_DURATION 8

 //variables
 unsigned long solenoidPins[] = {SOLENOID_1, SOLENOID_2, SOLENOID_3, SOLENOID_4, SOLENOID_5, SOLENOID_6, SOLENOID_7, SOLENOID_8, SOLENOID_9, SOLENOID_10, SOLENOID_11, SOLENOID_12, SOLENOID_13, SOLENOID_14};
 unsigned long prevOnTimeMillis[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //holds the last time the motor was turned on
 bool solenoidState[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW}; //keep track of the solenoid state

 MIDI_CREATE_DEFAULT_INSTANCE(); //use default MIDI settings
 

void setup() {
  //set solenoids as outputs
  for (int s = 0; s < NUM_SOLENOIDS; s++)
  {
    pinMode(solenoidPins[s], OUTPUT);
  }
 
  MIDI.begin(MIDI_CHANNEL_OMNI); //listen to all MIDI channels
  MIDI.setHandleNoteOn(handleNoteOn); //execute function when note on message is recieved
}

void loop() 
{
  MIDI.read(); //read MIDI messages
  turnOffSolenoid();  //reset solenoid after a certain duration
}

void handleNoteOn(byte channel, byte pitch, byte velocity) //MIDI Note ON Command
{
  int solenoid = pitch - 24; //which solenoid to activate
  // when a C1 is played, the first solenoid will be selected, because 
  // MIDI pitch 24 corresponds to C1.

  digitalWrite(solenoidPins[solenoid], HIGH); //turn on selected solenoid
  solenoidState[solenoid] = HIGH; //set state to true
  prevOnTimeMillis[solenoid] = millis(); //update time
  
}

void turnOffSolenoid()
{
  for (int i = 0; i < NUM_SOLENOIDS; i++)
  {
    //when the time has elapsed and the solenoid is on turn off the solenoid
    if ((millis() - prevOnTimeMillis[i] >= HIT_DURATION) && (solenoidState == 1))
    {
      digitalWrite(solenoidPins[i], LOW);
      solenoidState[i] = LOW;
    }
  }
}
