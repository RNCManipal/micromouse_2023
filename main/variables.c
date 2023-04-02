#include "bot_functions.h"

//Variables
int algorithm = 0; // lsrb = 0, rslb = 1
int clearence ; //distance between sensor and wall

//Sensors
const int trigPin1 ;  // Trigger pin for the first sensor
const int echoPin1 ; // Echo pin for the first sensor
const int trigPin2 ;  
const int echoPin2 ;
const int trigPin3 ; 
const int echoPin3 ; 
const int trigPin4 ;  
const int echoPin4 ; 


//Motors
int MotFwd1 ;
int MotRev1 ; 
int MotFwd2 ;
int MotRev2 ; 
int MotFwd3 ;
int MotRev3 ; 
int MotFwd4 ;
int MotRev4 ; 


int measure_distance(int trigPin, int echoPin){
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration1 / 2) / 29.1;
    return distance;
}

void wheel_forward(int MotFwd, int MotRev){
    digitalWrite(MotFwd, LOW); 
    digitalWrite(MotRev, HIGH);
}

void wheel_backward(int MotFwd, int MotRev){
    digitalWrite(MotFwd, HIGH); 
    digitalWrite(MotRev, LOW);
}

void wheel_stop(int MotFwd, int MotRev){
    digitalWrite(MotFwd, LOW); 
    digitalWrite(MotRev, LOW);
}

void move_forward(){
    wheel_forward(MotFwd1, MotRev1);
    wheel_forward(MotFwd2, MotRev2);
    wheel_forward(MotFwd3, MotRev3);
    wheel_forward(MotFwd4, MotRev4);
}

void move_backward(){
    wheel_backward(MotFwd1, MotRev1);
    wheel_backward(MotFwd2, MotRev2);
    wheel_backward(MotFwd3, MotRev3);
    wheel_backward(MotFwd4, MotRev4);
}

void move_left(){
    wheel_forward(MotFwd1, MotRev1);
    wheel_forward(MotFwd2, MotRev2);
    wheel_backward(MotFwd3, MotRev3);
    wheel_backward(MotFwd4, MotRev4);
}

void move_right(){
    wheel_backward(MotFwd1, MotRev1);
    wheel_backward(MotFwd2, MotRev2);
    wheel_forward(MotFwd3, MotRev3);
    wheel_forward(MotFwd4, MotRev4);
}

void move_stop(){
    wheel_stop(MotFwd1, MotRev1);
    wheel_stop(MotFwd2, MotRev2);
    wheel_stop(MotFwd3, MotRev3);
    wheel_stop(MotFwd4, MotRev4);
}

void pid() {
  // Read the sensor data
  double sensor_value = analogRead(A0);

  // Calculate the error
  error = setpoint - sensor_value;

  // Update the error sum
  error_sum += error;

  // Calculate the derivative of the error
  derivative = error - last_error;

  // Calculate the control signal using PID
  control_signal = KP * error + KI * error_sum + KD * derivative;

  // Update the last error
  last_error = error;

  // Send the control signal to the motor
  analogWrite(3, control_signal);

  // Print the values for debugging
  Serial.print("Sensor Value: ");
  Serial.print(sensor_value);
  Serial.print("\tControl Signal: ");
  Serial.println(control_signal);

  // Wait for a short period of time
  delay(100);
}