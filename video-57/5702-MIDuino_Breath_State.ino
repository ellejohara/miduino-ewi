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

#define NOTE_ON		0x90
#define NOTE_OFF	0x80
#define VELOCITY	0x7F

int breathSensor;

void setup() {
	Serial.begin(9600);
}

void loop() {
	breathSensor = analogRead(BREATH_PIN);
	
	if (breathSensor >= 50) sendMidi(NOTE_ON, 60, VELOCITY);
	
	if (breathSensor < 50) sendMidi(NOTE_OFF, 60, 0);
	
	delay(15);
}

void sendMidi(byte command, byte data1, byte data2) {
	Serial.write(command);
	Serial.write(data1);
	Serial.write(data2);
}