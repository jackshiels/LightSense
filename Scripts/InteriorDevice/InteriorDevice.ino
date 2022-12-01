// PIR sensor variables
int PIRPin = D0;
int sensorVal = 0;

void setup() {
  // Set up the PIR
  pinMode(PIRPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  delay(100);
  sensorVal = digitalRead(PIRPin);
  if (sensorVal == HIGH){
    Serial.println("1");
  }
  else{
    Serial.println("0");
  }
}
