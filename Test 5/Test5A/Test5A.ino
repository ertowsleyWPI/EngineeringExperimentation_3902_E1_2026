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
  digitalWrite(enA, 0);

  Serial.println("ESP 32 Trials");
  Serial.println("Type 'Start' to turn motor on");


}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {//Checks the terminal for input 

    String command = Serial.readStringUntil('\n');

    command.trim();
    command.toUpperCase(); //corrects small letters

    Serial.println("Command Recieved");
    Serial.println(command);

    //Motor Commands

    if (command == "START") {

      digitalWrite(in1, HIGH);
      digitalWrite(in2, HIGH);
      analogWrite(enA, 200);

      Serial.println("Motor is Running");


    } else if (command == "STOP") {

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enA, 0);

      Serial.println("Motor is not Running");

    }





  }

}



