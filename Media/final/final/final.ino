// Sensor pins
const int sensors[5] = {0, 1, 2, 3, 6}; // D0, D1, D2, D3, D6

// Motor control pins (adjust if wired differently)
#define ENA 10
#define IN1 4
#define IN2 5
#define IN3 7
#define IN4 9
#define ENB 8

void setup() {
  Serial.begin(115200);

  // Sensor inputs
  for (int i = 0; i < 5; i++) {
    pinMode(sensors[i], INPUT);
  }

  // Motor outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, 150); // Set motor speed
  analogWrite(ENB, 150);

  Serial.println("Line Follower Bot Started");
}

void loop() {
  int sensorState[5];
  for (int i = 0; i < 5; i++) {
    sensorState[i] = digitalRead(sensors[i]);
  }

  // Print to Serial Monitor for debugging
  Serial.print("Sensors: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(sensorState[i]);
    Serial.print(" ");
  }

  // Simple logic
  if (sensorState[2] == 0 && sensorState[1] == 1 && sensorState[3] == 1) {
    moveForward(); Serial.println("-> Forward");
  } else if (sensorState[0] == 0 || sensorState[1] == 0) {
    turnLeft(); Serial.println("-> Left");
  } else if (sensorState[3] == 0 || sensorState[4] == 0) {
    turnRight(); Serial.println("-> Right");
  } else {
    stopMotors(); Serial.println("-> Stop");
  }

  delay(100);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
