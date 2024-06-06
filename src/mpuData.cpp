#include "easyMpu.hpp"
#include "registers.hpp"

void MPU::read_all_sensors()
{
    uint8_t buffer[14];
    get_bytes(m_address, ACCEL_XOUT_H, 14, buffer);

    accel.raw_x = ((int16_t)((buffer[0] << 8) | buffer[1])) - accel.off_x;
    accel.raw_y = ((int16_t)((buffer[2] << 8) | buffer[3])) - accel.off_y;
    accel.raw_z = ((int16_t)((buffer[4] << 8) | buffer[5])) - accel.off_z;
    
    raw_temp = (int16_t)((buffer[6] << 8) | buffer[7]);

    gyro.raw_x = ((int16_t)((buffer[8] << 8) | buffer[9])) - gyro.off_x;
    gyro.raw_y = ((int16_t)((buffer[10] << 8) | buffer[11])) - gyro.off_y;
    gyro.raw_z = ((int16_t)((buffer[12] << 8) | buffer[13])) - gyro.off_z;
    

    uint8_t mag_buffer[8];
    get_bytes(m_ak8963_address, HXL, 8, mag_buffer);

    mag.raw_x = ((int16_t)((mag_buffer[1] << 8) | mag_buffer[0])) - mag.off_x;
    mag.raw_y = ((int16_t)((mag_buffer[3] << 8) | mag_buffer[2])) - mag.off_y;
    mag.raw_z = ((int16_t)((mag_buffer[5] << 8) | mag_buffer[4])) - mag.off_z;
    
     
    // Convert accelerometer readings
    int scale_factor;
    switch (this->accel.curr_force) 
    {
        case G_2:
            scale_factor = 16384;
            break;
        case G_4:
            scale_factor = 8192;
            break;
        case G_8:
            scale_factor = 4096;
            break;
        case G_16:
            scale_factor = 2048;
            break;
        default:
            scale_factor = 16384;
    }

    accel.x = (float)accel.raw_x / scale_factor; 
    accel.y = (float)accel.raw_y / scale_factor;
    accel.z = (float)accel.raw_z / scale_factor;
    
    // Convert GYRO readings
    float dps_factor;
    switch (this->gyro.curr_dps) 
    {
        case DPS250:
            dps_factor = 131.0f;
            break;
        case DPS500:
            dps_factor = 65.5f;
            break;
        case DPS1000:
            dps_factor = 32.8f;
            break;
        case DPS2000:
            dps_factor = 16.4f;
            break;
        default:
            dps_factor = 131.0f;
    }
    gyro.x = (float)(gyro.raw_x) / dps_factor;
    gyro.y = (float)(gyro.raw_y) / dps_factor;
    gyro.z = (float)(gyro.raw_z) / dps_factor;

    temp = ((raw_temp - this->room_temp_offset) / TEMP_SENSITIVITY) + 21;
}


void MPU::set_gyro_dps(gyro_scale scale) {
    uint8_t value = read(MPU_ADDRESS, GYRO_CONFIG);
    value &= ~0x18;  
    value |= scale;  
    write(MPU_ADDRESS, GYRO_CONFIG, value);
    this->gyro.curr_dps = scale;
}



void MPU::set_accel_g(accel_scale scale) {
    uint8_t value = read(MPU_ADDRESS, ACCEL_CONFIG);
    value &= ~0x18;  
    value |= scale;  
    write(MPU_ADDRESS, ACCEL_CONFIG, value);
    this->accel.curr_force = scale;
}


void MPU::auto_calibrate_accelerometer()
{
    // Perform a series of measurements to determine the offset values
    int16_t offset_x = 0, offset_y = 0, offset_z = 0;
    const int num_samples = 100;

    for (int i = 0; i < num_samples; ++i) {
        read_all_sensors();
        offset_x += accel.raw_x;
        offset_y += accel.raw_y;
        offset_z += accel.raw_z;
        delay(5);  // Delay to allow sensor to stabilize
    }

    // Calculate the average offsets
    offset_x /= num_samples;
    offset_y /= num_samples;
    offset_z /= num_samples;

    // Store the offsets for later use
    accel.off_x = offset_x;
    accel.off_y = offset_y;
    accel.off_z = offset_z;
}

void MPU::auto_calibrate_gyroscope()
{
    int16_t offset_x = 0, offset_y = 0, offset_z = 0;
    const int num_samples = 100;

    for (int i = 0; i < num_samples; ++i) {
        read_all_sensors();
        offset_x += gyro.raw_x;
        offset_y += gyro.raw_y;
        offset_z += gyro.raw_z;
        delay(5);  // Delay to allow sensor to stabilize
    }

    // Calculate the average offsets
    offset_x /= num_samples;
    offset_y /= num_samples;
    offset_z /= num_samples;

    // Store the offsets for later use
    gyro.off_x = offset_x;
    gyro.off_y = offset_y;
    gyro.off_z = offset_z;
}

void MPU::auto_calibrate_magnetometer()
{
    // Perform a series of measurements to determine the min and max values
    int16_t min_x = 32767, min_y = 32767, min_z = 32767;
    int16_t max_x = -32768, max_y = -32768, max_z = -32768;
    const int num_samples = 100;

    for (int i = 0; i < num_samples; ++i) {
        read_all_sensors(); // unecassary but i am lazy
        if (mag.raw_x < min_x) min_x = mag.raw_x;
        if (mag.raw_y < min_y) min_y = mag.raw_y;
        if (mag.raw_z < min_z) min_z = mag.raw_z;
        if (mag.raw_x > max_x) max_x = mag.raw_x;
        if (mag.raw_y > max_y) max_y = mag.raw_y;
        if (mag.raw_z > max_z) max_z = mag.raw_z;
        delay(5);  // Delay to allow sensor to stabilize
    }

    // Calculate the offsets and scale factors
    mag.off_x = (max_x + min_x) / 2;
    mag.off_y = (max_y + min_y) / 2;
    mag.off_z = (max_z + min_z) / 2;
    mag.scale_x = (max_x - min_x) / 2;
    mag.scale_y = (max_y - min_y) / 2;
    mag.scale_z = (max_z - min_z) / 2;
}

void MPU::set_room_temperature(int t)
{
    this->room_temp_offset = t;
}
