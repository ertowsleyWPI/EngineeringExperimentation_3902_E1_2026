#include <WiFi.h>
#include <WiFiUdp.h>

// Wi-Fi Network credentials
const char* ssid = "ESP32_Motor";
const char* password = "password123";

WiFiUDP udp;
const int localPort = 1234; 
char packetBuffer[255]; 

// Motor Driver & Button Pins
const int enA = 14;
const int in1 = 27;
const int in2 = 26;
const int buttonPin = 32;

bool motorRunning = false;
bool lastButtonState = HIGH; 

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enA, LOW); 

  // Create the Wi-Fi Network
  WiFi.softAP(ssid, password);
  udp.begin(localPort);
}

void loop() {
  // 1. Physical Button Backup
  bool currentButtonState = digitalRead(buttonPin);
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    delay(50); 
    motorRunning = !motorRunning; 
    updateMotor(); 
  }
  lastButtonState = currentButtonState;

  // 2. Wi-Fi Packet Reading Logic
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0; // Null terminate the string
    }
    String command = String(packetBuffer);
    command.trim();

    if (command == "1") {
      motorRunning = true;
      updateMotor();
    } else if (command == "0") {
      motorRunning = false;
      updateMotor();
    }
  }
}

void updateMotor() {
  if (motorRunning) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(enA, HIGH); 
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(enA, LOW); 
  }
}