#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//OLED Settings

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Global variables and pin definitions
// Define the pins for the HC-SR04 sensor
const int trigPin3 = 4; // Pin that triggers the ultrasonic pulse
const int echoPin3 = 2; // Pin that receives the echo signal

// Variables to store the pulse duration and calculated distance
float duration3, distance3;
Servo myservo4;  // create servo object to control a servo
int pos4 = 0;    // variable to store the servo position


void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
  // Setup function: runs once at startup
  // Configure the trigger pin as an OUTPUT and the echo pin as an INPUT
  pinMode(trigPin3, OUTPUT); // Set trigger pin as output
  pinMode(echoPin3, INPUT);  // Set echo pin as input
  myservo4.attach(3);

  //OLED Settup

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x36))
  {
    Serial.println("SSD1306 Allocation Failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();


}


void loop() {
  // Main loop: continuously measures distance

  // Ensure the trigger pin is LOW to start
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2); // Short delay to allow sensor stabilization

  // Trigger the sensor by sending a HIGH pulse for 10 microseconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); // Pulse duration
  digitalWrite(trigPin3, LOW);

  // Read the duration of the echo pulse (in microseconds)
  duration3 = pulseIn(echoPin3, HIGH);

  // Calculate the distance (cm) using the speed of sound (0.0343 cm/us)
  // Dividing by 2 accounts for the round-trip distance
  distance3 = (duration3 * 0.0343) / 2;

  // Output the measured distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance3);


if(distance3 > 10 && distance3 <= 16){

  // Short delay before the next measurement
  delay(100);  for (pos4 = 0; pos4 <= 180; pos4 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos4); // tell servo to go to position in variable 'pos'
    delay(15); // waits 15 ms for the servo to reach the position
  }
  for (pos4 = 180; pos4 >= 0; pos4 -= 1) { // goes from 180 degrees to 0 degrees
    myservo4.write(pos4); // tell servo to go to position in variable 'pos'
    delay(15); // waits 15 ms for the servo to reach the position
  }

  delay(1000);

}

  //Diplay on OLED

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,0);

  display.println("Ultrasonic + Servo");

  display.setCursor(0, 20);
  display.println("Distance: ");
  display.print(distance3);

  display.println(" cm");

  display.display();

  delay(100);

  //distance condition

 


}


 
