#ifndef ENUM_REGISTERS_HPP
#define ENUM_REGISTERS_HPP

enum device_registers
{
    /*
     *  MPU REGISTERS IN ORDER
     */

    // gyro axis tests
    SELF_TEST_X_GYRO = 0x00,
    SELF_TEST_Y_GYRO = 0x01,
    SELF_TEST_Z_GYRO = 0x02,
    
    // accel axis tests
    SELF_TEST_X_ACCEL = 0x0D,
    SELF_TEST_Y_ACCEL = 0x0E,
    SELF_TEST_Z_ACCEL = 0x0f,

    // gyro offsets
    XG_OFFSET_H = 0x13,
    YG_OFFSET_H = 0x15,
    ZG_OFFSET_H = 0x17,
    
    // sample rate divider
    SMPLRT_DIV = 0x19,
    
    // configs
    CONFIG = 0x1A,
    GYRO_CONFIG = 0x1B,
    ACCEL_CONFIG = 0x1C,
    ACCEL_CONFIG_2 = 0x1D,
    
    // low power accelerometer ODR control
    LP_ACCEL_ODR = 0x1E,

    // wake on motion
    WOM_THR = 0x1F,
    
    // enable fifo for data registers
    FIFO_EN = 0x23,

    // I2C
    I2C_MST_CTRL = 0x24,

    I2C_SLV0_ADDR = 0x25,
    I2C_SLV1_ADDR = 0x28,
    I2C_SLV2_ADDR = 0x2B,
    I2C_SLV3_ADDR = 0x2E,
    I2C_SLV4_ADDR = 0x31,

    I2C_SLV0_REG = 0x26,
    I2C_SLV1_REG = 0x29,
    I2C_SLV2_REG = 0x2C,
    I2C_SLV3_REG = 0x2F,
    I2C_SLV4_REG = 0x32,

    I2C_SLV0_CTRL = 0x27,
    I2C_SLV1_CTRL = 0x2A,
    I2C_SLV2_CTRL = 0x2D,
    I2C_SLV3_CTRL = 0x30,
    I2C_SLV4_CTRL = 0x34,

    I2C_SLV4_DO = 0x33,
    I2C_SLV4_DI = 0x35,

    I2C_MST_STATUS = 0x36,

    // INT 
    INT_PIN_CFG = 0x37,
    INT_ENABLE = 0x38,
    INT_STATUS = 0x3A,

    // data registers high values
    ACCEL_XOUT_H = 0x3B,
    ACCEL_YOUT_H = 0x3D,
    ACCEL_ZOUT_H = 0x3F,
    TEMP_OUT_H = 0x41,
    GYRO_XOUT_H = 0x43,
    GYRO_YOUT_H = 0x45,
    GYRO_ZYOU_H = 0x47,
    EXT_SENS_DATA = 0x49, 
    // I2C slaves 
    I2C_SLV0_DO = 0x63,
    I2C_SLV1_DO = 0x64,
    I2C_SLV2_DO = 0x65,
    I2C_SLV3_DO = 0x66,

    I2C_MST_DELAY_CTRL = 0x67,

    // settings
    SIGNAL_PATH_RESET = 0x68,
    MOT_DETECT_CTRL = 0x69,
    USER_CTRL = 0x6A,
    PWR_MGMT_1 = 0x6B,
    PWR_MGMT_2 = 0x6C,

    // FIFO STUFF
    FIFO_COUNTH = 0x72,
    FIFO_COUNTIL = 0x73,
    FOFO_R_W = 0x74,
    
    // identify
    WHO_AM_I = 0x75,
    
    /*
     * MAGNOMETER REGISTERS
     */

    // INFO
    WIA = 0x00,
    INFO = 0x01,
    ST1 = 0x02,

    // MEASURMENT DATA
    HXL = 0x03,
    HXH = 0x04,
    HYL = 0x05,
    HYH = 0x06,
    HZL = 0x07,
    HZH = 0x08,
    
    // status and controls
    ST2 = 0x09,
    CNTL1 = 0x0A,
    CNTL2 = 0x0B,

    // tests
    ASTC = 0x0C,
    TS1 = 0x0D,
    TS2 = 0x0E,
    
    // disable i2C 
    I2CDIS = 0x0F,
    
    // adjustment
    ASAX = 0x10,
    ASAY = 0x11,
    ASAZ = 0x12,

};

enum device_addresses {
    MAG_ADDRESS = 0x0C,
    MPU_ADDRESS = 0x68,
};


enum accel_scale {
    G_2 = 0x00,  // ±2g
    G_4 = 0x08,  // ±4g
    G_8 = 0x10,  // ±8g
    G_16 = 0x18  // ±16g
};


enum gyro_scale {
    DPS250 = 0x00,  // ±250dps
    DPS500 = 0x08,  // ±500dps
    DPS1000 = 0x10, // ±1000dps
    DPS2000 = 0x18  // ±2000dps
};

enum sensorbits {
    ACCEL_X = 0x20,
    ACCEL_Y = 0x10,
    ACCEL_Z = 0x08,
    ACCEL_ALL= 0x38,

    GYRO_X = 0x04,
    GYRO_Y = 0x02,
    GYRO_Z = 0x01,
    GYRO_ALL = 0x07,
};

#endif // !ENUM_REGISTERS_HPP
