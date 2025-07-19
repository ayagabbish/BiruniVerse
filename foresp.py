from machine import Pin, PWM
import time

# Motor pins
right_in1 = Pin(22, Pin.OUT)
right_in2 = Pin(14, Pin.OUT)
left_in1 = Pin(23, Pin.OUT)
left_in2 = Pin(26, Pin.OUT)
ena = PWM(Pin(27), freq=1000)
end = PWM(Pin(28), freq=1000)
# Ultrasonic sensor pins
trig = Pin(5, Pin.OUT)
echo = Pin(18, Pin.IN)

# Motor control functions
def forward():
    right_in1.on()
    right_in2.off()
    left_in1.on()
    left_in2.off()

def backward():
    right_in1.off()
    right_in2.on()
    left_in1.off()
    left_in2.on()

def left():
    right_in1.off()
    right_in2.on()
    left_in1.on()
    left_in2.off()

def right():
    right_in1.on()
    right_in2.off()
    left_in1.off()
    left_in2.on()

def stop():
    right_in1.off()
    right_in2.off()
    left_in1.off()
    left_in2.off()

# Ultrasonic distance
def get_distance():
    trig.off()
    time.sleep_us(2)
    trig.on()
    time.sleep_us(10)
    trig.off()

    while echo.value() == 0:
        pass
    start = time.ticks_us()

    while echo.value() == 1:
        pass
    end = time.ticks_us()

    duration = time.ticks_diff(end, start)
    distance = (duration * 0.0343) / 2
    return round(distance, 2)

# Main loop
try:
    while True:
        dist = get_distance()
        print("Distance:", dist, "cm")

        if dist < 20:
            stop()
            time.sleep(0.5)
            left()
            time.sleep(0.8)
            stop()
        else:
            forward()

        time.sleep(0.1)

except KeyboardInterrupt:
    stop()
