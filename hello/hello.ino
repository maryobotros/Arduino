const int piezo = A1;
const int switchPin = 2;
const int redLed = 5;

int knockVal;
int switchVal;

const int quietKnock = 10;
const int loudKnock = 100;

const int normalKnock = 50;

int numberOfKnocks = 0;

void setup() {
  pinMode(switchPin, INPUT);

}

void loop() {
  // Read the value of vibration from the piezo and store it in knockVal
  knockVal = analogRead(piezo);

  Serial.println("Knock value: ");
  Serial.println(knockVal);
  
  
  
  // Read the switch value 
  switchVal = digitalRead(switchPin);



}
