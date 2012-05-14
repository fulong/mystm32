/**
 *  \file	commucation.h
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-10 上午11:00:52
 */


#ifndef COMMUCATION_H_
#define COMMUCATION_H_

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//下面的关于通信协议方面的定义与操作
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#define START_BYTE                              's'		//开始字母，start
#define STOP_BYTE                               'h'		//结束字母，halt

extern void communication_agreement_start(void);/*!<  启动使用通信协议*/


#endif /* COMMUCATION_H_ */
