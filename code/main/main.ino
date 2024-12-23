/*
main.ino

This is the main script for the motor movement in a CoreXY system. 

(c)2024 Felix Wittwer
*/

String serialtext; // for incoming serial data
int stepCounter;
int steps = 0;
int amount = 0;

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
int m2enpin = 10
int m2steppin = 9;
int m2dirpin = 8;
//endstops
int xstop = 12;
int ystop = 13;
//magnet
int magnetpin = 2;

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
}