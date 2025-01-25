/*
 * LiquidCrystal_I2C - библиотека для символьных ЖК дисплеев (Hitachi HD44780) со встроенным I2C интерфейсом
 * поддержка кириллицы
 * Автор Олег Евсегнеев для RobotClass (2025).
 * e-mail: oleg.evsegneev@gmail.com
 */
 
#include <inttypes.h>
#include "Print.h" 
#include <Wire.h>

#define IO_MODEL_PCA9534 0x01
#define IO_MODEL_PCF8574 0x02

#define IO_REG_OUTPUT 0x01
#define IO_REG_CONFIG 0x03

#define CP_UTF8 0
#define CP_CP1251 1

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit

class RobotClass_LiquidCrystal_I2C: public Print {
    public:
        RobotClass_LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t cp = CP_UTF8, uint8_t io = IO_MODEL_PCA9534);
        size_t print( const String &s );
        void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
        void clear();
        void home();
        void noDisplay();
        void display();
        void noBlink();
        void blink();
        void noCursor();
        void cursor();
        void scrollDisplayLeft();
        void scrollDisplayRight();
        void printLeft();
        void printRight();
        void leftToRight();
        void rightToLeft();
        void shiftIncrement();
        void shiftDecrement();
        void noBacklight();
        void backlight();
        void autoscroll();
        void noAutoscroll(); 
        void createChar(uint8_t, uint8_t[]);
        void setCursor(uint8_t, uint8_t); 
        virtual size_t write(uint8_t);
        void command(uint8_t);
        void init();

    private:
        String utf8rus(String source);
        String convertCyr( const String &s );
        uint8_t getCharCyr( uint8_t ch );

        void send(uint8_t, uint8_t);
        void write4bits(uint8_t);
        void expanderWrite(uint8_t, uint8_t);
        void pulseEnable(uint8_t);

        uint8_t _codepage;
        uint8_t _io;
        uint8_t _Addr;
        uint8_t _displayfunction;
        uint8_t _displaycontrol;
        uint8_t _displaymode;
        uint8_t _numlines;
        uint8_t _cols;
        uint8_t _rows;
        uint8_t _backlightval;
};