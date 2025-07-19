import cv2 as cv
import time
import RPi.GPIO as GPIO

# Motor pins
right1 = 11
right2 = 13
left1 = 15
left2 = 16

# Ultrasonic sensor pins
trig = 18  
echo = 22

# GPIO setup
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(right1, GPIO.OUT)
GPIO.setup(right2, GPIO.OUT)
GPIO.setup(left1, GPIO.OUT)
GPIO.setup(left2, GPIO.OUT)

GPIO.setup(trig, GPIO.OUT)
GPIO.setup(echo, GPIO.IN)

# Motor control functions
def forward():
    GPIO.output(right_in1, GPIO.HIGH)
    GPIO.output(right_in2, GPIO.LOW)
    GPIO.output(left_in1, GPIO.HIGH)
    GPIO.output(left_in2, GPIO.LOW)

def backward():
    GPIO.output(right_in1, GPIO.LOW)
    GPIO.output(right_in2, GPIO.HIGH)
    GPIO.output(left_in1, GPIO.LOW)
    GPIO.output(left_in2, GPIO.HIGH)

def left():
    GPIO.output(right_in1, GPIO.LOW)
    GPIO.output(right_in2, GPIO.HIGH)
    GPIO.output(left_in1, GPIO.HIGH)
    GPIO.output(left_in2, GPIO.LOW)

def right():
    GPIO.output(right_in1, GPIO.HIGH)
    GPIO.output(right_in2, GPIO.LOW)
    GPIO.output(left_in1, GPIO.LOW)
    GPIO.output(left_in2, GPIO.HIGH)

def stop():
    GPIO.output(right_in1, GPIO.LOW)
    GPIO.output(right_in2, GPIO.LOW)
    GPIO.output(left_in1, GPIO.LOW)
    GPIO.output(left_in2, GPIO.LOW)

# Measure distance using ultrasonic sensor
def get_distance():
    # Ensure trigger is LOW
    GPIO.output(trig, False)
    time.sleep(0.01)

    # Send 10us pulse to trigger
    GPIO.output(trig, True)
    time.sleep(0.00001)
    GPIO.output(trig, False)

    # Wait for echo start
    while GPIO.input(echo) == 0:
        pulse_start = time.time()

    # Wait for echo end
    while GPIO.input(echo) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start
    distance = pulse_duration * 17150  # Convert to cm

    return round(distance, 2)

# Initialize camera
cap = cv.VideoCapture(0)

if not cap.isOpened():
    print("Cannot open camera")
    exit()

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Can't receive frame. Exiting...")
            break

        # Show camera feed (optional)
        cv.imshow('Camera', frame)

        # Read distance from ultrasonic sensor
        dist = get_distance()
        print(f"Distance: {dist} cm")

        if dist < 20:
            print("Obstacle detected! Turning left...")
            stop()
            time.sleep(0.5)
            left()
            time.sleep(0.8)
            stop()
        else:
            forward()

        # Exit on 'q' key
        if cv.waitKey(1) & 0xFF == ord('q'):
            break

except KeyboardInterrupt:
    print("Stopped by User")

finally:
    cap.release()
    cv.destroyAllWindows()
    GPIO.cleanup()
