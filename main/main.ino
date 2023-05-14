
#include "Wire.h"
#include <MPU6050_light.h>
#include "bot_functions.h"

//Variable declaration 

MPU6050 mpu(Wire);


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

/* Input pins */
int mtrpin1_1 =in1 ;
int mtrpin1_2=in2;
int mtrpin2_1=in3 ;
int mtrpin2_2 =in4;

unsigned long int timer = 0;
int mtrspd1=PWMA ;
int mtrspd2=PWMB;

int kp1=0.2, ki1, kd1=1;
//Not using KP2, kd2
int kp3=1.5, ki3, kd3=3;
int threshold = 9;
int counts_per_rotation = 170;

int sens_trig0 =8, sens_echo0 =9;
int sens_trig1 =12, sens_echo1=13;
int sens_trig2 =A2, sens_echo2 =A3;
int sens_trig3 =A4, sens_echo3 =A5;



int buttonpin =A0;
bool wall_data[6][6][4];


int count = 0;

void readEncoder (){
    int b = digitalRead(ENCB);
    if(b > 0){
       count++; //count is current encoder count 
    } else{
       count--;
    }
}

void setup(){
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

  
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
    for (int i =0 ; i<6; i++){  //intializing wall array to 0 initially
        for (int j =0; j<6; j++){
            for (int k = 0; k<4; k++){
                wall_data[i][j][k] = 0;
            }
        }
    }
  

    
}


// short int arena_map[16][16] = {
//     {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
//     {13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
//     {12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
//     {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
//     {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
//     { 9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8, 9 },
//     { 8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7, 8 },
//     { 7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6, 7 },
//     { 7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6, 7 },
//     { 8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7, 8 },
//     { 9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8, 9 },
//     {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
//     {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
//     {12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
//     {13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
//     {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
// }; //arena node weight map

short int arena_map[6][6] = {
    {4, 3, 2, 2, 3, 4},
    {3, 2, 1, 1, 9, 3},
    {2, 1, 0, 0, 1, 2},
    {2, 1, 0, 0, 1, 2},
    {3, 2, 1, 1, 6, 3},
    {4, 3, 2, 2, 3, 4},
    
}; //arena node weight map

short int position[2] = {5, 0}; //Current position of bot
int facing = 1; // 0 = East, 1 = North, 2 = West, 3 = South
int found = 0;

void loop(){

    facing = 1;
    position[0] = 5;
    position[1] = 0; //Initializing bot information

    if (digitalRead(buttonpin)){
        while (!found){

            if (arena_map[position[0]][position[1]] == 0){ //Found the center
                found = 1;
                break;
            }

            if (digitalRead(buttonpin)){ // Time over, restart from beginning
                brake();
                break;
            }

            detect_wall(facing, position,wall_data); //Detect walls on current node

            int turn_direction = direction_wrt_bot(arena_map, position, facing, wall_data); //Decide direction to turn to so as to face the correct node
            switch (turn_direction)
            {
                case 0:
                    gyro_pid(-90); //Turn Left
                    facing = facing - 1;
                    if (facing == -1){
                        facing = 3;
                    }
                    break;

                case 1:
                    break; //Facing the correct node

                case 2:
                    facing = (facing + 1)%4;
                    gyro_pid (90); //Turn Right
                    break;

                case 3:
                    facing = (facing + 2)%4;
                    gyro_pid(90);  //Turn Back
                    gyro_pid(90);  //Turn Back
                    break;

                default:
                    Serial.println("Not possible");
                    break;
            }

            switch(facing){ //Update current position
                case 0:
                    position[1] -= 1;
                    break;

                case 1:
                    position[0] -= 1;
                    break;

                case 2:
                    position[1] += 1;
                    break;

                case 3:
                    position[0] += 1;
                    break;
            }

            p2p_pid(26); //Move forward 25 cms
            brake();
        }

        found =0;
    }
}

double gyro_pid(int angle) {
  int curr_angle = mpu.getAngleZ();  //fetch_angle()
  int req_angle = curr_angle - angle;

  double error = 0, lasterror = 0, pv = 0;

  while (1) {
    error = req_angle - mpu.getAngleZ();  // fetch_angle()
    pv = kp3 * error + kd3 * (error - lasterror);
    lasterror = error;

    Serial.print(error);
    Serial.print(" ");
    Serial.println(pv);

    if (pv >= -0.1 && pv <= 0.1) {
      brake();
      break;
    } else if (pv > 0) {
      int speed = min(max(pv, 50), 200);
      Motor_SetSpeed(speed, -speed);
    } else {
      int speed = min(max(pv, -200), -50);
      Motor_SetSpeed(speed, -speed);
    }
  }
}
