/*
 * si7006.h
 *
 *  Created on: 24-Mar-2021
 *      Author: neevee
 */
         /*   SI7006 I2C Humidity and Temperature sensor   */

#ifndef SI7006_H_
#define SI7006_H_


// SLAVE ADDRESS


#define     SI7006_ADDRESS       0x40                                                 /*   SI7006 I2C Address                                   */



// REGISTERS


#define            SI7006_MEASURE_RELATIVE_HUMIDITY_HOLD_MASTER_MODE              0xE5               /*  Measure Relative Humidity, Hold Master Mode           */
#define            SI7006_MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE           0xF5               /*  Measure Relative Humidity, No Hold Master Mode        */
#define            SI7006_MEASURE_TEMPERATURE_HOLD_MASTER_MODE                    0xE3               /*  Measure Temperature, Hold Master Mode                 */
#define            SI7006_MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE                 0xF3               /*  Measure Temperature, No Hold Master Mode              */
#define            SI7006_READ_TEMPERATURE_VALUE_FROM_PREVIOUS_RH_MEASUREMENT     0xE0               /*  Read Temperature Value from Previous RH Measurement   */
#define            SI7006_RESET                                                   0xFE               /*  Reset                                                 */
#define            SI7006_WRITE_RH_T_USER_REGISTER_1                              0xE6               /*  Write RH/T User Register 1                            */
#define            SI7006_READ_RH_T_USER_REGISTER_1                               0xE7               /*  Read RH/T User Register 1                             */
#define            SI7006_WRITE_HEATER_CONTROL_REGISTER                           0x51               /*  Write Heater Control Register                         */
#define            SI7006_READ_HEATER_CONTROL_REGISTER                            0x11              /*  Read Heater Control Register                          */
#define            SI7006_READ_ELECTRONIC_ID_FIRST_BYTE_CMD1                      0xFA               /* Read Electronic ID 1st Byte                           */
#define            SI7006_READ_ELECTRONIC_ID_FIRST_BYTE_CMD2                      0x0F               /*  Read Electronic ID 1st Byte                           */
#define            SI7006_READ_ELECTRONIC_ID_SECOND_BYTE_CMD1                     0xFC               /*  Read Electronic ID 2nd Byte                           */
#define            SI7006_READ_ELECTRONIC_ID_SECOND_BYTE_CMD2                     0xC9              /*  Read Electronic ID 2nd Byte                           */
#define            SI7006_READ_FIRMWARE_VERSION_CMD1                              0x84               /*  Read Firmware Revision                                */
#define            SI7006_READ_FIRMWARE_VERSION_CMD2                              0xB8                /*  Read Firmware Revision                                */





// RESOLUTIONS

#define         SI7006_RESOLUTION_MASK                     0x81           /* SI7006 Measurement Resolution                         */
#define         SI7006_RESOLUTION_RH_12_TEMP_14            0x00           /*  SI7006 12b RH 14b Temp.                               */
#define         SI7006_RESOLUTION_RH_8_TEMP_12             0x01           /*  SI7006 9b  RH 12b Temp.                               */
#define         SI7006_RESOLUTION_RH_10_TEMP_13            0x80           /*  SI7006 10b RH 13b Temp.                               */
#define         SI7006_RESOLUTION_RH_11_TEMP_11            0x81            /* SI7006 11b RH 11b Temp.                               */



// VDD

/* NOTE:   The minimum recommended operating voltage is 1.9 V. A transition
                of the VDD status bit from 0 to 1 indicates that VDD is
                between 1.8 V and 1.9 V. If the VDD drops below 1.8 V, the
                device will no longer operate correctly.*/



#define         SI7006_VDDS_STATUS_MASK                    0x40           //  SI7006 VDD mask.                                      */
#define         SI7006_VDDS_STATUS_VDD_OK                  ( 1 << 6 )     //  VDD OK.                                               */
#define         SI7006_VDDS_STATUS_VDD_LOW                 ( 0 << 6 )      //  VDD Low.                                              */



// HEATER

#define         SI7006_HTRE_MASK                           0x04          /*  SI7006 HTRE Mask                                      */
#define         SI7006_HEATER_ENABLED                        ( 1 << 2 )     /*  SI7006 On-chip Heater Enable                          */
#define         SI7006_HEATER_DISABLED                       ( 0 << 2 )      /*  SI7006 On-chip Heater Disable                         */



 // RESET


        // USER REGISTER 1
            /*
                NOTE:   Reset Settings = 0011_1010.
                        Except where noted, reserved register bits will always read back as “1,” and are not affected by write operations. For
                        future compatibility, it is recommended that prior to a write operation, registers should be read. Then the values read
                        from the RSVD bits should be written back unchanged during the write operation.
            */



  // I2C START / STOP / WAIT FUNCTIONS


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

// READ ANDV WRITE FUNCTIONS

      void i2c_write1(uint8_t slaveAddr, uint8_t regAddr)
                                {


                                	/* I2C0 Check for Bus Busy */
                                	while(I2C1->S & (1 << I2C_S_BUSY_SHIFT));

                                	/* Generate START Condition */
                                	I2C1_START;

                                	//I2C0->A1 = (slaveAddr << 1);

                                	/* Send Slave Address */
                                	I2C1->D = (slaveAddr << 1);
                                	I2C1_WAIT;

                                	/* Send Register Address */
                                	I2C1->D = regAddr;
                                	I2C1_WAIT;

                                	/* Send Slave Address */
                                	//I2C1->D = regVal;
                                	//I2C1_WAIT;

                                	/* Generate STOP Condition */
                                	I2C1_STOP;

                                	return;
                                }

    uint32_t  i2c_read1(uint8_t slaveAddr)
                                {
                                	uint8_t data;
                                	uint8_t timeDelay = 6;

                                	/* I2C0 Check for Bus Busy */
                                	while(I2C1->S & (1 << I2C_S_BUSY_SHIFT));

                                	/* Generate START Condition */
                                	I2C1_START;

                                	/* Send Slave Address */
                                	I2C1->D = (slaveAddr << 1);
                                	I2C1_WAIT;

                                	/* Send Register Address */
                                	//I2C1->D = regAddr;
                                	//I2C1_WAIT;

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

                void i2c_write(uint8_t slaveAddr, uint8_t regAddr, uint8_t regVal)
                {


                	/* I2C0 Check for Bus Busy */
                	while(I2C1->S & (1 << I2C_S_BUSY_SHIFT));

                	/* Generate START Condition */
                	I2C1_START;

                	//I2C0->A1 = (slaveAddr << 1);

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

                 uint32_t i2c_read(uint8_t slaveAddr, uint8_t regAddr)
                {
                	uint8_t data;
                	uint8_t timeDelay = 6;

                	/* I2C0 Check for Bus Busy */
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
// DELAY TIME

            int DelayCount;

                static void Delay(void)
                {
                    uint32_t i = 0;
                    for (i = 0; i < DelayCount; i++)
                    {
                        __NOP();
                    }
                }
#define I2C_RELEASE_SDA_PORT PORTE
#define I2C_RELEASE_SCL_PORT PORTE
#define I2C_RELEASE_SDA_GPIO GPIOE
#define I2C_RELEASE_SDA_PIN 0U
#define I2C_RELEASE_SCL_GPIO GPIOE
#define I2C_RELEASE_SCL_PIN 1U

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

static void DELAY(void)
{
for(int i = 0; i < 100000; i++)
	{

	}
}




#endif /* SI7006_H_ */
