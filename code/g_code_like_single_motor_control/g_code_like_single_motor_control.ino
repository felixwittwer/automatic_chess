String serialtext; // for incoming serial data
int stepCounter;
int steps = 0;
int amount = 0;
int speedm = 750;
int mtogo = 0;
int ntogo = 0;

void setup() {
  pinMode(3, OUTPUT); // Enable M1
  pinMode(5, OUTPUT); // Step M1
  pinMode(4, OUTPUT); // Richtung M1
  pinMode(10, OUTPUT); // Enable M2
  pinMode(9, OUTPUT); // Step M2
  pinMode(8, OUTPUT); // Richtung M2
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
      serialtext = Serial.readString();
    if (serialtext.startsWith("M")){
      serialtext.remove(0,1);
      Serial.print("M1 move: ");
      Serial.print(serialtext);
      amount = serialtext.toInt();
      mtogo = mtogo + amount;
    }
    if (serialtext.startsWith("N")){
      serialtext.remove(0,1);
      Serial.print("M2 move: ");
      Serial.print(serialtext);
      amount = serialtext.toInt();
      ntogo = ntogo + amount;
    }
    if (serialtext.startsWith("S")){
      serialtext.remove(0,1);
      Serial.print("Speed set to: ");
      Serial.print(serialtext);
      speedm = serialtext.toInt();
    }
    //go command for movement
    if (serialtext.startsWith("G")){
    serialtext.remove(0,1);
      if (mtogo!=0){
        motor(speedm,3,mtogo,5,4);
        Serial.println("M");
        mtogo = 0;
      }
      if (ntogo!=0){
        motor(speedm,10,ntogo,9,8);
        Serial.println("N");
        ntogo = 0;
      }
    }
    Serial.print("ToGo:");
    Serial.print(" M1:");
    Serial.print(mtogo);
    Serial.print(" M2:");
    Serial.println(ntogo);
  }
}

//motor(speedm,6,steps,5,4);
void motor(int speedm,int enpin, int steps, int steppin, int dirpin){
  // Enable motor
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
