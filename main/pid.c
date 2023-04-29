#include <stdio.h>
#include <stdlib.h>
#include "bot_functions.h"


void p2p_pid(int dist){
    //PID Controller. Used to control the speed of the bot. Function unverified
    double rotatn_req= (dist/10.681415); // number of rotations of wheel required to complete given distance
    //let encoder giving 'x' number of counts per rotation
    double setpnt_counts=(rotatn_req )* (170); // number of counts required to reach the set point(inshort this is our setpoint)
    double count =0; 
    double kp1=1;
    double kd1=0.9;
    double lasterror = 0, error = 0;
    double pv = 0;
    while (1)
       { error =(setpnt_counts)-(count); //x is the number of encoder counts per revolution
        pv = kp1*error + kd1*(error-lasterror);
        lasterror = error;
        printf("Distance to travel %f\n", error);
        if (pv >= -0.1 && pv<=0.1){  //Assuming lower and upper thresholds of speed of motors are 50, 200 respectively
            //brake();
           printf("break %f", pv);
           break;
        }
        else if ( pv > 0 ){
            int speed= min(max(pv, 1), 200);
            count++;
           // Motor_SetSpeed(speed, speed); //Set the parameters later. these parameters are speed of left and right wheel and will be for forward motion since pv>=0
           printf("elseif %d", speed);
        }
        else{
            count--;
            int speed= min(max(pv, -200), -1);
            //Motor_SetSpeed(speed, speed); //Set the parameters later. these parameters are speed of left and right wheel and will be for forward motion since pv>=0
          printf("el %d", speed);
        }
        printf("\n");
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

        if (pv >= -0.1 && pv<=0.1){
            brake();
            break;
        }

        Motor_SetSpeed(min(max(OPTIMUM_SPEED - pv, 0), 200), min(max(OPTIMUM_SPEED + pv, 0), 200));
    }

}

void turn(int angle){
    //PID controller for turning the bot by a given angle

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
            if (pv >= -0.1 && pv<=0.1){ //upper and lower threshold limits of pv
                brake();
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
                brake();
                break;
            }
            else if (pv>0){
                int speed= min(max(pv, 50), 200);
               Motor_SetSpeed(speed, -speed);
            } 
            else{
                int speed= min(max(pv, -200), -50);
                Motor_SetSpeed(speed, -speed);
            }
        }
    }
}