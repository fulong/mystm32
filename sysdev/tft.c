#include "tft.h"
#include "gpio.h"
#include "rcc.h"
#include "fsmc.h"
#include "../chip/ssd1963.h"

#if TFT_CONTROL_WAY == TFT_FSMC && CPU_TYPE == STM32F103VE
/**
 * @brief  FSMC引脚配置
 * @param  none
 *  这个参数可以取得到以下的值：\n
 *  	@arg
 * @retval none
 * \date May 22, 2012 1:46:13 PM
 * @note
 */

void FSMC_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,
			ENABLE); /* 使能各个端口时钟，重要！！！*/

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4
			| GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
			| GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9
			| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13
			| GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
/**
 * @brief  FSMC 配置使用FSMC的BANK1 NOR/PSRAM
 * @param  none
 *  这个参数可以取得到以下的值：\n
 *  	@arg
 * @retval none
 * \date May 22, 2012 1:47:38 PM
 * @note
 */

void FSMC_LCD_Init(void)
{
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef p;

	/* Configure FSMC Bank1 NOR/PSRAM */

	p.FSMC_AddressSetupTime = 0x02;
	p.FSMC_AddressHoldTime = 0x00;
	p.FSMC_DataSetupTime = 0x05;
	p.FSMC_BusTurnAroundDuration = 0x00;
	p.FSMC_CLKDivision = 0x00;
	p.FSMC_DataLatency = 0x00;
	p.FSMC_AccessMode = FSMC_AccessMode_B;

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =
			FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity =
			FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive =
			FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	/* Enable FSMC Bank1_SRAM Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}
#else
/**
  * @brief  这个函数是用来拓展用的，但用的是其他芯片或其他方式驱动TFT的时候，可将这函数拓展具体一点
  * @param  none
  *  这个参数可以取得到以下的值：\n
  *  	@arg
  * @retval none
  * \date May 22, 2012 3:14:54 PM
  * @note
  */
void something_about_tft_inited_by_another_way(void)
{
}
#endif
/**
 * @brief  LCD初始化
 * @param  none
 *  这个参数可以取得到以下的值：\n
 *  	@arg
 * @retval none
 * \date May 22, 2012 1:44:58 PM
 * @note
 */
void LCD_Init(void)
{
#if TFT_CONTROL_WAY == TFT_FSMC && CPU_TYPE == STM32F103VE
	FSMC_GPIO_Configuration();
	FSMC_LCD_Init();
#else
	something_about_tft_inited_by_another_way();
#endif
#ifdef SSD1963_DEVICE
	ssd1936_init();
#else
	other_device_init();//这个函数实际不存在，也是拓展用的，如果使用其他芯片的时候，这个就是那个芯片的初始化程序
#endif
}
