#include <Servo.h>
Servo myServo;

int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int piezo = 9;
const int switchPin = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int redLed = 5;

int knockVal;
int switchVal;

int potVal;
int angle;

boolean isOpen;

void setup() {
  // Attatch servo to pin 9
  myServo.attach(9);

  // Set lights as outputs and switch as input
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(switchPin, INPUT);

  Serial.begin(9600); // Initialize serial communication with computer 
  digitalWrite(redLed, HIGH); // Turn on the green led
  myServo.write(0); // Move the servo to the locked position 
  Serial.println("Blinds are open"); // right-close, left-open

  sensorValue = analogRead(A0); 
}

void loop() {
  sensorValue = analogRead(A0);
  potVal = analogRead(sensorValue);
  Serial.println("Light value: ");
  Serial.println(potVal);

  // If it is bright outside 
  if(potVal > 600){
    // Open the blinds 
    angle = 180;
    Serial.println("Angle: ");
    Serial.println(angle);
    myServo.write(angle);
    delay(1000);
  }
  else{
    angle = 0;
    Serial.println(", angle ");
    Serial.println(angle);
    myServo.write(angle);
    delay(1000);
  }
  
//   sensorValue = analogRead(A0);
//   potVal = analogRead(sensorValue);
//   Serial.println("potVal: ");
//   Serial.println(potVal);
//   delay(1000);
//   
//   // As long as the switch has been pressed
//   while(switchVal == HIGH){
//    // If the 
//    if(potVal >= 400){
//      angle = 90;
//      myServo.write(angle);
//      Serial.println("Angle moved");
//      delay(1000);
//    } 
  
}
