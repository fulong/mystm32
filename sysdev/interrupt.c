/**
 *  \file     interrupt.c
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
#include "interrupt.h"
INT32U second = 0;
extern INT8U USART_length;

/**
 * @brief 使能systick中断，但这个时候systick还未有开始工作
 * @note 如果过早地开中断，可能会出现时钟不对
 * @param none
 * @retval none
 */
// Function body
void interrupt_open()
{
	USART_length = 0; //初始化串口中断发送的字符串长度
	systick_enable_int(1);
}
/**
 * @brief  设置NVIC分组
 * @param  NVIC_Group:  NVIC分组 0~4 总共5组
 * @retval none
 * \date 2012-5-8 下午3:25:04
 * @note
 */

void NVIC_PriorityGroupConfig(u8 NVIC_Group)
{
	u32 temp, temp1;
	temp1 = (~NVIC_Group) & 0x07; //取后三位
	temp1 <<= 8;
	temp = SCB->AIRCR; //读取先前的设置
	temp &= 0X0000F8FF; //清空先前分组
	temp |= 0X05FA0000; //写入钥匙
	temp |= temp1;
	SCB->AIRCR = temp; //设置分组
}
/**
 * @brief 设置NVIC
 * @param NVIC_PreemptionPriority: 抢占优先级
 * @param NVIC_SubPriority: 响应优先级
 * @param NVIC_Channel: 中断编号
 * @param NVIC_Group: 中断分组 0~4
 * @retval none
 * \date 2012-5-8 下午3:19:21
 * @note 注意优先级不能超过设定的组的范围!否则会有意想不到的错误\n
 组划分:\n
 组0:0位抢占优先级,4位响应优先级\n
 组1:1位抢占优先级,3位响应优先级\n
 组2:2位抢占优先级,2位响应优先级\n
 组3:3位抢占优先级,1位响应优先级\n
 组4:4位抢占优先级,0位响应优先级\n
 NVIC_SubPriority和NVIC_PreemptionPriority的原则是,数值越小,越优先
 *
 */
void nvic_group(u8 NVIC_PreemptionPriority, u8 NVIC_SubPriority,
		IRQn_Type NVIC_Channel, u8 NVIC_Group)
{
	u32 temp;
	NVIC_PriorityGroupConfig(NVIC_Group); //设置分组
	temp = NVIC_PreemptionPriority << (4 - NVIC_Group);
	temp |= NVIC_SubPriority & (0x0f >> NVIC_Group);
	temp &= 0xf; //取低四位

	if (NVIC_Channel < 32)
		NVIC->ISER[0] |= 1 << NVIC_Channel; //使能中断位(要清除的话,相反操作就OK)
	else
		NVIC->ISER[1] |= 1 << (NVIC_Channel - 32);
	NVIC->IP[NVIC_Channel] |= temp << 4; //设置响应优先级和抢断优先级

}
/**
 * @brief  NVIC初始化，设置中断组,中断初始化等等
 * @param  none
 * @retval none
 * \date 2012-5-8 下午3:05:38
 * @note
 */
void NVIC_Init(void)
{
//	interrupt_open();
	nvic_group(3, 3, USART1_IRQn, 2); //组2，最低优先级
}
/**
 * @brief  systick中断函数
 * @param none
 *  这个参数可以取得到以下的值：\n
 *  	@arg
 * @retval none
 * \date 2012-5-14 下午3:19:18
 * @note SYSTICK_INT宏来控制这个函数的状态。1，代表使用中断。否则，则不便宜
 */
#ifdef SYSTICK_INT
volatile INT32U counter = 0;
static BOOLEAN led_glitter = 0;
#endif
void systick_Handle(void)
{
#if SYSTICK_INT == 1
#ifdef __LED_H__
	if (counter == SEC)
	{
		if (led_glitter)
		{
			led_glitter = 0;
			LED1 = 0;
		}
		else
		{
			led_glitter = 1;
			LED1 = 1;
		}
	}
#endif
	if (counter == SEC) //时间达到一秒后，秒会自增
	{
		counter = 0;
		second++;
	}
	counter++;
#endif
}
/**
 * @brief 串口的中断函数
 * @param none
 * @retval none
 * \date 2012-5-8 下午4:00:54
 * @note
 */
void USART1_Handler(void)
{
}

