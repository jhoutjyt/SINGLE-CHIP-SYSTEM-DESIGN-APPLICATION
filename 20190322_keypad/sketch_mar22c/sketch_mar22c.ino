#include"Password.h"
#include"Keypad.h"


Password password = Password("1234");
byte passwordlength;
bool state = 0;
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
bool TrueOrFalse(){
  if(password.evaluate()){
    Serial.println("  輸入正確");
    password.reset();
    return 1;
  }
  else{
    Serial.println("  輸入錯誤");
    password.reset();
    return 0;
  }  
}

void Back(){
  password.reset();
  Serial.println("請重新輸入密碼");
}

void ChangePs(bool state){
  if(state){
     Serial.println("請設定新的密碼");
     char key = keypad.getKey();
     char newpsw[10] = {};
     int index =0;
     while(key != 'A'){       
       if(key != NO_KEY){
          delay(100);
          Serial.print(key);
          newpsw[index] = key; 
          index +=1;                     
        }
        key = keypad.getKey();
     }
     Serial.println("請輸入密碼");
     newpsw[index] = '\0' ;
     //Serial.println(newpsw);
     password.set(newpsw);
    // Serial.println(password.target);
     newpsw[0] = '\0';
   }  
   else
   {
    Serial.println("權限不足");
   }
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
      case 'A' : state = TrueOrFalse(); break;
      case 'B' : Back(); break;
      case 'C' : ChangePs(state); break;
      default : KeyNumber(key);
    }
    
  }
  
}
