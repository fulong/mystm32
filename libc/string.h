/**
 *  \file	string.h
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-9 下午5:08:11
 */

#ifndef STRING_H_
#define STRING_H_

#include "../user/user_configure/configure.h"
#include "../libc/cpu_typed.h"

extern INT32U strlen(INT8U * str);
extern void *memcpy(void *dest, const void *source, INT32U size);
extern INT8U *strncpy(INT8U *str1, INT8U *str2, INT32U len);

#endif /* STRING_H_ */
