#include <Wire.h>

#define SLAVE_ADDRESS 0x12
#define SERIAL_BAUD 57600

void setup() {
 Wire.begin(SLAVE_ADDRESS);
 Wire.onReceive(receiveEvent);
 Serial.begin(SERIAL_BAUD);
 Serial.println("I2C slave.02 started\n");
 //Serial.println();

}

void loop() {}

void receiveEvent(int count){
  Serial.println("Receive Data:");
  while(Wire.available()){
    Serial.print((char)Wire.read());
  }
  Serial.println("\n");
}
