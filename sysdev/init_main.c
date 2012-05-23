/**
 *  \file	_main.c
 *  \brief  初始化设备，包括串口，tft，systick，touch等等
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-21 下午5:25:11
 */
#include "../chip/ssd1963.h"
#include "tft.h"
#include "systick.h"
#include "rcc.h"
#include "usart.h"
#include "gpio.h"
#include "../package/usart_package.h"
/**
 * @brief  初始化串口1，LED灯的端口
 * @param	none
 *  这个参数可以取得到以下的值：\n
 *  	@arg
 * @retval none
 * \date May 22, 2012 2:13:25 PM
 * @note
 */

void LED_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD
					| RCC_APB2Periph_GPIOE | RCC_APB2Periph_USART1, ENABLE); /* 使能各个端口时钟，重要！！！*/

	/* Configure IO connected to LD1, LD2 and LD3  leds *********************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Configure IO connected to KEY1 *********************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configure USART1 Tx (PA9) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Rx (PA10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/**
 * @brief 配置串口
 * @param USARTx： 将要配置的串口
 *  这个参数可以取得到以下的值：\n
 *  	@arg USART1
 *  	@arg USART2
 *  	@arg USART3
 * @retval none
 * \date May 22, 2012 2:14:35 PM
 * @note
 */
void USART_Configuration(USART_TypeDef* USARTx)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200; //波特率115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No; //无
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTx, &USART_InitStructure);
	USART_Cmd(USARTx, ENABLE);
}
void _main(void)
{
	LED_GPIO_Configuration();
	USART_Configuration(USART1);
#ifdef __DEBUG__
	printfs("this is in init fuction.\r\n");
	printfs("usart1's initation is compelete.\r\n");
	printfs("three lights can bright.\r\n");
#endif
	systick_init();
#ifdef __DEBUG__
	printfs("system ticket clock's initation is compelete.\r\n");
	printfs("\r\n");
	printfs("now into the tft's initation.\r\n");
#endif
	LCD_Init();
	set_orgin(120, 120);
}

