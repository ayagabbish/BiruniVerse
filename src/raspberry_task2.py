from teachable_machine_lite import TeachableMachineLite
import cv2 as cv
import serial

# Load model and labels
model_path = "model.tflite"
labels_path = "labels.txt"
tm_model = TeachableMachineLite(model_path=model_path, labels_file_path=labels_path)

# Open USB camera (usually at device 0)
cap = cv.VideoCapture(0)

# Open serial connection to ESP32
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

while True:
    ret, img = cap.read()
    if not ret:
        break
    
    # Save current frame temporarily
    image_file_name = "frame.jpg"
    cv.imwrite(image_file_name, img)
    
    # Run classification on the current frame
    results, result_img = tm_model.classify_and_show(image_file_name, convert_to_bgr=True)
    
    print("Results:", results)
    
    # Decision making
    if results[0] > 90:      # Red block detected
        ser.write(b'L\n')    # Send "Left" to ESP32
    elif results[1] > 90:    # Green block detected
        ser.write(b'R\n')    # Send "Right" to ESP32
    else:
        ser.write(b'F\n')    # No block → Forward
cap.release()
