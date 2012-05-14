/**
 *  \file	gpio.h
 *  \brief   
 *
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date      Apr 26, 2012 5:15:08 PM
 */


#ifndef GPIO_H_
#define GPIO_H_

#include "../stm32f103/STM32F10x/stm32f10x.h"

//JTAG模式设置定义
#define JTAG_SWD_DISABLE   0X02/*!< jtag，swd关闭 */
#define SWD_ENABLE         0X01/*!< swd使能 */
#define JTAG_SWD_ENABLE    0X00/*!< jtag，swd使能 */


#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14 selected */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15 selected */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /*!< All pins selected */

/**
  * @brief  Configuration Mode enumeration
  */

typedef enum
{ GPIO_Mode_AIN = 0x0,/*!< 模拟输入 */
  GPIO_Mode_IN_FLOATING = 0x04,/*!< 悬空输入 */
  GPIO_Mode_IPD = 0x28,/*!< 下拉输入 */
  GPIO_Mode_IPU = 0x48,/*!< 上拉输入 */
  GPIO_Mode_Out_OD = 0x14,/*!< 推挽输出 */
  GPIO_Mode_Out_PP = 0x10,/*!< 开漏复用 */
  GPIO_Mode_AF_OD = 0x1C,/*!< 开漏输出 */
  GPIO_Mode_AF_PP = 0x18 /*!< 推挽复用 */
}GPIOMode_TypeDef;

/**
  * @brief  Output Maximum frequency selection
  */
typedef enum
{
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz,
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;
/**
  * @brief  GPIO Init structure definition
  */

typedef struct
{
  uint16_t GPIO_Pin;             /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */

  GPIOSpeed_TypeDef GPIO_Speed;  /*!< Specifies the speed for the selected pins.
                                      This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIOMode_TypeDef GPIO_Mode;    /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_TypeDef */
}GPIO_InitTypeDef;

extern void set_io(GPIO_TypeDef* GPIOx,GPIOMode_TypeDef GPIOMode_TypeDef_x,uint16_t GPIO_Pinx,GPIOSpeed_TypeDef GPIO_Speed_x);/*!< 设置io口中的状态 */
extern void JTAG_Set(u8 mode);
#endif /* GPIO_H_ */
