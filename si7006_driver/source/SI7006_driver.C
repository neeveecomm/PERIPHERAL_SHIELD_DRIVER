/*
 * SI7006_driver.C
 *
 *  Created on: 25-Mar-2021
 *      Author: neevee
 */

void MEASURE_RELATIVE_HUMIDITY_HOLD_MASTER_MODE (void)
 {
	 uint32_t data1;
	 uint32_t data2;

	 // Send Relative humidity measurement command,  HOLD MASTER(0xE5)

	 		i2c_write1(SI7006_ADDRESS, SI7006_MEASURE_RELATIVE_HUMIDITY_HOLD_MASTER_MODE);



	 // Read 2 bytes of humidity data

	 // humidity msb, humidity lsb

	 		data1 = i2c_read1(SI7006_ADDRESS);
	        data2 = i2c_read1(SI7006_ADDRESS);

	 		//printf("data1 : 0x%02x\n",data1);
	 		//printf("data2 : 0x%02x\n",data2);

	 // Convert the data

	 			int humidity = ((((data1 * 256 )+ data2) * 125) / 65536) - 6;

	 // Output data to screen
                printf("FOR HOLD MASTER MODE\n");
	 			printf("Relative Humidity : %02d percentage\n", humidity);


 }

 void MEASURE_TEMPERATURE_HOLD_MASTER_MODE (void)
 {
	 uint32_t data3;
     uint32_t data4;
	 // Send temperature measurement command, NO HOLD MASTER(0xF3)

	 		i2c_write1(SI7006_ADDRESS, SI7006_MEASURE_TEMPERATURE_HOLD_MASTER_MODE);



	 // Read 2 bytes of temperature data

	 // humidity msb, humidity lsb


	 	         data3 =	i2c_read1(SI7006_ADDRESS);
	 	         data4 =	i2c_read1(SI7006_ADDRESS);

	 	        //printf("data3 : 0x%02x\n",data3);
	 	        //printf("data4 : 0x%02x\n",data4);


	 // Convert the data

	 			int cTemp = ((((data3 * 256) + data4) * 175.72) / 65536) - 46.85;
	 			int fTemp = ( cTemp * 1.8 )+ 32;

	 // Output data to screen
	 			printf("FOR HOLD MASTER MODE\n");
	 			printf("Temperature in Celsius : %02d C \n", cTemp);
	 			printf("Temperature in Fahrenheit : %02d F \n", fTemp);


 }





 void MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE (void)
 {
	 uint32_t data1;
	 uint32_t data2;

	 // Send Relative humidity measurement command, NO HOLD MASTER(0xF5)

	 		i2c_write1(SI7006_ADDRESS, SI7006_MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE);

	 // for time delay

	     DelayCount = 100000;
	      Delay ();


	 // Read 2 bytes of humidity data

	 // humidity msb, humidity lsb

	 		data1 = i2c_read1(SI7006_ADDRESS);
	        data2 = i2c_read1(SI7006_ADDRESS);

	 		//printf("data1 : 0x%02x\n",data1);
	 		//printf("data2 : 0x%02x\n",data2);

	 // Convert the data

	 			 int humidity = ((((data1 * 256 )+ data2) * 125) / 65536) - 6;



	 // Output data to screen
	 			printf("FOR NO HOLD MASTER MODE\n");
	 			printf("Relative Humidity : %02d percentage\n", humidity);


 }

 void MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE (void)
 {
	 uint32_t data3;
     uint32_t data4;

	 // Send temperature measurement command, NO HOLD MASTER(0xF3)

	 		i2c_write1(SI7006_ADDRESS, SI7006_MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE);

	 // For time delay

	 		 DelayCount = 100000;
	 		 Delay ();


	 // Read 2 bytes of temperature data

	 // humidity msb, humidity lsb


	 	         data3 =	i2c_read1(SI7006_ADDRESS);
	 	         data4 =	i2c_read1(SI7006_ADDRESS);

	 	        //printf("data3 : 0x%02x\n",data3);
	 	        //printf("data4 : 0x%02x\n",data4);


	 // Convert the data

	 			int cTemp = ((((data3 * 256) + data4) * 175.72) / 65536) - 46.85;
	 			int fTemp = ( cTemp * 1.8 )+ 32;

	 // Output data to screen
	 			printf("FOR NO HOLD MASTER MODE\n");
	 			printf("Temperature in Celsius : %02d C \n", cTemp);
	 			printf("Temperature in Fahrenheit : %02d F \n", fTemp);


 }



 void RESET_USER_REGISTER1 (void)
 {

	 i2c_write(SI7006_ADDRESS, SI7006_WRITE_RH_T_USER_REGISTER_1, 0x3A);

	 uint32_t data10;

	 	 data10 = i2c_read(SI7006_ADDRESS, SI7006_READ_RH_T_USER_REGISTER_1 );

	 	      //printf("data7 : 0x%02x\n",data10);

	 	  if(data10  == (0x3A| 0x00))
	 	  {
	 		  printf("RESET_USER REGISTER1 SUCCESSFULLY\n");
	 	  }
	 	  else
	 	  {
	 		  printf("RESET_USER REGISTER1 NOT SUCCESSFULLY\n");
	 	  }



 }

 void RESET (void)
 {
	 i2c_write1(SI7006_ADDRESS,  SI7006_RESET);
	 printf("RESET SUCCESSFULLY\n");
 }


 void  READ_TEMPERATURE_VALUE_FROM_PREVIOUS_RH_MEASUREMENT (void)
 {
	 uint32_t data5;
	 uint32_t data6;
      data5 = i2c_read(SI7006_ADDRESS, SI7006_READ_TEMPERATURE_VALUE_FROM_PREVIOUS_RH_MEASUREMENT);
      data6 = i2c_read(SI7006_ADDRESS, SI7006_READ_TEMPERATURE_VALUE_FROM_PREVIOUS_RH_MEASUREMENT);

      //printf("data5 : 0x%02x\n",data5);
      //printf("data6 : 0x%02x\n",data6);
      // Convert the data

     	 			int cTemp = ((((data5 * 256) + data6) * 175.72) / 65536) - 46.85;
     	 			int fTemp = ( cTemp * 1.8 )+ 32;

     	 // Output data to screen

     	 			printf("Temperature value from previous RH measurement in Celsius : %02d C \n", cTemp);
     	 			printf("Temperature value from previous RH measurement in Fahrenheit : %02d F \n", fTemp);

 }

void RESOLUTION_RH_11_TEMP_11 (void)
{
	i2c_write(SI7006_ADDRESS, SI7006_WRITE_RH_T_USER_REGISTER_1  , (1 << 7) | (1 << 0));

	uint32_t data11;

		 data11 = i2c_read(SI7006_ADDRESS, SI7006_READ_RH_T_USER_REGISTER_1 );

		      //printf("data11 : 0x%02x\n",data11);

		  if((data11 & 0x81) == 0x81)
		  {
			  printf("RESOLUTION_RH_11_TEMP_11 IS SET\n");
		  }
		  else
		  {
			  printf("RESOLUTION_RH_11_TEMP_11 IS NOT SET\n");
		  }

}

void RESOLUTION_RH_12_TEMP_14  (void)
{
	i2c_write(SI7006_ADDRESS, SI7006_WRITE_RH_T_USER_REGISTER_1  , (0 << 7) | (0 << 0));

	uint32_t data12;

			 data12 = i2c_read(SI7006_ADDRESS, SI7006_READ_RH_T_USER_REGISTER_1 );

			      //printf("data12 : 0x%02x\n",data12);

			  if((data12 & 0x3A) == 0x3A)
			  {
				  printf("RESOLUTION_RH_12_TEMP_14 IS SET\n");
			  }
			  else
			  {
				  printf("RESOLUTION_RH_12_TEMP_14 IS NOT SET\n");
			  }
}

void RESOLUTION_RH_8_TEMP_12  (void)
{
	i2c_write(SI7006_ADDRESS, SI7006_WRITE_RH_T_USER_REGISTER_1  , (0 << 7) | (1 << 0));

	uint32_t data13;

			 data13 = i2c_read(SI7006_ADDRESS, SI7006_READ_RH_T_USER_REGISTER_1 );

			     // printf("data13 : 0x%02x\n",data13);

			  if((data13 & 0x3B) == 0x3B)
			  {
				  printf("RESOLUTION_RH_8_TEMP_12 IS SET\n");
			  }
			  else
			  {
				  printf("RESOLUTION_RH_8_TEMP_12 IS NOT SET\n");
			  }
}

void RESOLUTION_RH_10_TEMP_13  (void)
{
	i2c_write(SI7006_ADDRESS, SI7006_WRITE_RH_T_USER_REGISTER_1  , (1 << 7) | (0 << 0));

	uint32_t data14;

			 data14 = i2c_read(SI7006_ADDRESS, SI7006_READ_RH_T_USER_REGISTER_1 );

			    //  printf("data14 : 0x%02x\n",data14);

			  if((data14 & 0xBA) == 0xBA)
			  {
				  printf("RESOLUTION_RH_10_TEMP_13 IS SET\n");
			  }
			  else
			  {
				  printf("RESOLUTION_RH_10_TEMP_13 IS NOT SET\n");
			  }
}

void VDD (void)
{

	uint32_t data7;

	 data7 = i2c_read(SI7006_ADDRESS, SI7006_READ_RH_T_USER_REGISTER_1 );

	    //  printf("data7 : 0x%02x\n",data7);

	  if((data7 & 0x40) == 0x40)
	  {
		  printf("VDD IS LOW\n");
	  }
	  else
	  {
		  printf("VDD IS OK\n");
	  }
}

void HEATER_ENABLED (void)
{
	uint32_t data8;

	i2c_write(SI7006_ADDRESS, SI7006_WRITE_RH_T_USER_REGISTER_1  , (1 << 2));

	 data8 = i2c_read(SI7006_ADDRESS, SI7006_READ_RH_T_USER_REGISTER_1 );

	// printf("data : 0x%02x\n",data8);

		     if((data8 & 0x3E) == 0x3E)
		     {
		    	 printf("HEATER ENABLED SUCCESSFULLY\n");
		     }
		     else
		     {
		    	 printf("HEATER NOT ENABLED\n");
		     }
}

void  HEATER_DISABLED (void)
{
	uint32_t data9;

	i2c_write(SI7006_ADDRESS, SI7006_WRITE_RH_T_USER_REGISTER_1  , (0 << 2));

	data9 = i2c_read(SI7006_ADDRESS, SI7006_READ_RH_T_USER_REGISTER_1 );

	 //printf("data9 : 0x%02x\n",data9);

	    if((data9 & 0x3A) == 0x3A)
			     {
			    	 printf("HEATER DISABLED SUCCESSFULLY\n");
			     }
			     else
			     {
			    	 printf("HEATER NOT DISABLED\n");
			     }

	}

void HEATER_CURRENT_3mA (void)
		{
           uint32_t datah1;

		i2c_write(SI7006_ADDRESS, SI7006_WRITE_HEATER_CONTROL_REGISTER, 0x00);

		datah1 = i2c_read(SI7006_ADDRESS,  SI7006_READ_HEATER_CONTROL_REGISTER);

		if(datah1 == 0x00)
		{
          printf("HEATER CURRENT IS 3.09mA\n");
		}
		else
		{
			printf("HEATER CURRENT IS NOT 3,09mA\n");
		}
	}
void HEATER_CURRENT_9mA (void)
		{
	 uint32_t datah2;

		i2c_write(SI7006_ADDRESS, SI7006_WRITE_HEATER_CONTROL_REGISTER, 0x01);

		datah2 = i2c_read(SI7006_ADDRESS,  SI7006_READ_HEATER_CONTROL_REGISTER);

				if(datah2 == 0x01)
				{
		          printf("HEATER CURRENT IS 9.18mA\n");
				}
				else
				{
					printf("HEATER CURRENT IS NOT 9.18mA\n");
				}


		}

void HEATER_CURRENT_15mA (void)
		{
	uint32_t datah3;

		i2c_write(SI7006_ADDRESS, SI7006_WRITE_HEATER_CONTROL_REGISTER, 0x02);

		datah3 = i2c_read(SI7006_ADDRESS,  SI7006_READ_HEATER_CONTROL_REGISTER);

				if(datah3 == 0x02)
				{
		          printf("HEATER CURRENT IS 15.24mA\n");
				}
				else
				{
					printf("HEATER CURRENT IS NOT 15.24mA\n");
				}


		}

void HEATER_CURRENT_27mA (void)
		{
	uint32_t datah4;

		i2c_write(SI7006_ADDRESS, SI7006_WRITE_HEATER_CONTROL_REGISTER, 0x04);

		datah4 = i2c_read(SI7006_ADDRESS,  SI7006_READ_HEATER_CONTROL_REGISTER);

				if(datah4 == 0x04)
				{
		          printf("HEATER CURRENT IS 27.39mA\n");
				}
				else
				{
					printf("HEATER CURRENT IS NOT 27.39mA\n");
				}


		}

void HEATER_CURRENT_51mA (void)
		{


	uint32_t datah5;


		i2c_write(SI7006_ADDRESS, SI7006_WRITE_HEATER_CONTROL_REGISTER, 0x08);


		datah5 = i2c_read(SI7006_ADDRESS,  SI7006_READ_HEATER_CONTROL_REGISTER);

				if(datah5 == 0x08)
				{
		          printf("HEATER CURRENT IS 51.69mA\n");
				}
				else
				{
					printf("HEATER CURRENT IS NOT 51.69mA\n");
				}


		}

void HEATER_CURRENT_94mA (void)
		{
	    uint32_t datah6;

		i2c_write(SI7006_ADDRESS, SI7006_WRITE_HEATER_CONTROL_REGISTER, 0x0F);


		datah6 = i2c_read(SI7006_ADDRESS,  SI7006_READ_HEATER_CONTROL_REGISTER);

				if(datah6 == 0x0F)
				{
		          printf("HEATER CURRENT IS 94.20mA\n");
				}
				else
				{
					printf("HEATER CURRENT IS NOT 94.20mA\n");
				}

		}

void READ_ELECTRONIC_ID_FIRST_BYTE_CMD (void)
{
	i2c_write(SI7006_ADDRESS, 0xFA, 0x0F);

	uint32_t data10;
	data10 = i2c_read1(SI7006_ADDRESS);

				      printf("ELECTRONIC ID FIRST BYTE : 0x%02x\n",data10);
		}
void READ_ELECTRONIC_ID_SECOND_BYTE_CMD (void)
{
	i2c_write(SI7006_ADDRESS, 0xFC, 0xC9);

	uint32_t data11;

	data11 = i2c_read1(SI7006_ADDRESS);


				      if(data11 == 0x06)
				      {
				    	  printf("SI7006\n");
				      }
		}

void  READ_FIRMWARE_VERSION_CMD    (void)
{
	i2c_write(SI7006_ADDRESS, 0x84, 0xB8);


	uint32_t data14;
	data14 = i2c_read1(SI7006_ADDRESS);


		 if (data14 == 0x20)
		 {
			 printf("FIRMWARE VERSION 2.0\n");
		 }
		 if(data14 == 0xFF)
		 {
			 printf("FIRMWARE VERSION 1.0\n");
		 }
		}

