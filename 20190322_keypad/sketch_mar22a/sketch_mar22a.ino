#include  <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX 、 TX
int led = 12;
char data;
bool state = LOW;
 
void setup()
 {
  Serial.begin(9600);
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
  pinMode (led,OUTPUT);
  digitalWrite(led,state);
 }
void loop()
 {
// Keep reading from HC-05 and send to Arduino Serial Monitor
if (BTSerial.available()){
  data = BTSerial.read();
  Serial.write(data);
  if(data == '1')
    state = HIGH;
  else if(data == '0')
    state = LOW;
  digitalWrite(led,state);
  }
  
// Keep reading from Arduino Serial Monitor and send to HC-05
if (Serial.available())
   BTSerial.write(Serial.read());
   }
