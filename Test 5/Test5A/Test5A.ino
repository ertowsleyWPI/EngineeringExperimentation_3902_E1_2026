// Motor Driver Pins

const int enA = 14;
const int in1 = 27;
const int in2 = 26;

String command;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  delay(500);

  //Initialize Motor Driver PIns

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //motor starts off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enA, LOW);

  Serial.println("ESP 32 Trials");
  Serial.println("Type 'Start' to turn motor on");


}

void loop() {
  // 1. Check if a new message has arrived
  if (Serial.available() > 0) { 

    // 2. Read and format the message
    command = Serial.readStringUntil('\n');
    command.trim();
    command.toUpperCase(); 

    Serial.println("Command Received:");
    Serial.println(command);

    // 3. Process the command INSIDE the Serial.available block
    if (command == "START") {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW); 
      digitalWrite(enA, HIGH); // Using 150 to ensure enough voltage to start

      Serial.println("Motor is Running");

    } else if (command == "STOP") {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(enA, LOW);

      Serial.println("Motor is not Running");
    }

  } // <-- 4. THIS is where the Serial.available block must close. 
}



