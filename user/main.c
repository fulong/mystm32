/*
 *  File name: 		main.c
 *
 *  Created on: 	����12:01:48 2012-4-20 2012 
 *  Author: 		fulong
 *  Version: 		1.0
 *  Compiler: 		GCC
 *  Language: 		C/C++
 *  Mail:		fulong.mo@gmail.com
 *  Comment:

 */
#include "../sysdev/usart.h"
int
main(void)
{
  while (1)
  USART1_Puts("hello\r\n");
  return 0;
}
