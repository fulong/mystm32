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

#ifndef LIBMATH_H_
#define LIBMATH_H_
#include "../libc/cpu_typed.h"

#include "../user/user_configure/configure.h"

typedef unsigned char math_status;
typedef unsigned int uint32;
typedef unsigned char uint8;

extern math_status oct_transfer(uint32,INT8S *,const uint32);/*!< 将十进制变成二进制，并存在buf缓冲区中 */


#endif /* LIBMATH_H_ */
