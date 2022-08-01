/*
 * LiquidCrystal_I2C library override for cyrillic LCD
 * Written by Oleg Evsegneev for RobotClass (2022).
 * e-mail: oleg.evsegneev@gmail.com
 */
#include "RobotClass_LiquidCrystal_I2C.h"

// overrides LiquidCrystal converter
RobotClass_LiquidCrystal_I2C::RobotClass_LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t cp): LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows){
  codepage = cp;
}

// converts utf-8 string to cp1251
// author V. Kirievskiy - vek2006_73@@mail.ru
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

// overrides print function from core Print module
// prints String with on-fly conversion to LCD codepage
size_t RobotClass_LiquidCrystal_I2C::print( const String &s ){
  if( codepage == CP_UTF8 ){
    return LiquidCrystal_I2C::print( convertCyr( utf8rus( s )));
  } else {
    return LiquidCrystal_I2C::print( convertCyr( s ));
  }
}

// converts cp1251 String to LCD codepage String
String RobotClass_LiquidCrystal_I2C::convertCyr( const String &s ){
  String target = s;
  for( int idx = 0; idx<s.length(); idx++ ){
    target[idx] = getCharCyr( s[idx] );
  }
  return target;
}

// converts cp1251 Char to LCD codepage Char
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