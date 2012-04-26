/**
 *  \file     led.h
 *  \brief   操作P口的led灯\n
 *
 *  \detail   目前只有使用PA8口上的LED
 *
 *
 *  \author     fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version:   1.0\n
 *  compiler:GCC\n
 *  \date      Apr 24, 2012 2:39:58 PM
 */

#ifndef LED_H_
#define LED_H_

#include "../stm32f103/STM32F10x/stm32f10x.h"
#include "../sysdev/sys.h"

#define LED0            PAout(8) /**< @brief  控制PA8口的输出，赋值1则输出高电平，0则为低电平*/
#define LED1            PDout(2) /**< @brief  控制PD2口的输出，赋值1则输出高电平，0则为低电平*/
/** @addtogroup 函数
 * @{
 */
/** @addtogroup libc
 * @{
 * @brief libc文件夹中的函数
 */
extern void LED_Init(void); /**< @brief 初始化连接到LED的P口，使他们都输出高电平*/
/**@}*/

/**@}*/
#endif /* LED_H_ */
