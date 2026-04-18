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
#define MPU9250_REG_CONFIG          0x1AU       // Configuration
#define MPU9250_REG_GYRO_CONFIG     0x1BU       // Gyroscope configuration
#define MPU9250_REG_ACCEL_CONFIG_1  0x1CU       // Accelerometer configuration 1
#define MPU9250_REG_ACCEL_CONFIG_2  0x1DU       // Accelerometer configuration 2

/* ACCELEROMETER SENSOR DATA REGISTERS */
#define MPU9250_REG_ACCEL_XOUT_H    0x3BU       // High byte accel x-axis measurement
#define MPU9250_REG_ACCEL_XOUT_L    0x3CU       // Low byte accel x-axis measurement
#define MPU9250_REG_ACCEL_YOUT_H    0x3DU       // High byte accel y-axis measurement
#define MPU9250_REG_ACCEL_YOUT_L    0x3EU       // Low byte accel y-axis measurement
#define MPU9250_REG_ACCEL_ZOUT_H    0x3FU       // High byte accel z-axis measurement
#define MPU9250_REG_ACCEL_ZOUT_L    0x40U       // Low byte accel z-axis measurement

/* THERMOMETER SENSOR DATA REGISTERS */
#define MPU9250_REG_TEMP_OUT_H      0x41U       // High byte temp measurement
#define MPU9250_REG_TEMP_OUT_L      0x42U       // Low byte temp measurement

/* GYROSCOPE SENSOR DATA REGISTERS */
#define MPU9250_REG_GYRO_XOUT_H    0x43U       // High byte gyro x-axis measurement
#define MPU9250_REG_GYRO_XOUT_L    0x44U       // Low byte gyro x-axis measurement
#define MPU9250_REG_GYRO_YOUT_H    0x45U       // High byte gyro y-axis measurement
#define MPU9250_REG_GYRO_YOUT_L    0x46U       // Low byte gyro y-axis measurement
#define MPU9250_REG_GYRO_ZOUT_H    0x47U       // High byte gyro z-axis measurement
#define MPU9250_REG_GYRO_ZOUT_L    0x48U       // Low byte gyro z-axis measurement

/* DEVICE MGMT REGISTERS */
#define MPU9250_REG_USER_CTRL       0X6AU       // User Control register
#define MPU9250_REG_PWR_MGMT_1      0x6BU       // Power Management 1 register
#define MPU9250_REG_PWR_MGMT_2      0x6CU       // Power Management 2 register
#define MPU9250_REG_WHO_AM_I        0x75U       // Device ID register

/* ===== MPU9250 REGISTER MAP END ===== */

/* ===== MPU9250 DRIVER BITMASK BEGIN ===== */
/*  CONFIGURATION  */
#define MPU9250_MASK_CONFIG_DLPF_CFG            0x07U       // CONFIG[FLPF_CFG[2:0]]

/* GYROSCOPE CONFIGURATION */
#define MPU9250_MASK_GYRO_CFG_GYRO_FS_SEL       0x18U       // GYRO_CFG[GYRO_FS_SEL[1:0]]
#define MPU9250_MASK_GYRO_CFG_FCHOICE_B         0x03U       // GYRO_CFG[Fchoice_b[1:0]]

/* ACCELEROMETER CONFIGURATION 1 */
#define MPU9250_MASK_ACC_CFG_1_ACCEL_FS_SEL     0x18U       // ACCEL_CFG[ACCEL_FS_SEL[1:0]]

/* ACCELEROMETER CONFIGURATION 2 */
#define MPU9250_MASK_ACC_CFG_2_ACCEL_FCHOICE_B      0x08U       // ACCEL_CFG[accel_fchoice_b]
#define MPU9250_MASK_ACC_CFG_2_A_DLPFCFG            0x07U       // ACCEL_CFG[A_DLPFCFG[2:0]]

/* POWER MANAGEMENT I */
#define MPU9250_MASK_PWR1_H_RESET   0x80U       // PWR_MGMT_1[H_RESET]
#define MPU9250_MASK_PWR1_SLEEP     0x40U       // PWR_MGMT_1[SLEEP]
#define MPU9250_MASK_PWR1_CLKSEL    0x07U       // PWR_MGMT_1[CLKSEL]

/* POWER MANAGEMENT II */
#define MPU9250_MASK_PWR2_DISABLE_XA    0x20U   // PWR_MGMT_2[DISABLE_XA]
#define MPU9250_MASK_PWR2_DISABLE_YA    0x10U   // PWR_MGMT_2[DISABLE_YA]
#define MPU9250_MASK_PWR2_DISABLE_ZA    0x08U   // PWR_MGMT_2[DISABLE_ZA]
#define MPU9250_MASK_PWR2_DISABLE_XG    0x04U   // PWR_MGMT_2[DISABLE_XG]
#define MPU9250_MASK_PWR2_DISABLE_YG    0x02U   // PWR_MGMT_2[DISABLE_YG]
#define MPU9250_MASK_PWR2_DISABLE_ZG    0x01U   // PWR_MGMT_2[DISABLE_ZG]

/* USER CTRL */
#define MPU9250_MASK_USR_CTL_I2C_IF_DIS     0x10U   // USR_CTRL[I2C_IF_DIS]

/* ===== MPU9250 DRIVER BITMASK END ===== */

/* ===== MPU9250 REGISTER VALUES BEGIN */
/* DIGITAL LOWPASS FILTER (Gyro, Acc) */
typedef enum
{
    MPU9250_DLPF_250Hz = 0x00U,     // Gyro: 250Hz, Accel: 218Hz
    MPU9250_DLPF_184Hz = 0x01U,     // Gyro: 184Hz, Accel: 218Hz
    MPU9250_DLPF_92Hz  = 0x02U,     // Gyro: 92Hz,  Accel: 99Hz
    MPU9250_DLPF_41Hz  = 0x03U,     // Gyro: 41Hz,  Accel: 44.8Hz
    MPU9250_DLPF_20Hz  = 0x04U,     // Gyro: 20Hz,  Accel: 21.2Hz
    MPU9250_DLPF_10Hz  = 0x05U,     // Gyro: 10Hz,  Accel: 10.2Hz
    MPU9250_DLPF_5Hz   = 0x06U,     // Gyro: 5Hz,   Accel: 5.05Hz
} MPU9250_DLPF_BW;

/* GYROSCOPE CONFIGURATION */
typedef enum
{
    MPU9250_GYRO_FS_250dps = 0x00U,
    MPU9250_GYRO_FS_500dps = 0x08U,
    MPU9250_GYRO_FS_1kdps = 0x10U,
    MPU9250_GYRO_FS_2kdps = 0x18U,
} MPU9250_GyroRange;

/* ACCELEROMETER CONFIGURATION 1 */
typedef enum
{
    MPU9250_ACCEL_FS_2G = 0x00U,
    MPU9250_ACCEL_FS_4G = 0x08U,
    MPU9250_ACCEL_FS_8G = 0x10U,
    MPU9250_ACCEL_FS_16G = 0x18U,
} MPU9250_AccelRange;

/* POWER MANAGEMENT I */
typedef enum
{
    MPU9250_PWR1_CLKSEL_20MHz = 0x00U,
    MPU9250_PWR1_CLKSEL_PLL = 0x01U,
    MPU9250_PWR1_CLKSEL_STOP = 0x07U,
} MPU9250_ClkSel;

/* ===== MPU9250 REGISTER VALUES END ===== */

#endif /* PROJECT_MPU9250_REG_H_ */
