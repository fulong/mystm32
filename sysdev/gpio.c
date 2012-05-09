/**
 *  \file	gpio.c
 *  \brief   
 *
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date      Apr 26, 2012 5:14:37 PM
 */

#include "gpio.h"
/**
 * @brief  Initializes the GPIOx peripheral according to the specified
 *         parameters in the GPIO_InitStruct.
 * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
 * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
 *         contains the configuration information for the specified GPIO peripheral.
 * @retval None
 */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
	uint32_t tmpreg = 0x00, pinmask = 0x00;

	/*---------------------------- GPIO Mode Configuration -----------------------*/
	currentmode = ((uint32_t) GPIO_InitStruct->GPIO_Mode) & ((uint32_t) 0x0F);
	if ((((uint32_t) GPIO_InitStruct->GPIO_Mode) & ((uint32_t) 0x10)) != 0x00)
	{
		/* Check the parameters */
		/* Output mode */
		currentmode |= (uint32_t) GPIO_InitStruct->GPIO_Speed;
	}
	/*---------------------------- GPIO CRL Configuration ------------------------*/
	/* Configure the eight low port pins */
	if (((uint32_t) GPIO_InitStruct->GPIO_Pin & ((uint32_t) 0x00FF)) != 0x00)
	{
		tmpreg = GPIOx->CRL;
		for (pinpos = 0x00; pinpos < 0x08; pinpos++)
		{
			pos = ((uint32_t) 0x01) << pinpos;
			/* Get the port pins position */
			currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
			if (currentpin == pos)
			{
				pos = pinpos << 2;
				/* Clear the corresponding low control register bits */
				pinmask = ((uint32_t) 0x0F) << pos;
				tmpreg &= ~pinmask;
				/* Write the mode configuration in the corresponding bits */
				tmpreg |= (currentmode << pos);
				/* Reset the corresponding ODR bit */
				if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
				{
					GPIOx->BRR = (((uint32_t) 0x01) << pinpos);
				}
				else
				{
					/* Set the corresponding ODR bit */
					if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
					{
						GPIOx->BSRR = (((uint32_t) 0x01) << pinpos);
					}
				}
			}
		}
		GPIOx->CRL = tmpreg;
	}
	/*---------------------------- GPIO CRH Configuration ------------------------*/
	/* Configure the eight high port pins */
	if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
	{
		tmpreg = GPIOx->CRH;
		for (pinpos = 0x00; pinpos < 0x08; pinpos++)
		{
			pos = (((uint32_t) 0x01) << (pinpos + 0x08));
			/* Get the port pins position */
			currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
			if (currentpin == pos)
			{
				pos = pinpos << 2;
				/* Clear the corresponding high control register bits */
				pinmask = ((uint32_t) 0x0F) << pos;
				tmpreg &= ~pinmask;
				/* Write the mode configuration in the corresponding bits */
				tmpreg |= (currentmode << pos);
				/* Reset the corresponding ODR bit */
				if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
				{
					GPIOx->BRR = (((uint32_t) 0x01) << (pinpos + 0x08));
				}
				/* Set the corresponding ODR bit */
				if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
				{
					GPIOx->BSRR = (((uint32_t) 0x01) << (pinpos + 0x08));
				}
			}
		}
		GPIOx->CRH = tmpreg;
	}
}
/**
 * @brief  JTAG模式设置,用于设置JTAG的模式
 * @param  mode: jtag,swd模式设置;\n
 *             00,全使能\n
 *             01,使能SWD\n
 *             10,全关闭
 * @retval none
 * \date 2012-5-3 上午11:00:58
 */
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp = mode;
	temp <<= 25;
	RCC->APB2ENR |= 1 << 0; //开启辅助时钟
	AFIO->MAPR &= 0XF8FFFFFF; //清除MAPR的[26:24]
	AFIO->MAPR |= temp; //设置jtag模式
}
/**
 * @brief  设置io口中的状态
 * @param  GPIOMode_TypeDef_x: 指定模式,只能指定一个模式\n
 *             GPIO_Mode_AIN\n
 *             GPIO_Mode_IN_FLOATING\n
 *             GPIO_Mode_IPD\n
 *             GPIO_Mode_IPU\n
 *             GPIO_Mode_Out_OD\n
 *             GPIO_Mode_Out_PP\n
 *             GPIO_Mode_AF_OD\n
 *             GPIO_Mode_AF_PP
 *
 * @param  GPIO_Pinx: 要改变状态的引脚，可以将要改变的引脚都加起来，进行同时配置.\n
 *             GPIO_Pin_0\n
 *             .\n
 *             .\n
 *             .\n
 *             GPIO_Pin_15
 *
 * @param  GPIOx: 要改变状态的IO组（GPIOA-GPIOG）
 * @param  GPIO_Speed_x: io口对应的速度设置\n
 *                     GPIO_Speed_10MHz\n
 *                     GPIO_Speed_2MH\n
 *                     GPIO_Speed_50MHz
 *
 *
 * @retval none
 * \date 2012-5-4 下午4:33:21
 */
void set_io(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIOMode_TypeDef_x,
		uint16_t GPIO_Pinx, GPIOSpeed_TypeDef GPIO_Speed_x)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_x;
	GPIO_InitStructure.GPIO_Mode = GPIOMode_TypeDef_x;
	GPIO_Init(GPIOx, &GPIO_InitStructure);

}
