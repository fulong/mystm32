/*
 *  File name: 		systick.h
 *
 *  Created on: 	����11:14:09 2012-4-20 2012 
 *  Author: 		fulong
 *  Version: 		1.0
 *  Compiler: 		GCC
 *  Language: 		C/C++
 *  Mail:		fulong.mo@gmail.com
 *  Comment:
    
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "../stm32f103/STM32F10x/stm32f10x.h"

/*
select_int_or_tickenable:1,��?ʱ��
*/
#define systick_enable(tickenable)        SysTick->CTRL |= tickenable
/*
select_int_or_tickenable:1,��?ʱ���
*/
#define systick_disable(tickenable)       SysTick->CTRL &= (~(tickenable))

extern void systick_init(void);

#if SYSTICK_INT != 1
extern void delay_ms(u16 ms);
extern void delay_us(u32 us);
#endif

#endif /* SYSTICK_H_ */
