// BTS7960 Forward & Stop (Constant PWM = 400)

#define RPWM 5    // GPIO5
#define LPWM 4    // GPIO4
#define REN  0    // GPIO0
#define LEN  2    // GPIO2

int speedValue = 200; // Constant PWM speed

void setup() {

  Serial.begin(9600);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(REN, OUTPUT);
  pinMode(LEN, OUTPUT);

  // Enable BTS7960
  digitalWrite(REN, HIGH);
  digitalWrite(LEN, HIGH);

  stopMotor();

  Serial.println("Ready");
  Serial.println("Send 'f' = Forward");
  Serial.println("Send 's' = Stop");
}

void loop() {

  if (Serial.available()) {

    char cmd = Serial.read();

    if (cmd == 'f') {
      forwardMotor();
    }

    else if (cmd == 's') {
      stopMotor();
    }
  }
}

void forwardMotor() {

  analogWrite(RPWM, speedValue); // Forward PWM
  analogWrite(LPWM, 0);

  Serial.println("Forward at PWM 400");
}

void stopMotor() {

  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);

  Serial.println("Stopped");
}