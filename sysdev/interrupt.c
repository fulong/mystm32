/*
 *  File name: 		interrupt.c
 *
 *  Created on: 	ионГ11:41:37 2012-4-20 2012 
 *  Author: 		fulong
 *  Version: 		1.0
 *  Compiler: 		GCC
 *  Language: 		C/C++
 *  Mail:		fulong.mo@gmail.com
 *  Comment:

 */
#include "interrupt.h"
#include "../libc/led.h"
#include "../libc/debug.h"


//---------------------------------------------------------
/*
 Function Name:
 ver 1.0
 first creat:			ионГ11:47:05  2012-4-20
 final alternative:
 Parameters:
   In: 		        None.
   Out: 		        None.
   In/Out: 	        None.
   Return Values:		None.
 Comments:
 */

// Function body
void
interrupt_open()
{
  systick_enable_int(1);
}

// End Function Name
//---------------------------------------------------------
#ifdef __DEBUG__
static volatile unsigned char i=0;
#endif
void systick_Handle(void)
{
  if(i < 100)
    {
      i++;
      LED0 = 0;
    }
  else
    {
      i++;
      if(i == 200)i=0;
      LED0 = 1;
    }
}
