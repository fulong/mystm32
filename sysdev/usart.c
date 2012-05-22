#include "usart.h"
#include "rcc.h"
/* �������� --------------------------------------------------------------*/
/* ���ö��� --------------------------------------------------------------*/

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

/* ���ú� -------------------------------------------------------------*/
/* ���ñ� -----------------------------------------------------------*/
/* ���ú���ԭ�� -------------------------------------------------------*/
/* ���ú��� -----------------------------------------------------------*/
/**
  * @����  ��� USART_InitStruct ��ָ���Ĳ����ʼ������ USARTx �Ĵ���.
  * @����  USARTx: ѡ�� USART ��Χ�豸. 
  *                ���������ȡ����ֵ֮һ: USART1, USART2, USART3, UART4 �� UART5.
  * @����  USART_InitStruct: ָ��ṹ USART_InitTypeDef ��ָ�룬�������� USART ��������Ϣ.
  * @����  û��
  */
uint32_t USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  uint32_t usartxbase = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  /* The hardware flow control is available only for USART1, USART2 and USART3 */
  usartxbase = (uint32_t)USARTx;

/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* ��� STOP[13:12] λ */
  tmpreg &= CR2_STOP_CLEAR_Mask;
  /* ���� USART ����λ, ʱ��, ʱ�Ӽ���, ʱ����λ �� ĩλ ------------*/
  /* ���� STOP[13:12] λ������ USART_StopBits ��ֵ */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;
  
  /* д USART CR2 */
  USARTx->CR2 = (uint16_t)tmpreg;

/*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* ��� M, PCE, PS, TE �� RE λ */
  tmpreg &= CR1_CLEAR_Mask;
  /* ���� USART �ֳ�, ��ż �� ģʽ ----------------------- */
  /* ���� M   λ������ USART_WordLength ��ֵ */
  /* ���� PCE �� PS λ������ USART_Parity ��ֵ */
  /* ���� TE  �� RE λ������ USART_Mode ��ֵ */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
            USART_InitStruct->USART_Mode;
  /* д USART CR1 */
  USARTx->CR1 = (uint16_t)tmpreg;

/*---------------------------- USART CR3 Configuration -----------------------*/  
  tmpreg = USARTx->CR3;
  /* ��� CTSE �� RTSE λ */
  tmpreg &= CR3_CLEAR_Mask;
  /* ���� USART HFC -------------------------------------------------*/
  /* ���� CTSE �� RTSE λ������ USART_HardwareFlowControl ��ֵ */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  /* д USART CR3 */
  USARTx->CR3 = (uint16_t)tmpreg;

/*---------------------------- USART BRR Configuration -----------------------*/
  /* ���� USART ������ -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  if (usartxbase == USART1_BASE)
  {
    apbclock = RCC_ClocksStatus.PCLK2_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.PCLK1_Frequency;
  }
  /* ȷ������� */
  integerdivider = ((0x19 * apbclock) / (0x04 * (USART_InitStruct->USART_BaudRate)));
  tmpreg = (integerdivider / 0x64) << 0x04;
  /* ȷ������� */
  fractionaldivider = integerdivider - (0x64 * (tmpreg >> 0x04));
  tmpreg |= ((((fractionaldivider * 0x10) + 0x32) / 0x64)) & ((uint8_t)0x0F);
  /* д USART BRR */
  USARTx->BRR = (uint16_t)tmpreg;
	return apbclock;
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
  while (!(USARTx->SR & USART_FLAG_TXE));
  USARTx->DR = (Data & (uint16_t)0x01FF);
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
  /* Check the parameters */
  //assert_param(IS_USART_ALL_PERIPH(USARTx));
  //assert_param(IS_USART_FLAG(USART_FLAG));
  /* The CTS flag is not available for UART4 and UART5 */
  if (USART_FLAG == USART_FLAG_CTS)
  {
    //assert_param(IS_USART_123_PERIPH(USARTx));
  }

  if ((USARTx->SR & USART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}
