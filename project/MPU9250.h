/*
 * MPU9250.h
 *
 *  Created on: 26 feb 2026
 *      Author: lukas
 */

#ifndef PROJECT_MPU9250_H_
#define PROJECT_MPU9250_H_

#include "sys_common.h"
#include "MPU9250_reg.h"
#include "spi.h"

struct MPU9250_device_config
{
    spiBASE_t *spi_reg;
    spiDAT1_t spi_config;
    uint8_t dev_id;
};
typedef struct MPU9250_device_config MPU9250_t;

/* DEVICE SPI TRANSACTION PRIMITIVES */
void MPU9250_Write(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, const uint8_t *txdata);
void MPU9250_Read(MPU9250_t *mpu, uint16_t reg, uint32_t bytesize, uint8_t *rxdata);

/* DEVICE REGISTER ACCESS HELPERS */
static inline uint8_t MPU9250_ReadReg(MPU9250_t *mpu, uint16_t reg)
{
    uint8_t val;
    MPU9250_Read(mpu, reg, 1U, &val);
    return val;
}

static inline void MPU9250_WriteReg(MPU9250_t *mpu, uint16_t reg, uint8_t val)
{
    MPU9250_Write(mpu, reg, 1U, &val);
}

static inline void MPU9250_SetBits(MPU9250_t *mpu, uint16_t reg, uint8_t bits)
{
    uint8_t val = MPU9250_ReadReg(mpu, reg);
    val |= bits;
    MPU9250_WriteReg(mpu, reg, val);
}

static inline void MPU9250_ClearBits(MPU9250_t *mpu, uint16_t reg, uint8_t bits)
{
    uint8_t val = MPU9250_ReadReg(mpu, reg);
    val &= ~bits;
    MPU9250_WriteReg(mpu, reg, val);
}

static inline void MPU9250_UpdateBits(MPU9250_t *mpu, uint16_t reg, uint8_t bits, uint8_t value)
{
    uint8_t val = MPU9250_ReadReg(mpu, reg);
    val = (val & ~bits) | (bits & value);
    MPU9250_WriteReg(mpu, reg, val);
}

/* APPLICATION PUBLIC DRIVER API FUNCTIONS */
void MPU9250_Init(MPU9250_t* mpu, spiBASE_t *spi, spiDAT1_t cfg);

#endif /* PROJECT_MPU9250_H_ */
