#include <Stepper.h>

//1.8 deg per step -> 200 steps per Rev


const int StepsPerRev = 200;
int sensor2 = 10; // sensor pin
int val2; // 1: Magnetic field detected, 0: No magnetic field detected
int lastVal2 = 1;


//Stepper Library
// (Steps, AIN1, AIN2, BIN1, BIN2)
Stepper nema17Stepper(StepsPerRev, 5, 6, 4, 7);

void setup() {
  //Settup code, runs once

  pinMode(sensor2, INPUT_PULLUP); // set sensor pin as input

  //Motor Speed (rpm)

  nema17Stepper.setSpeed(10);

  Serial.begin(9600);

  Serial.println("NEMA 17 is initialized with TB6612");


}

void loop() {

  //main code loops

  Serial.println("Moving Clockwise");
  for(int i = 0; i < StepsPerRev; i++) {
    nema17Stepper.step(1); 
    checkSensor();
  }
  delay(1000);

  Serial.println("Moving Counter Clockwise");
  for(int i = 0; i < StepsPerRev; i++) {
    nema17Stepper.step(-1); 
    checkSensor();
  }

  delay(1000);




}


void checkSensor() {
  val2 = digitalRead(sensor2);
  
  // Only print if the sensor state has CHANGED (prevents massive text spam)
  if (val2 != lastVal2) {
    if (val2 == 0) {
      Serial.println("Magnet is detected!");
    } else {
      Serial.println("Magnet is not detected.");
    }
    lastVal2 = val2; // Update the state
  }
}