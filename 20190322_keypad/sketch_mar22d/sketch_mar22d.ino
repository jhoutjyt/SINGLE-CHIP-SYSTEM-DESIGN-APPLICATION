#include"Password.h"
#include"Keypad.h"

Password password = Password("1234");
byte passwordlength;
int SEG_COM[4] = {10,11,12,13};
int SEG_Data[14][8] = {{1,1,1,1,1,1,0,0},//0
                       {0,1,1,0,0,0,0,0},//1
                       {1,1,0,1,1,0,1,0},//2
                       {1,1,1,1,0,0,1,0},//3
                       {0,1,1,0,0,1,1,0},//4
                       {1,0,1,1,0,1,1,0},//5
                       {1,0,1,1,1,1,1,0},//6
                       {1,1,1,0,0,0,0,0},//7
                       {1,1,1,1,1,1,1,0},//8
                       {1,1,1,0,0,1,1,0},//9
                       {0,0,1,1,1,0,1,0},//o
                       {0,1,1,1,1,0,1,0},//d
                       {1,1,1,0,1,1,1,0},//A
                       {0,0,1,1,1,1,1,0}//b
};
char key[4][4]={
   {'1','2','3','A'},
   {'4','5','6','B'},
   {'7','8','9','C'},
   {'*','0','#','D'}
};

int number = 0;
int disp[4] = {0,0,0,0};
long time1;
int state = 1;
void Number_Transfer (int Num) // 數值轉換為陣列模式
{
 disp[3] = Num / 1000;
 disp[2] = (Num % 1000) / 100;
 disp[1] = (Num % 100) /10;
 disp[0] = Num % 10;
  
}
void SEG_Drive (int Number)
{
  
  for( int i = 2; i<= 9 ; i++)
  {
    digitalWrite(i, SEG_Data[Number][i-2]);
  }
}

byte colPin[4] = {0,1,A5,A4};
byte rowPin[4] = {A0,A1,A2,A3};

Keypad keypad = Keypad(makeKeymap(key), rowPin, colPin, 4, 4);

void KeyNumber(char key){
  password.append(key);
  Serial.print(key);
  
}
void TrueOrFalse(){
  if(password.evaluate()){
    Serial.println("  輸入正確");
    password.reset();
    disp[0] = 9;
    disp[1] = 10;
    disp[2] = 10;
    disp[3] = 11;
    for(int i=0; i <=3; i++)
    {
      Serial.println(disp[i]);    
      digitalWrite(SEG_COM[i], LOW);    
      SEG_Drive(disp[i]);
      delay(5);
      digitalWrite(SEG_COM[i], HIGH);    
    }
    delay(1000);
  }
  else{
    Serial.println("  輸入錯誤");
    password.reset();
    disp[0] = 0;
    disp[1] = 13;
    disp[2] = 12;
    disp[3] = 11;
    for(int i=0; i <=3; i++)
    {
      Serial.println(disp[i]);
      if((i == 3 && disp[i] ==0) ||
          (disp[3] ==0 && i == 2 && disp[i] ==0) ||
           (disp[3] ==0 && i == 1 && disp[2] ==0 && disp[i] ==0)){
           }
      else{
      digitalWrite(SEG_COM[i], LOW);
      }
      SEG_Drive(disp[i]);
      delay(5);
      digitalWrite(SEG_COM[i], HIGH);    
    }
    delay(1000);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("請輸入密碼");
  for(int i=2;i<=13;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
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
  number = password.target;
  Number_Transfer(number);
  
  for(int i=0; i <=3; i++)
  {
    Serial.println(disp[i]);
    if((i == 3 && disp[i] ==0) ||
        (disp[3] ==0 && i == 2 && disp[i] ==0) ||
         (disp[3] ==0 && i == 1 && disp[2] ==0 && disp[i] ==0)){
         }
    else{
    digitalWrite(SEG_COM[i], LOW);
    }
    SEG_Drive(disp[i]);
    delay(5);
    digitalWrite(SEG_COM[i], HIGH);    
  }
  
}
