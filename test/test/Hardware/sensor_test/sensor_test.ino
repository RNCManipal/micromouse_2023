int sens_trig0 =8, sens_echo0 =9;
int sens_trig1 =12, sens_echo1=13;
int sens_trig2 =A2, sens_echo2 =A3;
int sens_trig3 =A4, sens_echo3 =A5;

int threshold = 10;

int sensor_output(int sonartrig, int sonarecho){
    //Measures distance to a barrier in cm (maybe)

    digitalWrite(sonartrig, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(sonartrig, HIGH);
    delayMicroseconds(10);
    
    digitalWrite(sonartrig, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    int duration = pulseIn(sonarecho, HIGH, 0);

    // Calculating the distance
    int distance = duration * 0.034 / 2;

    return distance;
}

bool thresHold(int distance){
    if (distance > threshold){
        return 0;
    }
    else{
        return 1;
    }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(sens_trig0, OUTPUT);
  pinMode(sszxxxx, INPUT);
  pinMode(sens_trig1, OUTPUT);
  pinMode(sens_echo1, INPUT);
  pinMode(sens_trig2, OUTPUT);
  pinMode(sens_echo2, INPUT);
  pinMode(sens_trig3, OUTPUT);
  pinMode(sens_echo3, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(sensor_output(sens_trig0, sens_echo0));
  Serial.print("\t");
  Serial.print(sensor_output(sens_trig1, sens_echo1));
  Serial.print("\t");
  Serial.print(sensor_output(sens_trig2, sens_echo2));
  Serial.print("\t");
  Serial.println(sensor_output(sens_trig3, sens_echo3));
}
