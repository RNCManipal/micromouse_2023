#include "bot_functions.h"

int algorithm = 0; // lsrb = 0, rslb = 1
int clearence ; //distance between sensor and wall


const int trigPin1 = 9;  // Trigger pin for the first sensor
const int echoPin1 = 10; // Echo pin for the first sensor
const int trigPin2 = 3;  // Trigger pin for the second sensor
const int echoPin2 = 2; // Echo pin for the second sensor

const int trigPin3 = 4;  // Trigger pin for the first sensor
const int echoPin3 = 5; // Echo pin for the first sensor
const int trigPin4 = 7;  // Trigger pin for the second sensor
const int echoPin4 = 6; // Echo pin for the second sensor


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