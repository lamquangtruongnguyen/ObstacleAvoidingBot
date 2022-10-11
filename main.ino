//Define pins for Ultrasonic Sensor
  const int echoPinR = 9;
  const int trigPinR = 8;
  const int echoPinM = 11;
  const int trigPinM = 10;
  const int echoPinL = 13;
  const int trigPinL = 12;

  long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;

//L293 Connection   
  const int motorA1      = 2; // Left front  
  const int motorA2      = 3; // Left back
  const int motorAspeed  = 4;
  const int motorB1      = 6; // Right front
  const int motorB2      = 7; // Right back
  const int motorBspeed  = 5;

  int vSpeed = 110;                      
  int turn_speed = 230;       // 0 - 255  max
  int t_p_speed = 125;
  int stop_distance = 12;
  int turn_delay = 10000;

void setup() {
  //Ultrasonic
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinM, OUTPUT);
  pinMode(echoPinM, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  
  //Motor
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
    
  Serial.begin(9600);
  delay(3000);
   
}
void loop() {
  
/*
SensorRead(trigPinL, echoPinL);
LeftSensor = distance;
SensorRead(trigPinR, echoPinR);
RightSensor = distance;
SensorRead(trigPinM, echoPinM);
FrontSensor = distance;

Serial.print("Left:");
Serial.print(LeftSensor);
Serial.print(" Front: ");
Serial.print(FrontSensor);
Serial.print(" Right: ");
Serial.println(RightSensor);
*/


  SensorRead(trigPinM, echoPinM);
  FrontSensor = distance;
  RightSensor = 0;
  LeftSensor = 0;
  
  delay(50);
  
  if (FrontSensor <= 35) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    SensorRead(trigPinR, echoPinR);
    RightSensor = distance;
    delay(300);
    SensorRead(trigPinL, echoPinL);
    LeftSensor = distance;
    delay(300);
    if (RightSensor >= LeftSensor) {
      turnRight();
      delay(300);
      moveStop();
    } else {
      turnLeft();
      delay(300);
      moveStop();
    }
  } else {
    moveForward();
  }
 
}


void moveStop(){
  
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);
  
}

void moveForward(){

  digitalWrite(motorA1,HIGH);
  digitalWrite(motorA2,LOW);                       
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  analogWrite(motorAspeed, turn_speed);
  analogWrite(motorBspeed, vSpeed);
  
}

void moveBackward(){

  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,HIGH);                       
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,HIGH);

  analogWrite(motorAspeed, turn_speed);
  analogWrite(motorBspeed, vSpeed);
  
}

void turnRight(){

  digitalWrite(motorA1,HIGH);
  digitalWrite(motorA2,LOW);                       
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,HIGH);

  analogWrite(motorAspeed, turn_speed);
  analogWrite(motorBspeed, vSpeed);
  
}

void turnLeft(){
  
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,HIGH);                       
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  analogWrite(motorAspeed, turn_speed);
  analogWrite(motorBspeed, vSpeed);
  
}

void SensorRead(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
}
