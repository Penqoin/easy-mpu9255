#include "easyMpu.hpp"
#include "registers.hpp"


MPU::MPU(uint8_t address, TwoWire& bus) : m_address(address)
{
    m_i2c = &bus;
}

bool MPU::init()
{
     m_i2c->begin();
    m_i2c->setClock(m_settings.rate);
   
    write(m_address, PWR_MGMT_1, 0x01); // auto select best clock speed
    write(m_address, USER_CTRL, 0x20); // enable i2c master
    write(m_address, I2C_MST_CTRL, 0x0D); // set 400 kHz i2c bus speed

    write(m_ak8963_address, CNTL1, 0x00); // Power down AK8963
    write(m_address, PWR_MGMT_1, 0x00); // reset mpu-9255
    delay(1); // wait for mpu-9255 to wake up
    write(m_ak8963_address, CNTL2, 0x01); // reset AK8963 
    
    write(m_address, PWR_MGMT_1, 0x01); // auto select best clock speed

    // check if mpu-9255 is detected 
    if (read(m_address, WHO_AM_I) != 0x71 && read(m_address, WHO_AM_I) != 0x73)
        return -1;
    
    write(m_address, PWR_MGMT_2, 0x00); // enable accel and gyro
    
    write_AND(m_address, ACCEL_CONFIG, ~(0x0C)); // sets accel scale to 2G as default
    

    write_AND(m_address, GYRO_CONFIG, ~(0x0C)); // sets gyro to 250 DPS as default
    
    
    write_OR(m_address, ACCEL_CONFIG_2, 0x01); // set bandwidth 184Hz
    write_OR(m_address, CONFIG, 0x01); // set gyro bandwidth 184Hz

    write(m_address, SMPLRT_DIV, 0x00); // set sample rate divide to 0
    write(m_address, USER_CTRL, 0x20); // enable i2c master
    write(m_address, I2C_MST_CTRL, 0x0D); // set 400 kHz i2c bus speed
 
    if (read(m_ak8963_address, WIA) != 0x48)
        return -1;
    
    write(m_ak8963_address, CNTL1, 0x00); // power it down
    delay(100); // wait for ak8963

    write(m_ak8963_address, CNTL1, 0x0F); // give FUSE ROM access
    delay(100); // wait for it

    write(m_ak8963_address, CNTL1, 0x00); // power it down
    delay(100); // wait for ak8963

    write(m_address, PWR_MGMT_1, 0x01); // auto select best clock speed

    write(m_ak8963_address, CNTL1, 0x06);
    delay(100);

    this->gyro.curr_dps = DPS250;
    this->accel.curr_force = G_2;

    return 1;}
