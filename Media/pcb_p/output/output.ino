#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  // Start the OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is the default I2C address
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Loop forever if failed
  }

  // Clear the buffer
  display.clearDisplay();

  // Display a message
  display.setTextSize(2);             // Text size
  display.setTextColor(WHITE);        // Text color
  display.setCursor(10, 25);          // Position
  display.println("Hello, OLED!");    // Message
  display.display();                  // Show on screen
}

void loop() {
  // Nothing here
}

