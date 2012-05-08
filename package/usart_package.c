/**
 *  \file       usart_package.c
 *  \brief      对usart子函数打包成所需要的功能函数供main函数使用
 *
 *  \author     fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version:   1.0\n
 *  compiler:GCC\n
 *  \date      Apr 23, 2012 6:06:29 PM
 */

#include "usart_package.h"

#ifdef __DEBUG__
/**
  * @brief  利用串口打印一字符串
  * @param  str ：打印的目标字符串，打印时使用了轮询的方式。
  * @retval none
  */
void printfs(INT8U * str)
{
while(*str)
{
USART_SendData(USART1, *str++);
/* Loop until the end of transmission */
while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
}
/**
  * @brief  利用串口打印一字符串
  * @param str ：打印的目标字符串，打印时使用了轮询的方式。
  * @retval none
  * \date 2012-5-8 下午4:11:00
  * @note 与printfs函数不同，这个函数是用在开串口中断的情况下
  */
void printfs_int(INT8U * str)
{
  while(*str)
  {
  USART_SendData(USART1, *str++);
  }
}
#endif
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//下面的关于通信协议方面的定义与操作
/////////////////////////////////////////////////////////////////////////
//概述：
/*            (发送序列如下：
 *             开始字节
 *             目标命令
 *             结束字节
 *             验证和(client_sum)
 *             )
|-----------|  用户发送命令     |-----------|
|           |-------------->|           |
|  用户              |               |   客服           |
|           |<--------------|           |
|-----------|  客服端反馈          |-----------|
            (                                       (一边接收一边算)
                                  将用户的验证和client_sum与服务端的验证和     server_sum  对比
                                  匹配，反馈：0x00
                                  失败，反馈：非零值，重发
                )
*/
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
uint8_t                 command ;/*!<  控制命令*/
static uint32_t         server_sum;/*!< 服务端的验证和 */
static uint32_t         client_sum;/*!< 客户端的验证和 */
/**
  * @brief  启动使用通信协议
  * @param  none
  * @retval none
  * \date 2012-5-8 上午10:19:29
  * @note 打开串口的接收器，初始化接收缓存
  */
void communication_agreement_start(void)
{
/*  中断开始在USART_Configuration函数中实现*/
  /*agreement init*/
  command = 0;
  client_sum = 0;
  server_sum = 0;
}
