#include <MIDI.h>

/*
 * ARDUINO MIDI SOLENOID DRUMKIT
 * By: Jonathan Kayne, 2019
 * 
 * This program uses an Arduino Mega with a custom Shield
 * to drive 32 solenoids as drums.
 * This is based off the Adafruit version, but does not
 * have the same limitations due the use of a non-blocking delay.
 */

 #define NUM_SOLENOIDS 32

 //The delay value in milliseconds for the on time
 #define HIT_DURATION 8

 //variables
 unsigned const solenoidPins[] = {53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22};
 unsigned long prevOnTimeMillis[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //holds the last time the motor was turned on
 bool solenoidState[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW}; //keep track of the solenoid state

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
