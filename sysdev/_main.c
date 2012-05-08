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
  USART_Configuration(USART1);
#ifdef __DEBUG__
  printfs("success to finish usart Configuration!\r\n\r\n");
#endif
  LED_Init();
#ifdef __DEBUG__
  printfs("success to finish the led screen initiation!\r\n\r\n");
#endif
  systick_init();
#ifdef __DEBUG__
  printfs("success to finish the systick initiation!\r\n\r\n");
#endif
  tft_init();
#ifdef __DEBUG__
  printfs("success to finish the tft screen initiation!\r\n\r\n");
#endif
  touch_init();
#ifdef __DEBUG__
  printfs("success to finish the touch initiation!\r\n\r\n");
#endif
  NVIC_Init();
#ifdef __DEBUG__
  printfs("success to open the interrupt!(including systick's interrupt)\r\n\r\n");
#endif
  systick_enable(1);//systick定时器启动
#ifdef __DEBUG__
  printfs("success to start the systick!\r\n\r\n");
#endif
}

// End Function Name
//---------------------------------------------------------

