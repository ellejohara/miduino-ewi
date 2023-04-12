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

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write(144);
  Serial.write(60);
  Serial.write(127);
  delay(250);
  
  Serial.write(128);
  Serial.write(60);
  Serial.write(0);
  delay(250);
}
