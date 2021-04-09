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
 * @file    RGB_LED_PeripheralShield.c
 * @brief   Application entry point.
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
/*
 *
 */
typedef struct {
	uint32_t PCR[32];
}PORTRegs_t;
#define PORT_A ((PORTRegs_t*)0x40049000)
#define PORT_C ((PORTRegs_t*)0x4004B000)

typedef struct {
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;
}GPIORegs_t;
#define GPIO_A ((GPIORegs_t*)0x400FF000)
#define GPIO_C ((GPIORegs_t*)0x400FF080)





void RED_ON (void)
{
	GPIO_C->PCOR = (1<<8);
	GPIO_C->PSOR = (1<<9);
	GPIO_A->PSOR = (1<<13);


}

void GREEN_ON (void)
{
	GPIO_C->PSOR = (1<<8);
	GPIO_C->PCOR = (1<<9);
	GPIO_A->PSOR = (1<<13);

}

void BLUE_ON (void)
{
	GPIO_C->PSOR = (1<<8);
	GPIO_C->PSOR = (1<<9);
	GPIO_A->PCOR = (1<<13);

}

void LED_OFF (void)
{
	GPIO_C->PSOR = (1<<8);
	GPIO_C->PSOR = (1<<9);
	GPIO_A->PSOR = (1<<13);

}

void RGB_ON (void)

              {

	                GPIO_C->PSOR = (1<<9);
		    		GPIO_A->PSOR = (1<<13);
		    		GPIO_C->PCOR = (1<<8);

		    		for(int i = 0; i < 1000000; i++){

		    		}

		    		GPIO_C->PSOR = (1<<8);
		    		GPIO_A->PSOR = (1<<13);
		    		GPIO_C->PCOR = (1<<9);

		    		for(int i = 0; i < 1000000; i++){

		    		    		}

		    		GPIO_C->PSOR = (1<<8);
		    		GPIO_C->PSOR = (1<<9);
		    		GPIO_A->PCOR = (1<<13);


		    		for(int i = 0; i < 1000000; i++){

		    		    		    		}
		    		GPIO_A->PSOR = (1<<13);




}


int main(void) {


	SIM->SCGC5 = (1<<9)|(1<<11);
	PORT_A->PCR[13] = (1<<8);
	PORT_C->PCR[8] = (1<<8);
	PORT_C->PCR[9] = (1<<8);
    GPIO_A->PDDR = (1<<13);
    GPIO_A->PCOR = (1<<13);
    GPIO_A->PSOR = (1<<13);
    GPIO_C->PDDR = (1<<8)|(1<<9);
    GPIO_C->PCOR = (1<<8);
    GPIO_C->PSOR = (1<<8);
    GPIO_C->PCOR = (1<<9);
    GPIO_C->PSOR = (1<<9);


    while(1) {

    	    //GREEN_ON();
    	   // RED_ON();
    	    //BLUE_ON();
    	   // LED_OFF();
            RGB_ON();

    }

    return 0;
}



