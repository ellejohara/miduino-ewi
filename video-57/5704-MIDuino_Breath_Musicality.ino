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

#define NOTE_OFF    0x80
#define NOTE_WAIT   15
#define NOTE_ON     0x90
#define VELOCITY    0x7F

#define MIDI_CC     0xB0
#define CC_CHANNEL  2
#define CC_INTERVAL 50

int breathSensor, breathCC, note, noteState;
unsigned long breathMillis = 0L;
unsigned long ccSendTime = 0L;

#define TONIC       60
int doubleHarmonic[] = {1, 3, 1, 2, 1, 3, 1};
int scale[8];

void setup() {
	note = TONIC;
	scale[0] = TONIC;
	for (int i = 0; i < 7; i++) {
		note = note + doubleHarmonic[i];
		scale[i + 1] = note;
	}
	noteState = NOTE_OFF;
	Serial.begin(9600);
	midiReady();
}

void loop() {
	breathSensor = analogRead(BREATH_PIN);

	if (noteState == NOTE_ON) {
		if (breathSensor >= BREATH_ON && breathSensor < BREATH_MAX) {
			breathCC = map(constrain(breathSensor, BREATH_ON, BREATH_MAX), BREATH_ON, BREATH_MAX, 0, 127);

            if (millis() - ccSendTime >= CC_INTERVAL) {
                sendMidi(MIDI_CC, CC_CHANNEL, breathCC);
                ccSendTime = millis();
            }
		}

		if (breathSensor < BREATH_ON) {
			noteState = NOTE_OFF;
			sendMidi(NOTE_OFF, notePlaying, 0);
		}
	}

	if (noteState == NOTE_WAIT) {
		if (millis() - breathMillis >= NOTE_WAIT) {
			noteState = NOTE_ON;
            note = getNote();
            sendMidi(NOTE_ON, note, VELOCITY);
		}

		if (breathSensor < BREATH_ON) {
			noteState = NOTE_OFF;
		}
	}

	if (noteState == NOTE_OFF) {
		if (breathSensor >= BREATH_ON) {
			breathMillis = millis();
			noteState = NOTE_WAIT;
		}
	}
}

int getNote() {
	return scale[random(8)];
}

void sendMidi(byte command, byte data1, byte data2) {
	Serial.write(command);
	Serial.write(data1);
	Serial.write(data2);
}

void midiRready() {
	sendMidi(NOTE_ON, 60, 100);
	delay(125);
	sendMidi(NOTE_OFF, 60, 0);
	sendMidi(NOTE_ON, 67, 127);
	delay(125);
	sendMidi(NOTE_OFF, 67, 0);
}