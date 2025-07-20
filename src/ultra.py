#no longer in use
from machine import Pin, time_pulse_us
import time

# Define pins
TRIG = Pin(25, Pin.OUT)   # Use output-capable pin
ECHO = Pin(35, Pin.IN)    # OK, input-only

def get_distance():
    # Trigger low then high pulse
    TRIG.off()
    time.sleep_us(2)
    TRIG.on()
    time.sleep_us(10)
    TRIG.off()

    # Read echo time
    try:
        duration = time_pulse_us(ECHO, 1, 30000)  # timeout in μs
        distance_cm = (duration * 0.0343) / 2
        return round(distance_cm, 2)
    except OSError:
        return -1  # Timeout or no signal

try:
    while True:
        dist = get_distance()
        if dist == -1:
            print("No echo received (timeout)")
        else:
            print("Distance:", dist, "cm")
        time.sleep(0.5)

except KeyboardInterrupt:
    print("Stopped by user")
