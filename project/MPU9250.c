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

void MPU9250Read(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, uint8_t *rxdata)
{
    uint32_t blocksize = (bytesize >> 1U) + 1U;

    uint16_t srcbuff[MAX_BLOCKSIZE] = {0x0U};
    uint16_t destbuff[MAX_BLOCKSIZE] = {0x0U};

    srcbuff[0] = ((0x80U | reg ) << 8U);
    MPU9250_spiRead(mpu, blocksize, srcbuff, destbuff);

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

void MPU9250Write(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, const uint8_t *txdata)
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

    MPU9250_spiWrite(mpu, blocksize, srcbuff);

}

void MPU9250Init(MPU9250_t* mpu, spiBASE_t *spi, const spiDAT1_t cfg)
{
    mpu->spi_reg = spi;         // SPI Register
    mpu->spi_config = cfg;      // SPI Driver Register Configuration
}

#endif /* PROJECT_MPU9250_C_ */
