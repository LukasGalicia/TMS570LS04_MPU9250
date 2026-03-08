/*
 * MPU9250_port.h
 *
 *  Created on: 6 mar 2026
 *      Author: lukas
 */

#ifndef PROJECT_MPU9250_PORT_H_
#define PROJECT_MPU9250_PORT_H_

#include "sys_common.h"
#include "spi.h"

#define MAX_BLOCKSIZE 14U

struct MPU9250_device_config
{
    spiBASE_t *spi_reg;
    spiDAT1_t spi_config;
    uint8_t dev_id;
    float accel_scale;
    float gyro_scale;
};
typedef struct MPU9250_device_config MPU9250_t;

/* DEVICE REGISTER ACCESS HELPERS */
uint8_t MPU9250_ReadReg(MPU9250_t *mpu, uint16_t reg);
void MPU9250_WriteReg(MPU9250_t *mpu, uint16_t reg, uint8_t val);
void MPU9250_SetBits(MPU9250_t *mpu, uint16_t reg, uint8_t bits);
void MPU9250_ClearBits(MPU9250_t *mpu, uint16_t reg, uint8_t bits);
void MPU9250_UpdateBits(MPU9250_t *mpu, uint16_t reg, uint8_t bits, uint8_t value);
void MPU9250_ReadBurst(MPU9250_t *mpu, uint16_t base, uint32_t blocksize, uint8_t *data);

#endif /* PROJECT_MPU9250_PORT_H_ */
