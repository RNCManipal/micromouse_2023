import RPi.GPIO as GPIO
import time

# Set the GPIO mode
GPIO.setmode(GPIO.BCM)

# Define the pin connected to the sensor output
sensor_pin = 14  # Change this to your actual GPIO pin

# Setup the GPIO pin as an input
GPIO.setup(sensor_pin, GPIO.IN)

try:
    while True:
        # Read the sensor value
        sensor_value = GPIO.input(sensor_pin)

        # Print the sensor value
        print("Sensor value:", sensor_value)

        # Add a delay if needed
        time.sleep(0.1)  # Adjust this delay as necessary

except KeyboardInterrupt:
    GPIO.cleanup()
