#include <WiFi.h>

#define JOY_X D0
#define JOY_Y D1
#define JOY_SW 2

const char* ssid = "ESP_JOY_AP";
const char* password = "12345678";
const char* host = "192.168.4.1";
const uint16_t port = 8080;

void setup() {
  Serial.begin(115200);
  pinMode(JOY_SW, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to AP!");
}

void loop() {
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);
  bool sw = digitalRead(JOY_SW) == LOW;

  String msg = "CENTER";

  if (xVal < 1000) msg = "LEFT";
  else if (xVal > 3000) msg = "RIGHT";
  else if (yVal < 1000) msg = "UP";
  else if (yVal > 3000) msg = "DOWN";
  else if (sw) msg = "PRESSED";

  WiFiClient client;
  if (client.connect(host, port)) {
    client.println(msg);
    client.stop();
    Serial.println("Sent: " + msg);
  } else {
    Serial.println("Connection failed");
  }

  delay(200);
}
