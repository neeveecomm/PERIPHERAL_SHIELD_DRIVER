
/*
 * BH1745_DRIVER.C
 *
 *  Created on: 26-Mar-2021
 *      Author: neevee
 */

#include "BH1745.h"


void RBG_MEASUREMENT_TIME_160mSec (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL1, 0x00);
}

void RBG_MEASUREMENT_TIME_320mSec (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL1, 0x01);
}

void RBG_MEASUREMENT_TIME_640mSec (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL1, 0x02);
}

void RBG_MEASUREMENT_TIME_1280mSec (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL1, 0x03);
}

void RBG_MEASUREMENT_TIME_2560mSec (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL1, 0x04);
}

void RBG_MEASUREMENT_TIME_5120mSec (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL1, 0x05);
}

 void SYSTEM_CONTROL_SW_RESET (void)
 {
	 i2c_write(BH1745_SA_LOW , BH1745_SYSTEM_CONTROL, (1 << 7));
 }

 void SYSTEM_CONTROL_INT_RESET (void)
 {
	 i2c_write(BH1745_SA_LOW , BH1745_SYSTEM_CONTROL, (1 << 6));
 }

 void SYSTEM_CONTROL_READ (void)

 {
	 int system_control = i2c_read(BH1745_SA_LOW , BH1745_SYSTEM_CONTROL);

	     printf("system_control: 0x%02x \n", system_control);

 }
 void MODE_CONTROL1_READ (void)
 {
	 int  MODE_CONTROL1= i2c_read(BH1745_SA_LOW , BH1745_MODE_CONTROL1 );

	 	     printf("MODE_CONTROL1: 0x%02x \n", MODE_CONTROL1);
 }
void MODE_CONTROL3 (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL3, 0x02);
}

void RGBC_ENABLE (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL2, (1 << 4));

}

void ADC_GAIN_1X (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL2, (0 << 1)| (0 << 0));
}

void ADC_GAIN_2X (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL2, (0 << 1)| (1 << 0));
}

void ADC_GAIN_16X (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_MODE_CONTROL2, (1 << 1)| (0 << 0));
}

void MODE_CONTROL3_READ (void)
{
	int  MODE_CONTROL3= i2c_read(BH1745_SA_LOW , BH1745_MODE_CONTROL3 );

		 	     printf("MODE_CONTROL3: 0x%02x \n", MODE_CONTROL3);
}

void MODE_CONTROL2_READ (void)
{
	int  MODE_CONTROL2= i2c_read(BH1745_SA_LOW , BH1745_MODE_CONTROL2 );

		 	     printf("MODE_CONTROL2: 0x%02x \n", MODE_CONTROL2);

		 	     if((MODE_CONTROL2 & 0x80) == 0x80)
		 	     {
		 	    	 printf("RGBC data is updated after last writing MODE_CONTROL1,2,3 register or last reading MODE_CONTROL2 register");
		 	     }
		 	     else {
		 	    	 printf("RGBC data is not updated after last writing MODE_CONTROL1,2,3 register or last reading MODE_CONTROL2 register.");
		 	     }
}

void DINT_DATA (void)
{
int dataDINT = i2c_read(0x38, 0x58);
    printf("DINT_DATA_LBSs: 0x%02x \n", dataDINT);

    int dataDINT1 = i2c_read(0x38, 0x59);
    printf("DINT_DATA_MBSs: 0x%02x \n", dataDINT1);
}

void INTERRUPT_PIN_ENABLE (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_INTERRUPT, (1 << 0));

}

void INTERRUPT_PIN_DISABLE (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_INTERRUPT, (0 << 0));

}

void INT_SOURCE_RED_CHANNEL (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_INTERRUPT, (0 << 3) | (0 << 2));

}

void INT_SOURCE_GREEN_CHANNEL (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_INTERRUPT, (0 << 3) | (1 << 2));

}

void INT_SOURCE_BLUE_CHANNEL (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_INTERRUPT, (1 << 3) | (0 << 2));

}

void INT_SOURCE_CLEAR_CHANNEL (void)
{
	i2c_write(BH1745_SA_LOW , BH1745_INTERRUPT, (1 << 3) | (1 << 2));

}

void INT_LATCH_0 (void)
{
	// INT pin is latched until INTERRUPT register is read or initialized


	i2c_write(BH1745_SA_LOW , BH1745_INTERRUPT, (0 << 4));

}

void INT_LATCH_1 (void)
{
	// INT pin is updated after each measurement


	i2c_write(BH1745_SA_LOW , BH1745_INTERRUPT, (1 << 4));

}

void INTERRUPT_READ (void)
{
	int intread = i2c_read(BH1745_SA_LOW, BH1745_INTERRUPT);
		    printf("INTERRUPT  : 0x%02x \n", intread);

		    if((intread & 0x80) == 0x80)
		    {
		    	printf("Interrupt signal is active");
		    }else
		    {
		    	printf("Interrupt signal is inactive");
		    }

}


void MANUFACTURER_ID (void)
{
	 int ID = i2c_read(BH1745_SA_LOW, 0x92);
	    printf("MANUFACTURER_ID : 0x%02x \n", ID);
}

void RGB_DATA_FOR_READ(void)
{


	/* IF WE WANT TO READ RGBC
	 *
	 *       MODE_CONTROL_3:
	 *                      we have to write 0x02 in mode control 3
	 *
	 *              WE HAVE TO CALL THIS FUNCTION "   MODE_CONTROL3(); " BEFORE CALL " RGB_DATA_FOR_READ(); "
	 *
	 *        RGBC_ENABLE:
	 *                    we have to enable RGBC
	 *
	 *              WE HAVE TO CALL THIS FUNCTION "  RGBC_ENABLE ();" BEFORE CALL " RGB_DATA_FOR_READ(); "
	 *
	 */


	int data1 = i2c_read(0x38, 0x50);
   // printf("RED_DATA_LBS: 0x%02x \n", data1);

    int data2 = i2c_read(0x38, 0x51);
   // printf("RED_DATA_MBS: 0x%02x \n", data2);

    int data3 = i2c_read(0x38, 0x52);
   // printf("GREEN_DATA_LBS: 0x%02x \n", data3);

    int data4 = i2c_read(0x38, 0x53);
    //printf("GREEN_DATA_MBS: 0x%02x \n", data4);

    int data5 = i2c_read(0x38, 0x54);
   // printf("BLUE_DATA_LBS: 0x%02x \n", data5);

    int data6 = i2c_read(0x38, 0x55);
   // printf("BLUE_DATA_MBS: 0x%02x \n", data6);

    int data7 = i2c_read(0x38, 0x56);
   // printf("CLEAR_DATA_LBS: 0x%02x \n", data7);

    int data8 = i2c_read(0x38, 0x57);
   // printf("CLEAR_DATA_MBS: 0x%02x \n", data8);


    int red = ((data2 * 256 )+ data1);
	int green = ((data4 * 256) + data3);
   	int blue = ((data6 * 256 )+ data5);
   	int cData = ((data8 * 256 )+ data7);


  	printf("Red color luminance : %d lux \n", red);
   	printf("Green color luminance : %d lux \n", green);
    printf("Blue color luminance : %d lux \n", blue);
    printf("Clear Data  Luminance : %d lux \n ", cData);

}

