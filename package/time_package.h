/**
 *  \file	time_package.h
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-3 下午1:40:19
 */


#ifndef TIME_PACKAGE_H_
#define TIME_PACKAGE_H_

#include "../user/user_configure/cpu_typed.h"

extern INT32U get_sec(void);/*!< 取得函数运行的秒数 */
extern INT32U get_ms(void);/*!< 取得函数运行的毫秒数 */
extern void delay(INT8U ms);/*!< 延时ms*10毫秒，不是准确延时，误差在10MS以下 */

#endif /* TIME_PACKAGE_H_ */
