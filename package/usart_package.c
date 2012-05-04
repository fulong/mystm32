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

#ifdef __DEBUG__
/**
  * @brief  利用串口打印一字符串
  * @param  str ：打印的目标字符串，打印时使用了轮询的方式。
  * @retval none
  */
void printfs(INT8 * str)
{
while(*str)
{
USART_SendData(USART1, *str++);
/* Loop until the end of transmission */
while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
}


#endif
