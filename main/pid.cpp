#include <Arduino.h>
#include <stdlib.h>
#include "bot_functions.h"
#include <MPU6050_light.h>




void p2p_pid(int dist) {
  // PID Controller. Used to control the speed of the bot. Function
  double rotatn_req = (dist /(3.14*WHEEL_DIAMETER)); // number of rotations ofwheel required to complete given distance

  // let encoder giving 'x' number of counts per rotation
  double setpnt_counts =(rotatn_req) * (520); // number of counts requiredto reach the set point(inshort this is our setpoint)
  //Serial.print("setpnt_counts");
  count=0;
  double lasterror = 0;
  double kp1 = 0.2;
  double kd1 = 1.0;
  double last_error = 0, error = 0;
  double pv = 0;

  // double maxerror = kp1*setpnt_counts + kd1*(setpnt_counts);

  if (setpnt_counts < 0) {
    while (1) {

      error = (count) - (setpnt_counts);
      // Serial.println(count);
      // Serial.println(error);
      if (lasterror ==0) { // this condition is used to remove intial high gain in velocity
        pv = kp1 * error;
      } else {
        pv = kp1 * error + kd1 * (error - lasterror);
      }


      // pv= mapp(pv, -maxerror, maxerror, -255, 255);
      if (pv >= -0.3 && pv <= 0.3) { // Assuming lower and upper thresholds of speed of motors are 50, 200 respectively
         brake();
      

        break;
      } else if (pv > 0) {
        int speed = min(max(pv, 50), 200);
        Motor_SetSpeed(-speed, -speed); //Set the parameters later.
        // theseparameters are speed of left and right wheel and will be
        // forforward motion since pv>=0
      
      } else {
        int speed = min(max(pv, -200), -50);
        
        Motor_SetSpeed(speed, speed); //Set the parameters later.
        // theseparameters are speed of left and right wheel and will be
        // forforward motion since pv>=0

      }
    }
  } else if (setpnt_counts > 0) {
    while (1) {
      
      error = (setpnt_counts) -(count); // x is the number of encoder countsper revolution
      // Serial.println(count);
      // Serial.println(error);
      
      if (lasterror ==0) { // this condition is used to remove intial high gain in velocity
        pv = kp1 * error;
      } else {
        pv = kp1 * error + kd1 * (error - lasterror);
      }

      lasterror = error;

      if (pv >= -0.3 && pv <= 0.3) { // Assuming lower and upper thresholds of speed ofmotors are 50, 200 respectively
        brake();
        break;
      } else if (pv > 0) {
        int speed = min(max(pv, 50), 200);
       
        Motor_SetSpeed(speed, speed); //Set the parameters later.
        // theseparameters are speed of left and right wheel and will be
        // forforward motion since pv>=0
        

      } else if (pv < 0) {
        int speed = min(max(pv, -200), -50);
        
        Motor_SetSpeed(speed, speed); //Set the parameters later.
        // theseparameters are speed of left and right wheel and will be
        // forforward motion since pv>=0

      }
    }
  }
}





// void composite_pid(int dist){
//     // PID controller combining p2p_pid and sens_pid

//     double lasterror_p2p =0, lasterror_sens = 0;
//     double rotatn_req= (dist/WHEEL_DIAMETER); // number of rotations of wheel required to complete given distance
//     double setpnt_counts=(rotatn_req )* (counts_per_rotation); // number of counts required to reach the set point(inshort this is our setpoint)

//     double error_p2p = 0, error_sens = 0;

//     double pv_p2p, pv_sens; //Individual pv values for p2p and sens

//     while (1){
//         { //p2p_pid
//             error_p2p =(setpnt_counts)-(count); //x is the number of encoder counts per revolution
//             pv_p2p = kp1*error_p2p + kd1*(error_p2p-(lasterror_p2p));
//             lasterror_p2p = error_p2p;
//         }

//         { //sens_pid
//             int sensl = sensor_output(sens_trig0, sens_echo0);
//             int sensr = sensor_output(sens_trig2, sens_echo2);

//             if (thresHold(sensl) == 0 || thresHold(sensr) == 0){
//                 pv_sens = 0;
//             }
//             else{
//                 error_sens = sensl - sensr;
//                 pv_sens = kp2*error_sens + kd2*(error_sens-(lasterror_sens));
//                 lasterror_sens = error_sens;
//             }
//         }

//         pv_p2p = min(max(pv_p2p, -180), 180);

//         if (-1.5<(pv_p2p - pv_sens) && (pv_p2p - pv_sens)<1.5){
//             break;
//         }

//         int speedl = min(max(pv_p2p - pv_sens, -200), 200);
//         int speedr = min(max(pv_p2p + pv_sens, -200), 200);

//         Motor_SetSpeed(speedl, speedr);
//     }
// }

// double gyro_pid(int angle) {
//   int curr_angle = mpu.getAngleZ();  //fetch_angle()
//   int req_angle = curr_angle - angle;

//   double error = 0, lasterror = 0, pv = 0;

//   while (1) {
//     error = req_angle - mpu.getAngleZ();  // fetch_angle()
//     pv = kp3 * error + kd3 * (error - lasterror);
//     lasterror = error;

//     Serial.print(error);
//     Serial.print(" ");
//     Serial.println(pv);

//     if (pv >= -0.1 && pv <= 0.1) {
//       brake();
//       break;
//     } else if (pv > 0) {
//       int speed = min(max(pv, 50), 200);
//       Motor_SetSpeed(speed, -speed);
//     } else {
//       int speed = min(max(pv, -200), -50);
//       Motor_SetSpeed(speed, -speed);
//     }
//   }
// }