#include <stdio.h>
#include <stdlib.h>
#define OPTIMUM_SPEED 150

int max(int a, int b){
    if (a>b){
        return a;
    }
    return b;
}

int min(int a, int b){
    if (a<b){
        return a;
    }
    return b;
}

void p2p_pid(int dist){
    //PID Controller. Used to control the speed of the bot. Function unverified
    double pv_p2p, pv_sens;
    double lasterror_p2p =0, lasterror_sens = 0;
    double rotatn_req= (dist/10.681415); // number of rotations of wheel required to complete given distance
    double setpnt_counts=(rotatn_req )* (170); // number of counts required to reach the set point(inshort this is our setpoint)
    int count = 0;
    int sensl = 5, sensr =6;

    while (1){
        {
            double kp1=1;
            double kd1=0.9;
            double error = 0;
            error =(setpnt_counts)-(count); //x is the number of encoder counts per revolution
            pv_p2p = kp1*error + kd1*(error-(lasterror_p2p));
            lasterror_p2p = error;
        }

        {
            double kp2 = 1, kd2 = 0.8;
            double error;
            error = sensl - sensr;
            pv_sens = kp2*error + kd2*(error-(lasterror_sens));
            sensl = sensr;
            lasterror_sens = error;
        }

        if (pv_p2p>=0){
            pv_p2p = min(max(pv_p2p, 1), 180);
            count++;
        }
        else{
            pv_p2p = min(max(pv_p2p, -180), -1);
            count--;
        }

        if (-2<(pv_p2p - pv_sens) && (pv_p2p - pv_sens)<2){
            break;
        }

        int speedl = min(max(pv_p2p - pv_sens, -200), 200);
        int speedr = min(max(pv_p2p + pv_sens, -200), 200);

        printf("dist = %f \t p2p = %f \t sens = %f\n", (setpnt_counts)-(count) ,pv_p2p, pv_sens);
        // int pv = pv_p2p-pv_sens;


        if (pv_p2p >= -0.1 && pv_p2p<=0.1){  //Assuming lower and upper thresholds of speed of motors are 50, 200 respectively
           printf("right = %d \t left = %d", speedl, speedr);
        }
        printf("right = %d \t left = %d", speedl, speedr);

        printf("\n\n");
    }



        // printf("Distance to travel %f\n", error);
        // if (pv >= -0.1 && pv<=0.1){  //Assuming lower and upper thresholds of speed of motors are 50, 200 respectively
        //     //brake();
        //    printf("break %f", pv);
        //    return pv
        // }
        // else if ( pv > 0 ){
        //     int speed= min(max(pv, 1), 200);
        //     count++;
        //    // Motor_SetSpeed(speed, speed); //Set the parameters later. these parameters are speed of left and right wheel and will be for forward motion since pv>=0
        //    printf("elseif %d", speed);
        // }
        // else{
        //     count--;
        //     int speed= min(max(pv, -200), -1);
        //     //Motor_SetSpeed(speed, speed); //Set the parameters later. these parameters are speed of left and right wheel and will be for forward motion since pv>=0
        //   printf("el %d", speed);
        // }
        // printf("\n");
}

int main() {
  p2p_pid (25);
  return 0;
}

// void straight_pid(double sensor_left, double sensor_right, double lasterror){
//     //PID calculation for if the bot defers the straight line path and heads for a wall
//     //Makes use of the logic that the left and right sensor values should be same at all points of time
//     //Integrate with p2p pid later
//     double kp2 = 1, kd2 = 0.8;

//     double error, pv;
//         error = sensor_left - sensor_right;
//         pv = kp2*error + kd2*(error-(*lasterror));
//         *lasterror = error;
//         return pv;
//         // printf("%f\n", pv);

//         // if (pv >= -0.1 && pv<=0.1){
//         //     printf("brake");
//         //     return;
//         // }

//         // Motor_SetSpeed(min(max(OPTIMUM_SPEED - pv, 1), 200), min(max(OPTIMUM_SPEED + pv, 1), 200));
//         // printf("%d %d", min(max(OPTIMUM_SPEED - pv, 1), 200), min(max(OPTIMUM_SPEED + pv, 1), 200));
// }