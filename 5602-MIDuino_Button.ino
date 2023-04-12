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
