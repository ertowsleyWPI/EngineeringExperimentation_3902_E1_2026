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
  // Initialize Motor Driver Pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Initialize Button with internal pull-up (defaults to HIGH, goes LOW when pressed)
  pinMode(buttonPin, INPUT_PULLUP);

  // Motor starts off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enA, LOW); 
}

void loop() {
  // Read the button
  bool currentButtonState = digitalRead(buttonPin);

  // Check if button was just pressed (transitioned from HIGH to LOW)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    delay(50); // Tiny delay to debounce the physical button press
    
    motorRunning = !motorRunning; // Toggle the state

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

  // Save the state for the next loop
  lastButtonState = currentButtonState;
}