#include <Servo.h>
Servo myServo;

const int lightSensor = A0;
const int piezo = A1;
const int switchPin = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int redLed = 5;

int knockVal;
int switchVal;
int lightVal;

int angle;

void setup() {
  // Attatch servo to pin 9
  myServo.attach(9);

  // Set lights as outputs and switch as input
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(switchPin, INPUT);

  // Initialize serial communication with computer 
  Serial.begin(9600); 
  // Turn on the yellow led
  digitalWrite(yellowLed, HIGH); 
  // Move the servo to the closed blinds position 
  myServo.write(0); 
  // Output statement indicating blinds are closed
  Serial.println("Blinds are CLOSED"); // right-open, left-close
}

void loop() {
  // Read the value of vibration from the piezo and store it in knockVal
  knockVal = analogRead(piezo);
  
  // Read the value of the switch and store it in switchVal
  switchVal = digitalRead(switchPin);

  // Read the value of the phototransistor and store it in potValue
  lightVal = analogRead(lightSensor); 

  // Print the light value 
  Serial.print("Light value: ");
  Serial.println(lightVal);

  // If it is bright outside 
  if(lightVal > 600){
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

    // Output statement indicating blinds are open
    Serial.println("Blinds are OPEN");

    // Print the knock value 
    Serial.print("Knock value: ");
    Serial.println(knockVal);
    delay(100);

    // Call checkForVibration method
    checkForVibration(knockVal);
  }

  // Else if it is dim outside
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

    // Output statement indicating blinds are closed
    Serial.println("Blinds are CLOSED");

    // Print the knock value 
    Serial.print("Knock value: ");
    Serial.println(knockVal);
    delay(100);

    // Call checkForVibration method
    checkForVibration(knockVal);
  }
}

// Method to check for vibration
void checkForVibration(int knockVal){
  // If a vibration is sensed
  if(knockVal >= 5){
    // Flash red led, output alert,  and close blinds, until the switch deactivates the alarm
    while(switchVal != HIGH){
      Serial.println("!!!!!!!!!!INTRUDER ALERT!!!!!!!!!!");
      myServo.write(0);
      digitalWrite(redLed, HIGH);
      delay(50);
      digitalWrite(redLed, LOW);
      delay(50);
  
      switchVal = digitalRead(switchPin);
      
      // Yellow led should be turned back on and green led should be off
      digitalWrite(yellowLed, HIGH);
      digitalWrite(greenLed, LOW);
    }
  }
}
