/*
  This program tests the Adafruit VL53L0X Time of Flight Distance Sensor.
  It initializes the sensor, reads a distance measurement, and prints the 
  distance in millimeters to the serial monitor.
  Note: The VL53L0X can handle about 50 - 1200 mm of range distance.

  Board: (Originally wrote for a Arduino Uno R4 (or R3), changed to a Nano for the remainder of this experiment)
  Component: Time of Flight Distance Sensor (GY-530 base on VL53L0X)
  Library: https://github.com/adafruit/Adafruit_VL53L0X  (Adafruit_VL53L0X by Adafruit)



  Update 1: Got the ToF Sensor functioning, had to solder the board
  Update 2: Got the ToF Sensor dialed in 

*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_VL53L0X.h>

//OLED SETTINGS

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Global Variables 

const int trigPin = 4; //Ultrasonic Pulse Trigger Pin
const int echoPin = 5; //Ultrasonic Pulse Echo Pin

float distanceUS, distanceToF, duration;

//Create an object of the Adafruit_VL53L0X class
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 Allocation Failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();

  // wait until serial port opens for native USB devices
  while (!Serial) {
    delay(1);
  }

  //Initialize the sensor
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1)  //Stop the program if the sensor cannot be initialized
      ;
  }

  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));

  Serial.print(F("Time in Milliseconds"));
  Serial.print(F(" , "));
  Serial.println(F("Distance"));

}


void loop() {
  

  //US Related

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // Short to allow sensor stabilization

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Pulse Duration
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // Read the duration of the echo pulse (in microseconds)

  distanceUS = (duration * 0.0343) / 2;

  //ToF Sensor Related
  
  VL53L0X_RangingMeasurementData_t measure;

  Serial.print(millis());
  Serial.print(" , ");
  lox.rangingTest(&measure, false);  // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print(F("Distance (mm): "));
    distanceToF = measure.RangeMilliMeter;
    Serial.println(distanceToF);
  } else {
    Serial.println(F(" out of range "));
  }
    Serial.print(F(" , "));
    Serial.println(distanceUS);

  delay(1000); // to make debugging easier

  //OLED Output

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.setCursor(0, 20);
  display.println(F("ToF Distance: "));
  display.print(distanceToF);
  display.println(F(" mm"));
  display.println(F("US Distance: "));
  display.print(distanceUS);
  display.println(F(" cm"));

  display.display();
  delay(100);

}