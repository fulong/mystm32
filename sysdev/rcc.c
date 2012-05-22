#include "rcc.h"
#define CFGR_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR_SW_Mask              ((uint32_t)0xFFFFFFFC)
#define CFGR_HPRE_Reset_Mask      ((uint32_t)0xFFFFFF0F)
#define CFGR_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Reset_Mask     ((uint32_t)0xFFFFF8FF)
#define CFGR_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR_PPRE2_Reset_Mask     ((uint32_t)0xFFFFC7FF)
#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Reset_Mask    ((uint32_t)0xFFFF3FFF)
#define CFGR_ADCPRE_Set_Mask      ((uint32_t)0x0000C000)

/* 自用类型 --------------------------------------------------------------*/
/* 自用定义 --------------------------------------------------------------*/

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

/* 自用宏 -------------------------------------------------------------*/
/* 自用变量 -----------------------------------------------------------*/
static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};
/**
  * @简述  使能或失能高速 APB (APB2) 外围设备时钟.
  * @参数  RCC_APB2Periph: 用于门控时钟的 AHB2 外围设备.
  *                        这个参数可以是下面任意值的组合:
  *          RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
  *          RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
  *          RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
  *          RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
  *          RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3
  * @参数  NewState: 指定外围设备时钟的新状态.
  *                  这个参数可以取: ENABLE 或 DISABLE.
  * @返回  没有
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}
/**
  * @简述  返回片上时钟的不同频率.
  * @参数  RCC_Clocks: 指向包括时钟频率的 RCC_ClocksTypeDef 结构的指针.
  * @返回  没有
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;

#ifdef  STM32F10X_CL
  uint32_t prediv1source = 0, prediv1factor = 0, prediv2factor = 0, pll2mull = 0;
#endif /* STM32F10X_CL */
    
  /* 得到系统时钟源 -------------------------------------------------------*/
  tmp = RCC->CFGR & CFGR_SWS_Mask;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      break;
    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_Value;
      break;
    case 0x08:  /* PLL used as system clock */

      /* 得到 PLL 时钟源和倍频因数 ----------------------*/
      pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
      pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;
      
#ifndef STM32F10X_CL      
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {/* HSI 振荡时钟的2分频作为 PLL 时钟源 */
        RCC_Clocks->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
      }
      else
      {/* HSE 作为 PLL 时钟源 */
        if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (uint32_t)RESET)
        {/* HSE 振荡时钟被2分频 */
          RCC_Clocks->SYSCLK_Frequency = (HSE_Value >> 1) * pllmull;
        }
        else
        {
          RCC_Clocks->SYSCLK_Frequency = HSE_Value * pllmull;
        }
      }
#else
      pllmull = pllmull >> 18;
      
      if (pllmull != 0x0D)
      {
         pllmull += 2;
      }
      else
      { /* PLL 倍频因数 = PLL 输入时钟 * 6.5 */
        pllmull = 13 / 2; 
      }
            
      if (pllsource == 0x00)
      {/* HSI 振荡时钟被2分频作为 PLL 时钟源 */
        RCC_Clocks->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
      }
      else
      {/* PREDIV1 作为 PLL 时钟源 */
        
        /* 指定 PREDIV1 时钟源和分频系数 */
        prediv1source = RCC->CFGR2 & CFGR2_PREDIV1SRC;
        prediv1factor = (RCC->CFGR2 & CFGR2_PREDIV1) + 1;
        
        if (prediv1source == 0)
        { /* HSE 振荡时钟被选定作为 PREDIV1 时钟源 */
          RCC_Clocks->SYSCLK_Frequency = (HSE_Value / prediv1factor) * pllmull;          
        }
        else
        {/* PLL2 时钟作为 PREDIV1 时钟源 */
          
          /* 指定 PREDIV2 分频系数 和 PLL2 倍频系数 */
          prediv2factor = ((RCC->CFGR2 & CFGR2_PREDIV2) >> 4) + 1;
          pll2mull = ((RCC->CFGR2 & CFGR2_PLL2MUL) >> 8 ) + 2; 
          RCC_Clocks->SYSCLK_Frequency = (((HSE_Value / prediv2factor) * pll2mull) / prediv1factor) * pllmull;                         
        }
      }
#endif /* STM32F10X_CL */ 
      break;

    default:
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      break;
  }

  /* 计算 HCLK, PCLK1, PCLK2 , ADCCLK 时钟频率 ----------------*/
  /* 得到 HCLK 预分频器 */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK 时钟频率 */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
  /* 得到 PCLK1 预分频器 */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 时钟频率 */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* 得到 PCLK2 预分频器 */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 时钟频率 */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* 得到 ADCCLK 预分频器 */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];
  /* ADCCLK 时钟频率 */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}
/**
  * @简述  使能或者失能 USART 外设.
  * @参数  USARTx: 选择 USART 或者 UART 的外围设备. 
  *                这个参数可以是下面的值之一 : USART1, USART2, USART3, UART4 或 UART5.
  * @参数  NewState: USARTx 外围设备的新状态.
  *                  这个参数可以是: ENABLE or DISABLE.
  * @返回  没有
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{  
  if (NewState != DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CR1 register */
    USARTx->CR1 |= CR1_UE_Set;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CR1 register */
    USARTx->CR1 &= CR1_UE_Reset;
  }
}
/**
  * @简述  使能或失能 AHB 外围设备时钟.
  * @参数  RCC_AHBPeriph: 用于门控时钟的 AHB 外围设备.
  *   
  *        STM32_互联系列微处理器, 这个参数可以取下列值中的一个:      
  *                                RCC_AHBPeriph_DMA1
  *                                RCC_AHBPeriph_DMA2
  *                                RCC_AHBPeriph_SRAM
  *                                RCC_AHBPeriph_FLITF
  *                                RCC_AHBPeriph_CRC
  *                                RCC_AHBPeriph_OTG_FS    
  *                                RCC_AHBPeriph_ETH_MAC   
  *                                RCC_AHBPeriph_ETH_MAC_Tx
  *                                RCC_AHBPeriph_ETH_MAC_Rx
  * 
  *           其它_STM32_微处理器, 这个参数可以取下列值中的一个:         
  *                                RCC_AHBPeriph_DMA1
  *                                RCC_AHBPeriph_DMA2
  *                                RCC_AHBPeriph_SRAM
  *                                RCC_AHBPeriph_FLITF
  *                                RCC_AHBPeriph_CRC
  *                                RCC_AHBPeriph_FSMC
  *                                RCC_AHBPeriph_SDIO
  *   
  * @注解  SRAM 和 FLITF 时钟只有在睡眠的模式下可以无效.
  * @参数  NewState: 指定外围设备时钟新的状态.
  *                  这个参数可以取: ENABLE 或 DISABLE.
  * @返回  没有
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* 检查参数 */

  if (NewState != DISABLE)
  {
    RCC->AHBENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}
