/**
 *  \file       tft.c
 *  \brief
 *
 *  \author     fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version:   1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-3 下午3:03:54
 */
#include "tft.h"
#include "gpio.h"
#include "rcc.h"

#define LCD_PORT                GPIOC
#define LCD_CS_SET              LCD_PORT->BSRR=1<<9    //片选端口               PC9
#define LCD_RS_SET              LCD_PORT->BSRR=1<<8    //数据/命令          PC8
#define LCD_WR_SET              LCD_PORT->BSRR=1<<7    //写数据                        PC7
#define LCD_RD_SET              LCD_PORT->BSRR=1<<6    //读数据                        PC6

#define LCD_CS_CLR              LCD_PORT->BRR=1<<9     //片选端口               PC9
#define LCD_RS_CLR              LCD_PORT->BRR=1<<8     //数据/命令          PC8
#define LCD_WR_CLR              LCD_PORT->BRR=1<<7     //写数据                        PC7
#define LCD_RD_CLR              LCD_PORT->BRR=1<<6     //读数据                        PC6

//PB0~15,作为数据线
#define DATAOUT(x) GPIOB->ODR=x; //数据输出
#define DATAIN     GPIOB->IDR;   //数据输入

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
}
void LCD_WR_REG(u8 data)
{

        LCD_RS_CLR;//写地址
        LCD_CS_CLR;
        DATAOUT(data);
        LCD_WR_CLR;
        LCD_WR_SET;
        LCD_CS_SET;
}
//写寄存器
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
        LCD_WR_REG(LCD_Reg);
        LCD_WR_DATA(LCD_RegValue);
}

/**
  * @brief  tft屏的端口配置与初始化
  * @param  none
  * @retval none
  * \data 2012-5-3 下午3:07:32
  */

// Function body
#define LCD_RD                  GPIO_Pin_6
#define LCD_WR                  GPIO_Pin_7
#define LCD_RS                  GPIO_Pin_8
#define LCD_CS                  GPIO_Pin_9
#define LCD_BL                  GPIO_Pin_10
void tft_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //使能串口、串口所用的I/O口以及端口复用时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
  JTAG_Set(SWD_ENABLE);  //开启SWD
  /*配置lcd功能口*/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = LCD_RD | LCD_WR | LCD_RS | LCD_CS | LCD_BL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//推挽输出
  GPIO_Init(GPIOC,&GPIO_InitStructure);
  GPIOC->ODR|=0X07C0;
  //PORTB 推挽输出，LCD DATA口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//推挽输出
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  GPIOB->ODR |= 0XFFFF;
}
// End Function Name
//---------------------------------------------------------



