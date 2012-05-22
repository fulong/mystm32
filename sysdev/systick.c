#include "systick.h"
/**
 *  \file	systick.c
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       May 22, 2012 1:53:37 PM
 */

#define FCLK 72//MHz
#define HCLK 72//MHz
#ifndef SYSTICK_INT
INT32U delayUs;
INT32U delayMs;
#endif


void systick_init(void)
{
#ifdef SYSTICK_INT
	SysTick->CTRL &= 0xfffffff8; //bit2���,ѡ���ⲿʱ��  HCLK/8
	SysTick->LOAD = (u32) ((HCLK / 8) * 1000 * 10); //ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL = 0x00; //��ռ�����
#else
	SysTick->CTRL &= 0xFFFFFFFB; //bit2清空,选择外部时钟  HCLK/8
	delayUs = FCLK/8;
	delayMs = delayUs * 1000;
#endif
}
#ifndef SYSTICK_INT
/**
  * @brief  延时ms函数
  * @param  ms: 延时ms个单位
  *  这个参数可以取得到以下的值：\n
  *  	@arg
  * @retval
  * \date 2012-5-14 下午3:42:26
  * @note 对72M条件下,ms<=1864
  */
void delay_ms(u16 ms)
{
	SysTick->LOAD = ms * delayMs;
	SysTick->VAL  = 0x00;
	SysTick->CTRL = 0x01;
	while(!(SysTick->CTRL&(1<<16)));
	SysTick->CTRL = 0x00;
	SysTick->VAL  = 0x00;
}
/**
  * @brief  延时us函数
  * @param  us: 延时us个单位
  *  这个参数可以取得到以下的值：\n
  *  	@arg
  * @retval
  * \date 2012-5-14 下午3:38:36
  * @note 对72M条件下
  */
void delay_us(u32 us)
{
	SysTick->LOAD = us * delayUs;
	SysTick->VAL  = 0x00;
	SysTick->CTRL = 0x01;
	while(!(SysTick->CTRL&(1<<16)));
	SysTick->CTRL = 0x00;
	SysTick->VAL  = 0x00;
}
#endif
