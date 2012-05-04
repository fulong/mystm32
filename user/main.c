#include "./user_configure/include.h"
#include "../libc/libmath.h"
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
int
main(void)
{
#ifdef __DEBUG__
  volatile uint32_t i=100000;
  uint32_t volatile temp ;
  INT8U buf[32];
  printfs("now be in the main funtion\r\n\r\n");
  oct_transfer(i,buf,'b');
  printfs(buf);
  printfs("\r\n\r\n");
  oct_transfer(i,buf,'h');
  printfs(buf);
  printfs("\r\n\r\n");
  while(1){
      temp = get_sec();
      if(i != temp){
          oct_transfer(temp,buf,'h');
          printfs(buf);
          printfs("\r\n");
          i = temp;
      }
  }
#endif
  return 0;
}
