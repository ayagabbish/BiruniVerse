import cv2 as cv
import time
import RPi.GPIO as GPIO
right_in1 = 11
right_in2 = 13
left_in1= 15
left_in2= 16
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(right_in1, GPIO.OUT)
GPIO.setup(right_in2, GPIO.OUT)
GPIO.setup(left_in1, GPIO.OUT) 
GPIO.setup(left_in2, GPIO.OUT)


#ultrasonic
trig = 18  
echo = 22

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


cap = cv.VideoCapture(0)


