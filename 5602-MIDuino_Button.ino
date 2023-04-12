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

bool buttonState, prevState;

void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  buttonState = !digitalRead(2);
  
  if (buttonState != prevState) {
    if (buttonState == HIGH) {
      Serial.write(144);
      Serial.write(60);
      Serial.write(127);
      delay(250);
    }
    
    if (buttonState == LOW) {
      Serial.write(128);
      Serial.write(60);
      Serial.write(0);
      delay(1000);
    }
  }
  
  prevState = buttonState;
}
