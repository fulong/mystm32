/**
 *  \file	commucation.c
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-10 上午10:58:44
 */
#include "commucation.h"

#include "../user/user_configure/include.h"

INT8U* TX_buf_bp;
INT8U TX_buf[64];
INT8U RX_buf[64];

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
INT8U command;/*!<  控制命令*/
static INT32U server_sum;/*!< 服务端的验证和 */
static INT32U client_sum;/*!< 客户端的验证和 */
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
	INT8U i = 0;
	command = 0;
	client_sum = 0;
	server_sum = 0;
	for (i = 0; i < 64; i++)
	{
		TX_buf[i] = 0;
		RX_buf[i] = 0;
	}
}
/**
  * @brief  将命令打包成发送格式
  * @param  command: 服务端发送给客户端的命令
  *   *  这个参数可以取得到以下的值：\n
  *  	@arg 暂时还未有定义
  * @param  commu_package: 命令包存储的地方
  * @retval none
  * \date 2012-5-9 下午4:05:49
  * @note commu_package就是命令包所在的数组中，
  * 而且commu_package的数组一定要大于4，
  * 不然会有意想不到的情况出现
  */
void commad_package(INT8U command,INT8U* commu_package)
{
	INT16U sum;
	INT8* temp;
	commu_package[0] = START_BYTE;
	commu_package[1] = command;
	commu_package[2] = STOP_BYTE;
	sum = START_BYTE + command + STOP_BYTE;
	temp = (INT8*)(&sum);
	commu_package[3] = temp[1];
	commu_package[4] = temp[0];
}
/**
  * @brief  发送通信命令
  * @param  command
  *  这个参数可以取得到以下的值：\n
  *  	@arg
  * @retval
  * \date 2012-5-9 下午4:32:14
  * @note
  */
void commu_send_command(INT8U command)
{

}



