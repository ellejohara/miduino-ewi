/**
 * MIDuino EWI YouTube Tutorial Code
 * written by Astrid Lydia Johannsen
 *
 * https://www.youtube.com/watch?v=YNRCnk9FI3I
 * 
 * Copyright 2023 ellejohara
 * GNU General Public License v3 or later
 *
 * This code was used with the Arduino UNO and Arduino Diecimila boards.
 */

#define NOTE_ON  0x0090 // 144
#define NOTE_OFF 0x0080 // 128
#define VELOCITY 0x007F // 127

int thePins[] = {2};
#define NUM_PINS sizeof(thePins);

int note = 60;

bool buttonState, prevState;

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(thePins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop() {
  buttonState = !digitalRead(2);
  
  if (buttonState != prevState) {
    if (buttonState == HIGH) {
      sendMidi(144, 60, 127);
    }
    
    if (buttonState == LOW) {
      sendMidi(128, 60, 127);
    }
  }
  
  prevState = buttonState;
}

void sendMidi(byte command, byte data1, byte data2) {
  Serial.write(command);
  Serial.write(data1);
  Serial.write(data2);
}
