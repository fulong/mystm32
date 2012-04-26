/**
 *  \file	_main.c
 *  \brief      详细可看_main.h
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       上午11:33:22 2012-4-20
 */
#include "_main.h"
//---------------------------------------------------------
/*
 * \fn          void _main(void)
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
_main(void)
{
  systick_init();
  usart1_init();
  tft_init();
  touch_init();
  interrupt_open();
  LED_Init();
  systick_enable(1);//systick定时器启动
}

// End Function Name
//---------------------------------------------------------

