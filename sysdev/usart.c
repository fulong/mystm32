/*
 *  File name: 		usart.c
 *
 *  Created on: 	����11:44:23 2012-4-20 2012 
 *  Author: 		fulong
 *  Version: 		1.0
 *  Compiler: 		GCC
 *  Language: 		C/C++
 *  Mail:		fulong.mo@gmail.com
 *  Comment:

 */
#include "usart.h"
#include "rcc.h"
#include "gpio.h"

#define CR1_UE_Set                ((uint16_t)0x2000)  /*!< USART Enable Mask */
#define CR1_UE_Reset              ((uint16_t)0xDFFF)  /*!< USART Disable Mask */

#define CR1_WAKE_Mask             ((uint16_t)0xF7FF)  /*!< USART WakeUp Method Mask */

#define CR1_RWU_Set               ((uint16_t)0x0002)  /*!< USART mute mode Enable Mask */
#define CR1_RWU_Reset             ((uint16_t)0xFFFD)  /*!< USART mute mode Enable Mask */
#define CR1_SBK_Set               ((uint16_t)0x0001)  /*!< USART Break Character send Mask */
#define CR1_CLEAR_Mask            ((uint16_t)0xE9F3)  /*!< USART CR1 Mask */
#define CR2_Address_Mask          ((uint16_t)0xFFF0)  /*!< USART address Mask */

#define CR2_LINEN_Set              ((uint16_t)0x4000)  /*!< USART LIN Enable Mask */
#define CR2_LINEN_Reset            ((uint16_t)0xBFFF)  /*!< USART LIN Disable Mask */

#define CR2_LBDL_Mask             ((uint16_t)0xFFDF)  /*!< USART LIN Break detection Mask */
#define CR2_STOP_CLEAR_Mask       ((uint16_t)0xCFFF)  /*!< USART CR2 STOP Bits Mask */
#define CR2_CLOCK_CLEAR_Mask      ((uint16_t)0xF0FF)  /*!< USART CR2 Clock Mask */

#define CR3_SCEN_Set              ((uint16_t)0x0020)  /*!< USART SC Enable Mask */
#define CR3_SCEN_Reset            ((uint16_t)0xFFDF)  /*!< USART SC Disable Mask */

#define CR3_NACK_Set              ((uint16_t)0x0010)  /*!< USART SC NACK Enable Mask */
#define CR3_NACK_Reset            ((uint16_t)0xFFEF)  /*!< USART SC NACK Disable Mask */

#define CR3_HDSEL_Set             ((uint16_t)0x0008)  /*!< USART Half-Duplex Enable Mask */
#define CR3_HDSEL_Reset           ((uint16_t)0xFFF7)  /*!< USART Half-Duplex Disable Mask */

#define CR3_IRLP_Mask             ((uint16_t)0xFFFB)  /*!< USART IrDA LowPower mode Mask */
#define CR3_CLEAR_Mask            ((uint16_t)0xFCFF)  /*!< USART CR3 Mask */

#define CR3_IREN_Set              ((uint16_t)0x0002)  /*!< USART IrDA Enable Mask */
#define CR3_IREN_Reset            ((uint16_t)0xFFFD)  /*!< USART IrDA Disable Mask */
#define GTPR_LSB_Mask             ((uint16_t)0x00FF)  /*!< Guard Time Register LSB Mask */
#define GTPR_MSB_Mask             ((uint16_t)0xFF00)  /*!< Guard Time Register MSB Mask */
#define IT_Mask                   ((uint16_t)0x001F)  /*!< USART Interrupt Mask */

/* USART OverSampling-8 Mask */
#define CR1_OVER8_Set             ((u16)0x8000)  /* USART OVER8 mode Enable Mask */
#define CR1_OVER8_Reset           ((u16)0x7FFF)  /* USART OVER8 mode Disable Mask */

/* USART One Bit Sampling Mask */
#define CR3_ONEBITE_Set           ((u16)0x0800)  /* USART ONEBITE mode Enable Mask */
#define CR3_ONEBITE_Reset         ((u16)0xF7FF)  /* USART ONEBITE mode Disable Mask */

/**
 * @brief  Deinitializes the USARTx peripheral registers to their default reset values.
 * @param  USARTx: Select the USART or the UART peripheral.
 *   This parameter can be one of the following values:
 *      USART1, USART2, USART3, UART4 or UART5.
 * @retval None
 */
void USART_DeInit(USART_TypeDef* USARTx)
{
	/* Check the parameters */
//  assert_param(IS_USART_ALL_PERIPH(USARTx));
	if (USARTx == USART1)
	{
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
	}
	else if (USARTx == USART2)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
	}
	else if (USARTx == USART3)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
	}
	else if (USARTx == UART4)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
	}
	else
	{
		if (USARTx == UART5)
		{
			RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
			RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
		}
	}
}

/**
 * @brief  Initializes the USARTx peripheral according to the specified
 *         parameters in the USART_InitStruct .
 * @param  USARTx: Select the USART or the UART peripheral.
 *   This parameter can be one of the following values:
 *   USART1, USART2, USART3, UART4 or UART5.
 * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
 *         that contains the configuration information for the specified USART
 *         peripheral.
 * @retval None
 */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
	uint32_t tmpreg = 0x00, apbclock = 0x00;
	uint32_t integerdivider = 0x00;
	uint32_t fractionaldivider = 0x00;
	uint32_t usartxbase = 0;
	RCC_ClocksTypeDef RCC_ClocksStatus;
	/* The hardware flow control is available only for USART1, USART2 and USART3 */

	usartxbase = (uint32_t) USARTx;

	/*---------------------------- USART CR2 Configuration -----------------------*/
	tmpreg = USARTx->CR2;
	/* Clear STOP[13:12] bits */
	tmpreg &= CR2_STOP_CLEAR_Mask;
	/* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
	/* Set STOP[13:12] bits according to USART_StopBits value */
	tmpreg |= (uint32_t) USART_InitStruct->USART_StopBits;

	/* Write to USART CR2 */
	USARTx->CR2 = (uint16_t) tmpreg;

	/*---------------------------- USART CR1 Configuration -----------------------*/
	tmpreg = USARTx->CR1;
	/* Clear M, PCE, PS, TE and RE bits */
	tmpreg &= CR1_CLEAR_Mask;
	/* Configure the USART Word Length, Parity and mode ----------------------- */
	/* Set the M bits according to USART_WordLength value */
	/* Set PCE and PS bits according to USART_Parity value */
	/* Set TE and RE bits according to USART_Mode value */
	tmpreg |= (uint32_t) USART_InitStruct->USART_WordLength
			| USART_InitStruct->USART_Parity | USART_InitStruct->USART_Mode;
	/* Write to USART CR1 */
	USARTx->CR1 = (uint16_t) tmpreg;

	/*---------------------------- USART CR3 Configuration -----------------------*/
	tmpreg = USARTx->CR3;
	/* Clear CTSE and RTSE bits */
	tmpreg &= CR3_CLEAR_Mask;
	/* Configure the USART HFC -------------------------------------------------*/
	/* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
	tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
	/* Write to USART CR3 */
	USARTx->CR3 = (uint16_t) tmpreg;

	/*---------------------------- USART BRR Configuration -----------------------*/
	/* Configure the USART Baud Rate -------------------------------------------*/
	RCC_GetClocksFreq(&RCC_ClocksStatus);
	if (usartxbase == USART1_BASE)
	{
		apbclock = RCC_ClocksStatus.PCLK2_Frequency;
	}
	else
	{
		apbclock = RCC_ClocksStatus.PCLK1_Frequency;
	}

	/* Integer part computing in case Oversampling mode is 16 Samples */
	integerdivider =
			((25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate)));
	tmpreg = (integerdivider / 100) << 4;

	/* Determine the fractional part */
	fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

	/* Implement the fractional part in the register */
	tmpreg |= ((((fractionaldivider * 16) + 50/*当超过0.5的时候将进一来确保波特率符合错误虑见到最少*/)
			/ 100)) & ((uint8_t) 0x0F);

	/* Write to USART BRR */
	USARTx->BRR = (uint16_t) tmpreg;
}

void USART_Configuration(USART_TypeDef *USARTx)
{
	USART_InitTypeDef USART_InitStructure;
	USART_DeInit(USARTx);
//使能串口、串口所用的I/O口以及端口复用时钟
	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO,
			ENABLE);
	/* A9 USART1_Tx */
	set_io(GPIOA, GPIO_Mode_AF_PP, GPIO_Pin_9, GPIO_Speed_2MHz); //推挽输出-TX
			/* A10 USART1_Rx */
	set_io(GPIOA, GPIO_Mode_AF_PP, GPIO_Pin_10, GPIO_Mode_IN_FLOATING); //浮空输入-RX

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_DATA_BIT_8;
	USART_InitStructure.USART_StopBits = USART_STOP_BIT_1_0;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = EN_USART_TX | EN_USART_RX | USART_FLAG_TC; //|USART_FLAG_RXNE /*开RX中断*/| USART_FLAG_TXE;
	USART_Init(USART1, &USART_InitStructure);
	/* Enable the USARTx */
	USART_ENABLE(USARTx);
}
/**
 * @brief  Checks whether the specified USART flag is set or not.
 * @param  USARTx: Select the USART or the UART peripheral.
 *   This parameter can be one of the following values:
 *   USART1, USART2, USART3, UART4 or UART5.
 * @param  USART_FLAG: specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg USART_FLAG_CTS:  CTS Change flag (not available for UART4 and UART5)
 *     @arg USART_FLAG_LBD:  LIN Break detection flag
 *     @arg USART_FLAG_TXE:  Transmit data register empty flag
 *     @arg USART_FLAG_TC:   Transmission Complete flag
 *     @arg USART_FLAG_RXNE: Receive data register not empty flag
 *     @arg USART_FLAG_IDLE: Idle Line detection flag
 *     @arg USART_FLAG_ORE:  OverRun Error flag
 *     @arg USART_FLAG_NE:   Noise Error flag
 *     @arg USART_FLAG_FE:   Framing Error flag
 *     @arg USART_FLAG_PE:   Parity Error flag
 * @retval The new state of USART_FLAG (SET or RESET).
 */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
	FlagStatus bitstatus = RESET;
	/* The CTS flag is not available for UART4 and UART5 */

	if ((USARTx->SR & USART_FLAG) != (uint16_t) RESET)
	{
		bitstatus = SET;
	}
	else
	{
		bitstatus = RESET;
	}
	return bitstatus;
}
/**
 * @brief  Transmits single data through the USARTx peripheral.
 * @param  USARTx: Select the USART or the UART peripheral.
 *   This parameter can be one of the following values:
 *   USART1, USART2, USART3, UART4 or UART5.
 * @param  Data: the data to transmit.
 * @retval None
 */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{

	/* Transmit Data */
	USARTx->DR = (Data & (uint16_t) 0x01FF);
}
/**
 * @brief  Returns the most recent received data by the USARTx peripheral.
 * @param  USARTx: Select the USART or the UART peripheral.
 *   This parameter can be one of the following values:
 *   USART1, USART2, USART3, UART4 or UART5.
 * @retval The received data.
 */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
	/* Receive Data */
	return (uint16_t) (USARTx->DR & (uint16_t) 0x01FF);
}

