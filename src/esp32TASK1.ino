#include <Arduino.h>
#include <Servo.h>

// --- Pin Definitions 

// Ultrasonic Left
const int ULTRASONIC_LEFT_ECHO_PIN = 35;
const int ULTRASONIC_LEFT_TRIG_PIN = 25;

// Ultrasonic Right
const int ULTRASONIC_RIGHT_ECHO_PIN = 13;
const int ULTRASONIC_RIGHT_TRIG_PIN = 12;

// Infrared Sensor
const int INFRARED_SENSOR_PIN = 14;

// Servo Motor (Front Steering)
const int SERVO_PIN = 21;

// DC Motor (Rear Wheels) - H-bridge Control (L298N-like setup)
// Selected from your list: D27, D26, D25, D33, D23, D22.
// Using D27 and D26 for direction, and D33 for PWM speed control.
const int DC_MOTOR_IN1_PIN = 27;
const int DC_MOTOR_IN2_PIN = 26;
const int DC_MOTOR_ENABLE_PIN = 33; // This pin is used for PWM

// Encoder for DC Motor (Rear Wheels)
// D19 for Channel A (interrupt), D18 for Channel B.
const int ENCODER_DC_MOTOR_A_PIN = 19;
const int ENCODER_DC_MOTOR_B_PIN = 18;

// Color Sensor (TCS3200/TCS34725)
const int COLOR_SENSOR_OE_PIN = 17;
const int COLOR_SENSOR_S0_PIN = 4;
const int COLOR_SENSOR_S1_PIN = 16;
const int COLOR_SENSOR_S2_PIN = 21;  // Moved from D15
const int COLOR_SENSOR_S3_PIN = 22;  // Moved from D22
const int COLOR_SENSOR_OUT_PIN = 15; // Moved from D2

// --- Constants ---
#define US_SOUND_SPEED_CM_PER_US 0.0343 //to calculate distance from ultrasonic
#define MAX_DISTANCE_CM 200 

// Motor Speed
const int FORWARD_SPEED = 150; // PWM value (0-255) for forward movement dc motor
const int TURN_SPEED = 100;    // PWM value for turning if needed

// Servo Angles
const int SERVO_STRAIGHT = 90; // Angle for straight
const int SERVO_TURN_LEFT = 0; // Angle for full left (adjust if your servo range is different)
const int SERVO_TURN_RIGHT = 180; // Angle for full right

// Distance Thresholds for Corner Detection
const int CORNER_DIFFERENCE_THRESHOLD_CM = 50; // Difference in ultrasonic readings to detect a corner
const int CORNER_INNER_SIDE_LARGE_DISTANCE_CM = 100; // Threshold for the inner side ultrasonic reading

// Color Sensor Thresholds (These are initial guesses based on RGB, YOU MUST CALIBRATE)
// Assuming your sensor outputs 'higher' values for 'less' of a color (e.g., lower red reading if much red is present)
// These thresholds will likely need to be adjusted based on your sensor's actual output range and lighting.
const int COLOR_THRESHOLD_BLUE_R = 150; // Lower red than green/blue
const int COLOR_THRESHOLD_BLUE_G = 150; // Lower green than blue
const int COLOR_THRESHOLD_BLUE_B = 50;  // Significantly higher blue

const int COLOR_THRESHOLD_ORANGE_R = 50;  // Significantly higher red
const int COLOR_THRESHOLD_ORANGE_G = 150; // Lower green than red
const int COLOR_THRESHOLD_ORANGE_B = 150; // Lower blue than red

const int MAX_COLOR_COUNT = 12; // Robot stops when this count is reached

// --- Global Variables ---
Servo frontServo;

volatile long encoderDcMotorPulses = 0; // Use volatile for variables modified in ISR

int colorCounter = 0;
bool lastColorWasBlue = false; // To track consecutive colors

// --- Function Prototypes ---
long readUltrasonicDistance(int trigPin, int echoPin);
void setMotorSpeed(int speed);
void setMotorDirection(bool forward); // true for forward, false for backward
void stopMotor();
void rotateServoSlowly(int targetAngle, int delayMs);
void readColorSensor(int &r, int &g, int &b);
void checkAndCountColor();

// Encoder Interrupt Service Routine
void IRAM_ATTR handleDcMotorEncoderA();

// --- Setup ---
void setup() {
    Serial.begin(115200);
    Serial.println("Robot starting up...");

    // Ultrasonic Pins
    pinMode(ULTRASONIC_LEFT_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_LEFT_ECHO_PIN, INPUT);
    pinMode(ULTRASONIC_RIGHT_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_RIGHT_ECHO_PIN, INPUT);

    // Infrared Sensor
    pinMode(INFRARED_SENSOR_PIN, INPUT);

    // Servo Motor
    frontServo.attach(SERVO_PIN);
    frontServo.write(SERVO_STRAIGHT); // Start straight

    // DC Motor H-bridge Pins
    pinMode(DC_MOTOR_IN1_PIN, OUTPUT);
    pinMode(DC_MOTOR_IN2_PIN, OUTPUT);
    pinMode(DC_MOTOR_ENABLE_PIN, OUTPUT);
    ledcSetup(0, 5000, 8); // Setup PWM channel 0, 5kHz frequency, 8-bit resolution (0-255)
    ledcAttachPin(DC_MOTOR_ENABLE_PIN, 0); // Attach pin to PWM channel

    // Encoder Pins - Setup interrupts for quadrature
    pinMode(ENCODER_DC_MOTOR_A_PIN, INPUT_PULLUP);
    pinMode(ENCODER_DC_MOTOR_B_PIN, INPUT_PULLUP);
    // Attach interrupt to Channel A, triggering on CHANGE (both rising and falling edges)
    // to detect quadrature signals for both speed and direction.
    attachInterrupt(digitalPinToInterrupt(ENCODER_DC_MOTOR_A_PIN), handleDcMotorEncoderA, CHANGE);

    // Color Sensor Pins
    pinMode(COLOR_SENSOR_OE_PIN, OUTPUT);
    pinMode(COLOR_SENSOR_S0_PIN, OUTPUT);
    pinMode(COLOR_SENSOR_S1_PIN, OUTPUT);
    pinMode(COLOR_SENSOR_S2_PIN, OUTPUT);
    pinMode(COLOR_SENSOR_S3_PIN, OUTPUT);
    pinMode(COLOR_SENSOR_OUT_PIN, INPUT);

    digitalWrite(COLOR_SENSOR_OE_PIN, LOW); // Enable the color sensor
    // Set frequency scaling for TCS3200/TCS34725. HIGH, HIGH is usually 100%
    digitalWrite(COLOR_SENSOR_S0_PIN, HIGH);
    digitalWrite(COLOR_SENSOR_S1_PIN, HIGH);
}

// --- Loop ---
void loop() {
    if (colorCounter >= MAX_COLOR_COUNT) {
        stopMotor();
        frontServo.write(SERVO_STRAIGHT);
        Serial.println("Color count reached! Robot stopped.");
        while (true) {
            // Robot stops completely.
            delay(100);
        }
    }

    long leftDistance = readUltrasonicDistance(ULTRASONIC_LEFT_TRIG_PIN, ULTRASONIC_LEFT_ECHO_PIN);
    long rightDistance = readUltrasonicDistance(ULTRASONIC_RIGHT_TRIG_PIN, ULTRASONIC_RIGHT_ECHO_PIN);

    Serial.print("Left Dist: "); Serial.print(leftDistance); Serial.print(" cm, ");
    Serial.print("Right Dist: "); Serial.print(rightDistance); Serial.print(" cm, ");
    Serial.print("Encoder Pulses: "); Serial.println(encoderDcMotorPulses);

    // Check for corner detection
    if (abs(leftDistance - rightDistance) > CORNER_DIFFERENCE_THRESHOLD_CM) {
        if (leftDistance > CORNER_INNER_SIDE_LARGE_DISTANCE_CM) {
            // Likely a left turn (left side is "open" - inner side of corner)
            Serial.println("Corner detected! Turning left slowly.");
            stopMotor();
            rotateServoSlowly(SERVO_TURN_LEFT, 50);
            delay(100);
            delay(2000); // Stay in corner for 2 seconds to allow adjustment/color reading
            checkAndCountColor(); // Read color while adjusting/at corner
            frontServo.write(SERVO_STRAIGHT); // Straighten wheels for next section
            delay(500); // Allow servo to reset
            setMotorDirection(true); // Ensure direction is forward
            setMotorSpeed(FORWARD_SPEED); // Move fast again
        } else if (rightDistance > CORNER_INNER_SIDE_LARGE_DISTANCE_CM) {
            // Likely a right turn (right side is "open" - inner side of corner)
            Serial.println("Corner detected! Turning right slowly.");
            stopMotor();
            rotateServoSlowly(SERVO_TURN_RIGHT, 50);
            delay(100);
            delay(2000); // Stay in corner for 2 seconds
            checkAndCountColor();
            frontServo.write(SERVO_STRAIGHT);
            delay(500);
            setMotorDirection(true); // Ensure direction is forward
            setMotorSpeed(FORWARD_SPEED);
        }
    } else {
        // No corner detected, keep moving forward
        Serial.println("Moving forward...");
        setMotorDirection(true); // Always ensure forward direction
        setMotorSpeed(FORWARD_SPEED);
        frontServo.write(SERVO_STRAIGHT); // Ensure wheels are straight
    }

    // You can add more frequent color checking here if desired, but be mindful of timing.
    // For now, it's primarily checked during corner adjustments.
    /*
    if (millis() % 500 == 0) {
        checkAndCountColor();
    }
    */

    delay(50);
}

// --- Function Implementations ---

// Ultrasonic Sensor Reading
long readUltrasonicDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms (max distance approx 5m)
    if (duration == 0) return MAX_DISTANCE_CM; // If no echo, assume max distance
    long distanceCm = duration * US_SOUND_SPEED_CM_PER_US / 2;
    return min(distanceCm, (long)MAX_DISTANCE_CM); // Cap at max distance
}

// DC Motor Control
void setMotorSpeed(int speed) {
    if (speed > 255) speed = 255;
    if (speed < 0) speed = 0;
    ledcWrite(0, speed); // Use PWM channel 0
    // Serial.print("Motor speed set to: "); Serial.println(speed); // Uncomment for more frequent debug output
}

void setMotorDirection(bool forward) {
    if (forward) {
        digitalWrite(DC_MOTOR_IN1_PIN, HIGH);
        digitalWrite(DC_MOTOR_IN2_PIN, LOW);
    } else { // Reverse
        digitalWrite(DC_MOTOR_IN1_PIN, LOW);
        digitalWrite(DC_MOTOR_IN2_PIN, HIGH);
    }
}

void stopMotor() {
    setMotorSpeed(0);
    digitalWrite(DC_MOTOR_IN1_PIN, LOW);
    digitalWrite(DC_MOTOR_IN2_PIN, LOW);
    Serial.println("Motor stopped.");
}

// Servo Motor Slow Rotation
void rotateServoSlowly(int targetAngle, int delayMs) {
    int currentAngle = frontServo.read();
    Serial.print("Rotating servo from "); Serial.print(currentAngle); Serial.print(" to "); Serial.println(targetAngle);

    if (targetAngle > currentAngle) {
        for (int angle = currentAngle; angle <= targetAngle; angle++) {
            frontServo.write(angle);
            delay(delayMs);
        }
    } else if (targetAngle < currentAngle) {
        for (int angle = currentAngle; angle >= targetAngle; angle--) {
            frontServo.write(angle);
            delay(delayMs);
        }
    }
    Serial.println("Servo rotation complete.");
}

// Color Sensor Reading (TCS3200/TCS34725 common logic)
void readColorSensor(int &r, int &g, int &b) {
    // Set sensor to read RED filter
    digitalWrite(COLOR_SENSOR_S2_PIN, LOW);
    digitalWrite(COLOR_SENSOR_S3_PIN, LOW);
    r = pulseIn(COLOR_SENSOR_OUT_PIN, HIGH, 100000); // Measure duration of HIGH pulse (inverse of frequency)
    if (r == 0) r = 65535; // Handle timeout/no pulse
    r = map(r, 0, 65535, 255, 0); // Invert duration and scale to 0-255 (Higher frequency = shorter pulse = more of that color)

    // Set sensor to read GREEN filter
    digitalWrite(COLOR_SENSOR_S2_PIN, HIGH);
    digitalWrite(COLOR_SENSOR_S3_PIN, HIGH);
    g = pulseIn(COLOR_SENSOR_OUT_PIN, HIGH, 100000);
    if (g == 0) g = 65535;
    g = map(g, 0, 65535, 255, 0);

    // Set sensor to read BLUE filter
    digitalWrite(COLOR_SENSOR_S2_PIN, LOW);
    digitalWrite(COLOR_SENSOR_S3_PIN, HIGH);
    b = pulseIn(COLOR_SENSOR_OUT_PIN, HIGH, 100000);
    if (b == 0) b = 65535;
    b = map(b, 0, 65535, 255, 0);

    Serial.print("Color R: "); Serial.print(r);
    Serial.print(" G: "); Serial.print(g);
    Serial.print(" B: "); Serial.println(b);
}

void checkAndCountColor() {
    int red, green, blue;
    readColorSensor(red, green, blue);

    bool currentColorIsBlue = false;
    bool currentColorIsOrange = false;

    // Basic color detection. YOU MUST CALIBRATE THESE THRESHOLDS with your actual sensor readings.
    // The logic below is based on the idea that for a color, its dominant component is high, others are low.
    // For Blue: Blue is high, Red & Green are low
    // For Orange (approx. Red/Yellow): Red is high, Green is moderate, Blue is low
    if (blue > COLOR_THRESHOLD_BLUE_B && red < COLOR_THRESHOLD_BLUE_R && green < COLOR_THRESHOLD_BLUE_G) {
        currentColorIsBlue = true;
    } else if (red > COLOR_THRESHOLD_ORANGE_R && green > COLOR_THRESHOLD_ORANGE_G && blue < COLOR_THRESHOLD_ORANGE_B) {
        currentColorIsOrange = true;
    }

    if (currentColorIsBlue) {
        Serial.println("Detected Blue!");
        if (!lastColorWasBlue) { // Only increment if the color changed from non-blue to blue
            colorCounter++;
            Serial.print("Color Counter: "); Serial.println(colorCounter);
            lastColorWasBlue = true;
        }
    } else if (currentColorIsOrange) {
        Serial.println("Detected Orange!");
        if (lastColorWasBlue) { // Only increment if the color changed from blue to orange (or vice-versa for orange detection logic)
            colorCounter++;
            Serial.print("Color Counter: "); Serial.println(colorCounter);
            lastColorWasBlue = false; // Reset for next color detection
        }
    } else {
        Serial.println("Detected Unknown Color. Resetting last color tracking.");
        // If you want to ensure distinct blue/orange detection,
        // you might reset lastColorWasBlue to a neutral state if an unknown color is read.
        // This prevents double-counting if the sensor briefly loses track.
        // For simplicity, I'm setting it to false which implies "not blue"
        lastColorWasBlue = false;
    }
}

// Encoder ISR for DC Motor (Quadrature)
// This ISR is called on any CHANGE (rising or falling edge) of Encoder A.
// It checks the state of Encoder B to determine the direction of rotation.
void IRAM_ATTR handleDcMotorEncoderA() {
    // Read the current state of both encoder pins
    int encoderAState = digitalRead(ENCODER_DC_MOTOR_A_PIN);
    int encoderBState = digitalRead(ENCODER_DC_MOTOR_B_PIN);

    // If A leads B, it's one direction; if B leads A, it's the other direction.
    // This simplified logic assumes standard quadrature encoder behavior.
    if (encoderAState == HIGH) { // If A is rising edge
        if (encoderBState == LOW) { // B is low, then A leads B (e.g., forward)
            encoderDcMotorPulses++;
        } else { // B is high, then B leads A (e.g., reverse)
            encoderDcMotorPulses--;
        }
    } else { // If A is falling edge
        if (encoderBState == HIGH) { // B is high, then A leads B (e.g., forward)
            encoderDcMotorPulses++;
        } else { // B is low, then B leads A (e.g., reverse)
            encoderDcMotorPulses--;
        }
    }
}

