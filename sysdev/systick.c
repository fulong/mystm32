/*
 *  File name: 		systick.c
 *
 *  Created on: 	����11:09:12 2012-4-20 2012 
 *  Author: 		fulong
 *  Version: 		1.0
 *  Compiler: 		GCC
 *  Language: 		C/C++
 *  Mail:		fulong.mo@gmail.com
 *  Comment:

 */

#include "systick.h"
//---------------------------------------------------------
/*
 Function Name:                 systick_init
 ver 1.0
 first creat:			����11:19:04  2012-4-20
 final alternative:
 Parameters:
 In: 		                None.
 Out: 		                None.
 In/Out: 	                None.
 Return Values:		        None.
 Comments: 			��ʼ��systickʱ�ӣ�10ms����һ���ж�
 */

// Function body
#define HCLK 72//MHz
#define FCLK 72//MHz
#if SYSTICK_INT != 1
INT32U delayUs;
INT32U delayMs;
#endif

void systick_init(void)
{
#if SYSTICK_INT == 1
	SysTick->CTRL &= 0xfffffff8; //bit2���,ѡ���ⲿʱ��  HCLK/8
	SysTick->LOAD = (u32) ((HCLK / 8) * 1000 * 10); //ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL = 0x00; //��ռ�����
#else
	SysTick->CTRL &= 0xFFFFFFFB; //bit2清空,选择外部时钟  HCLK/8
	delayUs = FCLK/8;
	delayMs = delayUs * 1000;
#endif
}

// End Function Name
//---------------------------------------------------------
#if SYSTICK_INT != 1
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
