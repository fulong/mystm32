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
/** @brief 对寄存器进行写入data这个数据*/
#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
}/*!< 对寄存器进行写入data这个数据 */
/**
 * @brief 寄存器寻址
 * @param data: 写入的ir中的寄存器地址（index register）
 * @retval none
 * \date 2012-5-4 下午6:08:03
 * @note
 */
void LCD_WR_REG(u8 data)
{

	LCD_RS_CLR; //写地址
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
}
/**
 * @brief  写寄存器
 * @param  LCD_Reg: 要寻址的寄存器
 * @param  LCD_RegValue: 写入这个寄存器的值
 * @retval none
 * \date 2012-5-4 下午5:57:33
 * @note
 */
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
	LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}

#define LCD_RD                  GPIO_Pin_6
#define LCD_WR                  GPIO_Pin_7
#define LCD_RS                  GPIO_Pin_8
#define LCD_CS                  GPIO_Pin_9
#define LCD_BL                  GPIO_Pin_10

/**
 * @brief  tft屏的端口配置与初始化
 * @param  none
 * @retval none
 * \date 2012-5-3 下午3:07:32
 * @note
 */
void tft_init(void)
{
	//使能串口、串口所用的I/O口以及端口复用时钟
	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,
			ENABLE);
	JTAG_Set(SWD_ENABLE); //开启SWD
	/*配置lcd功能口*/
	set_io(GPIOC, GPIO_Mode_AF_PP, (LCD_RD | LCD_WR | LCD_RS | LCD_CS | LCD_BL),
			GPIO_Speed_50MHz);
	GPIOC->ODR |= 0X07C0;
	//PORTB 推挽输出，LCD DATA口配置
	set_io(GPIOB, GPIO_Mode_AF_PP, GPIO_Pin_All, GPIO_Speed_50MHz);
	GPIOB->ODR |= 0XFFFF;
}

