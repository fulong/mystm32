/**
 *  \file     led.c
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

#include "led.h"
#include "gpio.h"
#include "rcc.h"
/**
 * @brief 初始化连接到LED的P口（PA8与PD2），使他们都输出高电平
 * @note 在使用GPIO作为输入输出的时候，要先设置好端口频率，这时初始化端口工作频率。
 * @param none
 * @retval none
 */
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	set_io(GPIOD, GPIO_Mode_Out_PP, GPIO_Pin_13 | GPIO_Pin_6 | GPIO_Pin_12, GPIO_Speed_50MHz);
	LED1 = 0 ;
	LED2 = 0 ;
	LED3 = 0 ;
}

