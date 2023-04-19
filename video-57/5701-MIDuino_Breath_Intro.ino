/**
 * MIDuino EWI YouTube Tutorial Code - Part 2
 * written by Astrid Lydia Johannsen
 *
 * https://www.youtube.com/watch?v=93xHCjz47Ic
 * 
 * Copyright 2023 ellejohara
 * GNU General Public License v3 or later
 *
 * This code was used with the Arduino UNO and Arduino Diecimila boards.
 */

#define BREATH_PIN	A0

int breathSensor;

void setup() {
	Serial.begin(9600);
}

void loop() {
	breathSensor = analogRead(BREATH_PIN);
	
	Serial.println(breathSensor);
	
	delay(100);
}