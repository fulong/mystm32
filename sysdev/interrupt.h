/*
 *  File name: 		interrupt.h
 *
 *  Created on: 	上午11:39:24 2012-4-20 2012 
 *  Author: 		fulong
 *  Version: 		1.0
 *  Compiler: 		GCC
 *  Language: 		C/C++
 *  Mail:		fulong.mo@gmail.com
 *  Comment:
    
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "../stm32f103/STM32F10x/stm32f10x.h"

/*
select_int_or_tickenable:1,代表定时器开
*/
#define systick_enable_int(tickenable)        SysTick->CTRL |= (tickenable << 1)
/*
select_int_or_tickenable:1,代表定时器关
*/
#define systick_disable_int(tickenable)       SysTick->CTRL &= (~(tickenable << 1))

extern void interrupt_open();



#endif /* INTERRUPT_H_ */
