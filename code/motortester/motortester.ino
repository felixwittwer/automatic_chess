String serialtext; // for incoming serial data
int stepCounter;
int steps = 0;
int amount = 0;
int speedm = 750;
int mtogo = 0;
int enpin = 10;
int steppin = 9;
int dirpin = 8;

void setup() {
    pinMode(enpin, OUTPUT); // Enable M1
    pinMode(steppin, OUTPUT); // Step M1
    pinMode(dirpin, OUTPUT); // Richtung M1
    Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    serialtext = Serial.readString();
    if (serialtext = "enLOW"){
      digitalWrite(enpin, LOW);
    }
    if (serialtext = "enHIGH"){
      digitalWrite(enpin, HIGH);
    }
    if (serialtext = "dirLOW"){
      digitalWrite(dirpin, LOW);
    }
    if (serialtext = "dirHIGH"){
      digitalWrite(dirpin, HIGH);
    }
    if (serialtext.startsWith("S")){
      serialtext.remove(0,1);
      Serial.print("Speed set to: ");
      Serial.print(serialtext);
      speedm = serialtext.toInt();
    }
    if (serialtext.startsWith("M")){
      serialtext.remove(0,1);
      Serial.print("M1 move: ");
      Serial.print(serialtext);
      steps = serialtext.toInt();
      steps = abs(steps); //normaly + or - decides which direction but in this script it has to be set manually / the following loop would fail if steps is negative to prevent me forgetting this fact I added this line so the following loop runs even if I input a negative value
      for(stepCounter = 0; stepCounter <= steps; stepCounter++) {
        digitalWrite(steppin,HIGH);
        delayMicroseconds(speedm);
        digitalWrite(steppin,LOW);
        delayMicroseconds(speedm);
//      Serial.println(stepCounter); //be aware to only uncomment this line if baude rate is high enough so 115200 or more
      }
    }
  }
}
