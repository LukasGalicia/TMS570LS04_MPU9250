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

void MPU9250Init(MPU9250_t* mpu, spiBASE_t *spi, spiDAT1_t cfg);
void MPU9250Write(MPU9250_t *mpu, uint32_t rx_byte_size, uint16_t mpu_reg, uint16_t *databuff);
void MPU9250Read(MPU9250_t *mpu, uint32_t rx_byte_size, uint16_t mpu_reg, uint16_t *destbuff);

#endif /* PROJECT_MPU9250_H_ */
