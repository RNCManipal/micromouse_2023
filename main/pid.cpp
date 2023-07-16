#include <Arduino.h>
#include <stdlib.h>
#include "bot_functions.h"
#include <MPU6050_light.h>







void p2p_pid(int dist) //Point to  Point PID    
{   
   // PID Controller. Used to control the speed of the bot. Function
  double rotatn_req = (dist /(3.14*WHEEL_DIAMETER)); // number of rotations ofwheel required to complete given distance

  // let encoder giving 'x' number of counts per rotation
  double setpnt_counts =(rotatn_req) * (counts_per_rotation); // number of counts requiredto reach the set point(inshort this is our setpoint)
  Serial.print(setpnt_counts );
  count=0;
  double lasterror = 0;
  double kp1 = 0.2;
  double kd1 = 1.0;
  double last_error = 0, error = 0;
  double pv = 0;

  // double maxerror = kp1*setpnt_counts + kd1*(setpnt_counts);

  if (setpnt_counts < 0) {
    Serial.println("entered negative setpnt");
    while (1) {
      Serial.print("set point Count1 ");
      Serial.print(" : ");
      Serial.println(setpnt_counts);
      Serial.print("Count1 ");
      Serial.print(" : ");
      Serial.println(count);
      error = (-count) - (setpnt_counts);
      // Serial.println(error); 
      // Serial.println(); 
      Serial.print("error1");
      Serial.print(" : ");
      Serial.println(error);
      Serial.print("lasterror1");
      Serial.print(" : ");
      Serial.println(lasterror);
      if (lasterror ==0) { // this condition is used to remove intial high gain in velocity
        pv = kp1 * error;
      } else {
        pv = kp1 * error + kd1 * (error - lasterror);
      }
      Serial.print("pv1");
      Serial.print(" : ");
       Serial.println(pv);
      // pv= mapp(pv, -maxerror, maxerror, -255, 255);
      lasterror = error;
      if (pv >= -0.3 && pv <= 0.3) { // Assuming lower and upper thresholds of speed of motors are 50, 200 respectively
         brake();
        

        break;
      } else if (pv > 0) {
        int speed = min(max(pv, 50), 200);
        Serial.print("speed1");
        Serial.print(" : ");
        Serial.println(speed);
        Motor_SetSpeed(-speed, -speed); //Set the parameters later.
        // theseparameters are speed of left and right wheel and will be
        // forforward motion since pv>=0
      
      } else {
        int speed = min(max(pv, -200), -50);
        Serial.print("speed2");
        Serial.print(" : ");
        Serial.println(speed);
        Motor_SetSpeed(speed, speed); //Set the parameters later.
        // theseparameters are speed of left and right wheel and will be
        // forforward motion since pv>=0

      }
    }
  } else if (setpnt_counts > 0) {
    while (1) {
      Serial.print("set point Count2 ");
      Serial.print(" : ");
      Serial.println(setpnt_counts);
      Serial.print("Count2 ");
      Serial.print(" : ");
      Serial.println(count);
      error = (setpnt_counts) -(-count); // x is the number of encoder countsper revolution
       Serial.print("error2");
      Serial.print(" : ");
      Serial.println(error);
      Serial.print("lasterror2");
      Serial.print(" : ");
      Serial.println(lasterror);
      if (lasterror ==0) { // this condition is used to remove intial high gain in velocity
        pv = kp1 * error;
      } else {
        pv = kp1 * error + kd1 * (error - lasterror);
      }
      Serial.print("pv2");
      Serial.print(" : ");
       Serial.println(pv);
      //  Serial.println(pv);
      lasterror = error;
      // Serial.print(" ");
      //  Serial.println(pv);

      if (pv >= -0.3 && pv <= 0.3) { // Assuming lower and upper thresholds of speed ofmotors are 50, 200 respectively
        brake();
        break;
      } else if (pv > 0) {
        int speed = min(max(pv, 50), 200);
        Serial.print("speed3");
        Serial.print(" : ");
        Serial.println(speed);
        Motor_SetSpeed(speed, speed); //Set the parameters later.
        // theseparameters are speed of left and right wheel and will be
        // forforward motion since pv>=0
        

      } else if (pv < 0) {
        int speed = min(max(pv, -200), -50);
        Serial.print("speed4");
        Serial.print(" : ");
        Serial.println(speed);
        // Motor_SetSpeed(-speed, -speed); //Set the parameters later.
        // theseparameters are speed of left and right wheel and will be
        // forforward motion since pv>=0

      }
    }
  }
}
