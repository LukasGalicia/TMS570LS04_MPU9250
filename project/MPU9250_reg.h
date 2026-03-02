/*
 * MPU9250_reg.h
 *
 *  Created on: 1 mar 2026
 *      Author: lukas
 */

#ifndef PROJECT_MPU9250_REG_H_
#define PROJECT_MPU9250_REG_H_

/* ===== MPU9250 REGISTER MAP BEGIN ===== */

/* CONFIGURATION REGISTERS */
#define MPU9250_REG_GYRO_CONFIG     0x1BU       // Gyroscope configuration
#define MPU9250_REG_ACCEL_CONFIG_1  0x1CU       // Accelerometer configuration 1
#define MPU9250_REG_ACCEL_CONFIG_2  0x1DU       // Accelerometer configuration 2

/* ACCELEROMETER SENSOR DATA REGISTERS */
#define MPU9250_REG_ACCEL_XOUT_H    0x3BU       // High byte accel x-axis measurement
#define MPU9250_REG_ACCEL_XOUT_L    0x3CU       // Low byte accel x-axis measurement
#define MPU9250_REG_ACCEL_YOUT_H    0x3DU       // High byte accel y-axis measurement
#define MPU9250_REG_ACCEL_YOUT_L    0x3EU       // Low byte accel x-axis measurement
#define MPU9250_REG_ACCEL_ZOUT_H    0x3FU       // High byte accel z-axis measurement
#define MPU9250_REG_ACCEL_ZOUT_L    0x40U       // Low byte accel x-axis measurement

/* DEVICE MGMT REGISTERS */
#define MPU9250_REG_USER_CTRL       0X6AU       // User Control register
#define MPU9250_REG_PWR_MGMT_1      0x6BU       // Power Management 1 register
#define MPU9250_REG_PWR_MGMT_2      0x6CU       // Power Management 2 register
#define MPU9250_REG_WHO_AM_I        0x75U       // Device ID register

/* ===== MPU9250 REGISTER MAP END ===== */

/* ===== MPU9250 DRIVER BITMASK BEGIN ===== */

/* ===== MPU9250 DRIVER BITMASK END ===== */

#endif /* PROJECT_MPU9250_REG_H_ */
