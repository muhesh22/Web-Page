#define VRX_PIN 2   // A0
#define VRY_PIN 3   // A1
#define SW_PIN  0   // Digital button

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP); // Joystick button is active LOW
}

void loop() {
  int xValue = analogRead(VRX_PIN);
  int yValue = analogRead(VRY_PIN);
  int swState = digitalRead(SW_PIN);

  // Format for Serial Plotter: label:value, label:value
  Serial.print("X:");
  Serial.print(xValue);
  Serial.print(",Y:");
  Serial.print(yValue);
  Serial.print(",SW:");
  Serial.println(swState == LOW ? 0 : 4095); // show pressed/released as 0 or 4095

  delay(50); // smoother graph
}
