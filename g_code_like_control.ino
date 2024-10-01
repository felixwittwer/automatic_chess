String serialtext; // for incoming serial data
int stepCounter;
int steps = 0;
int button = 0;
int amount = 0;
int speedm = 1000;

void setup() {
  pinMode(2, INPUT); //arm button
  pinMode(6, OUTPUT); // Enable M1
  pinMode(5, OUTPUT); // Step M1
  pinMode(4, OUTPUT); // Richtung M1
  pinMode(10, OUTPUT); // Enable M1
  pinMode(9, OUTPUT); // Step M1
  pinMode(8, OUTPUT); // Richtung M1
  Serial.begin(9600);
  // Enable motors
//  digitalWrite(6, LOW);
//  digitalWrite(10, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    serialtext = Serial.readString();
    //Serial.println(serialtext);

    if (serialtext.startsWith("X")){
      serialtext.remove(0,1);
      Serial.print("XAchse move: ");
      Serial.print(serialtext);
      amount = serialtext.toInt();
      if (amount>0){
        digitalWrite(4,LOW);
        digitalWrite(8,HIGH);
      }else if (amount<0){
        digitalWrite(4,HIGH);
        digitalWrite(8,LOW);
      }  
    }

    if (serialtext.startsWith("Y")){
      serialtext.remove(0,1);
      Serial.print("YAchse move: ");
      Serial.print(serialtext);
      amount = serialtext.toInt();

      if (amount>0){
        digitalWrite(4,HIGH);
        digitalWrite(8,HIGH);
      }else if (amount<0){
        digitalWrite(4,LOW);
        digitalWrite(8,LOW);
      }
    }

    if (serialtext.startsWith("S")){
      serialtext.remove(0,1);
      Serial.print("Speed set to: ");
      Serial.print(serialtext);
      speedm = serialtext.toInt();
    }

    // Enable motors
    digitalWrite(6, LOW);
    digitalWrite(10, LOW);
    steps = abs(amount);
    for(stepCounter = 0; stepCounter < steps; stepCounter++) {
      digitalWrite(5,HIGH);
      digitalWrite(9,HIGH);
      delayMicroseconds(speedm);
      digitalWrite(5,LOW);
      digitalWrite(9,LOW);
      delayMicroseconds(speedm);
    }
    digitalWrite(6, HIGH);
    digitalWrite(10, HIGH);
  }
}
