#include <WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// LED Pins
#define UP_LED     D0
#define DOWN_LED   D9
#define LEFT_LED   D2
#define RIGHT_LED  D3

WiFiServer server(8080); // TCP server on port 8080

void setup() {
  Serial.begin(115200);
  
  pinMode(UP_LED, OUTPUT);
  pinMode(DOWN_LED, OUTPUT);
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Starting AP...");
  display.display();

  WiFi.softAP("ESP_JOY_AP", "12345678"); // AP SSID and Password

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String data = client.readStringUntil('\n');
    data.trim();
    Serial.println("Received: " + data);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(data);
    display.display();

    // Reset all LEDs
    digitalWrite(UP_LED, LOW);
    digitalWrite(DOWN_LED, LOW);
    digitalWrite(LEFT_LED, LOW);
    digitalWrite(RIGHT_LED, LOW);

    if (data == "UP") digitalWrite(UP_LED, HIGH);
    else if (data == "DOWN") digitalWrite(DOWN_LED, HIGH);
    else if (data == "LEFT") digitalWrite(LEFT_LED, HIGH);
    else if (data == "RIGHT") digitalWrite(RIGHT_LED, HIGH);
  }
}
