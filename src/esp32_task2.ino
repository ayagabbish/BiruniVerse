#include <ESP32Servo.h>

// Motor pins
const int IN1 = 4;
const int IN2 = 18;
const int EN  = 21;

// Servo pin
Servo steering;
int servoPin = 32;

// Ultrasonic pins (front sensor)
const int trigPin = 26;
const int echoPin = 25;

void setup() {
  Serial.begin(115200);

  // Motor setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT);

  // Servo setup
  steering.attach(servoPin);

  // Ultrasonic setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  stopMotor();
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    if (command == 'L') {
      steerLeft();
    } else if (command == 'R') {
      steerRight();
    } else if (command == 'F') {
      moveForward();
    }
  }

  // Stop if obstacle closer than 15 cm
  if (getDistance() < 15) {
    stopMotor();
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(EN, HIGH);
  steering.write(90);  // Straight
}

void steerLeft() {
  steering.write(45);  // Turn left
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(EN, HIGH);
}

void steerRight() {
  steering.write(135); // Turn right
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(EN, HIGH);
}

void stopMotor() {
  digitalWrite(EN, LOW);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;  // Convert to cm
}

