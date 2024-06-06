#include "easyMpu.hpp"
#include "registers.hpp"

/*
 * I2C communication functions
 */

void MPU::write(uint8_t addr, device_registers reg, uint8_t data)
{
    m_i2c->beginTransmission(addr);
    m_i2c->write(reg);
    m_i2c->write(data);
    m_i2c->endTransmission();
}

void MPU::write_OR(uint8_t addr, device_registers reg, uint8_t data)
{
    write(addr, reg, read(addr, reg) | data);
}

void MPU::write_AND(uint8_t addr, device_registers reg, uint8_t data)
{
    write(addr, reg, read(addr, reg) & data);
}

uint8_t MPU::read(uint8_t addr, device_registers reg)
{
    m_i2c->beginTransmission(addr);
    m_i2c->write(reg);
    m_i2c->endTransmission();
    m_i2c->requestFrom(addr, (uint8_t)1);
    return m_i2c->read();
}

void MPU::get_bytes(uint8_t addr, device_registers reg, uint8_t bytes, uint8_t* buffer)
{
    m_i2c->beginTransmission(addr);
    m_i2c->write(reg);
    m_i2c->endTransmission(false);
    m_i2c->requestFrom(addr, bytes);
    for (uint8_t i = 0; i < bytes; i++)
    {
        if (m_i2c->available())
        {
            buffer[i] = m_i2c->read();
        }
    }
}
