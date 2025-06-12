#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <time.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "Muhesh";
const char* password = "876543219";

int currentScreen = 0;
unsigned long lastSlideTime = 0;
const int slideInterval = 3000; // 3 seconds per slide

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 40) {
    delay(500);
    Serial.print(".");
    retry++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect WiFi");
  }
}

void setupTime() {
  configTime(19800, 0, "pool.ntp.org", "time.nist.gov");
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to get time");
  } else {
    Serial.println("Time synced");
  }
}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }
  display.clearDisplay();
  display.display();

  connectToWiFi();
  setupTime();
}

String getTimeString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "No Time";
  char buf[10];
  strftime(buf, sizeof(buf), "%H:%M:%S", &timeinfo);
  return String(buf);
}

String getDateString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "No Date";
  char buf[12];
  strftime(buf, sizeof(buf), "%d-%m-%Y", &timeinfo);
  return String(buf);
}

String getDayString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "No Day";
  char buf[12];
  strftime(buf, sizeof(buf), "%A", &timeinfo);
  return String(buf);
}

void drawIndicators(int activeIndex) {
  int dotY = SCREEN_HEIGHT - 10;
  int startX = (SCREEN_WIDTH - (3 * 16)) / 2; // Center 3 dots spaced 16px apart

  for (int i = 0; i < 3; i++) {
    if (i == activeIndex) {
      display.fillCircle(startX + i * 16, dotY, 5, SSD1306_WHITE);  // Big circle
    } else {
      display.fillCircle(startX + i * 16, dotY, 2, SSD1306_WHITE);  // Small circle
    }
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSlideTime >= slideInterval) {
    lastSlideTime = currentMillis;

    String textToShow;
    switch (currentScreen) {
      case 0: textToShow = getTimeString(); break;
      case 1: textToShow = getDateString(); break;
      case 2: textToShow = getDayString(); break;
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    int yPos = (SCREEN_HEIGHT - 16) / 2;
    display.setCursor((SCREEN_WIDTH - (textToShow.length() * 12)) / 2, yPos);
    display.print(textToShow);.

    drawIndicators(currentScreen);

    display.display();

    currentScreen = (currentScreen + 1) % 3;
  }
}
