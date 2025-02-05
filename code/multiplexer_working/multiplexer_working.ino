//Mux control pins
int en = 7;
int s0 = 8;
int s1 = 9;
int s2 = 10;
int s3 = 11;


//Mux in "SIG" pin
int SIG_pin = 3;

void setup() {
  pinMode(en, OUTPUT);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  
  pinMode(SIG_pin, INPUT);

  digitalWrite(en, LOW);
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  Serial.begin(9600);
}

void loop() {

  //Loop through and read all 16 values
  for (int i = 0; i < 16; i ++) {
    Serial.print("Value at channel ");
    Serial.print(i); Serial.print("is : ");
    Serial.println(readMux(i));
    delay(300);
  }
}

int readMux(int channel) {
  int controlPin[] = {s0, s1, s2, s3};
  int muxChannel[16][4] = { {0, 0, 0, 0},
                            {1, 0, 0, 0},
                            {0, 1, 0, 0},
                            {1, 1, 0, 0},
                            {0, 0, 1, 0},
                            {1, 0, 1, 0},
                            {0, 1, 1, 0},
                            {1, 1, 1, 0},
                            {0, 0, 0, 1},
                            {1, 0, 0, 1},
                            {0, 1, 0, 1},
                            {1, 1, 0, 1},
                            {0, 0, 1, 1},
                            {1, 0, 1, 1},
                            {0, 1, 1, 1},
                            {1, 1, 1, 1}
                          };
  //loop through the 4 sig
  for (int i = 0; i < 4; i ++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  //read the value at the SIG pin
  int val = digitalRead(SIG_pin); //return the value
  return val;
}