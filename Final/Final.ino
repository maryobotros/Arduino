#include <Servo.h>
Servo myServo;

int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int piezo = A1;
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
  digitalWrite(yellowLed, HIGH); // Turn on the green led
  myServo.write(0); // Move the servo to the locked position 
  Serial.println("Blinds are CLOSED"); // right-close, left-open

  sensorValue = analogRead(A0); 
}

void loop() {
  // Read the value of vibration from the piezo and store it in knockVal
  knockVal = analogRead(piezo);
  switchVal = digitalRead(switchPin);

  
  sensorValue = analogRead(A0);
  potVal = analogRead(sensorValue);
  Serial.print("Light value: ");
  Serial.println(potVal);

  // If it is bright outside 
  if(potVal > 600){
    // Open the blinds 
    angle = 180;
    Serial.print("Angle: ");
    Serial.println(angle);
    myServo.write(angle);
    delay(1000);

    // Turn on the green Led
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);

    // Output statement
    Serial.println("Blinds are OPEN");

    Serial.print("Knock value: ");
    Serial.println(knockVal);
    delay(100);
  
    if(knockVal >= 50){
      while(switchVal != HIGH){
        Serial.println("!!!!!!!!!!INTRUDER ALERT!!!!!!!!!!");
        myServo.write(0);
        digitalWrite(redLed, HIGH);
        delay(50);
        digitalWrite(redLed, LOW);
        delay(50);
  
        switchVal = digitalRead(switchPin);
      }
    }
  }

  // If it is dim outside
  else{
    // Close the blinds
    angle = 0;
    Serial.print("Angle ");
    Serial.println(angle);
    myServo.write(angle);
    delay(1000);

    // Turn on the yellow Led
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);

    // Output statement
    Serial.println("Blinds are CLOSED");
    
    Serial.print("Knock value: ");
    Serial.println(knockVal);
    delay(100);
    
    if(knockVal >= 50){
      while(switchVal != HIGH){
        Serial.println("!!!!!!!!!!INTRUDER ALERT!!!!!!!!!!");
        myServo.write(0);
        digitalWrite(redLed, HIGH);
        delay(50);
        digitalWrite(redLed, LOW);
        delay(50);
  
        switchVal = digitalRead(switchPin);
      }
    }
  }
}
