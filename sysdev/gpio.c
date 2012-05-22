#include "gpio.h"
/**
  * @brief  按照GPIO_InitStruct(结构体)的特定参数初始化GPIO部件
  * @param  GPIOx：x可为A到G来选择特定的GPIO设备，
  *        GPIO_InitStruct: 指向GPIO_InitTypeDef结构的指针，它包含特定GPIO部件的配置信息.
  *  这个参数可以取得到以下的值：\n
  *  	@arg
  * @retval none
  * \date May 22, 2012 12:02:59 PM
  * @note
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  
/*---------------------------- GPIO 模式配置 --------------------------------*/
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
    /* Output mode */
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
/*-------------------- GPIO CRL(端口控制寄存器低字节) 配置 -------------------*/
  /* 配置低8位端口管脚 */
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* 取得端口引脚的位置 */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* 清空相应的低位控制寄存器 */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* 写相应的模式配置位 */
        tmpreg |= (currentmode << pos);
        /* 复位相应的输出数据寄存器 (ODR) 位 */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* 置位相应的输出数据寄存器 (ODR) 位 */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOx->CRL = tmpreg;
  }
/*-------------------- GPIO CRH(端口控制寄存器高字节) 配置 -------------------*/
  /* 配置高8位端口引脚 */
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* 取得端口引脚的位置 */
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* 清空相应的低位控制寄存器 */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* 写相应的模式配置位 */
        tmpreg |= (currentmode << pos);
        /* 复位相应的输出数据寄存器 (ODR) 位 */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
        /* 置位相应的输出数据寄存器 (ODR) 位 */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
}
