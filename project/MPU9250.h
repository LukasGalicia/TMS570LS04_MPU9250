/*
 * MPU9250.h
 *
 *  Created on: 26 feb 2026
 *      Author: lukas
 */

#ifndef PROJECT_MPU9250_H_
#define PROJECT_MPU9250_H_

#include "sys_common.h"
#include "spi.h"

struct mod_conf_MPU9250
{
    spiBASE_t *spi_reg;
    spiDAT1_t spi_config;
    uint8_t device_id;
};
typedef struct mod_conf_MPU9250 MPU9250_t;

static inline uint32_t MPU9250_spiRead(MPU9250_t *mpu, uint32_t blocksize, uint16 *srcbuff, uint16 *destbuff)
{
    return spiTransmitAndReceiveData(mpu->spi_reg, &(mpu->spi_config), blocksize, srcbuff, destbuff);
}

static inline uint32_t MPU9250_spiWrite(MPU9250_t *mpu, uint32_t blocksize, uint16_t *srcbuff)
{
    return spiTransmitData(mpu->spi_reg, &mpu->spi_config, blocksize, srcbuff);
}

void MPU9250Write(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, const uint8_t *txdata);
void MPU9250Read(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, uint8_t *rxdata);
void MPU9250Init(MPU9250_t* mpu, spiBASE_t *spi, spiDAT1_t cfg);

#endif /* PROJECT_MPU9250_H_ */
