#include"Password.h"
#include"Keypad.h"


Password password = Password("1234");
byte passwordlength;

char key[4][4]={
   {'1','2','3','A'},
   {'4','5','6','B'},
   {'7','8','9','C'},
   {'*','0','#','D'}
};
byte colPin[4] = {2,3,4,5};
byte rowPin[4] = {A0,A1,A2,A3};

Keypad keypad = Keypad(makeKeymap(key), rowPin, colPin, 4, 4);

void KeyNumber(char key){
  password.append(key);
  Serial.print(key);
  
}
void TrueOrFalse(){
  if(password.evaluate()) Serial.println("  輸入正確");
  else Serial.println("  輸入錯誤");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("請輸入密碼");
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if(key != NO_KEY){
    delay(100);
    switch(key){
      case 'A' : TrueOrFalse(); break;
      default : KeyNumber(key);
    }
    
  }
  
}
