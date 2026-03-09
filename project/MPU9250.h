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

struct MPU9250_IMU_sensor_data {
    int16_t accel_x, accel_y, accel_z;
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
void MPU9250_ReadAccel(MPU9250_t *mpu, MPU9250Data_t *data);

#endif /* PROJECT_MPU9250_H_ */
