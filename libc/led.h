/*
 * led.h
 *
 *  Created on: Apr 23, 2012
 *      Author: fulong
 */

#ifndef LED_H_
#define LED_H_

#include "../stm32f103/STM32F10x/stm32f10x.h"
#include "../sysdev/sys.h"


#define LED0            PAout(8)// PA8

extern void LED_Init(void);

#endif /* LED_H_ */
