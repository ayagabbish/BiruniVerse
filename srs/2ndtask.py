#First attempt no longer in use

from teachable_machine_lite import TeachableMachineLite
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
cap = cv.VideoCapture(0)

model_path = 'model.tflite'
image_file_name = "frame.jpg"
labels_path = "labels.txt"

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


tm_model = TeachableMachineLite(model_path=model_path, labels_file_path=labels_path)

while True:
    ret, frame = cap.read()
    cv.imshow('Cam', frame)
    cv.imwrite(image_file_name, frame)
    
    results = tm_model.classify_frame(image_file_name)
    obstacle = results["label"]
    print("result label:",results["label"])

    if "0" == obstacle:
        print("left")
        left()


    if "1" == obstacle:
        print("right")
        right()
        

        

    

    k = cv.waitKey(1)
    if k% 255 == 27:
        # press ESC to close camera view.
        break

'''
{
            "id": label_id,
            "label": classification_label,
            "time": classification_time,
            "confidence": classification_confidence,
            "highest_class_id": label_id,
            "highest_class_prob": classification_confidence
        }
'''

    
