/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    BH174818.c
 * @brief   Application entry point.
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#include "BH1745.h"
#include "BH1745_driver.C"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */


/*
 * @brief   Application entry point.
 */




int main(void) {



	/* Enable clock for PORTE */
	SIM->SCGC5 = (1 << SIM_SCGC5_PORTE_SHIFT);

	/* Enable clock for I2C1 */
	SIM->SCGC4 = (1 << SIM_SCGC4_I2C1_SHIFT);

	BOARD_I2C_ReleaseBus();

	/* PORTE24 pin as I2C1_SCL */
	PORTE->PCR[1] = (6 << PORT_PCR_MUX_SHIFT) | (1 << PORT_PCR_PS_SHIFT) | (1<<PORT_PCR_PE_SHIFT) | (1<<PORT_PCR_SRE_SHIFT);

	/* PORTE25 pin as I2C1_SDA */
	PORTE->PCR[0] = (6 << PORT_PCR_MUX_SHIFT)  | (1 << PORT_PCR_PS_SHIFT) | (1<<PORT_PCR_PE_SHIFT) | (1<<PORT_PCR_SRE_SHIFT);


	/* I2C1 Frequency Divider */
	I2C1->F = 0x0F;

	/* I21 Enable, Master Mode */
	I2C1->C1 = (1 << I2C_C1_IICEN_SHIFT) | (1 << I2C_C1_IICIE_SHIFT);

	I2C1->S |= (1 << I2C_S_IICIF_SHIFT);

	/* I2C1 Check for Bus Busy */
	while(I2C1->S & (1 << I2C_S_BUSY_SHIFT));

/*
 * if we want to make any chance  in below follows
 *
 *       RGBC_MEASUREMENT TIME
 *       ADC_GAIN
 *       ENABLE INTEERUPT
 *       INTERRUPT SETTINGS
 *       SW RESET
 *       INT RESET
 *
 *           we just have to call the function
 *
 *          All the functions in "  BHI745.C "
 *
 *         for example: RGBC_MEASUREMENT TIME_160mSEC();
 *
 *
 *     And  if we want to make any chances in REGISTERS
 *
 *                 we just have to call the function
 *
 *              All the functions in "  BHI745.C "
 *
 *
 *    And also if we want READ any REGISTERS
 *
 *                 we just have to call the function
 *
 *              All the functions in "  BHI745.C "
 *
 */

	 MANUFACTURER_ID ();
	 MODE_CONTROL3();
	 RGBC_ENABLE ();
	 RGB_DATA_FOR_READ();
	// MODE_CONTROL2_READ ();

	  return (1);

	  }

void PERSISTENCE (void)
{
	/*Interrupt persistence function

	0x00 : Interrupt status is toggled at each measurement end.
	0x01 : Interrupt status is updated at each measurement end.
	0x02 : Interrupt status is updated if 4 consecutive threshold judgments are the same.
	0x03 : Interrupt status is updated if 8 consecutive threshold judgments are the same.

	 */

	i2c_write(BH1745_SA_LOW ,  BH1745_PERSISTENCE, 0x01);
}

void THRESHOLD (void)
{
	/*
	 * THRESHOLD HIGH
	 * DEFAULT VALUE = 0xFF
	 * IF WE WANT TO GIVE VALUE FOR THRESHOLD HIGH
	 * WE CAN CHANCE THE VALUE
	 *
	 * THRESHOLD LOW
	 * DEFAULT VALUE = 0x00
	 * IF WE WANT TO GIVE VALUE FOR THRESHOLD LOW
	 * WE CAN CHANCE THE VALUE
	 *
	 */
	int TH_LSBs = 0xFF;
	int TH_MSBs = 0xFF;
	int TL_LSBs = 0x00;
	int TL_MSBs = 0x00;

	i2c_write(BH1745_SA_LOW ,  BH1745_TH_LSBs, TH_LSBs);
	i2c_write(BH1745_SA_LOW ,  BH1745_TH_MSBs, TH_MSBs);
	i2c_write(BH1745_SA_LOW ,  BH1745_TL_LSBs, TL_LSBs);
	i2c_write(BH1745_SA_LOW ,  BH1745_TL_MSBs, TL_MSBs);
}

