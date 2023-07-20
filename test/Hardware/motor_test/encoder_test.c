

#define WHEEL_DIAMETER 4.38
// #define WHEEL_DIAMETER 10.681415
#define counts_per_rotation 840


MPU6050 mpu(Wire);
unsigned long timer = 0;

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


double start_time;
int pos = 0;
int i;

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode (PWMA, OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
}
// void stop_motor(){
//   digitalWrite(in1,LOW);
//   digitalWrite(in2,LOW);        
// }

// double time(){
//   start_time = millis();
//   return start_time;
// }

void loop() {
    Serial.println(pos);  
  //     if(pos<0) {
  //       stop_motor();
  //       double curr_time= millis();
  //       double time_elspased= (curr_time - start_time);
  //       Serial.println(time_elspased); 
         
  //     }

  //  if(pos==0){
  //    double start_time= time();
  //  }   
   
  //   if(pos>=0){
  //     digitalWrite(in1,HIGH);
  //     digitalWrite(in2,LOW);
  //     analogWrite (PWM, 255);
  //     delay(94);
  //     Serial.println(pos);
  //   }
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    pos++;
  }
  else{
    pos--;
  }
  
}