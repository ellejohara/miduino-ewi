#define NOTE_ON  0x0090 // 144
#define NOTE_OFF 0x0080 // 128
#define VELOCITY 0x007F // 127

uint8_t thePins[] = {2};
#define NUM_PINS sizeof(thePins);

int note = 60;

bool buttonState[NUM_PINS], prevState[NUM_PINS];

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(thePins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < NUM_PINS; i++) {
    buttonState[i] = !digitalRead(2);
    
   if (buttonState[i] != prevState[i]) {
     if (buttonState[i] == HIGH) {
       sendMidi(144, 60, 127);
      }
    
     if (buttonState[i] == LOW) {
        sendMidi(128, 60, 127);
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