#include <ESP32Servo.h>

// Servo setup
Servo myServo;
int servoPin = 32;

// Motor driver pins
const int IN1 = 4;
const int IN2 = 18;
const int EN  = 21;

// Ultrasonic sensor pins
const int trigLeft = 25;
const int echoLeft = 26;
const int trigRight = 27;
const int echoRight = 14;

// Lap counter
int lapCounter = 0;

// Function to measure distance
long readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  long distance = duration * 0.034 / 2;
  return distance; // in cm
}

void setup() {
  // Servo
  myServo.attach(servoPin);
  myServo.write(55);  // center steering
  delay(500);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT);

  // Set motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(EN, HIGH);

  // Ultrasonic pins
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  Serial.begin(115200);
}

void loop() {
  long distLeft = readUltrasonic(trigLeft, echoLeft);
  long distRight = readUltrasonic(trigRight, echoRight);

  Serial.print("Left: "); Serial.print(distLeft);
  Serial.print(" cm  Right: "); Serial.print(distRight);
  Serial.print(" cm  Laps: "); Serial.println(lapCounter);

  // Check for corner (open space >70 cm on one side)
  if (distLeft > 70 && distRight < 70) {
    myServo.write(100); // steer right
    delay(800);
    myServo.write(55);  // straighten
    lapCounter++;
  } 
  else if (distRight > 70 && distLeft < 70) {
    myServo.write(10);  // steer left
    delay(800);
    myServo.write(55);
    lapCounter++;
  }
  else {
    myServo.write(55);  // keep straight
  }

  // Stop after 12 turns (3 laps)
  if (lapCounter >= 12) {
    digitalWrite(EN, LOW);  // stop motor
    while (true);           // freeze program
  }
}
