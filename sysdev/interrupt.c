/**
 *  \file     interrupt.c
 *  \brief    对中断进行初始化\n
 *
 *  \detail   1.使能systick中断，但这个时候systick还未有开始工作
 *
 *
 *  \author     fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version:   1.0\n
 *  compiler:GCC\n
 *  \date      Apr 24, 2012 2:39:58 PM
 */
#include "interrupt.h"
INT32U second = 0;

/**
 * @brief 使能systick中断，但这个时候systick还未有开始工作
 * @note 如果过早地开中断，可能会出现时钟不对
 * @param none
 * @retval none
 */
// Function body
void
interrupt_open()
{
  systick_enable_int(1);
}
// End Function Name
static BOOLEAN led_glitter=0;
volatile INT32U counter = 0;

//---------------------------------------------------------
void systick_Handle(void)
{
#ifdef LED_H_
  if(counter == SEC)
    {
      if(led_glitter)
      {
          led_glitter = 0;
          LED1 = 0;
      }
      else
      {
          led_glitter = 1;
          LED1 = 1;
      }
    }
#endif
  if (counter == SEC)//时间达到一秒后，秒会自增
  {
      counter = 0;
      second++;
  }
  counter++;
}
