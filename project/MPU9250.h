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

/* APPLICATION PUBLIC DRIVER API FUNCTIONS */
void MPU9250_Init(MPU9250_t* mpu, spiBASE_t *spi, const spiDAT1_t cfg);
void MPU9250_Reset(MPU9250_t *mpu);
void MPU9250_DisableI2C(MPU9250_t *mpu);
void MPU9250_ConfigGyro(MPU9250_t *mpu, MPU9250_GyroRange fs_sel);
void MPU9250_ConfigAccel(MPU9250_t *mpu, MPU9250_AccelRange fs_sel);

#endif /* PROJECT_MPU9250_H_ */
