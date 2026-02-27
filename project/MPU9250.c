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

void MPU9250Read(MPU9250_t *mpu, uint32_t rx_byte_size, uint16_t mpu_reg, uint16_t *destbuff)
{
    uint32_t blocksize = (rx_byte_size >> 1U) + 1U;

    uint16_t srcbuff[MAX_BLOCKSIZE] = {0x0U};

    srcbuff[0] = ((0x80U | mpu_reg ) << 8U);
    spiTransmitAndReceiveData(mpu->spi_reg, &(mpu->spi_config), blocksize, srcbuff, destbuff);

}

void MPU9250Write(MPU9250_t *mpu, uint32_t tx_byte_size, uint16_t mpu_reg, uint16_t *srcbuff)
{
    uint32_t blocksize = ((tx_byte_size >> 1U) + 1U);

    srcbuff[0] = (mpu_reg << 8U) | (srcbuff[0] & 0x00FFU);
    spiTransmitData(mpu->spi_reg, &(mpu->spi_config), blocksize, srcbuff);

}

void MPU9250Init(MPU9250_t* mpu, spiBASE_t *spi, const spiDAT1_t cfg)
{
    mpu->spi_reg = spi;         // SPI Register
    mpu->spi_config = cfg;      // SPI Driver Register Configuration
}

#endif /* PROJECT_MPU9250_C_ */
