#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define address  0x3F
#define columns  16
#define lines    2

#define MAX_NAME 16

int pinsLines[] = { 6, 7, 8, 9 };
int pinsColumns[] = { 10, 11, 12, 13 };

char keys[4][4] = {{'1', '2', '3', 'A'},
                   {'4', '5', '6', 'B'},
                   {'7', '8', '9', 'C'},
                   {'*', '0', '#', 'D'}};

// -----------

struct Candidate
{
    char name[MAX_NAME]; // string
    unsigned char number; // byte
};
/*
string candPres[] = { "Ciro Gomes", "Eymael", "Felipe D'Ávila",
                      "Jair Bolsonaro", "Lula", "Léo Péricles",
                      "Pablo Marçal", "Roberto Jeff.", "Simone Tebet",
                      "Sofia Manzano", "Soraya Thronicke", "Vera" };
*/
Candidate pres[] = { {"Ciro Gomes", 12}, {"Eymael", 27}, {"Felipe D'Ávila", 30},
                     {"Jair Bolsonaro", 22}, {"Lula", 13}, {"Léo Péricles", 80},
                     {"Pablo Marçal", 90}, {"Roberto Jeff.", 14}, {"Simone Tebet", 15},
                     {"Sofia Manzano", 21}, {"Soraya Thronicke", 44}, {"Vera", 16} };

LiquidCrystal_I2C lcd(address, columns, lines);

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    
    for (int i = 0; i < 4; i++)
    {
        pinMode(pinsLines[i], OUTPUT);
        digitalWrite(pinsLines[i], HIGH);
    }
    
    for (int i = 0; i < 4; i++)
    {
        pinMode(pinsColumns[i], INPUT_PULLUP);
    }
    
    //Serial.begin(9600);
    //Serial.println("Waiting...");
}

void loop()
{
    for (int l = 0; l < 4; l++)
    {
        digitalWrite(pinsLines[l], LOW);
        
        for (int c = 0; c < 4; c++)
        {
            if (digitalRead(pinsColumns[c]) == LOW)
            {
                //Serial.print("Tecla: ");
                //Serial.println(keys[l][c]);
                
                while (digitalRead(pinsColumns[c]) == LOW) {}
            }
        }
        
        digitalWrite(pinsLines[l], HIGH);
    }
    
    delay(10);
}
