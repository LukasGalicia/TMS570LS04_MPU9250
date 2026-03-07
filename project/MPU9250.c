/*
 * MPU9250.c
 *
 *  Created on: 26 feb 2026
 *      Author: lukas
 */

#ifndef PROJECT_MPU9250_C_
#define PROJECT_MPU9250_C_

#include "MPU9250.h"

void MPU9250_Init(MPU9250_t* mpu, spiBASE_t *spi, const spiDAT1_t cfg)
{
    mpu->spi_reg = spi;         // SPI Register
    mpu->spi_config = cfg;      // SPI Driver Register Configuration

    mpu->dev_id = MPU9250_ReadReg(mpu, MPU9250_REG_WHO_AM_I);       // Get MPU9250 Device ID
}

void MPU9250_Reset(MPU9250_t *mpu)
{
    MPU9250_SetBits(mpu, MPU9250_REG_PWR_MGMT_1, MPU9250_MASK_PWR1_H_RESET);
}

void MPU9250_DisableI2C(MPU9250_t *mpu)
{
    MPU9250_SetBits(mpu, MPU9250_REG_USER_CTRL, MPU9250_MASK_USR_CTL_I2C_IF_DIS);
}

void MPU9250_ConfigGyro(MPU9250_t *mpu, MPU9250_GyroRange fs_sel)
{
    MPU9250_UpdateBits(mpu, MPU9250_REG_GYRO_CONFIG, MPU9250_MASK_GYRO_CFG_GYRO_FS_SEL, fs_sel);
}

void MPU9250_ConfigAccel(MPU9250_t *mpu, MPU9250_AccelRange fs_sel)
{
    MPU9250_UpdateBits(mpu, MPU9250_REG_ACCEL_CONFIG_1, MPU9250_MASK_ACC_CFG_1_ACCEL_FS_SEL, fs_sel);
}

#endif /* PROJECT_MPU9250_C_ */
