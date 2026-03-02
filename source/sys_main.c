/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
/* TI HW INCLUDE */
#include "gio.h"
#include "het.h"
#include "sci.h"
#include "spi.h"

/* Project Include */
#include "MPU9250.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void applicationInit(void)
{
    /* SYSTEM INIT START */
    /* TI HW Driver INIT */
    gioInit();
    hetInit();
    sciInit();
    spiInit();

    /* SYSTEM INIT END */
}

/* User macro BEGIN */
#define MPU9250_WHOAMI  0x75U
#define MPU9250_USER_CTRL 0x6AU
/* User macro END */

/* User var BEGIN */
MPU9250_t MPU;
/* User var BEGIN */

/* User fcn define BEGIN */
/* User fcn define END */

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    uint8_t spiData, usrCtrl;

    applicationInit();       // Initialize System modules
    
    MPU9250Init(&MPU, spiREG2, (spiDAT1_t){
        .CS_HOLD = true,        // Hold CS on transaction
        .WDEL = false,          // Wait Delay disabled
        .DFSEL = SPI_FMT_0,     // Using SPI Format 0
        .CSNR = SPI_CS_3        // Using SPI2NCS[3]
    });

    for (;;)
    {
        spiData = 0x00U;
        usrCtrl = 0x00U;

        // 1. Get module ID
        MPU9250Read(&MPU, MPU9250_WHOAMI, 1U, &spiData);

        // 2. Test write 0x00 to USER_CTRL
        MPU9250Write(&MPU, MPU9250_USER_CTRL, 1U, &usrCtrl);
        MPU9250Read(&MPU, MPU9250_USER_CTRL, 1U, &spiData);

        // 3. Write 0x10 to USER_CTRL (Write I2C_IF_DIS = 1)
        usrCtrl = 0x10U;
        MPU9250Write(&MPU, MPU9250_USER_CTRL, 1U, &usrCtrl);
        MPU9250Read(&MPU, MPU9250_USER_CTRL, 1U, &spiData);
        asm(" nop");
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */
