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


// Timer variables to prevent serial flooding
unsigned long lastDataTime = 0;
const int dataInterval = 100; // Output IMU data every 100 milliseconds

//Stepper Library
// (Steps, AIN1, AIN2, BIN1, BIN2)
Stepper nema17Stepper(StepsPerRev, 5, 6, 4, 7);

void setup() {
  //Settup code, runs once

  pinMode(sensor2, INPUT_PULLUP); // set sensor pin as input

  //Motor Speed (rpm)

  nema17Stepper.setSpeed(100);

  Serial.begin(115200);

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
  for(long i = 0; i < 300L* StepsPerRev; i++) { // 300 is 3 minutes at 100RPM
    nema17Stepper.step(1); 
    checkSensor();
  }
  delay(1000);

  Serial.println("Moving Counter Clockwise");
  for(long i = 0; i < 300L* StepsPerRev; i++) {
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

  // Non-blocking timer for the IMU data
  unsigned long currentTime = millis();
  if (currentTime - lastDataTime >= dataInterval) {
    sensors_event_t a3, g3, temp3;
    mpu3.getEvent(&a3, &g3, &temp3);

    Serial.print("Time: "); Serial.print(currentTime);
    Serial.print(" ms | Accel: "); Serial.print(a3.acceleration.x);
    Serial.print(", "); Serial.print(a3.acceleration.y);
    Serial.print(", "); Serial.print(a3.acceleration.z);
    Serial.print(" | Gyro: "); Serial.print(g3.gyro.x);
    Serial.print(", "); Serial.print(g3.gyro.y);
    Serial.print(", "); Serial.print(g3.gyro.z);
    Serial.print(" | Temp: "); Serial.println(temp3.temperature);

    lastDataTime = currentTime; // Reset the timer
  }

}