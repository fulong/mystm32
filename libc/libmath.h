/**
 *  \file	libmath.h
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-4-28 涓婂崍10:12:18
 */

#include "../user/user_configure/configure.h"
#ifndef LIBMATH_H_
#define LIBMATH_H_

typedef unsigned char math_status;
typedef unsigned int uint32;
typedef unsigned char uint8;

extern math_status oct_transfer(uint32,uint8 *,const uint32);/*!< 将十进制变成二进制，并存在buf缓冲区中 */


#endif /* LIBMATH_H_ */
