#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define address  0x3F
#define columns  16
#define lines    2

int pinsLines[] = { 6, 7, 8, 9 };
int pinsColumns[] = { 10, 11, 12, 13 };

char keys[4][4] = {{'1', '2', '3', 'A'}
                   {'4', '5', '6', 'B'}
                   {'7', '8', '9', 'C'}
                   {'*', '0', '#', 'D'}};

LiquidCrystal_I2C lcd(address, columns, lines);

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void loop() {
    
}
