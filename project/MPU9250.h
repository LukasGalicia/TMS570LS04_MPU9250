/*
 * MPU9250.h
 *
 *  Created on: 26 feb 2026
 *      Author: lukas
 */

#ifndef PROJECT_MPU9250_H_
#define PROJECT_MPU9250_H_

#include "MPU9250_reg.h"
#include "MPU9250_port.h"

#define MPU9250_ACCEL_SCALE_2G      16384.0f
#define MPU9250_ACCEL_SCALE_4G      8192.0f
#define MPU9250_ACCEL_SCALE_8G      4096.0f
#define MPU9250_ACCEL_SCALE_16G     2048.0f

#define MPU9250_GYRO_SCALE_250DPS       131.00f
#define MPU9250_GYRO_SCALE_500DPS        65.50f
#define MPU9250_GYRO_SCALE_1000DPS       32.80f
#define MPU9250_GYRO_SCALE_2000DPS       16.40f

static inline float MPU9250_GetAccel_G(int16_t raw_data, MPU9250_t *mpu)
{
    return (float)raw_data / mpu->accel_scale;
}

static inline float MPU9250_GetGyro_DPS(int16_t raw_data, MPU9250_t *mpu)
{
    return (float)raw_data / mpu->gyro_scale;
}

struct MPU9250_IMU_sensor_data {
    int16_t accel_x, accel_y, accel_z;
    int16_t temp;
    int16_t gyro_x,  gyro_y,  gyro_z;
};
typedef struct MPU9250_IMU_sensor_data MPU9250Data_t;

/* APPLICATION PUBLIC DRIVER API FUNCTIONS */
void MPU9250_Init(MPU9250_t* mpu, spiBASE_t *spi, const spiDAT1_t cfg);
void MPU9250_Reset(MPU9250_t *mpu);
void MPU9250_DisableI2C(MPU9250_t *mpu);
void MPU9250_ConfigClk(MPU9250_t *mpu, MPU9250_ClkSel clk);
void MPU9250_ConfigGyro(MPU9250_t *mpu, MPU9250_GyroRange fs_sel);
void MPU9250_ConfigAccel(MPU9250_t *mpu, MPU9250_AccelRange fs_sel);
void MPU9250_ConfigDLPF(MPU9250_t *mpu, MPU9250_DLPF_BW bw);
void MPU9250_ReadAll(MPU9250_t *mpu, MPU9250Data_t *raw);
void MPU9250_ReadGyro(MPU9250_t *mpu, MPU9250Data_t *raw);
void MPU9250_ReadAccel(MPU9250_t *mpu, MPU9250Data_t *raw);
int16_t MPU9250_ReadTemp(MPU9250_t *mpu);

#endif /* PROJECT_MPU9250_H_ */
