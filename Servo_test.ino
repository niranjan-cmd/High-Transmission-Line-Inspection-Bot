#include <Servo.h>

Servo myservo;
int servoPin = 14;   // connect servo signal to pin 14

void setup() {
  Serial.begin(115200);
  myservo.attach(servoPin);

  myservo.write(0);   // initial zero position

  Serial.println("Type commands:");
  Serial.println("o = OPEN (90 degrees)");
  Serial.println("c = CLOSE (0 degrees)");
}

void loop() {

  if (Serial.available()) {
    char command = Serial.read();

    if (command == 'o') {
      myservo.write(180);
      Serial.println("Servo OPEN");
    }

    if (command == 'c') {
      myservo.write(0);
      Serial.println("Servo CLOSED");
    }
  }
}