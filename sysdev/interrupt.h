/**
 *  \file     interrupt.h
 *  \brief    对中断进行初始化\n
 *
 *  \detail   1.使能systick中断，但这个时候systick还未有开始工作
 *
 *
 *  \author     fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version:   1.0\n
 *  compiler:GCC\n
 *  \date      Apr 24, 2012 2:39:58 PM
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "../stm32f103/STM32F10x/stm32f10x.h"
#include "led.h"


#define systick_enable_int(tickenable)        SysTick->CTRL |= (tickenable << 1)

#define SEC                                   (100)

/*
select_int_or_tickenable:1,��?ʱ����
*/
#define systick_disable_int(tickenable)       SysTick->CTRL &= (~(tickenable << 1))

/** @addtogroup 函数
 * @{
 */
/** @addtogroup sysdev
 * @{
 * @brief sysdev文件夹的函数
 */
extern void interrupt_open();

/**@}*/
/**@}*/


#endif /* INTERRUPT_H_ */
