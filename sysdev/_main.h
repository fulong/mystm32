/**
 *  \file	_main.h
 *  \brief   进入用户程序时进行的一系列初始化.\n
 *
 *  \detail   文件只有一个初始化函数 _main\n
 *            包含着初始化时需要的头文件
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date      Apr 24, 2012 2:39:58 PM
 */


#ifndef MAIN_H_
#define MAIN_H_

#include "../sysdev/interrupt.h"
#include "../sysdev/systick.h"
#include "../sysdev/touch.h"
#include "../sysdev/tft.h"
#include "../sysdev/usart.h"
#include "../libc/led.h"

/*
 * \fn          void _main(void)
*/
extern void _main(void);/**<\brief     初始化串口，systick，开中断，初始化屏幕等等*/


#endif /* MAIN_H_ */
