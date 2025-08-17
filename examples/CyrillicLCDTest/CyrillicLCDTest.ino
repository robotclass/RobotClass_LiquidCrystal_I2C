#include <RobotClass_LiquidCrystal_I2C.h>

RobotClass_LiquidCrystal_I2C lcd(0x3F, 16, 2);

byte idx = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print( "Привет!" );
  lcd.setCursor(0,1);
  lcd.print( "мир" );
}

void loop() {
}
