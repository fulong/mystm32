/**
 *  \file       usart_package.h
 *  \brief      对usart子函数打包成所需要的功能函数供main函数使用
 *
 *  \author     fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version:   1.0\n
 *  compiler:GCC\n
 *  \date      Apr 23, 2012 6:06:29 PM
 */

#ifndef DEBUG_H_
#define DEBUG_H_
#include "../sysdev/usart.h"

extern void printfs(INT8 * str);/*!< 利用串口打印一字符串 */

#endif /* DEBUG_H_ */
