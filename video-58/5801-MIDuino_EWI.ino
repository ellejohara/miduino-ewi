/**
 * MIDuino EWI YouTube Tutorial Code - Part 3
 * written by Astrid Lydia Johannsen
 *
 * https://www.youtube.com/watch?v=QJIAJ1hFpyM
 * 
 * Copyright 2023 ellejohara
 * GNU General Public License v3 or later
 *
 * This code was used with the Arduino UNO and Arduino Diecimila boards.
 */

// Breath Sensor Constants
#define BREATH_PIN  A0
#define BREATH_ON   50
#define BREATH_MID  178
#define BREATH_MAX  306

// MIDI Constants
#define NOTE_OFF    0x80
#define NOTE_WAIT   15
#define NOTE_ON     0x90
#define VELOCITY    0x7F
#define MIDI_CC     0xB0
#define CC_CHANNEL  2
#define CC_INTERVAL 50

// Open Key Note is Middle C
#define TONIC       60

// Key Pins
uint8_t thePins[] = {2, 3, 4, 5, 6, 7, 8, 9};
#define NUM_PINS sizeof(thePins)

// Key Variables
int note, newNote, noteState;
byte LH1, LH2, LH3, LH4, RH1, RH2, RH3, RH4;

// Breath Variables
int breathSensor, breathCC;
unsigned long breathMillis = 0L;
unsigned long ccSendTime = 0L;

// Setup
void setup() {
    // Set Pin Mode for Keys
	for (int i = 0; i < NUM_PINS; i++) {
        pinMode(thePins[i], INPUT_PULLUP);
    }

	// Set Initial Note State
	noteState = NOTE_OFF;

	// Initialize Serial Port
	Serial.begin(9600);

	// MIDI Ready Sound Alert
	midiReady();
}

// Loop
void loop() {
	breathSensor = analogRead(BREATH_PIN);

	// NOTE_ON
	if (noteState == NOTE_ON) {
		if (breathSensor >= BREATH_ON && breathSensor < BREATH_MAX) {
			newNote = getNote();
			if (breathSensor >= BREATH_MID) newNote = newNote + 12;

			if (newNote == note) {
				if (millis() - ccSendTime >= CC_INTERVAL) {
					breathCC = map(constrain(breathSensor, BREATH_ON, BREATH_MAX), BREATH_ON, BREATH_MAX, 0, 127);
					sendMidi(MIDI_CC, CC_CHANNEL, breathCC);
                	ccSendTime = millis();
            	}
			}

			if (newNote != note) {
				noteState = NOTE_WAIT;
				sendMidi(NOTE_OFF, note, 0);
			}
		}

		if (breathSensor < BREATH_ON) {
			noteState = NOTE_OFF;
			sendMidi(NOTE_OFF, note, 0);
		}
	}

	// NOTE_WAIT
	if (noteState == NOTE_WAIT) {
		if (millis() - breathMillis >= NOTE_WAIT) {
            note = getNote();
            
            if (breathSensor >= BREATH_MID) note = note + 12;

            noteState = NOTE_ON;
            sendMidi(NOTE_ON, note, VELOCITY);
		}

		if (breathSensor < BREATH_ON) {
			noteState = NOTE_OFF;
		}
	}

	// NOTE_OFF
	if (noteState == NOTE_OFF) {
		if (breathSensor >= BREATH_ON) {
			breathMillis = millis();
			noteState = NOTE_WAIT;
		}
	}
}

// Send MIDI Serial Data
void sendMidi(byte command, byte data1, byte data2) {
	Serial.write(command);
	Serial.write(data1);
	Serial.write(data2);
}

// MIDI Ready Sound Alert
void midiReady() {
	sendMidi(NOTE_ON, 60, 100);
	delay(125);
	sendMidi(NOTE_OFF, 60, 0);
	sendMidi(NOTE_ON, 67, 127);
	delay(125);
	sendMidi(NOTE_OFF, 67, 0);
}

// Buttons
int readButtons() {
    static uint8_t buttonState[NUM_PINS];
	for (int i = 0; i < NUM_PINS; i++) {
    	buttonState[i] = buttonState[i]<<1 | !digitalRead(thePins[i]);
	}

    LH1 = (buttonState[0] == 0xff) ? HIGH : LOW;
	LH2 = (buttonState[1] == 0xff) ? HIGH : LOW;
	LH3 = (buttonState[2] == 0xff) ? HIGH : LOW;
	LH4 = (buttonState[3] == 0xff) ? HIGH : LOW;
	RH1 = (buttonState[4] == 0xff) ? HIGH : LOW;
	RH2 = (buttonState[5] == 0xff) ? HIGH : LOW;
	RH3 = (buttonState[6] == 0xff) ? HIGH : LOW;
	RH4 = (buttonState[7] == 0xff) ? HIGH : LOW;

	return TONIC - LH1 - 2*LH2 - 2*LH3 + LH4 - RH1 - (RH1 && LH3) - RH2 - 2*RH3 - 2*RH4;
}

// Get MIDI Note Value from Buttons
int getNote() {
	int note, newNote;
	note = readButtons();
	delay(5);
	newNote = readButtons();
	return (newNote != note) ? newNote : note;
}