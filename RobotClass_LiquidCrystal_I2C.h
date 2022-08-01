/*
 * LiquidCrystal_I2C library override for cyrillic LCD
 * Written by Oleg Evsegneev for RobotClass (2022).
 * e-mail: oleg.evsegneev@gmail.com
*/
 
#include <LiquidCrystal_I2C.h>

#define CP_UTF8 0
#define CP_CP1251 1

class RobotClass_LiquidCrystal_I2C: public LiquidCrystal_I2C {
    public:
        RobotClass_LiquidCrystal_I2C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows, uint8_t cp);
        size_t print( const String &s );
    private:
        uint8_t codepage;
        String utf8rus(String source);
        String convertCyr( const String &s );
        uint8_t getCharCyr( uint8_t ch );
};