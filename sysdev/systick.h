/**
 *  \file	systick.h
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       May 22, 2012 1:53:53 PM
 */


#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "../stm32f103/STM32F10x/stm32f10x.h"


extern void systick_init(void);

#ifndef SYSTICK_INT
extern void delay_ms(u16 ms);
extern void delay_us(u32 us);
#endif



#endif /* SYSTICK_H_ */
