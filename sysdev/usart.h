/*
 *  File name: 		usart.h
 *
 *  Created on: 	����11:39:03 2012-4-20 2012 
 *  Author: 		fulong
 *  Version: 		1.0
 *  Compiler: 		GCC
 *  Language: 		C/C++
 *  Mail:		fulong.mo@gmail.com
 *  Comment:
    
 */

#ifndef USART_H_
#define USART_H_

#include "../stm32f103/STM32F10x/stm32f10x.h"

#define USART_HardwareFlowControl_None       ((uint16_t)0x0000)
#define USART_HardwareFlowControl_RTS        ((uint16_t)0x0100)
#define USART_HardwareFlowControl_CTS        ((uint16_t)0x0200)
#define USART_HardwareFlowControl_RTS_CTS    ((uint16_t)0x0300)

/*停止位为1位*/
#define USART_STOP_BIT_1_0                   ((uint16_t)(0x0 << 12))
/*停止位为0.5位*/
#define USART_STOP_BIT_0_5                   ((uint16_t)(0x1 << 12))
/*停止位为2位*/
#define USART_STOP_BIT_2_0                   ((uint16_t)(0x2 << 12))
/*停止位为1.5位*/
#define USART_STOP_BIT_1_5                   ((uint16_t)(0x3 << 12))

/*数据位为8位*/
#define USART_DATA_BIT_8                     ((uint16_t)(0x0 << 12))
/*数据位为9位*/
#define USART_DATA_BIT_9                     ((uint16_t)(0x1 << 12))

#define USART_Parity_No                      0
#define EN_USART_TX                          ((uint16_t)(0x1 << 3))
#define EN_USART_RX                          ((uint16_t)(0x1 << 2))

#define PARITY_EN                            ((uint16_t)(0x1 << 10))
#define PARITY_SELECT                        ((uint16_t)(0x1 << 9))

#define USART1_ENABLE(USARTx)                      (USARTx->CR1 |= 0x2000)
#define USART1_DISABLE(USARTx)                     (USARTx->CR1 &= 0xDFFF)

#define USART_FLAG_CTS                       ((uint16_t)0x0200)
#define USART_FLAG_LBD                       ((uint16_t)0x0100)
#define USART_FLAG_TXE                       ((uint16_t)0x0080)
#define USART_FLAG_TC                        ((uint16_t)0x0040)
#define USART_FLAG_RXNE                      ((uint16_t)0x0020)
#define USART_FLAG_IDLE                      ((uint16_t)0x0010)
#define USART_FLAG_ORE                       ((uint16_t)0x0008)
#define USART_FLAG_NE                        ((uint16_t)0x0004)
#define USART_FLAG_FE                        ((uint16_t)0x0002)
#define USART_FLAG_PE                        ((uint16_t)0x0001)
/**
  * @brief  USART Init Structure definition
  */
typedef struct
{
  uint32_t USART_BaudRate;            /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

  uint16_t USART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */

  uint16_t USART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */

  uint16_t USART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */

  uint16_t USART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */

  uint16_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control */
} USART_InitTypeDef;



extern void USART_Configuration(USART_TypeDef *USARTx);
extern int _fputc(int ch);

#endif /* USART_H_ */
