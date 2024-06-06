#ifndef CLASS_MPU9255_H
#define CLASS_MPU9255_H

#define TEMP_SENSITIVITY 333.87f

#include "Arduino.h"
#include "Wire.h"
#include "registers.hpp"

struct accelometer
{
    int16_t raw_x, raw_y, raw_z; // raw values from sensors
    int16_t off_x = 0, off_y = 0, off_z = 0;
    float x, y, z; 

    accel_scale curr_force;
};

struct magnometer
{
    int16_t raw_x, raw_y, raw_z;
    int16_t off_x = 0, off_y = 0, off_z = 0;
    int16_t scale_x, scale_y, scale_z;

    float x, y, z;
};

struct gyroscope
{
    int16_t raw_x, raw_y, raw_z;
    int16_t off_x = 0, off_y = 0, off_z = 0;
    float x, y, z;

    gyro_scale curr_dps;
};


struct i2c_settings
{
    uint32_t rate = 400000;
};

class MPU 
{
public:
    /*
     * DATA 
     */
    accelometer accel;
    gyroscope gyro;  
    magnometer mag;

    int16_t raw_temp;
    int16_t temp;

public:
    /*
     *  CONSTRUCTORS
     */
    MPU(uint8_t address, TwoWire& i2c);
    
    /*
     *  INIT
     */
    bool init();

    void set_motion_interrupt(uint8_t sensitivity);
    void clear_interrupt();

    /*
     * DATA fetching functions
     */
    void read_all_sensors(); 

    void set_gyro_dps(gyro_scale scl);
    void set_accel_g(accel_scale scl);
    void set_room_temperature(int t);

    void disable_sensor(sensorbits sens);
    void enable_sensor(sensorbits sens);
    
    void auto_calibrate_accelerometer();
    void auto_calibrate_gyroscope();
    void auto_calibrate_magnetometer();
    
private:
    uint8_t m_address;
    TwoWire* m_i2c;
    const i2c_settings m_settings;

    uint8_t m_ak8963_address = 0x0C;
    uint16_t room_temp_offset = 21;

private:
    /*
     * I2C communication
     */
    void write(uint8_t addr, device_registers reg, uint8_t data);
    void write_OR(uint8_t addr, device_registers reg, uint8_t data);
    void write_AND(uint8_t addr, device_registers reg, uint8_t data);

    uint8_t read(uint8_t addr, device_registers reg);
    void get_bytes(uint8_t addr, device_registers reg, uint8_t bytes, uint8_t* buffer);

};

#endif // !CLASS_MPU9255_H
