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
  
  // the default room temperature is set to 21 C
  // but if you are in a hotter environment you need
  // to set this value
  mpu.set_room_temperature(0);

  // optional but do give better reaulst
  // this might also take some time
  
  // mpu.auto_calibrate_accelerometer();
  // mpu.auto_calibrate_gyroscope();
  // mpu.auto_calibrate_magnetometer();
}


void loop() {
    // Read all the sensors
    mpu.read_all_sensors();

    // Display sensor readings
    Serial.println("Accelerometer (m/s^2):");
    Serial.print("X: "); Serial.print(mpu.accel.x, 4); Serial.print("\t");
    Serial.print("Y: "); Serial.print(mpu.accel.y, 4); Serial.print("\t");
    Serial.print("Z: "); Serial.println(mpu.accel.z, 4);

    Serial.println("Gyroscope (deg/s):");
    Serial.print("X: "); Serial.print(mpu.gyro.x, 4); Serial.print("\t");
    Serial.print("Y: "); Serial.print(mpu.gyro.y, 4); Serial.print("\t");
    Serial.print("Z: "); Serial.println(mpu.gyro.z, 4);

    Serial.println("Magnetometer (uT):");
    Serial.print("X: "); Serial.print(mpu.mag.x, 4); Serial.print("\t");
    Serial.print("Y: "); Serial.print(mpu.mag.y, 4); Serial.print("\t");
    Serial.print("Z: "); Serial.println(mpu.mag.z, 4);

    Serial.print("Temperature (°C): ");
    Serial.println(mpu.temp);
    
    // Add delay if needed to control the output rate
    delay(1000);
}
