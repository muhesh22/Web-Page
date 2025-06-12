void setup() {
  pinMode(9, OUTPUT);
  }

  void loop() {
    for (int u = 0; u < 255; u++){
    analogWrite(9, u);
    delay(50);
    }
  }