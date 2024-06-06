#include "easyMpu.hpp"
#include "registers.hpp"

void MPU::enable_sensor(sensorbits sen)
{
    uint8_t current = read(m_address, PWR_MGMT_2);
    current &= ~sen;  // Clear the bits corresponding to the sensors to enable them
    write(m_address, PWR_MGMT_2, current);
}

void MPU::disable_sensor(sensorbits sen) {
    uint8_t current = read(m_address, PWR_MGMT_2);
    current |= sen;  
    write(m_address, PWR_MGMT_2, current);
}

void MPU::set_motion_interrupt(uint8_t sensitivty)
{
    write(MPU_ADDRESS, WOM_THR, sensitivty);
    write(MPU_ADDRESS, MOT_DETECT_CTRL, (1 << 7));
    
    write_AND(MPU_ADDRESS, INT_PIN_CFG, ~(1 << 7));
    write_AND(MPU_ADDRESS, INT_PIN_CFG, ~(1 << 6));

    write_OR(MPU_ADDRESS, INT_PIN_CFG, ~(1 << 5));
    write_OR(MPU_ADDRESS, INT_ENABLE, (1 << 6));
}

void MPU::clear_interrupt()
{
    read(MPU_ADDRESS, INT_STATUS);
}
