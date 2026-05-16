#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "*****";
const char* password = "*****";

// MOTOR PINS
#define RPWM 5
#define LPWM 4
#define REN  0
#define LEN  2

int speedValue = 50;

// SERVO PINS
#define SERVO1_PIN 15
#define SERVO2_PIN 12
#define SERVO3_PIN 14

Servo servo1, servo2, servo3;

// Track current positions
int pos1 = 0, pos2 = 0, pos3 = 0;

ESP8266WebServer server(80);

// ===== Smooth Servo Move =====
void moveServoSmooth(Servo &servo, int &currentPos, int targetPos, int delayMs = 250) {
  targetPos = constrain(targetPos, 0, 180);
  if (currentPos < targetPos) {
    for (int p = currentPos; p <= targetPos; p++) {
      servo.write(p);
      server.handleClient(); // keep web server alive during move
      delay(delayMs);
    }
  } else {
    for (int p = currentPos; p >= targetPos; p--) {
      servo.write(p);
      server.handleClient();
      delay(delayMs);
    }
  }
  currentPos = targetPos;
}

// ===== Motor Functions =====
void forwardMotor() {
  analogWrite(RPWM, speedValue);
  analogWrite(LPWM, 0);
  Serial.println("Motor Forward");
}

void stopMotor() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  Serial.println("Motor Stopped");
}

// ===== Servo Handlers =====
void handleServo1() {
  if (server.hasArg("angle")) {
    int angle = server.arg("angle").toInt();
    Serial.print("Servo1 -> "); Serial.println(angle);
    server.sendHeader("Location", "/");
    server.send(303);
    moveServoSmooth(servo1, pos1, angle);
  } else {
    server.sendHeader("Location", "/");
    server.send(303);
  }
}

void handleServo2() {
  if (server.hasArg("angle")) {
    int angle = server.arg("angle").toInt();
    Serial.print("Servo2 -> "); Serial.println(angle);
    server.sendHeader("Location", "/");
    server.send(303);
    moveServoSmooth(servo2, pos2, angle);
  } else {
    server.sendHeader("Location", "/");
    server.send(303);
  }
}

void handleServo3() {
  if (server.hasArg("angle")) {
    int angle = server.arg("angle").toInt();
    Serial.print("Servo3 -> "); Serial.println(angle);
    server.sendHeader("Location", "/");
    server.send(303);
    moveServoSmooth(servo3, pos3, angle);
  } else {
    server.sendHeader("Location", "/");
    server.send(303);
  }
}

// ===== Web Page =====
void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>ESP8266 Control</title>";
  html += "<style>";
  html += "body { font-family: Arial; text-align: center; padding: 20px; background: #f0f0f0; }";
  html += "h2 { color: #333; } h3 { color: #555; }";
  html += ".btn { width: 150px; height: 60px; font-size: 20px; margin: 5px; border: none; border-radius: 8px; cursor: pointer; }";
  html += ".btn-fwd { background: #4CAF50; color: white; }";
  html += ".btn-stop { background: #f44336; color: white; }";
  html += ".btn-set { background: #2196F3; color: white; width: 80px; height: 40px; font-size: 16px; border-radius: 6px; border: none; cursor: pointer; }";
  html += "input[type='number'] { width: 80px; height: 40px; font-size: 16px; text-align: center; border-radius: 6px; border: 1px solid #ccc; }";
  html += ".card { background: white; border-radius: 10px; padding: 15px; margin: 10px auto; max-width: 350px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }";
  html += ".note { font-size: 12px; color: #888; margin-top: 5px; }";
  html += "</style></head><body>";

  html += "<h2>ESP8266 Motor & Servo Control</h2>";

  // Motor Card
  html += "<div class='card'><h3>Motor</h3>";
  html += "<a href='/forward'><button class='btn btn-fwd'>FORWARD</button></a> ";
  html += "<a href='/stop'><button class='btn btn-stop'>STOP</button></a></div>";

  // Current positions display
  html += "<div class='card'><h3>Current Positions</h3>";
  html += "<p>Servo 1: <b>" + String(pos1) + "°</b> &nbsp; Servo 2: <b>" + String(pos2) + "°</b> &nbsp; Servo 3: <b>" + String(pos3) + "°</b></p></div>";

  // Servo 1
  html += "<div class='card'><h3>Servo 1</h3>";
  html += "<form action='/servo1'>";
  html += "<input type='number' name='angle' min='0' max='180' value='" + String(pos1) + "'> ";
  html += "<button class='btn-set' type='submit'>SET</button>";
  html += "</form><p class='note'>Moves smoothly (20ms/degree)</p></div>";

  // Servo 2
  html += "<div class='card'><h3>Servo 2</h3>";
  html += "<form action='/servo2'>";
  html += "<input type='number' name='angle' min='0' max='180' value='" + String(pos2) + "'> ";
  html += "<button class='btn-set' type='submit'>SET</button>";
  html += "</form><p class='note'>Moves smoothly (20ms/degree)</p></div>";

  // Servo 3
  html += "<div class='card'><h3>Servo 3</h3>";
  html += "<form action='/servo3'>";
  html += "<input type='number' name='angle' min='0' max='180' value='" + String(pos3) + "'> ";
  html += "<button class='btn-set' type='submit'>SET</button>";
  html += "</form><p class='note'>Moves smoothly (20ms/degree)</p></div>";

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleForward() { forwardMotor(); handleRoot(); }
void handleStop()    { stopMotor();   handleRoot(); }

// ===== Setup =====
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\nBooting...");

  pinMode(RPWM, OUTPUT); pinMode(LPWM, OUTPUT);
  pinMode(REN, OUTPUT);  pinMode(LEN, OUTPUT);
  digitalWrite(REN, HIGH); digitalWrite(LEN, HIGH);
  stopMotor();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println();
  Serial.print("Connected! IP: "); Serial.println(WiFi.localIP());

  servo1.attach(SERVO1_PIN); servo2.attach(SERVO2_PIN); servo3.attach(SERVO3_PIN);
  servo1.write(0); servo2.write(0); servo3.write(0);
  Serial.println("Servos attached and ready.");

  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/stop", handleStop);
  server.on("/servo1", handleServo1);
  server.on("/servo2", handleServo2);
  server.on("/servo3", handleServo3);
  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}