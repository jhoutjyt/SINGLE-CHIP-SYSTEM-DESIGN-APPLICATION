#include <Wire.h>                                                          
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
}

void loop()
{
    for(int i = 0; i < 11; i++)
    {   
        char key = keypad.getKey();
        lcd.clear();
        lcd.setCursor(i,0);
        lcd.print("NCKUEE");
        delay(500);
    }   
}

