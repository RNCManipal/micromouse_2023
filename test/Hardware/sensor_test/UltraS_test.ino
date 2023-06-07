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

int trig1=8, trig2=12, trig3=A2, trig4= A4 ;
int echo1=9, echo2=13, echo3=A3, echo4=A5;
int pos1 = 0,pos2=0;
int i;

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(ENCC,INPUT);
  pinMode(ENCD,INPUT);
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);
  pinMode(echo3,INPUT);
  pinMode(echo4,INPUT);
  pinMode (PWMA, OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode (trig1, OUTPUT);
  pinMode (trig2, OUTPUT);
  pinMode(trig3,OUTPUT);
  pinMode(trig4,OUTPUT);
  // attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder1,RISING);
  // attachInterrupt(digitalPinToInterrupt(ENCC),readEncoder2,RISING);

}

void trigger(int pinNo){
  digitalWrite (pinNo, LOW);
  delayMicroseconds(2);
  digitalWrite (pinNo, HIGH);
  delayMicroseconds(10);
  digitalWrite (pinNo, LOW);
}

int distance (int pinNo){
  int read, dis;
  read = pulseIn(pinNo, HIGH);
  dis = (read * 0.034) / 2;

  return dis;
}

void loop() {
  // digitalWrite(in1,HIGH);
  // digitalWrite(in2,LOW);
  // digitalWrite(in3,HIGH);
  // digitalWrite(in2,LOW);
  // analogWrite (PWMA, 255);
  // analogWrite(PWMB,255);
  // Serial.println(pos1/1000);
  // Serial.println(pos2/1000);

  trigger(trig1);
  int dis1= distance(echo1);
  trigger(trig2);
  int dis2= distance(echo2);
  trigger(trig3);
  int dis3= distance(echo3);
  trigger(trig4);
  int dis4= distance(echo4);
  


  Serial.print (dis1);
  Serial.print (" ");
  Serial.print (dis2);
  Serial.print (" ");
  Serial.print (dis3);
  Serial.print (" ");
  Serial.println (dis4);
  

  
}

