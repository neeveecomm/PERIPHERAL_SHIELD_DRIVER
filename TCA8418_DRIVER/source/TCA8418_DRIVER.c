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
 * @file    TCA8418_DRIVER_I2C.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_i2c.h"



/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */



/* KEYPAD 4X4 MATRIX _ I2C DRIVER  */


/* IF YOU WANT GPIO DRIVER , WE HAVE SOURCE FILE " TCA8418_GPIO.C "  */

#define TCA8418_SA

#define I2C1_START		I2C1->C1 |= (1 << I2C_C1_MST_SHIFT) | (1 << I2C_C1_TX_SHIFT)
#define I2C1_STOP		I2C1->C1 &= ~((1 << I2C_C1_MST_SHIFT) | (1 << I2C_C1_TX_SHIFT) | (1 << I2C_C1_TXAK_SHIFT))
#define I2C1_RSTART		I2C1->C1 |= (1 << I2C_C1_RSTA_SHIFT) | (1 << I2C_C1_TX_SHIFT)
#define I2C1_XMIT		I2C1->C1 |= (1 << I2C_C1_TX_SHIFT)
#define I2C1_RECV		I2C1->C1 &= ~(1 << I2C_C1_TX_SHIFT)
#define I2C1_MASTER		I2C1->C1 |= (1 << I2C_C1_MST_SHIFT)
#define I2C1_WAIT		while((I2C1->S & (1 << I2C_S_IICIF_SHIFT)) == 0); \
						I2C1->S |= (1 << I2C_S_IICIF_SHIFT)
#define I2C1_READ_WAIT			while((I2C1->S & (1 << I2C_S_IICIF_SHIFT)) == 0); \
								I2C1->S |= (1 << I2C_S_IICIF_SHIFT)

void i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t regVal)
{
	uint8_t data;

	/* I2C1 Check for Bus Busy */
	while(I2C1->S & (1 << I2C_S_BUSY_SHIFT));

	/* Generate START Condition */
	I2C1_START;



	/* Send Slave Address */
	I2C1->D = (slaveAddr << 1);
	I2C1_WAIT;

	/* Send Register Address */
	I2C1->D = regAddr;
	I2C1_WAIT;

	/* Send Slave Address */
	I2C1->D = regVal;
	I2C1_WAIT;

	/* Generate STOP Condition */
	I2C1_STOP;

	return;
}

uint8_t i2c_read(uint8_t slaveAddr, uint8_t regAddr)
{
	uint8_t data;
	uint8_t timeDelay = 6;

	/* I2C1 Check for Bus Busy */
	while(I2C1->S & (1 << I2C_S_BUSY_SHIFT));

	/* Generate START Condition */
	I2C1_START;

	/* Send Slave Address */
	I2C1->D = (slaveAddr << 1);
	I2C1_WAIT;

	/* Send Register Address */
	I2C1->D = regAddr;
	I2C1_WAIT;

	/* Generate Repeated Start */
	I2C1_RSTART;

    /* Add some delay to wait the Re-Start signal. */
    while (timeDelay--)
    {
        __NOP();
    }

	/* Send Slave Address */
	I2C1->D = (slaveAddr << 1) | 0x01;
	I2C1_WAIT;

	I2C1_RECV;

	I2C1->C1 |= (1 << I2C_C1_TXAK_SHIFT);

	/* Dummy Read */
	data = I2C1->D;
	I2C1_READ_WAIT;

	/* Generate STOP Condition */
	I2C1_STOP;

	/* Read the value from Data Register */
	data = I2C1->D;

	return data;
}

#define I2C_RELEASE_SDA_PORT PORTE
#define I2C_RELEASE_SCL_PORT PORTE
#define I2C_RELEASE_INT_PORT PORTA
#define I2C_RELEASE_SDA_GPIO GPIOE
#define I2C_RELEASE_SDA_PIN 0U
#define I2C_RELEASE_SCL_GPIO GPIOE
#define I2C_RELEASE_SCL_PIN 1U
#define I2C_RELEASE_INT_GPIO GPIOA
#define I2C_RELEASE_INT_PIN 5U

static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < 1000; i++)
    {
        __NOP();
    }
}

void BOARD_I2C_ReleaseBus(void)
{
    uint8_t i = 0;
    gpio_pin_config_t pin_config;
    port_pin_config_t i2c_pin_config = {0};

    /* Config pin mux as gpio */
    i2c_pin_config.pullSelect = kPORT_PullUp;
    i2c_pin_config.mux = kPORT_MuxAsGpio;

    pin_config.pinDirection = kGPIO_DigitalOutput;
    pin_config.outputLogic = 1U;
    CLOCK_EnableClock(kCLOCK_PortE);
    CLOCK_EnableClock(kCLOCK_PortA);
    PORT_SetPinConfig(I2C_RELEASE_SCL_PORT, I2C_RELEASE_SCL_PIN, &i2c_pin_config);
    PORT_SetPinConfig(I2C_RELEASE_SDA_PORT, I2C_RELEASE_SDA_PIN, &i2c_pin_config);

    GPIO_PinInit(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, &pin_config);
    GPIO_PinInit(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_WritePinOutput(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA low */
    for (i = 0; i < 9; i++)
    {
        GPIO_WritePinOutput(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_WritePinOutput(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_WritePinOutput(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_WritePinOutput(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_WritePinOutput(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_WritePinOutput(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_WritePinOutput(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
    i2c_release_bus_delay();
}

/*
 * @brief   Application entry point.
 */



/* if you have any doubt in registers value or given value to respective register , you have to check in datasheet.


 */


void keylock (void)

/* IF YOU WANT TO RELEASE KEYPAD , YOU  SHOULD FIRST PRESS "#" THEN WITHIN 2 SECOND PRESS "1".
 *
 * IT WILL BE RELAESE
 *
 */
{       i2c_write(0x34, 0x1D, 0x0F);
        i2c_write(0x34, 0x1E, 0x0F);
        i2c_write(0x34, 0x1F, 0x00);
        i2c_write(0x34, 0x03, 0x40);
	    i2c_write(0x34, 0x01, 0xBD);
		i2c_write(0x34, 0x0E, 0x52);
		i2c_write(0x34, 0x0F, 0x0B);
		i2c_write(0x34, 0x10, 0x22);

}

void GPIO (void)

{
	        i2c_write(0x34, 0x01, 0xD2);
	        i2c_write(0x34, 0x1D, 0x00);
		    i2c_write(0x34, 0x1E, 0x00);


	        i2c_write(0x34, 0x17, 0x0F);
	        i2c_write(0x34, 0x18, 0x0F);
	        i2c_write(0x34, 0x1A, 0x0F);
	        i2c_write(0x34, 0x1B, 0x0F);
		    i2c_write(0x34, 0x26, 0x0F);
			i2c_write(0x34, 0x27, 0x0F);

			i2c_write(0x34, 0x23, 0x0F);
			i2c_write(0x34, 0x24, 0x0F);

			i2c_write(0x34, 0x2C, 0x0F);
			i2c_write(0x34, 0x2D, 0x0F);
			i2c_write(0x34, 0x29, 0x0F);
			i2c_write(0x34, 0x30, 0x0F);


}

void keypress (void)
{
	i2c_write(0x34, 0x1D, 0x0F);
	i2c_write(0x34, 0x1E, 0x0F);
	i2c_write(0x34, 0x20, 0x0F);
	i2c_write(0x34, 0x21, 0x0F);


	int data1 = i2c_read(0x34, 0x04);
	// printf("data1 : 0x %02x\n", data1 );


	int data2 = i2c_read(0x34, 0x05);
	// printf("data2 : 0x %02x\n", data2 );

	int data3 = i2c_read(0x34, 0x06);
	// printf("data3 : 0x %02x\n", data3 );


	int data4 = i2c_read(0x34, 0x07);
	//  printf("data4 : 0x %02x\n", data4 );


	int data5 = i2c_read(0x34, 0x02);
		// printf("data5 : 0x %02x\n", data5 );

	int data6 = i2c_read(0x34, 0x03);
			//	printf("data6 : 0x %02x\n", data6 );



if((data1 == 0xa2)|(data2 == 0xa2)|(data3 == 0xa2)|(data4 == 0xa2))
{
	printf("1");
}

if((data1 == 0x98)|(data2 == 0x98)|(data3 == 0x98)|(data4 == 0x98))
{
	printf("2");
}

if((data1 == 0x8e)|(data2 == 0x8e)|(data3 == 0x8e)|(data4 == 0x8e))
{
	printf("3");
}

if((data1 == 0x84)|(data2 == 0x84)|(data3 == 0x84)|(data4 == 0x84))
{
	printf("A");
}

if((data1 == 0xa1)|(data2 == 0xa1)|(data3 == 0xa1)|(data4 == 0xa1))
{
	printf("4");
}

if((data1 == 0x97)|(data2 == 0x97)|(data3 == 0x97)|(data4 == 0x97))
{
	printf("5");
}

if((data1 == 0x8d)|(data2 == 0x8d)|(data3 == 0x8d)|(data4 == 0x8d))
{
	printf("6");
}

if((data1 == 0x83)|(data2 == 0x83)|(data3 == 0x83)|(data4 == 0x83))
{
	printf("B");
}

if((data1 == 0xa0)|(data2 == 0xa0)|(data3 == 0xa0)|(data4 == 0xa0))
{
	printf("7");
}

if((data1 == 0x96)|(data2 == 0x96)|(data3 == 0x96)|(data4 == 0x96))
{
	printf("8");
}

if((data1 == 0x8c)|(data2 == 0x8c)|(data3 == 0x8c)|(data4 == 0x8c))
{
	printf("9");
}

if((data1 == 0x82)|(data2 == 0x82)|(data3 == 0x82)|(data4 == 0x82))
{
	printf("C");
}

if((data1 == 0x9f)|(data2 == 0x9f)|(data3 == 0x9f)|(data4 == 0x9f))
{
	printf("*");
}

if((data1 == 0x95)|(data2 == 0x95)|(data3 == 0x95)|(data4 == 0x95))
{
	printf("0");
}

if((data1 == 0x8b)|(data2 == 0x8b)|(data3 == 0x8b)|(data4 == 0x8b))
{
	printf("#");
}

if((data1 == 0x81)|(data2 == 0x81)|(data3 == 0x81)|(data4 == 0x81))
{
	printf("D");
}
}

void keyrelease (void)
{
	i2c_write(0x34, 0x1D, 0x0F);
	i2c_write(0x34, 0x1E, 0x0F);
	i2c_write(0x34, 0x20, 0x0F);
	i2c_write(0x34, 0x21, 0x0F);



	int data1 = i2c_read(0x34, 0x04);
	// printf("data1 : 0x %02x\n", data1 );


	int data2 = i2c_read(0x34, 0x05);
	// printf("data2 : 0x %02x\n", data2 );

	int data3 = i2c_read(0x34, 0x06);
	// printf("data3 : 0x %02x\n", data3 );


	int data4 = i2c_read(0x34, 0x07);
	 // printf("data4 : 0x %02x\n", data4 );


	int data5 = i2c_read(0x34, 0x02);
	  // printf("data5 : 0x %02x\n", data5 );

    int data6 = i2c_read(0x34, 0x03);
		//	printf("data6 : 0x %02x\n", data6 );



if((data1 == 0x22)|(data2 == 0x22)|(data3 == 0x22)|(data4 == 0x22))
{
	printf("-1");
}

if((data1 == 0x18)|(data2 == 0x18)|(data3 == 0x18)|(data4 == 0x18))
{
	printf("-2");
}

if((data1 == 0x0e)|(data2 == 0x0e)|(data3 == 0x0e)|(data4 == 0x0e))
{
	printf("-3");
}

if((data1 == 0x04)|(data2 == 0x04)|(data3 == 0x04)|(data4 == 0x04))
{
	printf("-A");
}

if((data1 == 0x21)|(data2 == 0x21)|(data3 == 0x21)|(data4 == 0x21))
{
	printf("-4");
}

if((data1 == 0x17)|(data2 == 0x17)|(data3 == 0x17)|(data4 == 0x17))
{
	printf("-5");
}

if((data1 == 0x0d)|(data2 == 0x0d)|(data3 == 0x0d)|(data4 == 0x0d))
{
	printf("-6");
}

if((data1 == 0x03)|(data2 == 0x03)|(data3 == 0x03)|(data4 == 0x03))
{
	printf("-B");
}

if((data1 == 0x20)|(data2 == 0x20)|(data3 == 0x20)|(data4 == 0x20))
{
	printf("-7");
}

if((data1 == 0x16)|(data2 == 0x16)|(data3 == 0x16)|(data4 == 0x16))
{
	printf("-8");
}

if((data1 == 0x0c)|(data2 == 0x0c)|(data3 == 0x0c)|(data4 == 0x0c))
{
	printf("-9");
}

if((data1 == 0x02)|(data2 == 0x02)|(data3 == 0x02)|(data4 == 0x02))
{
	printf("-C");
}

if((data1 == 0x1f)|(data2 == 0x1f)|(data3 == 0x1f)|(data4 == 0x1f))
{
	printf("-*");
}

if((data1 == 0x15)|(data2 == 0x15)|(data3 == 0x15)|(data4 == 0x15))
{
	printf("-0");
}

if((data1 == 0x0b)|(data2 == 0x0b)|(data3 == 0x0b)|(data4 == 0x0b))
{
	printf("-#");
}

if((data1 == 0x01)|(data2 == 0x01)|(data3 == 0x01)|(data4 == 0x01))
{
	printf("-D");
}
}



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

	/* I2C1 Enable, Master Mode */
	I2C1->C1 = (1 << I2C_C1_IICEN_SHIFT) | (1 << I2C_C1_IICIE_SHIFT);

	I2C1->S |= (1 << I2C_S_IICIF_SHIFT);

	/* I2C1 Check for Bus Busy */
	while(I2C1->S & (1 << I2C_S_BUSY_SHIFT));

	//keylock();

    while (1) {

          keypress();
        //keyrelease();



         }

return 0 ;

}
