#include<MPU6050.h>
#include<Wire.h>
#include<math.h>
#include<LiquidCrystal_I2C.h>
#define button 13
MPU6050 accelgyro;
int16_t ax, ay, az, gx, gy, gz;
int angle_x, angle_y, angle_z;
int angle_x_last, angle_y_last, angle_z_last;
bool state;
long counter = 0;
long result;
long last=0;

LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  accelgyro.initialize();
  lcd.init();
  lcd.backlight();
  pinMode(button, INPUT_PULLUP);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(0);
}




void loop() {
  if(!digitalRead(button))
  {
    counter = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(0);
  }
  
  // put your main code here, to run repeatedly:
 accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  result = pow((pow(ax, 2) + pow(ay, 2) + pow(az, 2)), 0.5);
    //Serial.println(result);
    //Serial.println(millis()- last);
  if(result > 1.5 * 16384  && (millis()-last) > 500){
    counter ++;
    Serial.print(counter);
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print(counter);
    last = millis();
  }
  
  

}
