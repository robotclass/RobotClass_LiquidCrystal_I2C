/*
 * LiquidCrystal_I2C - библиотека для символьных ЖК дисплеев (Hitachi HD44780) со встроенным I2C интерфейсом
 * поддержка кириллицы
 * Автор Олег Евсегнеев для RobotClass (2025).
 * e-mail: oleg.evsegneev@gmail.com
 */
#include "RobotClass_LiquidCrystal_I2C.h"

#include "Arduino.h"

RobotClass_LiquidCrystal_I2C::RobotClass_LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t cp, uint8_t io){
    _codepage = cp;
    _io = io;
    
    _Addr = lcd_Addr;
    _cols = lcd_cols;
    _rows = lcd_rows;
    _backlightval = LCD_NOBACKLIGHT;
}

/*-------- Поддержка кириллицы --------*/

// преобразование строк utf-8 в cp1251
String RobotClass_LiquidCrystal_I2C::utf8rus(String source){
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
  return target;
}

// перегрузка функции print из модуля Print
// выводит строки с преобразованием из кодировки IDE в кодировку дисплея
size_t RobotClass_LiquidCrystal_I2C::print( const String &s ){
    if( _codepage == CP_UTF8 ){
        return Print::print( convertCyr( utf8rus( s )));
    } else {
        return Print::print( convertCyr( s ));
    }
}

// преобразует строку из кодировки IDE в кодировку дисплея
String RobotClass_LiquidCrystal_I2C::convertCyr( const String &s ){
    String target = s;
    for( int idx = 0; idx<s.length(); idx++ ){
        target[idx] = getCharCyr( s[idx] );
    }
    return target;
}

// преобразует сивол из кодировки IDE в кодировку дисплея
uint8_t RobotClass_LiquidCrystal_I2C::getCharCyr( uint8_t ch ){
  char rch = ch;
  switch (ch){
    case 0xC0: rch = 0x41; break;
    case 0xC1: rch = 0xA0; break;
    case 0xC2: rch = 0x42; break;
    case 0xC3: rch = 0xA1; break;
    case 0xC4: rch = 0xE0; break;
    case 0xC5: rch = 0x45; break;
    case 0xC6: rch = 0xA3; break;
    case 0xC7: rch = 0xA4; break;
    case 0xC8: rch = 0xA5; break;
    case 0xC9: rch = 0xA6; break;
    case 0xCA: rch = 0x4B; break;
    case 0xCB: rch = 0xA7; break;
    case 0xCC: rch = 0x4D; break;
    case 0xCD: rch = 0x48; break;
    case 0xCE: rch = 0x4F; break;
    case 0xCF: rch = 0xA8; break;

    case 0xD0: rch = 0x50; break;
    case 0xD1: rch = 0x43; break;
    case 0xD2: rch = 0x54; break;
    case 0xD3: rch = 0xA9; break;
    case 0xD4: rch = 0xAA; break;
    case 0xD5: rch = 0x58; break;
    case 0xD6: rch = 0xE1; break;
    case 0xD7: rch = 0xAB; break;
    case 0xD8: rch = 0xAC; break;
    case 0xD9: rch = 0xE2; break;
    case 0xDA: rch = 0xAD; break;
    case 0xDB: rch = 0xAE; break;
    case 0xDC: rch = 0x62; break;
    case 0xDD: rch = 0xAF; break;
    case 0xDE: rch = 0xB0; break;
    case 0xDF: rch = 0xB1; break;

    case 0xE0: rch = 0x61; break;
    case 0xE1: rch = 0xB2; break;
    case 0xE2: rch = 0xB3; break;
    case 0xE3: rch = 0xB4; break;
    case 0xE4: rch = 0xE3; break;
    case 0xE5: rch = 0x65; break;
    case 0xE6: rch = 0xB6; break;
    case 0xE7: rch = 0xB7; break;
    case 0xE8: rch = 0xB8; break;
    case 0xE9: rch = 0xB9; break;
    case 0xEA: rch = 0xBA; break;
    case 0xEB: rch = 0xBB; break;
    case 0xEC: rch = 0xBC; break;
    case 0xED: rch = 0xBD; break;
    case 0xEE: rch = 0x6F; break;
    case 0xEF: rch = 0xBE; break;

    case 0xF0: rch = 0x70; break;
    case 0xF1: rch = 0x63; break;
    case 0xF2: rch = 0xBF; break;
    case 0xF3: rch = 0x79; break;
    case 0xF4: rch = 0xE4; break;
    case 0xF5: rch = 0x78; break;
    case 0xF6: rch = 0xE5; break;
    case 0xF7: rch = 0xC0; break;
    case 0xF8: rch = 0xC1; break;
    case 0xF9: rch = 0xE6; break;
    case 0xFA: rch = 0xC2; break;
    case 0xFB: rch = 0xC3; break;
    case 0xFC: rch = 0xC4; break;
    case 0xFD: rch = 0xC5; break;
    case 0xFE: rch = 0xC6; break;
    case 0xFF: rch = 0xC7; break;

    case 0xA8: rch = 0xA2; break;
    case 0xB8: rch = 0xB5; break;
  }
  return rch;
}

void RobotClass_LiquidCrystal_I2C::init(){
    Wire.begin();
    if( _io == IO_MODEL_PCA9534 ){
        expanderWrite(IO_REG_CONFIG, 0x00);
    }
    
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
    begin(_cols, _rows);  
}

void RobotClass_LiquidCrystal_I2C::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
    if (lines > 1) {
        _displayfunction |= LCD_2LINE;
    }
    _numlines = lines;

    // for some 1 line displays you can select a 10 pixel high font
    if ((dotsize != 0) && (lines == 1)) {
        _displayfunction |= LCD_5x10DOTS;
    }

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40ms after power rises above 2.7V
    // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
    delay(50); 
  
    // Now we pull both RS and R/W low to begin commands
    expanderWrite(IO_REG_OUTPUT, _backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
    delay(1000);

    //put the LCD into 4 bit mode
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46
	
    // переход в 4-разрядный режим
    write4bits(0x03 << 4);
    delayMicroseconds(4500); // wait min 4.1ms
   
    // попытка 2
    write4bits(0x03 << 4);
    delayMicroseconds(4500); // wait min 4.1ms
   
    // попытка 3
    write4bits(0x03 << 4); 
    delayMicroseconds(150);
   
    // установка 4-разрядного режима
    write4bits(0x02 << 4); 


    // настройка отображения
    command(LCD_FUNCTIONSET | _displayfunction);  
	
    // включение дисплея без курсора
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    display();
	
    // очистка дисплея
    clear();
	
    // настройка направления текста
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
    // set the entry mode
    command(LCD_ENTRYMODESET | _displaymode);
	
    home();
}

/*-------- Методы высокого уровня --------*/

// очистка дисплея, перевод курсора в нулевую позицию
void RobotClass_LiquidCrystal_I2C::clear(){
    command(LCD_CLEARDISPLAY);
    delayMicroseconds(2000);
}

// перевод курсора в нулевую позицию
void RobotClass_LiquidCrystal_I2C::home(){
    command(LCD_RETURNHOME);
    delayMicroseconds(2000);
}

// перевод курсора в позицию col, row
void RobotClass_LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row){
    int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    if ( row > _numlines ) {
        row = _numlines-1;    // we count rows starting w/0
    }
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// включение/выключение дисплея
void RobotClass_LiquidCrystal_I2C::noDisplay() {
    _displaycontrol &= ~LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void RobotClass_LiquidCrystal_I2C::display() {
    _displaycontrol |= LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// включение/выключение подчерка под курсором
void RobotClass_LiquidCrystal_I2C::noCursor() {
    _displaycontrol &= ~LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void RobotClass_LiquidCrystal_I2C::cursor() {
    _displaycontrol |= LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// включение/выключение мигающего курсора
void RobotClass_LiquidCrystal_I2C::noBlink() {
    _displaycontrol &= ~LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void RobotClass_LiquidCrystal_I2C::blink() {
    _displaycontrol |= LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// перемотка дисплея без изменения памяти
void RobotClass_LiquidCrystal_I2C::scrollDisplayLeft(void) {
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void RobotClass_LiquidCrystal_I2C::scrollDisplayRight(void) {
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// направление текста слева направо
void RobotClass_LiquidCrystal_I2C::leftToRight(void) {
    _displaymode |= LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displaymode);
}

// направление текста справа налево
void RobotClass_LiquidCrystal_I2C::rightToLeft(void) {
    _displaymode &= ~LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displaymode);
}

// выравнивание текста справа
void RobotClass_LiquidCrystal_I2C::autoscroll(void) {
    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | _displaymode);
}

// выравнивание текста слева
void RobotClass_LiquidCrystal_I2C::noAutoscroll(void) {
    _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | _displaymode);
}

// Перезапись первых 8 CGRAM (символов)
void RobotClass_LiquidCrystal_I2C::createChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x7; // we only have 8 locations 0-7
    command(LCD_SETCGRAMADDR | (location << 3));
    for (int i=0; i<8; i++) {
        write(charmap[i]);
    }
}

// Включение/выключение подсветки
void RobotClass_LiquidCrystal_I2C::noBacklight(void) {
    _backlightval=LCD_NOBACKLIGHT;
    expanderWrite(IO_REG_OUTPUT, 0);
}

void RobotClass_LiquidCrystal_I2C::backlight(void) {
    _backlightval=LCD_BACKLIGHT;
    expanderWrite(IO_REG_OUTPUT, 0);
}

/*-------- Методы низкого уровня --------*/

inline void RobotClass_LiquidCrystal_I2C::command(uint8_t value) {
    send(value, 0);
}

inline size_t RobotClass_LiquidCrystal_I2C::write(uint8_t value) {
	send(value, Rs);
	return 1;
}

/*-------- Методы интерфейсов --------*/

void RobotClass_LiquidCrystal_I2C::send(uint8_t value, uint8_t mode) {
    uint8_t highnib = value & 0xf0;
    uint8_t lownib = (value << 4) & 0xf0;
    write4bits( highnib | mode );
    write4bits( lownib | mode ); 
}

void RobotClass_LiquidCrystal_I2C::write4bits(uint8_t value) {
    expanderWrite(IO_REG_OUTPUT, value);
    pulseEnable(value);
}

void RobotClass_LiquidCrystal_I2C::expanderWrite(uint8_t reg, uint8_t _data){                                        
    Wire.beginTransmission(_Addr);
    if(_io == IO_MODEL_PCA9534){
        Wire.write(reg);
    }
    Wire.write(_data | _backlightval);
    Wire.endTransmission();   
}

void RobotClass_LiquidCrystal_I2C::pulseEnable(uint8_t _data){
    expanderWrite(IO_REG_OUTPUT, _data | En);	// En high
    delayMicroseconds(1);		// enable pulse must be >450ns
	
    expanderWrite(IO_REG_OUTPUT, _data & ~En);	// En low
    delayMicroseconds(50);		// commands need > 37us to settle
}