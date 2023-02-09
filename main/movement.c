#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include "bot_functions.h"

/*
    in1, in2 => motor 1
    in3, in4 => motor 2 
*/

void forward(int in1, int in2, int in3, int in4){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void brake(int in1, int in2, int in3, int in4){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void backward(int in1, int in2, int in3, int in4){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


void right(int in1, int in2, int in3, int in4){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  /*add delay*/
}


void left(int in1, int in2, int in3, int in4){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  /*add delay*/
}


void turn_around(int in1, int in2, int in3, int in4){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  /*add delay*/
}
