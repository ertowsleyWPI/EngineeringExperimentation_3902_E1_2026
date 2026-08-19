#include <Stepper.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

//1.8 deg per step -> 200 steps per Rev


const int StepsPerRev = 200;
int sensor2 = 10; // sensor pin
int val2; // 1: Magnetic field detected, 0: No magnetic field detected
int lastVal2 = 1;
Adafruit_MPU6050 mpu3;


//Stepper Library
// (Steps, AIN1, AIN2, BIN1, BIN2)
Stepper nema17Stepper(StepsPerRev, 5, 6, 4, 7);

void setup() {
  //Settup code, runs once

  pinMode(sensor2, INPUT_PULLUP); // set sensor pin as input

  //Motor Speed (rpm)

  nema17Stepper.setSpeed(100);

  Serial.begin(9600);

  Serial.println("NEMA 17 is initialized with TB6612");
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize MPU at I2C address 3 (change this to your MPU's actual address)!
  if (!mpu3.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

}

void loop() {

  //main code loops

  Serial.println("Moving Clockwise");
  for(int i = 0; i < 30* StepsPerRev; i++) {
    nema17Stepper.step(1); 
    checkSensor();
  }
  delay(1000);

  Serial.println("Moving Counter Clockwise");
  for(int i = 0; i < 30* StepsPerRev; i++) {
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

  sensors_event_t a3, g3, temp3;
  mpu3.getEvent(&a3, &g3, &temp3);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a3.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a3.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a3.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g3.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g3.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g3.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp3.temperature);
  Serial.println(" degC");
  

}