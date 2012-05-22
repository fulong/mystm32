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

#include "../sysdev/usart.h"
#include "../libc/libmath.h"
#include "usart_package.h"
#ifdef __DEBUG__
/**
 * @brief  利用串口打印一字符串
 * @param  str ：打印的目标字符串，打印时使用了轮询的方式。
 * @retval none
 */
void printfs(const INT8S* str)
{
	while(*str)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
			;
		USART_SendData(USART1,*str++);
	}
}
/**
  * @brief  打印数字，但不能打印10进制的，可以选择两种进制进行输出，16与2进制。
  * @param  disnum: 源数字，要输出转换的。
  * @param  hex_or_bin: 进制的转换选择
  *  这个参数可以取得到以下的值：\n
  *  	@arg 'h': 代表转换成16进制
  *  	@arg 'b': 代表转换成2进制
  * @retval
  * \date 2012-5-18 下午5:27:25
  * @note
  */

void printf_num(INT32U disnum,INT8U hex_or_bin)
{
 INT8S buf[32];
 oct_transfer(disnum,buf,hex_or_bin);
 printfs(buf);
}
#endif
