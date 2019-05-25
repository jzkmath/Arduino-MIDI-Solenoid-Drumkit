# Arduino-MIDI-Solenoid-Drumkit
Uses an Arduino Mega and a custom Shield PCB to drive 14 solenoids (RevA) or 32 solenoids (RevB) via MIDI

## Rev A:
![PCB RevA](https://github.com/jzkmath/Arduino-MIDI-Solenoid-Drumkit/blob/master/KiCAD/RevA/Drumkit%20Render2.png)
## Rev B:
![PCB RevB](https://github.com/jzkmath/Arduino-MIDI-Solenoid-Drumkit/blob/master/KiCAD/RevB/Pluralsight_Drumkit_RevB_Driver/Driver%20Render.png)

This design is based off the [Adafruit Crikit](https://www.adafruit.com/product/3343) and MIDI Solenoid Drumkit that they did, but instead uses a non-blocking delay and can handle more solenoids. The Solenoids are connected to 5V/12V and a Darlington Array (ULN2003A) connects the negative to ground when turned on. 

Just like in the [Adafuit version](https://learn.adafruit.com/midi-solenoid-drummer/overview), the first solenoid corresponds to a C1 (MIDI Note #24) and the following solenoids correspond to the following notes in chromatic order.

## NOTE:
There is a two pin header (J3) that is the programming jumper. The jumper should be installed here and removed when the Arduino is being programmed. This is because the MIDI Rx line is also use to program the Arduino when its being flashed.
