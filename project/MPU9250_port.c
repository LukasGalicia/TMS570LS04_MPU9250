/*
 * MPU9250_port.c
 *
 *  Created on: 6 mar 2026
 *      Author: lukas
 */

#include "MPU9250_port.h"

/* HAL SPI INTERNAL WRAPPERS */
static inline uint32_t _MPU9250_spiReceive(MPU9250_t *mpu, uint32_t blocksize, uint16 *srcbuff, uint16 *destbuff)
{
    return spiTransmitAndReceiveData(mpu->spi_reg, &(mpu->spi_config), blocksize, srcbuff, destbuff);
}

static inline uint32_t _MPU9250_spiTransmit(MPU9250_t *mpu, uint32_t blocksize, uint16_t *srcbuff)
{
    return spiTransmitData(mpu->spi_reg, &mpu->spi_config, blocksize, srcbuff);
}

/* DEVICE SPI TRANSACTION PRIMITIVES */
static void _MPU9250_Read(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, uint8_t *rxdata)
{
    uint32_t blocksize = (bytesize >> 1U) + 1U;

    uint16_t srcbuff[MAX_BLOCKSIZE] = {0x0U};
    uint16_t destbuff[MAX_BLOCKSIZE] = {0x0U};

    srcbuff[0] = ((0x80U | reg ) << 8U);
    _MPU9250_spiReceive(mpu, blocksize, srcbuff, destbuff);

    /*
     * ====== Buffer unpackaging ======
     * Hercules's HAL returns 16 bit words on SPI
     * RX.
     *
     * */
    rxdata[0] = (uint8_t) (destbuff[0] & 0x00FFU);      // First unpackaging: Remove dummy byte

    uint32_t i = 1;
    uint32_t k = 1;
    while (i < blocksize)
    {
        rxdata[k] = (uint8_t) (destbuff[i] >> 8U);
        // Parity byte count check:
        if((k + 1) < bytesize)
            rxdata[k + 1] = (uint8_t) (destbuff[i] & 0x00FFU);

        i++;
        k += 2;
    }

}

static void _MPU9250_Write(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, const uint8_t *txdata)
{
    uint32_t blocksize = ((bytesize >> 1U) + 1U);

    uint16_t srcbuff[MAX_BLOCKSIZE] = {0x0U};

    /*
     * ====== Buffer packaging ======
     * Hercules's HAL requires 16 bit words for SPI
     * transfer.
     *
     * */
    srcbuff[0] = (reg << 8U) | txdata[0];     // First packaging: Register address + MSByte

    uint32_t i = 1;
    uint32_t k = 1;
    while (i < blocksize)
    {
        uint16_t high = ((uint16_t) txdata[k]) << 8U;
        // Parity byte count check:
        uint16_t low = ((k + 1) < bytesize) ? ((uint16_t) txdata[k + 1]) : 0x00U;

        srcbuff[i] = high | low;

        i++;
        k += 2;
    }

    _MPU9250_spiTransmit(mpu, blocksize, srcbuff);

}

/* DEVICE REGISTER ACCESS HELPERS */
uint8_t MPU9250_ReadReg(MPU9250_t *mpu, uint16_t reg)
{
    uint8_t val;
    _MPU9250_Read(mpu, reg, 1U, &val);
    return val;
}

void MPU9250_WriteReg(MPU9250_t *mpu, uint16_t reg, uint8_t val)
{
    _MPU9250_Write(mpu, reg, 1U, &val);
}

void MPU9250_SetBits(MPU9250_t *mpu, uint16_t reg, uint8_t bits)
{
    uint8_t val = MPU9250_ReadReg(mpu, reg);
    val |= bits;
    MPU9250_WriteReg(mpu, reg, val);
}

void MPU9250_ClearBits(MPU9250_t *mpu, uint16_t reg, uint8_t bits)
{
    uint8_t val = MPU9250_ReadReg(mpu, reg);
    val &= ~bits;
    MPU9250_WriteReg(mpu, reg, val);
}

void MPU9250_UpdateBits(MPU9250_t *mpu, uint16_t reg, uint8_t bits, uint8_t value)
{
    uint8_t val = MPU9250_ReadReg(mpu, reg);
    val = (val & ~bits) | (bits & value);
    MPU9250_WriteReg(mpu, reg, val);
}

void MPU9250_ReadBurst(MPU9250_t *mpu, uint16_t base, uint32_t blocksize, uint8_t *data)
{
    _MPU9250_Read(mpu, base, blocksize, data);
}
