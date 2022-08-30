#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define address  0x3F
#define columns  16
#define lines    2

#define PRES_LENGTH 12
#define GOV_LENGTH 10

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

Candidate pres[] = { {"Ciro Gomes", 12, 0}, {"Eymael", 27, 0}, {"Felipe D'Avila", 30, 0},
                     {"Jair Bolsonaro", 22, 0}, {"Lula", 13, 0}, {"Léo Pericles", 80, 0},
                     {"Pablo Marcal", 90, 0}, {"Roberto Jeff.", 14, 0}, {"Simone Tebet", 15, 0},
                     {"Sofia Manzano", 21, 0}, {"Soraya Thronicke", 44, 0}, {"Vera", 16, 0} };

Candidate gov[] = { {"Altino", 16, 0}, {"Antonio Jorge", 27, 0}, {"Carol Vigliar", 80, 0},
                    {"Edson Dorta", 29, 0}, {"Elvis Cezar", 12, 0}, {"Fernando Haddad", 13, 0},
                    {"Gabriel Colombo", 21, 0}, {"Rodrigo Garcia", 45, 0}, {"Tarcisio", 10, 0},
                    {"Vinicius Poit", 30, 0} };

LiquidCrystal_I2C lcd(address, columns, lines);

bool isNumber(char c)
{
    return c >= '0' && c <= '9';
}

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
    lcd.clear();
    
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
        lcd.setCursor(0, 0);
        lcd.print("Presidente");
        
        char c1 = '_';
        char c2 = '_';
        int pointer = 0;
        
        char key = '\0';
        
        while (pointer < 2)
        {
            lcd.setCursor(0, 1);
            lcd.print(c1);
            
            lcd.setCursor(1, 1);
            lcd.print(c2);
            
            key = keypad.getKey();
            
            if (!isNumber(key)) {
                key = '\0';
                continue;
            }
            
            if (key)
            {
                if (pointer == 0)
                {
                    c1 = key;
                }
                else if (pointer == 1)
                {
                    c2 = key;
                }
                
                pointer++;
            }
        }
        
        lcd.clear();
        
        lcd.setCursor(0, 1);
        lcd.print(c1);
        
        lcd.setCursor(1, 1);
        lcd.print(c2);
        
        char num[2] = {c1, c2};
        int number = atoi(num);
        int index = -1;
        
        for (int i = 0; i < PRES_LENGTH; i++)
        {
            if (pres[i].number == number)
            {
                index = i;
                break;
            }
        }
        
        String name = pres[index].name;
        
        if (index < 0)
        {
            name = "Voto nulo";
        }
        
        lcd.setCursor(0, 0);
        
        lcd.print(name);
        
        key = '\0';
        
        while (!key)
        {
            key = keypad.getKey();
        }
        
        if (key == '#')
        {
            if (index < 0)
            {
                state++;
                return;
            }
            
            pres[index].votes++;
            state++;
        }
        else
        {
            return;
        }
    }
    else if (state == 2)
    {
        lcd.setCursor(0, 0);
        lcd.print("Governador");
        
        char c1 = '_';
        char c2 = '_';
        int pointer = 0;
        
        char key = '\0';
        
        while (pointer < 2)
        {
            lcd.setCursor(0, 1);
            lcd.print(c1);
            
            lcd.setCursor(1, 1);
            lcd.print(c2);
            
            key = keypad.getKey();
            
            if (!isNumber(key)) {
                key = '\0';
                continue;
            }
            
            if (key)
            {
                if (pointer == 0)
                {
                    c1 = key;
                }
                else if (pointer == 1)
                {
                    c2 = key;
                }
                
                pointer++;
            }
        }
        
        lcd.clear();
        
        lcd.setCursor(0, 1);
        lcd.print(c1);
        
        lcd.setCursor(1, 1);
        lcd.print(c2);
        
        char num[2] = {c1, c2};
        int number = atoi(num);
        int index = -1;
        
        for (int i = 0; i < GOV_LENGTH; i++)
        {
            if (gov[i].number == number)
            {
                index = i;
                break;
            }
        }
        
        String name = gov[index].name;
        
        if (index < 0)
        {
            name = "Voto nulo";
        }
        
        lcd.setCursor(0, 0);
        lcd.print(name);
        
        key = '\0';
        
        while (!key)
        {
            key = keypad.getKey();
        }
        
        if (key == '#')
        {
            if (index < 0)
            {
                state++;
                return;
            }
            
            gov[index].votes++;
            state++;
        }
        else
        {
            return;
        }
    }
    else if (state == 3)
    {
        lcd.clear();
        
        lcd.setCursor(0, 0);
        lcd.print("Fim");
        
        lcd.setCursor(0, 1);
        lcd.print("Votou");
        
        delay(3000);
        
        state = 1;
    }
}
