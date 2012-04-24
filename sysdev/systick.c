/*
 *  File name: 		systick.c
 *
 *  Created on: 	����11:09:12 2012-4-20 2012 
 *  Author: 		fulong
 *  Version: 		1.0
 *  Compiler: 		GCC
 *  Language: 		C/C++
 *  Mail:		fulong.mo@gmail.com
 *  Comment:
    
 */


#include "systick.h"
//---------------------------------------------------------
/*
 Function Name:                 systick_init
 ver 1.0
 first creat:			����11:19:04  2012-4-20
 final alternative:
 Parameters:
 In: 		                None.
 Out: 		                None.
 In/Out: 	                None.
 Return Values:		        None.
 Comments: 			��ʼ��systickʱ�ӣ�10ms����һ���ж�
 */

// Function body
#define HCLK 72//MHz

void
systick_init(void)
{
  SysTick->CTRL &= 0xfffffff8; //bit2���,ѡ���ⲿʱ��  HCLK/8
  SysTick->LOAD = (u32) ((HCLK/8) * 1000 * 10); //ʱ�����(SysTick->LOADΪ24bit)
  SysTick->VAL = 0x00; //��ռ�����
}


// End Function Name
//---------------------------------------------------------
