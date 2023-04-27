#include "bot_functions.h"
#define OPTIMUM_SPEED 150

int algorithm = 0;

int kp, ki, kd;


/* Input pins */
int motor1_0 ;
int motor1_1 ;
int motor2_0 ;
int motor2_1 ;

int motor_speed ;

int sens_pin1 ;
int sens_pin2 ;
int sens_pin3 ;
int sens_pin4 ;
int sens_pin5 ;

int enable1 ;
int enable2 ;