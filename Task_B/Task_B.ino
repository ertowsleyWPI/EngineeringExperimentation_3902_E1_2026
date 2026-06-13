const int LED1_Pin = 2; // LED Pin number on Arduino
const int LED2_Pin = 5;
const int button1_Pin = 3; // Button Pin number
const int button2_Pin = 4;

int button1_state = 0;
int button2_state = 0;

void setup() {
  //Initialize serial communication - allows printing to the console for debug
  Serial.begin(9600);
  pinMode(LED1_Pin, OUTPUT); // Set the LED Anode pin as an output pin

  pinMode(button1_Pin, INPUT); //Set the Button pin as an input

  pinMode(LED2_Pin, OUTPUT);

  pinMode(button2_Pin, INPUT);
}

void loop() {
  
  //Read Button State
  button1_state = digitalRead(button1_Pin);
  button2_state = digitalRead(button2_Pin);
  
//  // put your main code here, to run repeatedly:
// digitalWrite(LED1_Pin, HIGH); //Turn the LED on
//  delay(1000); // Wait 1000ms
//  digitalWrite(LED1_Pin, LOW); Turn the LED off
//  delay(1000); //wait 1000ms

  if (button1_state == HIGH){
    Serial.println("Button 1 is Pressed");

    digitalWrite(LED1_Pin, HIGH); // Turn the LED on


  } else {
    Serial.println("Buttton 1 is not pressed"); //print msg
    digitalWrite(LED1_Pin, LOW); // Turn the LED Off
  }
  

  if (button2_state == HIGH){
    Serial.println("Button 2 is Pressed");

    digitalWrite(LED2_Pin, HIGH); // Turn the LED on


  } else {
    Serial.println("Button 2 is not pressed"); //print msg
    digitalWrite(LED2_Pin, LOW); // Turn the LED Off
  }
  delay(100); // Small delay to limit inputs
}
