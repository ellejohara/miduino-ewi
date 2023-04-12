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
