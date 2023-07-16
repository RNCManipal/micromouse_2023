#include "Wire.h"
#include <MPU6050_light.h>
#define OPTIMUM_SPEED 150
#define WHEEL_DIAMETER 4.38


MPU6050 mpu(Wire);
unsigned long timer = 0;

#define ENCA 0
#define ENCB MOSI
#define PWMA 10
#define PWMB 11
#define ENCC 1
#define ENCD SS
#define in1 4
#define in2 5
#define in3 6
#define in4 A1

int mtrpin1_1 = in1;
int mtrpin1_2 = in2;
int mtrpin2_1 = in3;
int mtrpin2_2 = in4;

int mtrspd1 = PWMA;
int mtrspd2 = PWMB;

double kp1, kd1;//set the values
int kp2, kd2;//set the values
double kp3, kd3; //set the values

int count;
int counts_per_rotation ; //Set the value

// int ENCA, ENCB, ENCC, ENCD;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  count = 0;
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){Serial.println("Not Connected"); } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(ENCC,INPUT);
  pinMode(ENCD,INPUT);
  
  pinMode (PWMA, OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  
  // attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
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


void brake(){
  digitalWrite(mtrpin1_1, LOW);
  digitalWrite(mtrpin1_2, LOW);

  digitalWrite(mtrpin2_1, LOW);
  digitalWrite(mtrpin2_2, LOW);
}



double gyro_pid(int angle) {
  int curr_angle = int(mpu.getAngleZ())%360;  //fetch_angle()
  int req_angle = (curr_angle - angle)%360;
 
  // Serial.println(req_angle);

  double error = 0, lasterror = 0, pv = 0;

  while (1) {
    mpu.update();
    error = req_angle - (int(mpu.getAngleZ())%(360));  // fetch_angle()
    pv = (kp3 * error) + (kd3 * (error - lasterror));
    Serial.println((kp3 * error));
    Serial.println(" ");
    lasterror = error;
    Serial.println((kd3 * (error - lasterror)));
    if (pv >= -0.1 && pv <= 0.1) {
      brake();
      break;
    } else if (pv > 0) {
      int speed = min(max(pv, 50), 200);
      Motor_SetSpeed(-speed, speed);
    } else {
      int speed = min(max(pv, -200), -50);
      Motor_SetSpeed(speed, -speed);
    }
  }
}

void loop() {
  mpu.update();

  gyro_pid(90);
  Serial.println("Finished");
  Motor_SetSpeed(0,0);
    delay(2000);
  


}

