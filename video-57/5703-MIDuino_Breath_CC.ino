/**
 * MIDuino EWI YouTube Tutorial Code - Part 2
 * written by Astrid Lydia Johannsen
 *
 * YOUTUBE LINK
 * 
 * Copyright 2023 ellejohara
 * GNU General Public License v3 or later
 *
 * This code was used with the Arduino UNO and Arduino Diecimila boards.
 */

#define BREATH_PIN  A0
#define BREATH_ON   50
#define BREATH_MAX  306

#define NOTE_ON     0x90
#define NOTE_WAIT   15
#define NOTE_OFF    0x80
#define VELOCITY	0x7F

int breathSensor, note, noteState;
unsigned long breathMillis = 0L;

void setup() {
	note = 60;
	noteState = NOTE_OFF;
	Serial.begin(9600);
}

void loop() {
	breathSensor = analogRead(BREATH_PIN);

	if (noteState == NOTE_ON) {
		if (breathSensor < BREATH_ON) {
			noteState = NOTE_OFF;
			sendMidi(NOTE_OFF, note, 0);
		}
    }

	if (noteState == NOTE_WAIT) {
		if (millis() - breathMillis >= NOTE_WAIT) {
			noteState = NOTE_ON;
			sendMidi(NOTE_ON, note, VELOCITY);
		}
	}

	if (noteState == NOTE_OFF) {
		if (breathSensor >= BREATH_ON) {
			breathMillis = millis();
			noteState = NOTE_WAIT;
		}
	}
}

void sendMidi(byte command, byte data1, byte data2) {
	Serial.write(command);
	Serial.write(data1);
	Serial.write(data2);
}