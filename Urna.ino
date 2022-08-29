#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define address  0x3F
#define columns  16
#define lines    2

unsigned char pinsLines[] = { 6, 7, 8, 9 };
unsigned char pinsColumns[] = { 10, 11, 12, 13 };

char keys[4][4] = {{'1', '2', '3', 'A'},
                   {'4', '5', '6', 'B'},
                   {'7', '8', '9', 'C'},
                   {'*', '0', '#', 'D'}};

Keypad keypad = Keypad(makeKeymap(keys), pinsLines, pinsColumns, 4, 4);

int state = 0;

// 0 - start
// 1 - presidente
// 2 - governador
// 3 - fim votou
// 4 - mais votados

// -----------

struct Candidate
{
    String name;
    unsigned char number; // byte
    int votes;
};

Candidate pres[] = { {"Ciro Gomes", 12, 0}, {"Eymael", 27, 0}, {"Felipe D'Ávila", 30, 0},
                     {"Jair Bolsonaro", 22, 0}, {"Lula", 13, 0}, {"Léo Péricles", 80, 0},
                     {"Pablo Marçal", 90, 0}, {"Roberto Jeff.", 14, 0}, {"Simone Tebet", 15, 0},
                     {"Sofia Manzano", 21, 0}, {"Soraya Thronicke", 44, 0}, {"Vera", 16, 0} };

Candidate gov[] = { {"Altino", 16, 0}, {"Antonio Jorge", 27, 0}, {"Carol Vigliar", 80, 0},
                    {"Edson Dorta", 29, 0}, {"Elvis Cezar", 12, 0}, {"Fernando Haddad", 13, 0},
                    {"Gabriel Colombo", 21, 0}, {"Rodrigo Garcia", 45, 0}, {"Tarcísio", 10, 0},
                    {"Vinicius Poit", 30, 0} };

LiquidCrystal_I2C lcd(address, columns, lines);

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    
    Serial.begin(9600);
    Serial.println("Waiting...");
}

void loop()
{
    if (state == 0)
    {
        lcd.setCursor(0, 0);
        lcd.print("Urna 2022");
        
        lcd.setCursor(0, 1);
        lcd.print("Aperte uma tecla");
        
        char c = '\0';
        while (!c)
        {
            c = keypad.getKey();
        }
        
        state++;
    }
    else if (state == 1)
    {
        
    }
}
