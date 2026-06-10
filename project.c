#include <Servo.h>

// -------------------- Pin Definitions --------------------
#define FLAME_SENSOR_LEFT   A0
#define FLAME_SENSOR_CENTER A3   // Center sensor on A3
#define FLAME_SENSOR_RIGHT  A2

#define MOTOR_L1 5    // Left motor IN1
#define MOTOR_L2 6    // Left motor IN2
#define MOTOR_R1 9    // Right motor IN3
#define MOTOR_R2 10   // Right motor IN4


#define RELAY_PIN 7
#define SERVO_PIN 3   // Servo connected to D3

// -------------------- Global Constants --------------------
#define FIRE_DETECTED_THRESHOLD 800
#define FIRE_ALIGN_THRESHOLD    800   // Move forward when below this
#define FIRE_STOP_THRESHOLD     400   // Stop and spray

#define SERVO_LEFT_LIMIT 60
#define SERVO_RIGHT_LIMIT 120

#define MOTOR_SPEED_SLOW 120    // Slow turning speed
#define MOTOR_SPEED_NORMAL 200  // Normal forward speed

// -------------------- Global Variables --------------------
Servo waterServo;
bool servoDirection = true; // true = left-to-right, false = right-to-left
int servoPos = 90;

// -------------------- Setup --------------------
void setup() {
  Serial.begin(9600);

  pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_L2, OUTPUT);
  pinMode(MOTOR_R1, OUTPUT);
  pinMode(MOTOR_R2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);

  waterServo.attach(SERVO_PIN);
  waterServo.write(90);  // Center position

  Serial.println("🚀 Fire-Fighting Robot Ready...");
}

// -------------------- Main Loop --------------------
void loop() {
  int flameLeft = analogRead(FLAME_SENSOR_LEFT);
  int flameCenter = analogRead(FLAME_SENSOR_CENTER);
  int flameRight = analogRead(FLAME_SENSOR_RIGHT);

  Serial.print("L:"); Serial.print(flameLeft);
  Serial.print(" C:"); Serial.print(flameCenter);
  Serial.print(" R:"); Serial.println(flameRight);

  // -------- Fire Detection Logic --------
  if (flameLeft > FIRE_DETECTED_THRESHOLD && flameCenter > FIRE_DETECTED_THRESHOLD && flameRight > FIRE_DETECTED_THRESHOLD) {
    Serial.println("✅ No fire detected. Standing by...");
    stopMotors();
    digitalWrite(RELAY_PIN, LOW);  // Turn OFF relay
  }
  else if (flameLeft < FIRE_DETECTED_THRESHOLD && flameLeft < flameCenter && flameLeft < flameRight) {
    Serial.println("🔥 Fire LEFT — Turning slowly...");
    turnLeftSlow();
    digitalWrite(RELAY_PIN, LOW);  // Relay OFF while turning
  }
  else if (flameRight < FIRE_DETECTED_THRESHOLD && flameRight < flameCenter && flameRight < flameLeft) {
    Serial.println("🔥 Fire RIGHT — Turning slowly...");
    turnRightSlow();
    digitalWrite(RELAY_PIN, LOW);  // Relay OFF while turning
  }
  else if (flameCenter < FIRE_ALIGN_THRESHOLD && flameCenter > FIRE_STOP_THRESHOLD) {
    Serial.println("🚗 Fire ahead — Moving forward...");
    moveForwardNormal();
    digitalWrite(RELAY_PIN, LOW);  // Relay OFF while moving forward
  }
  else if (flameCenter <= FIRE_STOP_THRESHOLD) {
    Serial.println("🚒 Fire very close — Spraying water...");
    stopMotors();
    digitalWrite(RELAY_PIN, HIGH);  // Relay ON
    sweepServo();                    // Sweep servo while spraying
  }

  delay(100);
}

// -------------------- Motor Control Functions --------------------
void moveForwardNormal() {
  analogWrite(ENA, MOTOR_SPEED_NORMAL);
  digitalWrite(MOTOR_L1, HIGH);
  digitalWrite(MOTOR_L2, LOW);

  analogWrite(ENB, MOTOR_SPEED_NORMAL);
  digitalWrite(MOTOR_R1, HIGH);
  digitalWrite(MOTOR_R2, LOW);
}

void turnLeftSlow() {
  analogWrite(ENA, MOTOR_SPEED_SLOW);
  digitalWrite(MOTOR_L1, LOW);
  digitalWrite(MOTOR_L2, HIGH);

  analogWrite(ENB, MOTOR_SPEED_SLOW);
  digitalWrite(MOTOR_R1, HIGH);
  digitalWrite(MOTOR_R2, LOW);
}

void turnRightSlow() {
  analogWrite(ENA, MOTOR_SPEED_SLOW);
  digitalWrite(MOTOR_L1, HIGH);
  digitalWrite(MOTOR_L2, LOW);

  analogWrite(ENB, MOTOR_SPEED_SLOW);
  digitalWrite(MOTOR_R1, LOW);
  digitalWrite(MOTOR_R2, HIGH);
}

