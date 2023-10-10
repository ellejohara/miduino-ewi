/**
 * MIDuino EWI YouTube Tutorial Code - Part 1
 * written by Astrid Lydia Johannsen
 *
 * https://www.youtube.com/watch?v=YNRCnk9FI3I
 * 
 * Copyright 2023 ellejohara
 * GNU General Public License v3 or later
 *
 * This code was used with the Arduino UNO and Arduino Diecimila boards.
 */

#define NOTE_ON  0x90
#define NOTE_OFF 0x80
#define VELOCITY 0x7F

uint8_t thePins[] = {2};
#define NUM_PINS sizeof(thePins)

bool buttonState[NUM_PINS], prevState[NUM_PINS];

int note = 60; // C3

void setup() {
    for (int i = 0; i < NUM_PINS; i++) {
        pinMode(thePins[i], INPUT_PULLUP);
    }
    Serial.begin(9600);
    Serial.println("READY");
}

void loop() {
    for (int i = 0; i < NUM_PINS; i++) {
        buttonState[i] = debounce(i);

        if (buttonState[i] != prevState[i]) {
            if (buttonState[i] == HIGH) {
				sendMidi(NOTE_ON, note, VELOCITY);
			}
			if (buttonState[i] == LOW) {
				sendMidi(NOTE_OFF, note, 0);
			}
        }

        prevState[i] = buttonState[i];
    }
}

void sendMidi(byte command, byte, data1, byte data2) {
	Serial.write(command);
	Serial.write(data1);
	Serial.write(data2);
}

bool debounce(int i) {
    static uint8_t state[NUM_PINS];
    state[i] = state[i]<<1 | !digitalRead(thePins[i]);
    delay(1);
    return (state[i] == 0xff) ? HIGH : LOW;
}