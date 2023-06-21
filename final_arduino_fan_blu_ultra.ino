#include <HCSR04.h>

UltraSonicDistanceSensor ultrasonic1(A0, A1);
UltraSonicDistanceSensor ultrasonic2(A2, A3);
UltraSonicDistanceSensor ultrasonic3(A4, A5);   // Add a third ultrasonic sensor

float distance1, distance2, distance3;   // Declare a variable for each sensor distance
int rightMotor1 = 12;  
int rightMotor2 = 5;
int leftMotor1 =13; 
int leftMotor2 = 4;
int enA = 9;
int enB = 3;

int fanPin = 8; 

void setup() {
  Serial.begin(9600);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(fanPin, OUTPUT);
}

void loop() {

  byte command = Serial.read(); 
 
  if (command == 'u') { 
    stop();      
    digitalWrite(fanPin, LOW);    
  }
  else if (command == 'f') {
    digitalWrite(fanPin, HIGH); 
  }
 
  

 
  // Measure the distance for each sensor
  distance1 = ultrasonic1.measureDistanceCm();
  distance2 = ultrasonic2.measureDistanceCm();
  distance3 = ultrasonic3.measureDistanceCm();
   
  // Check if any of the sensors detect an obstacle
  if ((distance1 > -1 && distance1 < 25) || (distance2 > -1 && distance2 < 15) || (distance3 > -1 && distance3 < 15)) {
    stop();
    delay(1000);
    gobackward();
    delay(300);
    stop();
    delay(1000);
    if (random(0, 2) == 0) {
      goRight();
    } else {
      goLeft();
    }
    delay(500);
    stop();
    delay(700);
  }
  else { 
    goForward();
  }
  if (command == 's') {
    stop();  
  }
 
}

void goForward() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
}

void gobackward() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
}

void goRight() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
}

void goLeft() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
}

void stop() {
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
}