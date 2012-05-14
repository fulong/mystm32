/**
 *  \file       usart_package.c
 *  \brief      对usart子函数打包成所需要的功能函数供main函数使用
 *
 *  \author     fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version:   1.0\n
 *  compiler:GCC\n
 *  \date      Apr 23, 2012 6:06:29 PM
 */

#include "usart_package.h"

extern INT8U* TX_buf_bp;//在commucaion.C中
extern INT8U TX_buf[64];//在commucaion.C中

#ifdef __DEBUG__
/**
 * @brief  利用串口打印一字符串
 * @param  str ：打印的目标字符串，打印时使用了轮询的方式。
 * @retval none
 */
void printfs(INT8 * str)
{
	while (*str)
	{
		USART_SendData(USART1, *str++);
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
			;
	}
}
/**
 * @brief  利用串口打印一字符串
 * @param str ：打印的目标字符串，打印时使用了轮询的方式。
 * @retval none
 * \date 2012-5-8 下午4:11:00
 * @note 与printfs函数不同，这个函数是用在开串口中断的情况下
 */
INT32U printfs_int(INT8 * str)
{
	if(USART_length == 0)
	{
		INT32U i;
		i = strlen(str);
		strncpy(TX_buf,str,i);
		TX_buf_bp = TX_buf;
		USART_length = i ;
		USARTx_IT_Configure(USART1, USART_FLAG_TXE_INT
								   ,ENABLE);
	}
	return USART_length;
}
#endif
