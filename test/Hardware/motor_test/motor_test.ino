#define OPTIMUM_SPEED 150
// #define WHEEL_DIAMETER 4.427
#define WHEEL_DIAMETER 10.681415
#define counts_per_rotation 840

#define ENCA 0
#define ENCB MOSI
#define PWMA 10
#define PWMB 11
#define ENCC 1
#define ENCD SS
#define in1 4
#define in2 7
#define in3 5
#define in4 6


int mtrpin1_1 = in1;
int mtrpin1_2 = in2;
int mtrpin2_1 = in3;
int mtrpin2_2 = in4;

int mtrspd1 = PWMA;
int mtrspd2 = PWMB;

// double kp1, kd1;//set the values
// int kp2, kd2;//set the values
// double kp3, kd3; //set the values

int count;


void readEncoder (){
    int b = digitalRead(ENCB);
    if(b > 0){
       count++; //count is current encoder count 
    } else{
       count--;
    }
    return count;
}

void setup() {
  // put your setup code here, to run once:
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
  count = 0;
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  // attachInterrupt(digitalPinToInterrupt(ENCC),readEncoder,RISING);
  Serial.begin(96000);
  
}


void Motor_SetSpeed(int spdL, int spdR){
  if (spdL < 0){
    analogWrite(mtrspd1, -spdL);
    digitalWrite(mtrpin1_1, LOW);
    digitalWrite(mtrpin1_2, HIGH);
  }

  else{
    analogWrite(mtrspd1, spdL);
    digitalWrite(mtrpin1_1, HIGH);
    digitalWrite(mtrpin1_2, LOW);
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



void loop() {

  //testing straight pid
  p2p_pid(26);
  while(1){
    Motor_SetSpeed(0,0);
  }


}