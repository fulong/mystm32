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
int main(void)
{
#ifdef __DEBUG__
/*
	volatile uint32_t i = 100000;
	uint32_t volatile temp;
	INT8U buf[32];
*/
while(1)
{
	printfs("test\r\n");
	delay(1000,0);
}
/*
	printfs_int("\r\n\r\n");

	printfs_int("now be in the main funtion\r\n\r\n");
	oct_transfer(i, buf, 'b');
	printfs_int(buf);
	printfs_int("\r\n\r\n");
	oct_transfer(i, buf, 'h');
	printfs_int(buf);
	printfs_int("\r\n\r\n");
	temp = get_sec();
	printfs_int("time:");
	oct_transfer(temp, buf, 'h');
	printfs_int(buf);
	printfs_int("\r\n");
	while(get_sec() == temp);
	temp = get_sec();
	printfs_int("time1:");
	oct_transfer(temp, buf, 'h');
	printfs_int(buf);
	printfs_int("\r\n");
*/
#endif
	return 0;
}
