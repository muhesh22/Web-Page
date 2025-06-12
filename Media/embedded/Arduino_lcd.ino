#include <Adafruit_LiquidCrystal.h>
int seconds = 0; 
Adafruit_LiquidCrystal lcd_1(0);
    
void setup() {
  lcd_1.begin(16, 2);
  lcd_1.print("Welcome to Fab");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Academy");
  delay(2000);
  lcd_1.clear();
}
    
void loop() {
  lcd_1.setCursor(0, 0);
  lcd_1.print("Time (sec): ");
  lcd_1.setCursor(11, 0);
  lcd_1.print(seconds);
        
  lcd_1.setBacklight(1);
  delay(500);
  lcd_1.setBacklight(0);
  delay(500);

  seconds++;
}
        