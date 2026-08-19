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

//Part 3

unsigned long previousStepMicros = 0; //
//50 RPM (doesnt need to be as fast for 3 whole minutes) = 1.2s/rot. 4s/200steps = 0.006 seconds = 6000 microseconds
unsigned long stepIntervalMicros = 6000;
long stepCount = 0;
float angle = 0.0;

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

  nema17Stepper.setSpeed(50);

  Serial.begin(115200);

  Serial.println("NEMA 17 is initialized with TB6612");
  while (!Serial){
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize MPU at I2C address 3 (change this to your MPU's actual address)!
  if (!mpu3.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  Serial.println("Time(ms),StepCount,Angle(deg),HallEffect,GyroX,GyroY,GyroZ");

}

void loop() {

  //main code loops

  long targetSteps = 30000; // 3 min * 50rpm = 150 rots 150 * 200 = 30000steps.
  stepCount = 0;
  angle = 0.0;
 
 // Serial.println("Moving Clockwise");
  //for(long i = 0; i < 300L* StepsPerRev; i++) { // 300 is 3 minutes at 100RPM
 //   nema17Stepper.step(1); 
 //   checkSensor();
 // }
  //delay(1000);

  //Serial.println("Moving Counter Clockwise");
  //for(long i = 0; i < 300L* StepsPerRev; i++) {
  //  nema17Stepper.step(-1); 
  //  checkSensor();
  //}

  // Non-blocking step execution using micros()
  while (stepCount < targetSteps) {
    unsigned long currentMicros = micros();
    
    // Trigger exactly when the interval has passed
    if (currentMicros - previousStepMicros >= stepIntervalMicros) {
      previousStepMicros = currentMicros;
      
      // Step -1 (CCW) to match the PMKS simulation parameters
      nema17Stepper.step(-1); 
      stepCount++;
      
      // Calculate approximate angle (1.8 deg per step)
      angle = stepCount * 1.8; 
      
      // Output data instantly upon stepping
      checkSensorAndPrint(); 
    }
  }

  delay(5000); // Delay now 5s




}


void checkSensorAndPrint() {
  val2 = digitalRead(sensor2);
  
  sensors_event_t a3, g3, temp3;
  mpu3.getEvent(&a3, &g3, &temp3);

  // STRICTLY SPACE-FREE FORMATTING: Time,Step,Angle,Hall,GyroX,GyroY,GyroZ
  Serial.print(millis());
  Serial.print(",");
  Serial.print(stepCount);
  Serial.print(",");
  Serial.print(angle);
  Serial.print(",");
  Serial.print(val2);
  Serial.print(",");
  Serial.print(g3.gyro.x);
  Serial.print(",");
  Serial.print(g3.gyro.y);
  Serial.print(",");
  Serial.println(g3.gyro.z);
}