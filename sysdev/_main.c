/*
 *  File name: 		_main.c
 *
 *  Created on: 	����11:33:22 2012-4-20 2012 
 *  Author: 		fulong
 *  Version: 		1.0
 *  Compiler: 		GCC
 *  Language: 		C/C++
 *  Mail:		fulong.mo@gmail.com
 *  Comment:

 */
#include "../sysdev/interrupt.h"
#include "../sysdev/systick.h"
#include "../sysdev/touch.h"
#include "../sysdev/tft.h"
#include "../sysdev/usart.h"
#include "../libc/led.h"

//---------------------------------------------------------
/*
 Function Name:
 ver 1.0
 first creat:			����11:33:38  2012-4-20
 final alternative:
 Parameters:
 In: 		None.
 Out: 		None.
 In/Out: 	None.
 Return Values:		None.
 Comments: 			This is a comment of function template
 */

// Function body
void
_main()
{
  systick_init();
  usart_init();
  tft_init();
  touch_init();
  interrupt_open();
  LED_Init();
  systick_enable(1);//systick�жϺͶ�ʱ������
}

// End Function Name
//---------------------------------------------------------

