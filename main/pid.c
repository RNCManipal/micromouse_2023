#include <Arduino.h>
#include <stdlib.h>
#include "bot_functions.h"

void p2p_pid(int dist) //Point to  Point PID    
{   
    // PID Controller. Used to control the speed of the bot. Function unverified
    double rotatn_req = (dist / WHEEL_DIAMETER); // number of rotations of wheel required to complete given distance
    // let encoder giving 'x' number of counts per rotation

    double setpnt_counts = (rotatn_req) * (counts_per_rotation); // number of counts required to reach the set point(inshort this is our setpoint)
    count = 0;
    double lasterror = 0, error = 0;
    double pv = 0;

    while (1)
    {
        error = (setpnt_counts) - (count); // x is the number of encoder counts per revolution

        if (lasterror == 0)
        { // this condition is used to remove intial high gain in velocity
            pv = kp1 * error;
        }
        else
        {
            pv = kp1 * error + kd1 * (error - lasterror);
        }

        lasterror = error;

        if (pv >= -0.1 && pv <= 0.1)
        { // Assuming lower and upper thresholds of speed of motors are 1, 200 respectively
            brake();
            break;
        }

        int speed = min(max(pv, -200), 200);
        Motor_SetSpeed(speed, speed); // Set the parameters later. these parameters are speed of left and right wheel and will be for forward motion since pv>=0
    }
}

void sens_pid()
{
    // PID calculation for if the bot defers the straight line path and heads for a wall
    // Makes use of the logic that the left and right sensor values should be same at all points of time
    // Integrate with p2p pid later

    double sensor_left, sensor_right, error, lasterror = 0, pv;
    while (1)
    {
        sensor_left = sensor_output(sens_trig0, sens_echo0);
        sensor_right = sensor_output(sens_trig2, sens_echo2);

        int detection_s0 = thresHold(sensor_output(sens_trig0, sens_echo0));
        int detection_s2 = thresHold(sensor_output(sens_trig2, sens_echo2));

        if (detection_s0 == 0 || detection_s2 == 0)
        {
            break;
        }

        error = sensor_left - sensor_right;
        pv = kp2 * error + kd2 * (error - lasterror);
        lasterror = error;

        Motor_SetSpeed(min(max(OPTIMUM_SPEED - pv, 1), 200), min(max(OPTIMUM_SPEED + pv, 1), 200));
    }
}

void turn(int angle)
{
    // PID controller for turning the bot by a given angle
    double theta_in_rad = (angle * 3.14159265359) / 180;

    double distance_turned_for_given_angle = (theta_in_rad * WHEEL_DIAMETER);
    count = 0; // encoder count
    double error = 0, lasterror = 0, pv = 0;

    double encoder_Counts_required = (counts_per_rotation * distance_turned_for_given_angle) / (3.14159265359 * WHEEL_DIAMETER);
    double maxerror = kp3 * encoder_Counts_required + kd3 * (encoder_Counts_required);

    if (encoder_Counts_required < 0)
    { // anticlockwise rotation
        while (1)
        {
            error = (-encoder_Counts_required) - (count);
            pv = kp3 * error + kd3 * (error - lasterror);
            lasterror = error;

            if (pv >= -0.1 && pv <= 0.1)
            { // upper and lower threshold limits of pv
                brake();
                break;
            }
            else if (pv > 0)
            {
                int speed = min(max(pv, 1), 200);
                Motor_SetSpeed(-speed, speed);
            }
            else
            {
                int speed = min(max(pv, -200), -1);
                Motor_SetSpeed(-speed, speed);
            }
        }
    }

    else
    { // clockwise rotation
        while (1)
        {
            error = (encoder_Counts_required) - (count);
            pv = kp3 * error + kd3 * (error - lasterror);
            lasterror = error;

            if (pv >= -0.1 && pv <= 0.1)
            {
                brake();
                break;
            }
            else if (pv > 0)
            {
                int speed = min(max(pv, 50), 200);
                Motor_SetSpeed(speed, -speed);
            }
            else
            {
                int speed = min(max(pv, -200), -50);
                Motor_SetSpeed(speed, -speed);
            }
        }
    }
}

void composite_pid(int dist){
    // PID controller combining p2p_pid and sens_pid

    double lasterror_p2p =0, lasterror_sens = 0;
    double rotatn_req= (dist/WHEEL_DIAMETER); // number of rotations of wheel required to complete given distance
    double setpnt_counts=(rotatn_req )* (counts_per_rotation); // number of counts required to reach the set point(inshort this is our setpoint)

    double error_p2p = 0, error_sens = 0;

    double pv_p2p, pv_sens; //Individual pv values for p2p and sens

    while (1){
        { //p2p_pid
            error_p2p =(setpnt_counts)-(count); //x is the number of encoder counts per revolution
            pv_p2p = kp1*error_p2p + kd1*(error_p2p-(lasterror_p2p));
            lasterror_p2p = error_p2p;
        }

        { //sens_pid
            int sensl = sensor_output(sens_trig0, sens_echo0);
            int sensr = sensor_output(sens_trig2, sens_echo2);

            if (thresHold(sensl) == 0 || thresHold(sensr) == 0){
                pv_sens = 0;
            }
            else{
                error_sens = sensl - sensr;
                pv_sens = kp2*error_sens + kd2*(error_sens-(lasterror_sens));
                lasterror_sens = error_sens;
            }
        }

        pv_p2p = min(max(pv_p2p, -180), 180);

        if (-1.5<(pv_p2p - pv_sens) && (pv_p2p - pv_sens)<1.5){
            break;
        }

        int speedl = min(max(pv_p2p - pv_sens, -200), 200);
        int speedr = min(max(pv_p2p + pv_sens, -200), 200);

        Motor_SetSpeed(speedl, speedr);
    }
}