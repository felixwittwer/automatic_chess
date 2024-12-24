/*
main.ino

This is the main script for the motor movement in a CoreXY system. 

(c)2024 Felix Wittwer
*/

String serialtext; // for incoming serial data
int stepCounter;
int steps = 0;

//variables for motorsystem
int speedm = 750;
int mtogo = 0; //motor one steps to go
int ntogo = 0; //motor two steps to go

//variables for xy coordinate system
int curx = 0; //current x
int cury = 0; //current y
int xtogo = 0;
int ytogo = 0;

//IO variables
int m1enpin = 3;
int m1steppin = 5;
int m1dirpin = 4;
int m2enpin = 10;
int m2steppin = 9;
int m2dirpin = 8;
//endstops
int xstop = 12;
int ystop = 13;
//magnet
int magnetpin = 2;
bool magnetstatus = false;

void setup(){
  pinMode(m1enpin, OUTPUT);
  pinMode(m1steppin, OUTPUT);
  pinMode(m1dirpin, OUTPUT);
  pinMode(m2enpin, OUTPUT);
  pinMode(m2steppin, OUTPUT);
  pinMode(m2dirpin, OUTPUT);
  pinMode(magnetpin, OUTPUT);
  pinMode(xstop, INPUT);
  pinMode(ystop, INPUT);
  Serial.begin(115200); //Make shure the baudrate is high enough for your pupouse. When too low it could hinder the execution of the code. This is in the case of motorcontrol with very small delays crucial. 
  digitalWrite(m1enpin, HIGH);
  digitalWrite(m2enpin, HIGH);
}

void loop(){
  if (Serial.available() > 0) {
    serialtext = Serial.readString();
    //change process variables based on given arguments by the serial connection
    if (serialtext.startsWith("X")){
      serialtext.remove(0,1);
      Serial.print(serialtext);
      xtogo += serialtext.toInt();
    }
    if (serialtext.startsWith("Y")){
      serialtext.remove(0,1);
      Serial.print(serialtext);
      ytogo += serialtext.toInt();
    }
    if (serialtext.startsWith("M")){
      serialtext.remove(0,1);
      Serial.println("Magnet");
      if (magnetstatus == false){
        magnetstatus = true;
        digitalWrite(magnetpin, HIGH);
      } else if (magnetstatus == true){
        magnetstatus = false;
        digitalWrite(magnetpin, LOW);
      }
    }
    if (serialtext.startsWith("S")){
      serialtext.remove(0,1);
      Serial.print("Speed set to: ");
      Serial.print(serialtext);
      speedm = serialtext.toInt();
    }
    if (serialtext.startsWith("G")){
      movement();
    }
  }
}

void movement(){
  //calculate steps for each motor
  mtogo = xtogo + ytogo;
  ntogo = xtogo - ytogo;
  while (mtogo != 0 or ntogo != 0) {
    // if (mtogo = 0){
    //   motor(speedm, m2enpin, ntogo, m2steppin, m2dirpin);
    //   ntogo = 0;
    // }
    // if (ntogo = 0){
    //   motor(speedm, m1enpin, mtogo, m1steppin, m1dirpin);
    //   mtogo = 0;
    // }
    if (mtogo != 0){
      if (mtogo < 0){
        motor(speedm, m1enpin, -1, m1steppin, m1dirpin);
        mtogo = mtogo + 1;
      }
      if (mtogo > 0){
        motor(speedm, m1enpin, 1, m1steppin, m1dirpin);
        mtogo = mtogo - 1;
      }
    }
    if (ntogo != 0){
      if (ntogo < 0){
        motor(speedm, m2enpin, -1, m2steppin, m2dirpin);
        ntogo = ntogo + 1;
      }
      if (ntogo > 0){
        motor(speedm, m2enpin, 1, m2steppin, m2dirpin);
        ntogo = ntogo - 1;
      }
    }
    Serial.print(mtogo);
    Serial.print(",");
    Serial.println(ntogo);
  }
  Serial.println("finished");
  // digitalWrite(m1enpin, HIGH);
  // digitalWrite(m2enpin, HIGH);
  xtogo = 0;
  ytogo = 0;
}

void motor(int speedm,int enpin, int steps, int steppin, int dirpin){
  digitalWrite(enpin, LOW);
  if (steps > 0){
    digitalWrite(dirpin, LOW);
  }else if (steps < 0){
    digitalWrite(dirpin, HIGH);
  }
  steps = abs(steps);
  for(stepCounter = 0; stepCounter <= steps; stepCounter++) {
    digitalWrite(steppin,HIGH);
    delayMicroseconds(speedm);
    digitalWrite(steppin,LOW);
    delayMicroseconds(speedm);
//      Serial.println(stepCounter);
  }
  digitalWrite(enpin, HIGH);
}