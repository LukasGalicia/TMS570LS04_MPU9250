/*
 * MPU9250.c
 *
 *  Created on: 26 feb 2026
 *      Author: lukas
 */

#ifndef PROJECT_MPU9250_C_
#define PROJECT_MPU9250_C_

#include "MPU9250.h"

#define MAX_BLOCKSIZE 10U

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
void MPU9250_Read(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, uint8_t *rxdata)
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

void MPU9250_Write(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, const uint8_t *txdata)
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


void MPU9250_Init(MPU9250_t* mpu, spiBASE_t *spi, const spiDAT1_t cfg)
{
    mpu->spi_reg = spi;         // SPI Register
    mpu->spi_config = cfg;      // SPI Driver Register Configuration

    mpu->dev_id = MPU9250_ReadReg(mpu, MPU9250_REG_WHO_AM_I);       // Get MPU9250 Device ID
}

#endif /* PROJECT_MPU9250_C_ */
