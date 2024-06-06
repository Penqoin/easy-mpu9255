#include "easyMpu.hpp"
#include "Wire.h"

// define the mpu 
MPU mpu(0x68, Wire);

void setup() {
  Serial.begin(9600);
  
  // check if it is found
  if (!mpu.init()) {
      Serial.print("mpu 9255 not found");
      return;
  }
  
  mpu.set_motion_interrupt(10);

  pinMode(2,INPUT);

  pinMode(LED_BUILTIN,OUTPUT);
}


void loop() {
    if (digitalRead(2) == LOW) {
      Serial.println("I AM IN MOATION");
      mpu.clear_interrupt();
    }
}
