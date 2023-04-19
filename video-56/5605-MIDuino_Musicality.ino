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

#define NOTE_ON  0x0090 // 144
#define NOTE_OFF 0x0080 // 128
#define VELOCITY 0x007F // 127

uint8_t thePins[] = {2};
#define NUM_PINS sizeof(thePins);

#define TONIC 60; // middle C
int doubleHarmonic[] = {1, 3, 1, 2, 1, 3, 1};
int scale[8];
int note;

bool buttonState[NUM_PINS], prevState[NUM_PINS];

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(thePins[i], INPUT_PULLUP);
  }
  
  scale[0] = TONIC;
  for (int j = 0; j < 7; j++) {
    note = note + doubleHarmonic[j];
    scale[j + 1] = note;
  }
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < NUM_PINS; i++) {
    buttonState[i] = !digitalRead(2);
    
   if (buttonState[i] != prevState[i]) {
     if (buttonState[i] == HIGH) {
       note = scale[random(8)];
       sendMidi(NOTE_ON, note, VELOCITY);
      }
    
     if (buttonState[i] == LOW) {
        sendMidi(NOTE_OFF, note, 0);
      }
    }
  
    prevState[i] = buttonState[i];
  }
}

void sendMidi(byte command, byte data1, byte data2) {
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
