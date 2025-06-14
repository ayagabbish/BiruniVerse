import sys
sys.modules['RPi'] = __import__('fake_rpi')  # Mock RPi.GPIO
import RPi.GPIO as GPIO  # Correct import (not gpiozero!)

led_pin = 5
buzzer_pin = 7
GPIO.setmode(GPIO.BOARD)  # Now works (fake_rpi mimics RPi.GPIO)
GPIO.setwarnings(False)
GPIO.setup(led_pin, GPIO.OUT)
GPIO.setup(buzzer_pin, GPIO.OUT)

GPIO.output(led_pin, GPIO.HIGH)
print("LED ON (Simulated)")  # Fix: Use print(), not printf()

from gpiozero import LED, Buzzer  # gpiozero uses objects, not pin numbers

led = LED(5)          # No setup/setmode needed
buzzer = Buzzer(7)    # Buzzer is active_high by default

led.on()              # Turn LED on
print("LED ON (Simulated)")