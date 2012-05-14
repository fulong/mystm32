/**
 *  \file	string.c
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-9 下午5:07:37
 */

#include "string.h"
/*
 * strlen
 *
 * works just like the library function
 */
INT32U strlen(INT8U * str)
{
	int len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return len;
}
void *memcpy(void *dest, const void *source, INT32U size)
{
	INT32U counter;
	for (counter = 0; counter < size; counter++)
	{
		*((INT8U *) dest + counter) = *((INT8U *) source + counter);
	}
	return (void *) 1;
}
/*
 * strncpy
 *
 * works just like the library function
 */
INT8U *strncpy(INT8U *str1, INT8U *str2, INT32U len)
{
	while (len-- && *str2)
	{
		*(str1++) = *(str2++);
	}
	*str1 = 0;
	return str1;
}
