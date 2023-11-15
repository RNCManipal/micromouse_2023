from machine import ADC, Pin
import time

# Define your sensor pins
sens_trig0 = 0  # Replace with the GPIO pin connected to the first Sharp IR sensor
sens_trig2 = 2  # Replace with the GPIO pin connected to the second Sharp IR sensor

# Create an ADC object
adc = ADC()

# Function to read distance from Sharp IR sensor
def sensor_output(sensor_pin):
    # Read the analog voltage from the sensor
    sensor_value = adc.read(sensor_pin)

    # Convert the analog voltage to distance (adjust the formula based on your sensor's datasheet)
    # Assuming a 3.3V reference voltage
    distance = (1000 / (sensor_value / 1023.0 * 3.3 - 3.3))   # change the value of refernmce voltage 

    return distance

# Function to apply threshold to sensor output
def thresHold(value):
    # Implement your threshold logic here
    # Adjust this threshold based on your requirements
    threshold = 50  # Adjust this value based on your calibration  # adjust the threshold value
    if value < threshold:
        return 0
    else:
        return 1

def sens_pid():
    # PID calculation for if the bot defers the straight line path and heads for a wall
    # Makes use of the logic that the left and right sensor values should be same at all points of time
    # Integrate with p2p pid later

    kp2 = 1  # Adjust these values based on your tuning
    kd2 = 0.1  # Adjust these values based on your tuning
    OPTIMUM_SPEED = 100  # Adjust this value based on your requirements

    last_error = 0

    while True:
        sensor_left = sensor_output(sens_trig0)
        sensor_right = sensor_output(sens_trig2)

        detection_s0 = thresHold(sensor_left)
        detection_s2 = thresHold(sensor_right)

        if detection_s0 == 0 or detection_s2 == 0:
            break

        error = sensor_left - sensor_right
        pv = kp2 * error + kd2 * (error - last_error)
        last_error = error

        # Adjust motor speed based on PID output
        left_speed = min(max(OPTIMUM_SPEED - pv, 1), 200)
        right_speed = min(max(OPTIMUM_SPEED + pv, 1), 200)

        # Implement Motor_SetSpeed or your motor control logic here
        # Assuming you have a function Motor_SetSpeed for setting motor speeds
        Motor_SetSpeed(left_speed, right_speed)

        # Add a delay before the next iteration
        time.sleep(0.1)

# Call the sens_pid function to start the PID control loop
sens_pid()