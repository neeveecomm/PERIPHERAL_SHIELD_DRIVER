/*
 * TCA8418_GPIO.C
 *
 *  Created on: 05-Apr-2021
 *      Author: neevee
 */


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include <stdint.h>
#include "mkl25z4.h"
#include "Gpio_Pin.h"


/* IF you want to change gpio pin , you have to change port and pin in header file " Gpio_Pin.h"
 * */

/*  KEYPAD  4X4  MATRIX _  GPIO DRIVER */

static void search_col1(void);
static void search_col2(void);
static void search_col3(void);
static void search_col4(void);




void keypad_scan(void)
{

		GPIOA->PDOR &= (~ROW1 & ~ROW2 & ~ROW4);
		GPIOD->PDOR &= (~ROW3);

		if ((GPIOC->PDIR & COL1) == 0)
		{

			search_col1();
		}
		else if ((GPIOC->PDIR & COL2) == 1)
		{

			search_col2();
		}
		else if ((GPIOA->PDIR & COL3) == 1)
		{

			search_col3();
		}
		else if ((GPIOA->PDIR & COL4) == 1)
		{

			search_col4();
		}
		else
		{
			// col exit
		}
}




static void search_col1(void)
{

	GPIOA->PDOR &= (~ROW1);
	GPIOA->PDOR |= (ROW2 | ROW4);
	GPIOD->PDOR |= (ROW3);

	if ((GPIOC->PDIR & COL1) == 0)
	{

      printf("1");
		return;
	}


	GPIOA->PDOR &= (~ROW2);
	GPIOA->PDOR |= (ROW1 | ROW4);
	GPIOD->PDOR |= (ROW3);

	if ((GPIOC->PDIR & COL1) == 1)
	{

		printf("4");
		return;
	}


	GPIOD->PDOR &= (~ROW3);
	GPIOA->PDOR |= (ROW1 | ROW2 | ROW4);

	if ((GPIOC->PDIR & COL1) == 1)
	{

		printf("7");
		return;
	}


	GPIOA->PDOR &= (~ROW4);
	GPIOA->PDOR |= (ROW1 | ROW2);
	GPIOD->PDOR |= (ROW3);

	if ((GPIOC->PDIR & COL1) == 1)
	{

		printf("*");
	}
}



static void search_col2(void)
{

	GPIOA->PDOR &= (~ROW1);
	GPIOA->PDOR |= (ROW2 | ROW4);
	GPIOD->PDOR |= (ROW3);


	if ((GPIOC->PDIR & COL2) == 1)
	{

	printf("2");
		return;
	}


	GPIOA->PDOR &= (~ROW2);
	GPIOA->PDOR |= (ROW1 | ROW4);
	GPIOD->PDOR |= (ROW3);

	if ((GPIOC->PDIR & COL2) == 1)
	{

		printf("5");
		return;
	}


	GPIOD->PDOR &= (~ROW3);
	GPIOA->PDOR |= (ROW1 | ROW2 | ROW4);

	if ((GPIOC->PDIR & COL2) == 1)
	{

		printf("8");
	   return;
	}


	GPIOA->PDOR &= (~ROW4);
	GPIOA->PDOR |= (ROW1 | ROW2);
	GPIOD->PDOR |= (ROW3);

	if ((GPIOC->PDIR & COL2) == 1)
	{

		printf("0");
	}
}



static void search_col3(void)
{

	GPIOA->PDOR &= (~ROW1);
	GPIOA->PDOR |= (ROW2 | ROW4);
	GPIOD->PDOR |= (ROW3);


	if ((GPIOA->PDIR & COL3) == 1)
	{

		printf("3");
		return;
	}


	GPIOA->PDOR &= (~ROW2);
	GPIOA->PDOR |= (ROW1 | ROW4);
	GPIOD->PDOR |= (ROW3);

	if ((GPIOA->PDIR & COL3) == 1)
	{

		printf("6");
		return;
	}


	GPIOD->PDOR &= (~ROW3);
	GPIOA->PDOR |= (ROW1 | ROW2 | ROW4);

	if ((GPIOA->PDIR & COL3) == 1)
	{

		printf("9");
		return;
	}


	GPIOA->PDOR &= (~ROW4);
	GPIOA->PDOR |= (ROW1 | ROW2);
	GPIOD->PDOR |= (ROW3);

	if ((GPIOA->PDIR & COL3) == 1)
	{

		printf("#");
	}
}



static void search_col4(void)
{

	GPIOA->PDOR &= (~ROW1);
	GPIOA->PDOR |= (ROW2 | ROW4);
	GPIOD->PDOR |= (ROW3);


	if ((GPIOA->PDIR & COL4) == 1)
	{

		printf("A");
		return;
	}


	GPIOA->PDOR &= (~ROW2);
	GPIOA->PDOR |= (ROW1 | ROW4);
	GPIOD->PDOR |= (ROW3);

	if ((GPIOA->PDIR & COL4) == 1)
	{

		printf("B");
		return;
	}


	GPIOD->PDOR &= (~ROW3);
	GPIOA->PDOR |= (ROW1 | ROW2 | ROW4);

	if ((GPIOA->PDIR & COL4) == 1)
	{

		printf("C");
		return;
	}


	GPIOA->PDOR &= (~ROW4);
	GPIOA->PDOR |= (ROW1 | ROW2);
	GPIOD->PDOR |= (ROW3);

	if ((GPIOA->PDIR & COL4) == 1)
	{

		printf("D");
	}
}




int main (){


	while(1)

	{

	 keypad_scan();

	 search_col1();
	 search_col2();
     search_col3();
     search_col4();

	}

}

