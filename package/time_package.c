/**
 *  \file	time_package.c
 *  \brief      对定时器一些必要的操作
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-3 下午1:39:46
 */
#include "time_package.h"

extern volatile INT32U second;
extern volatile INT32U counter;
/**
  * @brief  取得函数运行的秒数
  * @param  none
  * @retval 返回函数运行的秒数
  * \date 2012-5-3 下午1:52:34
  */
INT32U get_sec(void)
{
  return second;
}
/**
  * @brief  取得函数运行的毫秒数
  * @param  none
  * @retval 返回函数运行的毫秒数
  * \date 2012-5-3 下午2:35:29
  */
INT32U get_ms(void)
{
  return counter;
}
/**
  * @brief  延时ms*10毫秒，不是准确延时，误差在10MS以下
  * @param  ms:
  *             需要延时多少个十毫秒，单位是十毫秒。
  * @retval none
  * \date 2012-5-3 下午2:36:47
  */
void delay(INT8U ms)
{
  INT32U sum_cur;
  INT32U sum_pre;
  sum_pre = get_sec()*100 + get_ms();
  sum_cur = sum_pre;
  while((sum_cur - sum_pre) != ms)//判断延时到了没有
    {
      sum_cur = get_sec()*100 + get_ms();
    }
}


