#include <Wire.h>                                                          
#include "LiquidCrystal_I2C.h"
#include "Keypad.h"
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_I2C lcd(0x27,16,2);

int n1, n2, ans;
int op = -1;
char number1[5] = {'0','0','0','0','0'};

char anser[5]   = {'0','0','0','0','0'};
int index = 0;
void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
}
int tmp = 0;


void loop()
{
  
    char key = keypad.getKey();
    if(key != NO_KEY){

    switch(key){

    case 'A':
          op = 0;
          lcd.print("+");
          delay(500);
          break;
    case 'B':
          op = 1;
          lcd.print("-");
          delay(500);
          break;
    case 'C':
          op = 2;
          lcd.print("*");
          delay(500);
          break;
    case 'D':
          op = 3;
          lcd.print("/");
          delay(500);
          break;
    case '*':
       lcd.clear();
       lcd.setCursor(0,0);
       op = -1;
       n1 = 0;
       n2 = 0;
       break;
    case '#':

          switch (op){
            case 0:
                ans = n1 + n2;
                lcd.setCursor(0,1);
                lcd.print("=");
                lcd.print(ans);
                delay(500);
                break;
            case 1:
                ans = n1 - n2;
                lcd.setCursor(0,1);
                lcd.print("=");
                lcd.print(ans);
                delay(500);
                break;
            case 2:
                ans = n1 * n2;
                lcd.setCursor(0,1);
                lcd.print("=");
                lcd.print(ans);
                delay(500);
                break;
            case 3:
                ans = n1 / n2;
                lcd.setCursor(0,1);
                lcd.print("=");
                lcd.print(ans);
                delay(500);
                break;
          }
          break;
    default:
    if(op < 0)
      n1 = n1 * 10 + (key - 48);
    else
      n2 = n2 * 10 + (key - 48);
      lcd.print(key);
      delay(500);
       
      break;
    }
    }
}
    
