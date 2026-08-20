// Motor Driver Pins
const int enA = 14;
const int in1 = 27;
const int in2 = 26;

// Button Pin
const int buttonPin = 32;

// State tracking
bool motorRunning = false;
bool lastButtonState = HIGH; 

void setup() {
  Serial.begin(115200); // Open the port for MATLAB

  // Initialize Motor Driver Pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Initialize Button with internal pull-up 
  pinMode(buttonPin, INPUT_PULLUP);

  // Motor starts off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enA, LOW); 
}

void loop() {
  // --- 1. PHYSICAL BUTTON LOGIC ---
  bool currentButtonState = digitalRead(buttonPin);

  // Check if button was just pressed
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    delay(50); // Tiny delay to debounce
    motorRunning = !motorRunning; // Toggle the state
    updateMotor(); 
  }
  lastButtonState = currentButtonState;

  // --- 2. MATLAB SERIAL LOGIC ---
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Strip any invisible carriage returns

    if (command == "1") {
      motorRunning = true;
      updateMotor();
    } else if (command == "0") {
      motorRunning = false;
      updateMotor();
    }
  }
}

// --- HELPER FUNCTION ---
void updateMotor() {
  if (motorRunning) {
    // START MOTOR
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(enA, HIGH); 
  } else {
    // STOP MOTOR
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(enA, LOW); 
  }
}