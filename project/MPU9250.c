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
    mpu->spi_reg = spi;             // SPI Register
    mpu->spi_config = cfg;          // SPI Driver Register Configuration

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

void MPU9250_ConfigClk(MPU9250_t *mpu, MPU9250_ClkSel clk)
{
    MPU9250_UpdateBits(mpu, MPU9250_REG_PWR_MGMT_1, MPU9250_MASK_PWR1_CLKSEL, clk);
}

void MPU9250_ConfigGyro(MPU9250_t *mpu, MPU9250_GyroRange fs_sel)
{
    MPU9250_UpdateBits(mpu, MPU9250_REG_GYRO_CONFIG, MPU9250_MASK_GYRO_CFG_GYRO_FS_SEL, fs_sel);

    switch(fs_sel)
    {
        case MPU9250_GYRO_FS_250dps:    mpu->gyro_scale = MPU9250_GYRO_SCALE_250DPS;    break;
        case MPU9250_GYRO_FS_500dps:    mpu->gyro_scale = MPU9250_GYRO_SCALE_500DPS;    break;
        case MPU9250_GYRO_FS_1kdps:     mpu->gyro_scale = MPU9250_GYRO_SCALE_1000DPS;   break;
        case MPU9250_GYRO_FS_2kdps:     mpu->gyro_scale = MPU9250_GYRO_SCALE_2000DPS;   break;
        default:                        mpu->gyro_scale = MPU9250_GYRO_SCALE_250DPS;    break;
    }

}

void MPU9250_ConfigAccel(MPU9250_t *mpu, MPU9250_AccelRange fs_sel)
{
    MPU9250_UpdateBits(mpu, MPU9250_REG_ACCEL_CONFIG_1, MPU9250_MASK_ACC_CFG_1_ACCEL_FS_SEL, fs_sel);

    switch(fs_sel)
    {
        case MPU9250_ACCEL_FS_2G:   mpu->accel_scale = MPU9250_ACCEL_SCALE_2G;      break;
        case MPU9250_ACCEL_FS_4G:   mpu->accel_scale = MPU9250_ACCEL_SCALE_4G;      break;
        case MPU9250_ACCEL_FS_8G:   mpu->accel_scale = MPU9250_ACCEL_SCALE_8G;      break;
        case MPU9250_ACCEL_FS_16G:  mpu->accel_scale = MPU9250_ACCEL_SCALE_16G;     break;
        default:                    mpu->accel_scale = MPU9250_ACCEL_SCALE_2G;      break;
    }
}

void MPU9250_ConfigDLPF(MPU9250_t *mpu, MPU9250_DLPF_BW bw)
{
    // Set gyroscope/thermometer DLPF
    MPU9250_ClearBits(mpu, MPU9250_REG_GYRO_CONFIG, MPU9250_MASK_GYRO_CFG_FCHOICE_B);
    MPU9250_UpdateBits(mpu, MPU9250_REG_CONFIG, MPU9250_MASK_CONFIG_DLPF_CFG, bw);

    // Set accelerometer DLPF
    MPU9250_UpdateBits(mpu, MPU9250_REG_ACCEL_CONFIG_2, MPU9250_MASK_ACC_CFG_2_ACCEL_FCHOICE_B | MPU9250_MASK_ACC_CFG_2_A_DLPFCFG, bw);
}

void MPU9250_ReadAll(MPU9250_t *mpu, MPU9250Data_t *raw)
{
    uint8_t imu_data[14] = {0U};

    MPU9250_ReadBurst(mpu, MPU9250_REG_ACCEL_XOUT_H, 14, imu_data);

    raw->accel_x = (int16_t)((imu_data[0] << 8) | imu_data[1]);
    raw->accel_y = (int16_t)((imu_data[2] << 8) | imu_data[3]);
    raw->accel_z = (int16_t)((imu_data[4] << 8) | imu_data[5]);

    raw->temp    = (int16_t)((imu_data[6] << 8) | imu_data[7]);

    raw->gyro_x  = (int16_t)((imu_data[8] << 8) | imu_data[9]);
    raw->gyro_y  = (int16_t)((imu_data[10] << 8) | imu_data[11]);
    raw->gyro_z  = (int16_t)((imu_data[12] << 8) | imu_data[13]);
}

void MPU9250_ReadGyro(MPU9250_t *mpu, MPU9250Data_t *raw)
{
    uint8_t gyro_data[6] = {0U};

    MPU9250_ReadBurst(mpu, MPU9250_REG_GYRO_XOUT_H, 6, gyro_data);

    raw->gyro_x = (int16_t) ((((uint16_t) gyro_data[0]) << 8U) | gyro_data[1]);
    raw->gyro_y = (int16_t) ((((uint16_t) gyro_data[2]) << 8U) | gyro_data[3]);
    raw->gyro_z = (int16_t) ((((uint16_t) gyro_data[4]) << 8U) | gyro_data[5]);
}

void MPU9250_ReadAccel(MPU9250_t *mpu, MPU9250Data_t *raw)
{
    uint8_t accel_data[6] = {0U};

    MPU9250_ReadBurst(mpu, MPU9250_REG_ACCEL_XOUT_H, 6, accel_data);

    raw->accel_x = (int16_t) ((((uint16_t) accel_data[0]) << 8U) | accel_data[1]);
    raw->accel_y = (int16_t) ((((uint16_t) accel_data[2]) << 8U) | accel_data[3]);
    raw->accel_z = (int16_t) ((((uint16_t) accel_data[4]) << 8U) | accel_data[5]);
}

int16_t MPU9250_ReadTemp(MPU9250_t *mpu)
{
    uint8_t temp_data[2] = {0U};

    MPU9250_ReadBurst(mpu, MPU9250_REG_TEMP_OUT_H, 2, temp_data);

    return (int16_t)((temp_data[0] << 8) | temp_data[1]);
}

#endif /* PROJECT_MPU9250_C_ */
