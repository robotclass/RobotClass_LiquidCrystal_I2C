#include <RobotClass_LiquidCrystal_I2C.h>

RobotClass_LiquidCrystal_I2C lcd(0x27, 16, 2, CP_UTF8);

byte idx = 0;

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print( "АБВГДЕЁЖЗИКЛМНОП" );
  lcd.setCursor(0,1);
  lcd.print( "абвгдеёжзиклмноп" );
  delay(1000);

  lcd.setCursor(0,0);
  lcd.print( "РСТУФХЦЧШЩЪЫЬЭЮЯ" );
  lcd.setCursor(0,1);
  lcd.print( "рстуфхцчшщъыьэюя" );
  delay(1000);
}
