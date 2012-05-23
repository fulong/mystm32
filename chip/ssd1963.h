/**
 *  \file	ssd1963.h
 *  \brief  tft相对于ssd1963初始化的基本操作函数
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-15 上午1:11:44
 */

#ifndef SSD1963_H_
#define SSD1963_H_
#include "../libc/cpu_typed.h"

#define _HPS								(800)			/*!<  实际的屏幕的水平像素数量*/
#define _VPS								(480)			/*!<  实际的屏幕的垂直像素数量*/
#define DISP_HOR_PULSE_WIDTH		1
#define DISP_HOR_FRONT_PORCH		210
#define DISP_HOR_BANKING			46
#define DISP_VER_PULSE_WIDTH		1
#define DISP_VER_BANKING			23
#define DISP_VER_FRONT_PORCH		22

/***********************************************************************************
 颜色数值
 ***********************************************************************************/
#define   BLACK        0x0000                    /* 黑色*/
#define   NAVY         0x000F                    /* 深蓝色*/
#define   DGREEN       0x03E0                    /* 深绿色*/
#define   DCYAN        0x03EF                    /* 深蓝绿色*/
#define   MAROON       0x7800                    /* 栗色*/
#define   PURPLE       0x780F                    /* 紫色*/
#define   OLIVE        0x7BE0                    /* 橄榄色*/
#define   LGRAY        0xC618                    /* 浅灰色*/
#define   DGRAY        0x7BEF                    /* 深灰色*/
#define   BLUE         0x001F                    /* 蓝色*/
#define   GREEN        0x07E0                 	 /* 绿色*/
#define   CYAN         0x07FF                    /* 蓝绿色*/
#define   RED          0xF800                    /* 红色*/
#define   MAGENTA      0xF81F                    /* 品红色*/
#define   YELLOW       0xFFE0                    /* 黄色*/
#define   WHITE        0xFFFF                    /* 白色*/

#include "../stm32f103/STM32F10x/stm32f10x.h"


#define SSD1963_NOP					0x00	/*!<  No operation*/
#define SSD1963_SOFT_RESET			0x01	/*!<  Software reset*/
#define SSD1963_GET_POWER_MODE		0x0A	/*!<  Get the current power mode*/
#define SSD1963_GET_ADDRESS_MODE	0x0B	/*!<  Get the frame memory to the display panel read order*/
#define SSD1963_GET_DISPLAY_MODE	0x0D	/*!<  The display module returns the Display Signal Mode*/
#define SSD1963_PIXEL_FORMAT		0x0C	/*!<  Get the current pixel format*/
#define SSD1963_SIGNAL_MODE			0x0E	/*!<  Get the current display mode from the peripheral*/
#define SSD1963_ENTER_SLEEP_MODE	0x10	/*!<  If GPIO0 is configured as normal GPIO or LCD miscellaneous signal with command set_gpio_conf,this command will be ignored*/
#define SSD1963_EXIT_SLEEP_MODE		0x11	/*!<  Turn on the panel.This command will pull high the GPIO0.If GPIO0 is configure as normal GPIO or LCD miscellaneous signal with command set_gpio_conf,this command will be ignored.*/
#define SSD1963_ENTER_PARTIAL_MODE	0x12	/*!<  Part of the display area is used for image display*/
#define SSD1963_ENTER_NORMAL_MODE	0x13	/*!<  The whole display area is used for image display.*/
#define SSD1963_EXIT_INVERT_MODE	0x20	/*!<  Displayed image colors are not inverted*/
#define SSD1963_ENTER_INVER_MODE	0x21	/*!<  Displayed image colors are inverted*/
#define SSD1963_SET_GAMMA_CURVE		0x26	/*!<  Selects the gamma curve used by the display device*/
#define SSD1963_SET_DISPLAY_OFF		0x28	/*!<  Blanks the display device*/
#define SSD1963_SET_DISPLAY_ON		0x29	/*!<  Show the image on the display device*/
#define SSD1963_SET_COLUMN_ADDRESS	0x2A	/*!<  Set the column extent*/
#define SSD1963_SET_PAGE_ADDRESS	0x2B	/*!<  Set the page extent*/
#define SSD1963_WRITE_MEMORY_START	0x2C	/*!<  Transfer image information from the host processor interface to the peripheral starting at the location provided by set_column_address and set_page_address*/
#define SSD1963_READ_MEMORY_START	0x2E	/*!<  Transfer image data from the peripheral to the host processor interface starting at the location provided by set_column_address and set_page_address*/
#define SSD1963_SET_PARTIAL_AREA	0x30	/*!<  Defines the partial display area on the display device*/
#define SSD1963_SET_SCROLL_AREA		0x33	/*!<  Defines the vertical scrolling and fixed area on display area*/
#define SSD1963_SET_TEAR_OFF		0x34	/*!<  Synchronization information is not sent from the display module to the host processor*/
#define SSD1963_SET_TEAR_ON			0x35	/*!<  Synchronization information is sent from the display module to the host processor at the start of VFP*/
#define SSD1963_SET_ADDRESS_MODE	0x36	/*!<  Set the read order from frame buffer to the display panel*/
#define SSD1963_SET_SCROLL_START	0x37	/*!<  Defines the vertical scrolling starting point*/
#define SSD1963_EXIT_IDLE_MODE		0x38	/*!<  Full color depth is used for the display panel*/
#define SSD1963_ENTER_IDLE_MODE		0x39	/*!<  Reduce color depth is used on the display panel*/
#define SSD1963_SET_PIXEL_FORMAT	0x3A	/*!<  Defines how many bits per pixel are used in the interface*/
#define SSD1963_WRITE_MEMORY_CONTINUE	0x3C /*!<  Transfer image information from the host processor interface to the peripheral from the last written location*/
#define SSD1963_READ_MEMORY_CONTINUE	0x3E /*!<  Read image information from the host processor interface to the peripheral from the last written location*/
#define SSD1963_TEAR_SCANLINE		0x44	/*!<  Synchronization information is sent from the display module to the host process when the display device refresh reaches the provided scanline*/
#define SSD1963_GET_SCANLINE		0x45	/*!<  Get the current scan line*/
#define SSD1963_READ_DDB			0xA1	/*!<  Read the DDB from the provided location*/
#define SSD1963_SET_LCD_MODE		0xB0	/*!<  Set the LCD panel mode(RGB TFT or TTL)*/
#define SSD1963_GET_LCD_MODE		0xB1	/*!<  Get the current LCD panel mode,pad strength and resolution*/
#define SSD1963_SET_HORI_PERIOD		0xB4	/*!<  Set front porch*/
#define SSD1963_GET_HORI_PERIOD		0xB5	/*!<  Get current front porch settings*/
#define SSD1963_SET_VERT_PERIOD		0xB6	/*!<  Set the vertical blanking interval between last scan line and next LFRAME pulse*/
#define SSD1963_GET_VERT_PERIOD		0xB7	/*!<  Get the vertical blanking interval between last scan line and next LFRAME pulse*/
#define SSD1963_SET_GPIO_CONF		0xB8	/*!<  Set the GPIO configuration. If the GPIO is not used for LCD.set the direction. Otherwise,they are toggled with LCD signals.*/
#define SSD1963_GET_GPIO_STATUS		0xBB	/*!<  Read current GPIO status. If the individual GPIO was configured as input,the value is the status of the corresponding pin.Otherwise,it is the programmed value*/
#define SSD1963_SET_POST_PROC		0xBC`	/*!<  Set the image post processor*/
#define SSD1963_GET_POST_PROC		0xBD	/*!<  Get the image post processor*/
#define SSD1963_SET_PWM_CONF		0xBE	/*!<  Set the image post processor*/
#define SSD1963_GET_PWM_CONF		0xBF	/*!<  Get the image post processor*/
#define SSD1963_SET_LCD_GEN0		0xC0	/*!<  Set the rise,fall,period and toggling properties of LCD signal generator 0*/
#define SSD1963_GET_LCD_GEN0		0xC1	/*!<  Get the current settings of LCD signal generator 0*/
#define SSD1963_SET_LCD_GEN1		0xC2	/*!<  Set the rise,fall,period and toggling properties of LCD signal generator 1*/
#define SSD1963_GET_LCD_GEN1		0xC3	/*!<  Get the current settings of LCD signal generator 1*/
#define SSD1963_SET_LCD_GEN2		0xC4	/*!<  Set the rise,fall,period and toggling properties of LCD signal generator 2*/
#define SSD1963_GET_LCD_GEN2		0xC5	/*!<  Get the current settings of LCD signal generator 3*/
#define SSD1963_SET_LCD_GEN3		0xC6	//同上
#define SSD1963_GET_LCD_GEN3		0xC7	//同上
#define SSD1963_SET_GPIO0_ROP		0xC8	/*!<  Set the GPIO0 with respect to the LCD signal generators using ROP3 operation.No effect if the GPIO0 is configured as general GPIO*/
#define SSD1963_GET_GPIO0_ROP		0xC9	/*!<  Get the GPIO0 properties with respect to the LCD signal generators*/
#define SSD1963_SET_GPIO1_ROP		0xCA	/*!<  Set the GPIO1 with respect to the LCD signal generators using ROP3 operation.No effect if the GPIO1 is configured as general GPIO*/
#define SSD1963_GET_GPIO1_ROP		0xCB	/*!<  Get the GPIO1 properties with respect to the LCD signal generators*/
#define SSD1963_SET_GPIO2_ROP		0xCC	/*!<  Set the GPIO2 with respect to the LCD signal generators using ROP3 operation.No effect if the GPIO2 is configured as general GPIO*/
#define SSD1963_GET_GPIO2_ROP		0xCD	/*!<  Get the GPIO2 properties with respect to the LCD signal generators*/
#define SSD1963_SET_GPIO3_ROP		0xCE	/*!<  Set the GPIO3 with respect to the LCD signal generators using ROP3 operation.No effect if the GPIO3 is configured as general GPIO*/
#define SSD1963_GET_GPIO3_ROP		0xCF	/*!<  Get the GPIO3 properties with respect to the LCD signal generators*/
#define SSD1963_SET_DBC_CONF		0xD0	/*!<  Set the dynamic back light configuration*/
#define SSD1963_GET_DBC_CONF		0xD1	/*!<  Get the current dynamic back light configuration*/
#define SSD1963_SET_DBC_TH			0xD4	/*!<  Set the threshold for each level of power saving*/
#define SSD1963_GET_DBC_TH			0xD5	/*!<  Get the threshold for each level of power saving*/
#define SSD1963_SET_PLL				0xE0	/*!<  Start the PLL.Before the start,the system was operated with the crystal oscillator or clock input*/
#define SSD1963_SET_PLL_MN			0xE2	/*!<  Set the PLL*/
#define SSD1963_GET_PLL_MN			0xE3	/*!<  Get the PLL settings*/
#define SSD1963_GET_PLL_STATUS		0xE4	/*!<  Get the current PLL status*/
#define SSD1963_SET_DEEP_SLEEP		0xE5	/*!<  Set deep sleep mode*/
#define SSD1963_SET_LSHIFT_FREQ		0xE6	/*!<  Set the LSHIFT(pixel clock)frequency */
#define SSD1963_GET_LSHIFT_FREQ		0xE7	/*!<  Get the LSHIFT(pixel clock)frequency*/
#define SSD1963_SET_PIXEL_DATA_INTERFACE 0xF0 /*!<  Set the pixel data format of the parallel host processor interface*/
#define SSD1963_GET_PIXEL_DATA_INTERFACE 0xF1 /*!<  Get the current pixel data format settings*/
/*SSD1963_SET_GAMMA_CURVE各位定义*/
#define GAMMA_CURVE0				1
#define GAMMA_CURVE1				2
#define GAMMA_CURVE2				4
#define GAMMA_CURVE3				8
/*SSD1963_SET_GAMMA_CURVE各位定义*/
/*SSD1963_SET_ADDRESS_MODE各位定义*/
//从主处理器到帧缓冲区的控制顺序是由[7:5]与[3]位控制，帧缓冲区到TFT面板的控制顺序是由[0:2]和[4]位控制。
/*
 -------------------SP(start page)
 |				  |
 |				  |
 |				  |<-----------------FRAME BUFFER
 |				  |				     host
 |				  |					 tft panel
 |				  |
 -------------------EP(end page)
 SC(start column)EC(end column)
 */
#define PAGE_ADDRESS_MODE_TOP2BUTTOM		(0 << 7)//从主处理器写到frame 缓冲区的时候，是以自上向底方向写进(SP 2 EP)
#define PAGE_ADDRESS_MODE_BUTTOM2TOP		(1 << 7)//从主处理器写到frame 缓冲区的时候，是以自底向上方向写进(EP 2 SP)
#define COLUMN_ADDRESS_MODE_L2R				(0 << 6)//从主处理器写到frame 缓冲区的时候，是以自左向右方向写进(SC 2 EC)
#define COLUMN_ADDRESS_MODE_R2C				(1 << 6)//从主处理器写到frame 缓冲区的时候，是以自右向左方向写进(EC 2 SC)
#define PAGE_COLUMN_ADDRESS_MODE_ENABLE		(1 << 5)//从主处理器写到frame 缓冲区的时候，SC到EC的数据写写到SP到EP中
#define PAGE_COLUMN_ADDRESS_MODE_DISABLE	(0 << 5)//从主处理器写到frame 缓冲区的时候，正常方式
#define LINE_ADDRESS_ORDER_TOP2BUTTOM		(0 << 4)//从frame 缓冲区写到tft面板的时候，是以自上向底方向写进(SP 2 EP)
#define LINE_ADDRESS_ORDER_BUTTOM2TOP		(1 << 4)//从frame 缓冲区写到tft面板的时候，是以自底向上方向写进(EP 2 SP)
#define RGB2BGR_ORDER						(0 << 3)//从frame 缓冲区写到tft面板的时候，自动将RGB转换为BGR格式
#define RGB_NO_CHANGE						(1 << 3)//从frame 缓冲区写到tft面板的时候，RGB格式不变，直接传送过去
#define DISPLAY_LATCH_DATA_ENABLE			(1 << 2)//这个位有置位，图像将无效
#define DISPLAY_LATCH_DATA_DISABLE			(0 << 2)

#define FLIP_HORIZONTAL_L2R					(0 << 1)//从frame 缓冲区写到tft面板的时候，是以自左向右方向写进(SC 2 EC),如果上面这个位置位的话
#define FLIP_HORIZONTAL_R2L					(1 << 1)//从frame 缓冲区写到tft面板的时候，是以自右向左方向写进(EC 2 SC),如果上面这个位置位的话
#define FLIP_VERTICAL_T2B					(0 << 0)//从frame 缓冲区写到tft面板的时候，是以自上向底方向写进(SP 2 EP)
#define FLIP_VERTICAL_B2T					(1 << 0)//从frame 缓冲区写到tft面板的时候，是以自底向上方向写进(EP 2 SP)
/*SSD1963_SET_ADDRESS_MODE各位定义*/
/*SSD1963_SET_LCD_MODE各位定义*/
//第1个参数：
#define TFT_PANEL_DATA_WITH_18				(0 << 5)		/*!<  TFT面板的数据宽度为18位*/
#define TFT_PANEL_DATA_WITH_24				(1 << 5)		/*!<  TFT面板的数据宽度为24位*/

#define TFT_COLOR_DEPTH_ENHANCEMENT_ENABLE	(1 << 4)		/*!<  使用FRC或者抖动方式来增强色彩深度*/
#define TFT_COLOR_DEPTH_ENHANCEMENT_DISABLE	(0 << 4)		/*!<  除能FRC或者抖动方式来增强色彩深度,如果数据宽度设为24位的时候，这两个颜色深度的值将会被忽略掉*/

#define TFT_FRC_ENABLE						(1 << 3)		/*!<  是上面位的扩展，如果上面位为1，则使用FRC来增强色彩深度*/
#define TFT_FRC_DISABLE						(0 << 3)		/*!<  是上面位的扩展，如果上面位为1，则使用抖动来增强色彩深度*/

#define LSHIFT_POLARITY_RISING_EDGE			(0 << 2)		/*!<  在上升沿来临时数据锁存*/
#define LSHIFT_POLARITY_FALLING_EDGE		(1 << 2)		/*!<  在下降沿来临时数据锁存*/

#define LLINE_POLARITY_LOW					(0 << 1)		/*!<  低电平有效*/
#define LLINE_POLARITY_HIGH					(1 << 1)		/*!<  高电平有效*/

#define LFRAME_POLARITY_LOW					(0 << 0)		/*!<  低电平有效*/
#define LFRAME_POLARITY_HIGH				(1 << 0)		/*!<  高电平有效*/
//第1个参数结束
//第2个参数
#define LCD_PANEL_MODE_RGB					(0 << 7)		/*!<  Hsync+vsync+de 模式*/
#define LCD_PANEL_MODE_TTL					(1 << 7)		/*!<  TTL 模式*/

#define TFT_TYPE_TFT_1						(0 << 5)		/*!<  TTL 模式*/
#define TFT_TYPE_TFT_2						(1 << 5)		/*!<  同样是TTL 模式*/
#define TFT_TYPE_RGB						(2 << 5)		/*!<  串行RGB模式*/
#define TFT_TYPE_RGB_DUMMY					(3 << 5) 		/*!<  虚拟串行RGB模式*/
//第2个参数结束
#define HPS_TEMP							(_HPS -1 )		/*!<  实际的像素数量 = HPS + 1,因而写进去的ssd1963的会少1*/
//第3个参数
#define HPS_HIGH							((HPS_TEMP >> 8) & 0xFF)/*!<  设置水平像素，首先写入最高三位*/
//第3个参数结束
//第4个参数
#define HPS_LOW								(HPS_TEMP & 0xFF)		/*!<  设置水平像素，写入低八位*/
//第4个参数结束
#define VPS_TEMP							(_VPS -1 )		/*!<  实际的像素数量 = VPS + 1,因而写进去的ssd1963的会少1*/
//第5个参数
#define VPS_HIGH							((VPS_TEMP >> 8) & 0xFF)	/*!<  设置垂直像素，首先写入最高三位*/
//第5个参数结束
//第6个参数
#define VPS_LOW								(VPS_TEMP & 0xFF)		/*!<  设置垂直像素，写入低八位*/
//第6个参数结束
//第7个参数
#define EVEN_LINE_RGB_SEQUENECE_RGB			(0 << 3)		/*!<  偶数行每个像素为RGB序列*/
#define EVEN_LINE_RGB_SEQUENECE_RBG			(1 << 3)		/*!<  偶数行每个像素为RBG序列*/
#define EVEN_LINE_RGB_SEQUENECE_GRB			(2 << 3)		/*!<  偶数行每个像素为GRB序列*/
#define EVEN_LINE_RGB_SEQUENECE_GBR			(3 << 3)		/*!<  偶数行每个像素为GBR序列*/
#define EVEN_LINE_RGB_SEQUENECE_BRG			(4 << 3)		/*!<  偶数行每个像素为BRG序列*/
#define EVEN_LINE_RGB_SEQUENECE_BGR			(5 << 3)		/*!<  偶数行每个像素为BGR序列*/

#define ODD_LINE_RGB_SEQUENECE_RGB			(0 << 0)		/*!<  奇数行每个像素为RGB序列*/
#define ODD_LINE_RGB_SEQUENECE_RBG			(1 << 0)		/*!<  奇数行每个像素为RBG序列*/
#define ODD_LINE_RGB_SEQUENECE_GRB			(2 << 0)		/*!<  奇数行每个像素为GRB序列*/
#define ODD_LINE_RGB_SEQUENECE_GBR			(3 << 0)		/*!<  奇数行每个像素为GBR序列*/
#define ODD_LINE_RGB_SEQUENECE_BRG			(4 << 0)		/*!<  奇数行每个像素为BRG序列*/
#define ODD_LINE_RGB_SEQUENECE_BGR			(5 << 0)		/*!<  奇数行每个像素为BGR序列*/
//第7个参数结束

/*SSD1963_SET_LCD_MODE各位定义*/
/*SSD1963_SET_HORI_PERIOD各位定义*/
#define HT_TOTAL 					(DISP_HOR_BANKING+DISP_HOR_FRONT_PORCH+DISP_HOR_PULSE_WIDTH+_HPS)//显示一行需要的DCLK
#define HT_TOTAL_TEMP				(HT_TOTAL - 1)
//第1个参数
#define HT_HIGH						((HT_TOTAL_TEMP >> 8) & 0x7)
//第1个参数结束
//第2个参数
#define HT_LOW						(HT_TOTAL_TEMP  & 0xFF)
//第2个参数结束
#define HDP_TOTAL					(DISP_HOR_PULSE_WIDTH+DISP_HOR_FRONT_PORCH)
#define HDP_TOTAL_TEMP				(HDP_TOTAL - 1)
//第3个参数
#define HDP_HIGH					((HDP_TOTAL_TEMP >> 8) & 0x7)
//第3个参数结束
//第4个参数
#define HDP_LOW						((HDP_TOTAL_TEMP) & 0xFF)
//第4个参数结束
//第5个参数
#define HPW							((DISP_HOR_PULSE_WIDTH) -1)
//第5个参数结束
//第6个参数
#define LPS_HIGH					0//水平同步脉冲的开始位置的高字节
//第6个参数结束
//第7个参数
#define LPS_LOW						0//水平同步脉冲的开始位置的低字节
//第7个参数结束
//第8个参数
#define LPSPP						0//水平同步脉冲子像素的开始位置的低字节
//第8个参数结束
/*SSD1963_SET_HORI_PERIOD各位定义*/
/*SSD1963_SET_VERT_PERIOD各位定义*/
#define VE_TOTAL 					(DISP_VER_BANKING+DISP_VER_FRONT_PORCH+DISP_VER_PULSE_WIDTH+_VPS)//显示一帧需要的TH
#define VE_TOTAL_TEMP				(VE_TOTAL - 1)
//第1个参数
#define VT_HIGH						((VE_TOTAL_TEMP >> 8) & 0x7)
//第1个参数结束
//第2个参数
#define VT_LOW						(VE_TOTAL_TEMP  & 0xFF)
//第2个参数结束
#define VDP_TOTAL					(DISP_VER_PULSE_WIDTH+DISP_VER_FRONT_PORCH)//不能显示的行数时钟数
#define VDP_TOTAL_TEMP				(VDP_TOTAL - 1)
//第3个参数
#define VDP_HIGH					((VDP_TOTAL_TEMP >> 8) & 0x7)
//第3个参数结束
//第4个参数
#define VDP_LOW						((VDP_TOTAL_TEMP) & 0xFF)
//第4个参数结束
//第5个参数
#define VPW							((DISP_VER_PULSE_WIDTH) -1)
//第5个参数结束
//第6个参数
#define FPS_HIGH					0//垂直同步脉冲的开始位置的高字节
//第6个参数结束
//第7个参数
#define FPS_LOW						0//垂直同步脉冲的开始位置的低字节
//第7个参数结束
/*SSD1963_SET_VERT_PERIOD各位定义*/
/*SSD1963_SET_GPIO_CONF各位定义*/
//第1个参数
#define GPIO0_CFG_HOST				(0 << 4)
#define GPIO1_CFG_HOST				(0 << 5)
#define GPIO2_CFG_HOST				(0 << 6)
#define GPIO3_CFG_HOST				(0 << 7)
#define GPIO0_CFG_LCDC				(1 << 4)
#define GPIO1_CFG_LCDC				(1 << 5)
#define GPIO2_CFG_LCDC				(1 << 6)
#define GPIO3_CFG_LCDC				(1 << 7)

#define GPIO0_OUTPUT				(1 << 0)
#define GPIO1_OUTPUT				(1 << 1)
#define GPIO2_OUTPUT				(1 << 2)
#define GPIO3_OUTPUT				(1 << 3)
#define GPIO0_INPUT					(0 << 0)
#define GPIO1_INPUT					(0 << 1)
#define GPIO2_INPUT					(0 << 2)
#define GPIO3_INPUT					(0 << 3)
//第1个参数结束
//第2个参数
#define GPIO0_SLEEP					(0)			//令gpio0有TFT唤醒功能
#define GPIO0_NORMAL				(1)			//作为普通IO使用
//第2个参数结束

/*SSD1963_SET_GPIO_VALUE各位定义*/
#define SSD1963_GET_GPIO_CONF		0xB9	/*!<  Get the current GPIO configuration*/
#define SSD1963_SET_GPIO_VALUE		0xBA	/*!<  Set GPIO value for GPIO configured as output*/
/*SSD1963_SET_GPIO_VALUE各位定义*/
#define SET_GPIO0_VALUE				(1 << 0)
#define SET_GPIO1_VALUE				(1 << 1)
#define SET_GPIO2_VALUE				(1 << 2)
#define SET_GPIO3_VALUE				(1 << 3)

#define CLR_GPIO0_VALUE				(0 << 0)
#define CLR_GPIO1_VALUE				(0 << 1)
#define CLR_GPIO2_VALUE				(0 << 2)
#define CLR_GPIO3_VALUE				(0 << 3)

/*SSD1963_SET_GPIO_VALUE各位定义*/
/*SSD1963_SET_DBC_CONF各位定义*/
#define DBC_MANUAL_ENABLE				(0 << 6)//使能DBC手工配置
#define DBC_MANUAL_DISABLE				(1 << 6)//除能DBC手工配置
#define TRANSITION_EFFECT_DISABLE		(0 << 6)//除能转换效果
#define TRANSITION_EFFECT_ENSABLE		(1 << 6)//使能转换效果，如果要求快速亮度变化的话，这个位推荐使用
#define ENERGY_DBC_DISABLE				(0 << 2)//DBC除能的时候
#define DBC_CONSERVATIVE_MODE			(1 << 2)//DBC保守模式
#define DBC_NORMAL_MODE					(2 << 2)//DBC正常模式
#define DBC_AGGRESSIVE_MODE				(3 << 2)//DBC激进模式
#define DBC_DISABLE						(0 << 0)//DBC除能
#define DBC_ENABLE						(1 << 0)//DBC使能
/*SSD1963_SET_DBC_CONF各位定义*/
/*SSD1963_SET_PIXEL_DATA_INTERFACE各位定义*/
/*
 像素格式：
 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 24BIT:|r|r|r|r|r|r|r|r|g|g|g|g|g|g|g|g|b|b|b|b|b|b|b|b|只有一个周期
 18BIT:| | | | | | |r|r|r|r|r|r|g|g|g|g|g|g|b|b|b|b|b|b|只有一个周期
 565格式
 16BIT:| | | | | | | | |r|r|r|r|r|g|g|g|g|g|g|b|b|b|b|b|只有一个周期
 packed格式
 16BIT:| | | | | | | | |r|r|r|r|r|r|x|x|g|g|g|g|g|g|x|x|第一个周期
 16BIT:| | | | | | | | |b|b|b|b|b|b|x|x|r|r|r|r|r|r|x|x|第二个周期
 16BIT:| | | | | | | | |g|g|g|g|g|g|x|x|b|b|b|b|b|b|x|x|第三个周期

 9BIT: | | | | | | | | | | | | | | | |r|r|r|r|r|r|g|g|g|第一个周期
 9BIT: | | | | | | | | | | | | | | | |g|g|g|b|b|b|b|b|b|第二个周期

 8BIT: | | | | | | | | | | | | | | | |r|r|r|r|r|r|r|x|x|第一个周期
 8BIT: | | | | | | | | | | | | | | | |g|g|g|g|g|g|g|x|x|第二个周期
 8BIT: | | | | | | | | | | | | | | | |b|b|b|b|b|b|b|x|x|第三个周期
 */
#define PIXEL_FORMAT_8B					0
#define PIXEL_FORMAT_12B				1
#define PIXEL_FORMAT_16B_PACKED			2
#define PIXEL_FORMAT_16B_565			3
#define PIXEL_FORMAT_18B				4
#define PIXEL_FORMAT_24B				5
#define PIXEL_FORMAT_9B					6
/*SSD1963_SET_PIXEL_DATA_INTERFACE各位定义*/

extern void LCD_Clear(uint16_t Color);
extern void ssd1936_init(void);
extern void set_orgin(INT16U x,INT16U y);

#endif /* SSD1963_H_ */

