/**
 *  \file	rcc.c
 *  \brief   
 *
 *  \detail     
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date      Apr 25, 2012 10:08:17 AM
 */

#include "rcc.h"

static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};
static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

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
/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
  *          RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
  *          RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
  *          RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
  *          RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3,
  *          RCC_APB2Periph_TIM15, RCC_APB2Periph_TIM16, RCC_APB2Periph_TIM17,
  *          RCC_APB2Periph_TIM9, RCC_APB2Periph_TIM10, RCC_APB2Periph_TIM11
  * @param  NewState: new state of the specified peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
// assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
//  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB1Periph_TIM2, RCC_APB1Periph_TIM3, RCC_APB1Periph_TIM4,
  *          RCC_APB1Periph_TIM5, RCC_APB1Periph_TIM6, RCC_APB1Periph_TIM7,
  *          RCC_APB1Periph_WWDG, RCC_APB1Periph_SPI2, RCC_APB1Periph_SPI3,
  *          RCC_APB1Periph_USART2, RCC_APB1Periph_USART3, RCC_APB1Periph_USART4,
  *          RCC_APB1Periph_USART5, RCC_APB1Periph_I2C1, RCC_APB1Periph_I2C2,
  *          RCC_APB1Periph_USB, RCC_APB1Periph_CAN1, RCC_APB1Periph_BKP,
  *          RCC_APB1Periph_PWR, RCC_APB1Periph_DAC, RCC_APB1Periph_CEC,
  *          RCC_APB1Periph_TIM12, RCC_APB1Periph_TIM13, RCC_APB1Periph_TIM14
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
//  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
//  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
  * @brief  Returns the frequencies of different on chip clocks.
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
  *         the clocks frequencies.
  * @note   The result of this function could be not correct when using
  *         fractional value for HSE crystal.
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & CFGR_SWS_Mask;

  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock */

      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
      pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;
      pllmull = ( pllmull >> 18) + 2;

      if (pllsource == 0x00)
      {/* HSI oscillator clock divided by 2 selected as PLL clock entry */
        RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {
          /* HSE selected as PLL clock entry */
          if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (uint32_t)RESET)
          {/* HSE oscillator clock divided by 2 */
            RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE >> 1) * pllmull;
          }
          else
          {
            RCC_Clocks->SYSCLK_Frequency = HSE_VALUE * pllmull;
          }
      }
      break;

    default:
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
  }
  /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* Get ADCCLK prescaler */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];
  /* ADCCLK clock frequency */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;

}

