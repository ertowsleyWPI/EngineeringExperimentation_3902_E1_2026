#include <Stepper.h>

//1.8 deg per step -> 200 steps per Rev


const int StepsPerRev = 200;
int sensor2 = 3; // sensor pin
int val2; // 1: Magnetic field detected, 0: No magnetic field detected


//Stepper Library
// (Steps, AIN1, AIN2, BIN1, BIN2)
Stepper nema17Stepper(StepsPerRev, 5, 6, 4, 7);

void setup() {
  //Settup code, runs once

  pinMode(sensor2, INPUT); // set sensor pin as input

  //Motor Speed (rpm)

  nema17Stepper.setSpeed(10);

  Serial.begin(9600);

  Serial.println("NEMA 17 is initialized with TB6612");


}

void loop() {

  //main code loops

  Serial.println("Moving Clockwise");
  val2 = digitalRead(sensor2); // Read the sensor
  Serial.print("ky003 value: ");
  Serial.println(val2);
  nema17Stepper.step(StepsPerRev);

  delay(1000);

  Serial.println("Moving Counter Clockwise");
  val2 = digitalRead(sensor2); // Read the sensor
  Serial.print("ky003 value: ");
  Serial.println(val2);
  nema17Stepper.step(-StepsPerRev);

  delay(1000);


}