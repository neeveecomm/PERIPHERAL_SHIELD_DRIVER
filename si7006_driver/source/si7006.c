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
 * @file    si7006_driver2.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_i2c.h"

#include "SI7006.h"
#include "SI7006_driver.C"
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

	/* PORTE1 pin as I2C1_SCL */
	PORTE->PCR[1] = (6 << PORT_PCR_MUX_SHIFT) | (1 << PORT_PCR_PS_SHIFT) | (1<<PORT_PCR_PE_SHIFT) | (1<<PORT_PCR_SRE_SHIFT);

	/* PORTE0 pin as I2C1_SDA */
	PORTE->PCR[0] = (6 << PORT_PCR_MUX_SHIFT)  | (1 << PORT_PCR_PS_SHIFT) | (1<<PORT_PCR_PE_SHIFT) | (1<<PORT_PCR_SRE_SHIFT);


	/* I2C1 Frequency Divider */
	I2C1->F = 0x0F;

	/* I2C1 Enable, Master Mode */
	I2C1->C1 = (1 << I2C_C1_IICEN_SHIFT) | (1 << I2C_C1_IICIE_SHIFT);

	I2C1->S |= (1 << I2C_S_IICIF_SHIFT);






	MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE ();

	MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE ();

	//MEASURE_RELATIVE_HUMIDITY_HOLD_MASTER_MODE ();
	//MEASURE_TEMPERATURE_HOLD_MASTER_MODE ();
	//READ_TEMPERATURE_VALUE_FROM_PREVIOUS_RH_MEASUREMENT ();
	//RESOLUTION_RH_11_TEMP_11 ();
	//RESOLUTION_RH_12_TEMP_14 ();
	//RESOLUTION_RH_8_TEMP_12 ();
    //RESOLUTION_RH_10_TEMP_13 ();
	//VDD ();
	//HEATER_ENABLED ();
	//HEATER_DISABLED ();
	//HEATER_CURRENT_3mA ();
	//HEATER_CURRENT_9mA ();
    //HEATER_CURRENT_15mA ();
	//HEATER_CURRENT_27mA ();
	//HEATER_CURRENT_51mA ();
	//HEATER_CURRENT_94mA ();
	//READ_ELECTRONIC_ID_FIRST_BYTE_CMD ();
	//READ_ELECTRONIC_ID_SECOND_BYTE_CMD ();
	//READ_FIRMWARE_VERSION_CMD ();

return (0);
}
