#include <stdio.h>
#include <stdlib.h>
#include "bot_functions.h"


void p2p_pid(int dist){
    //PID Controller. Used to control the speed of the bot. Function unverified
    //Attach Interrupt

    float num_of_rotatn= (dist/10.681415); // number of rotations of wheel required to complete given distance
    //let encoder giving 'x' number of counts per rotation
    double setpnt_counts=(num_of_rotatn*x); // number of counts required to reach the set point(inshort this is our setpoint)

    count =0; 
    double last_error = 0, error = 0;
    double pv = 0;
    double maxerror = kp1*setpnt_counts + kd1*(setpnt_count);

    while (1){

        error =(setpnt_counts)-(count); //x is the number of encoder counts per revolution
        pv = kp1*error + kd1*(error-lasterror);
        lasterror = error;

        map(pv, -maxerror, maxerror, -255, 255);
        if (pv >= -0.1 && pv<=0.1){
            break;
        }
        else if ( pv > 0 ){
            int speed= min(max(pv, 50), 200);
            Motor_SetSpeed(speed, speed); //Set the parameters later. these parameters are speed of left and right wheel and will be for forward motion since pv>=0
        }
        else{
            int speed= min(max(pv, -200), -50);
            Motor_SetSpeed(speed, speed); //Set the parameters later. these parameters are speed of left and right wheel and will be for forward motion since pv>=0
        }
    } 
}

void straight_pid(){
    //PID calculation for if the bot defers the straight line path and heads for a wall
    //Makes use of the logic that the left and right sensor values should be same at all points of time
    //Integrate with p2p pid later

    int sensor_left, sensor_right, error, lasterror = 0, pv;
    while (1)
    {
        sensor_left = sensor_output(sens_trig0, sens_echo0);
        sensor_right = sensor_output(sens_trig2, sens_echo2);

        error = sensor_left - sensor_right;
        pv = kp2*error + kd2*(error-lasterror);
        lasterror = error;

        Motor_SetSpeed(min(max(OPTIMUM_SPEED - pv, 0), 200), min(max(OPTIMUM_SPEED + pv, 0), 200));
    }

}

void turn(int angle){

     double lasterror=0;
     const int COUNTS_PER_ROTATION ; //put the value here
     const float WHEEL_DIAMETER ; //put the value here

     double theta_in_rad =(angle*3.14159265359)/180;

     double distance_turned_for_given_angle=( theta_in_rad * WHEEL_DIAMETER);
     count  =0 ; //encoder count
     double error =0, lasterror =0, pv =0;

     double encoder_Counts_required=(COUNTS_PER_ROTATION * distance_turned_for_given_angle )/(3.14159265359 * WHEEL_DIAMETER);
     double maxerror = kp3*encoder_Counts_required + kd3*(encoder_Counts_required);
    
    if (encoder_Counts_required < 0){  //anticlockwise rotation
        while(1){
           error=(-encoder_Counts_required)-(count);
           pv = kp3*error + kd3*(error-lasterror);
           lasterror = error;

            map(pv, -maxerror, maxerror, -255, 255);
            if (pv >= -0.1 && pv<=0.1){
                break;  
            }
            else if (pv>0){
                int speed= min(max(pv, 50), 200);
               Motor_SetSpeed(-speed, speed);
            } 
            else{
                int speed= min(max(pv, -200), -50);
               Motor_SetSpeed(-speed, speed); 
            }
        }
    }

    else{ //clockwise rotation
        while(1){ 
           error=(encoder_Counts_required)-(count);
           pv = kp3*error + kd3*(error-lasterror);
           lasterror = error;

            map(pv, -maxerror, maxerror, -255, 255);
            
           if (pv >= -0.1 && pv<=0.1){
                break;  
            }
            else if (pv<0){
               Motor_SetSpeed();  
            } 
            else{
                Motor_SetSpeed();  
            }
        }
    }
}