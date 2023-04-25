#include "bot_functions.h"

int readEncoder (int count){
    int b = digitalRead(ENCB);
    if(b > 0){
       count++; //count is current encoder count 
    } else{
       count--;
    }
    return count;
}

void p2p_pid(int dist){
    //PID Controller. Used to control the speed of the bot. Function unverified
    //Attach Interrupt

    float num_of_rotatn= (dist/10.681415); // number of rotations of wheel required to complete given distance
    //let encoder giving 'x' number of counts per rotation
    double setpnt_counts=(num_of_rotatn*x); // number of counts required to reach the set point(inshort this is our setpoint)

    int count =0 , last_error = 0, error = 0, pv = 0;
    int b;

    double maxerror = kp1*setpnt_counts + kd1*(setpnt_count);

    while (1){

        count = readEncoder(count);

        error =(setpnt_counts)-(count); //x is the number of encoder counts per revolution
        pv = kp1*error + kd1*(error-lasterror);
        lasterror = error;

        map(pv, -maxerror, maxerror, -255, 255);
        if (pv >= -0.1 && pv<=0.1){
            break;
        }
        else if ( pv > 0 ){
            int speed= min(max(pv, 100), 200);
            Motor_SetSpeed(speed, speed); //Set the parameters later. these parameters are speed of left and right wheel and will be for forward motion since pv>=0
        }
        else{
            int speed= min(max(pv, -200), -100);
            Motor_SetSpeed(speed, speed); //Set the parameters later. these parameters are speed of left and right wheel and will be for forward motion since pv>=0
        }
    } 
}

void straight_pid(){
    //PID calculation for if the bot defers the straight line path and heads for a wall
    //Makes use of the logic that the left and right sensor values should be same at all points of time

    int sensor_left, sensor_right,error, lasterror = 0, pv;
    while (1)
    {
        sensor_left = sensor_output();
        sensor_right = sensor_output();

        error = sensor_left - sensor_right;
        pv = kp2*error + kd2*(error-lasterror);
        lasterror = error;

        Motor_SetSpeed(min(max(OPTIMUM_SPEED - pv, 0), 200), min(max(OPTIMUM_SPEED + pv, 0), 200));
    }

}

short int arena_map[16][16] = {
    {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
    {13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
    {12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
    {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
    {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
    { 9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8, 9 },
    { 8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7, 8 },
    { 7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6, 7 },
    { 7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6, 7 },
    { 8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7, 8 },
    { 9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8, 9 },
    {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
    {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
    {12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
    {13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
    {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
}; //arena node weight map

bool wall_data[16][16][4];

short int position[2] = {15, 0}; //Current position of bot
int facing = 1; // 0 = East, 1 = North, 2 = West, 3 = South

void setup(){

    for (int i =0 ; i<16; i++){  //intializing wall array to 0 initially
        for (int j =0; j<16; j++){
            for (int k = 0; k<4; k++){
                wall_data[i][j][k] = 0;
            }
        }
    }

    Serial.begin(96000);
}

void loop(){
}