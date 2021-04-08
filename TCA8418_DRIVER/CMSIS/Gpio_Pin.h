/*
 * Gpio_Pin.h
 *
 *  Created on: 08-Apr-2021
 *      Author: neevee
 */


#ifndef GPIO_PIN_H_
#define GPIO_PIN_H_

// Keypad IO Pins
#define ROW1  ((uint32_t)1 << 1)  // PTA1
#define ROW2  ((uint32_t)1 << 2)  // PTA2
#define ROW3  ((uint32_t)1 << 4)  // PTD4
#define ROW4  ((uint32_t)1 << 12)  // PTA12

#define COL4   ((uint32_t)1 << 4)  // PTA4
#define COL3   ((uint32_t)1 << 5)  // PTA5
#define COL2   ((uint32_t)1 << 8)  // PTC8
#define COL1     ((uint32_t)1 << 9)  // PTC9

#endif /* GPIO_PIN_H_ */



