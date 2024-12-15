int stepCounter;
int steps = 2000;

void setup() {
  pinMode(6, OUTPUT); // Enable M1
  pinMode(5, OUTPUT); // Step M1
  pinMode(4, OUTPUT); // Richtung M1
  pinMode(10, OUTPUT); // Enable M1
  pinMode(9, OUTPUT); // Step M1
  pinMode(8, OUTPUT); // Richtung M1
  Serial.begin(9600);
  // Enable motors
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
}

void loop() {
  digitalWrite(4,HIGH); // im Uhrzeigersinn
  digitalWrite(8,HIGH); // im Uhrzeigersinn

  for(stepCounter = 0; stepCounter < steps; stepCounter++) {
    digitalWrite(5,HIGH);
    digitalWrite(9,HIGH);
    delayMicroseconds(1000);
    digitalWrite(5,LOW);
    digitalWrite(9,LOW);
    delayMicroseconds(1000);
    Serial.println(stepCounter);
  }
//  
//  delay(1000);
//
//  digitalWrite(4,LOW); // gegen den Uhrzeigersinn
//
//  for(stepCounter = 0; stepCounter < steps; stepCounter++) {
//    digitalWrite(5,HIGH);
//    delayMicroseconds(500);
//    digitalWrite(5,LOW);
//    delayMicroseconds(500);
//  }
//
//  delay(1000);
}
