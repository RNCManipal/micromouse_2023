#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include "bot_functions.h"

void forward(){
  digitalWrite(mtrpin1_1, HIGH);
  digitalWrite(mtrpin1_2, LOW);

  digitalWrite(mtrpin2_1, HIGH);
  digitalWrite(mtrpin2_2, LOW);

  analogWrite(mtrspd1, OPTIMUM_SPEED);
  analogWrite(mtrspd2, OPTIMUM_SPEED);
}


void brake(){
  digitalWrite(mtrpin1_1, LOW);
  digitalWrite(mtrpin1_2, LOW);

  digitalWrite(mtrpin2_1, LOW);
  digitalWrite(mtrpin2_2, LOW);
}


void backward(){
  digitalWrite(mtrpin1_1, LOW);
  digitalWrite(mtrpin1_2, HIGH);

  digitalWrite(mtrpin2_1, LOW);
  digitalWrite(mtrpin2_2, HIGH);

  analogWrite(mtrspd1, OPTIMUM_SPEED);
  analogWrite(mtrspd2, OPTIMUM_SPEED);
}


void right(){
  digitalWrite(mtrpin1_1, LOW);
  digitalWrite(mtrpin1_2, LOW);
  digitalWrite(mtrpin2_1, HIGH);
  digitalWrite(mtrpin2_2, LOW);

  analogWrite(mtrspd1, OPTIMUM_SPEED);
  analogWrite(mtrspd2, OPTIMUM_SPEED);
  /*add delay*/
}


void left(){
  digitalWrite(mtrpin1_1, HIGH);
  digitalWrite(mtrpin1_2, LOW);
  digitalWrite(mtrpin2_1, LOW);
  digitalWrite(mtrpin2_2, LOW);

  analogWrite(mtrspd1, OPTIMUM_SPEED);
  analogWrite(mtrspd2, OPTIMUM_SPEED);
  /*add delay*/
}


void turn_around(){
  digitalWrite(mtrpin1_1, HIGH);
  digitalWrite(mtrpin1_2, LOW);
  digitalWrite(mtrpin2_1, LOW);
  digitalWrite(mtrpin2_2, HIGH);

  analogWrite(mtrspd1, OPTIMUM_SPEED);
  analogWrite(mtrspd2, OPTIMUM_SPEED);
  /*add delay*/
}

void Motor_SetSpeed(int spdL, int spdR){
  if (spdL < 0){
    analogWrite(mtrspd1, -spdL);
    digitalWrite(mtrpin1_1, HIGH);
    digitalWrite(mtrpin1_2, LOW);
  }

  else{
    analogWrite(mtrspd1, spdL);
    digitalWrite(mtrpin1_1, LOW);
    digitalWrite(mtrpin1_2, HIGH);
  }


  if (spdR < 0){
    analogWrite(mtrspd2, -spdR);
    digitalWrite(mtrpin2_1, LOW);
    digitalWrite(mtrpin2_2, HIGH);
  }

  else{
    analogWrite(mtrspd2, spdR);
    digitalWrite(mtrpin2_1, HIGH);
    digitalWrite(mtrpin2_2, LOW);
  }
}
