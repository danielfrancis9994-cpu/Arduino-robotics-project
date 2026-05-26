#include <Servo.h>

Servo servo;

// Pins
const int servoPin = 8;
const int buzzerPin = 2;
const int trigPin = 4;
const int echoPin = 5;

// Settings
const int distanceThreshold = 10;

int angle = 0;
int direction = 1;

void setup() {
  servo.attach(servoPin);

  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(buzzerPin, LOW);
}

void loop() {

  // ===== Servo Sweep =====
  servo.write(angle);

  angle += direction * 1;

  // Change direction at limits
  if (angle >= 120 || angle <= 0) {
    direction *= -1;
  }

  // ===== Ultrasonic Reading =====
  long distance = getDistance();

  // ===== Buzzer Control =====
  if (distance > 0 && distance <= distanceThreshold) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(20); // Small delay for smooth motion
}


// ===============================
// Function to Read Distance
// ===============================
long getDistance() {

  long duration;
  long distance;

  // Clear trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo with timeout
  duration = pulseIn(echoPin, HIGH, 20000);

  // If no signal received
  if (duration == 0) {
    return -1;
  }

  // Convert to cm
  distance = duration * 0.034 / 2;

  return distance;
}
