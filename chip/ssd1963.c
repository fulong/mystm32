#include "ssd1963.h"
#include "../sysdev/systick.h"
#include "../package/usart_package.h"
#include "image.h"
/**
 *  \file	ssd1963.c
 *  \brief  ssd1963的基础操作函数
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-18 下午5:53:10
 */

static void LCD_WriteCOM(uint16_t RGB_Code);
static void LCD_WriteRAM(uint16_t RGB_Code);
static INT8U ReadData(void);

/* LCD is connected to the FSMC_Bank1_NOR/SRAM1 and NE4 is used as ship select signal */
#define LCD_RAM    *(__IO uint16_t *) ((uint32_t)0x60020000)    //disp Data ADDR
#define LCD_REG    *(__IO uint16_t *) ((uint32_t)0x60000000)	 //disp Reg ADDR
/**
 * @brief  设置原点，显示的图片的将会在这个坐标上写数据
 * @param  x: x轴坐标，最大值800
 * 		y: y轴坐标，最大值480
 *  这个参数可以取得到以下的值：\n
 *  	@arg
 * @retval none
 * \date 2012-5-19 下午5:18:35
 * @note
 */
void set_orgin(INT16U x, INT16U y)
{
	INT32U l = 14400;
	INT16U x_high;
	INT16U x_low;
	INT16U y_high;
	INT16U y_low;
	INT16U *image_temp = (INT16U *)gImage_image ;
	x_high = (((x - 1) >> 8) & 0xFF);
	x_low = ((x - 1) & 0xFF);
	y_high = (((y - 1) >> 8) & 0xFF);
	y_low = ((y - 1) & 0xFF);
	LCD_WriteCOM(SSD1963_SET_COLUMN_ADDRESS);
	LCD_WriteRAM(0);
	LCD_WriteRAM(0);
	LCD_WriteRAM(x_high);
	LCD_WriteRAM(x_low);
	LCD_WriteCOM(SSD1963_SET_PAGE_ADDRESS);
	LCD_WriteRAM(0);
	LCD_WriteRAM(0);
	LCD_WriteRAM(y_high);
	LCD_WriteRAM(y_low);
	LCD_WriteCOM(SSD1963_WRITE_MEMORY_START);

	while (l--)
	{
		LCD_WriteRAM(*image_temp++);
	}
	LCD_WriteCOM(SSD1963_WRITE_MEMORY_CONTINUE);

	while (l--)
	{
		LCD_WriteRAM(*image_temp++);
	}
}

void ssd1936_init(void)
{
#define PLL_M 0x1D
#define PLL_N	0x02
	LCD_WriteCOM(SSD1963_SET_PLL_MN); //Set PLL with OSC = 10MHz (hardware),	Multiplier N = 35, 250MHz < VCO < 800MHz = OSC*(N+1), VCO = 360MHz
	LCD_WriteRAM(PLL_M); //PLL = 内部时钟*(PLL_M+1)/(PLL_N)
	LCD_WriteRAM(PLL_N); //PLL = 100M
	LCD_WriteRAM(0x04); //使分配系数有效

	LCD_WriteCOM(SSD1963_SET_PLL);
	LCD_WriteRAM(0x0001); // PLL enable
	delay_ms(5);
	LCD_WriteCOM(SSD1963_SET_PLL); //稳定后再次启动PLL
	LCD_WriteRAM(0x0003); //now, use PLL output as system clock
	delay_ms(5);
	LCD_WriteCOM(SSD1963_SOFT_RESET); // software reset
	delay_ms(5);
	LCD_WriteCOM(SSD1963_GET_PLL_MN);
#ifdef __DEBUG__
	printfs("about pll setting");
	printfs("\r\n");
	printfs("PLL_M:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("PLL_N:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("PLL status:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
#endif
	/*****************************************************************
	 * 7" TFT model # AT070TN94
	 *****************************************************************/
	//Set LSHIFT freq, i.e. the DCLK with PLL freq 120MHz set previously
	//Typical DCLK for TY700TFT800480 is 33.3MHz(datasheet), experiment shows 30MHz gives a stable result
	//30MHz = 120MHz*(LCDC_FPR+1)/2^20
	//LCDC_FPR = 262143 (0x3FFFF)
	//Time per line = (DISP_HOR_RESOLUTION+DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH+DISP_HOR_FRONT_PORCH)/30 us = 1056/30 = 35.2us
	LCD_WriteCOM(SSD1963_SET_LSHIFT_FREQ); //PLL setting for PCLK, depends on resolution
	LCD_WriteRAM(0x05);
	LCD_WriteRAM(0x47);
	LCD_WriteRAM(0xAD);
	LCD_WriteCOM(SSD1963_GET_LSHIFT_FREQ);
#ifdef __DEBUG__
	printfs("about LSHIFT_FREQ setting");
	printfs("\r\n");
	printfs("high byte:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("mid byte:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("low byte:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
#endif
	LCD_WriteCOM(SSD1963_SET_LCD_MODE); // set 24-bit for 7" panel AT070TN94
	LCD_WriteRAM(
			TFT_PANEL_DATA_WITH_18 + TFT_COLOR_DEPTH_ENHANCEMENT_ENABLE
					+ TFT_FRC_DISABLE + LSHIFT_POLARITY_RISING_EDGE
					+ LLINE_POLARITY_LOW + LFRAME_POLARITY_LOW);
	LCD_WriteRAM(LCD_PANEL_MODE_RGB + TFT_TYPE_TFT_1);
	LCD_WriteRAM(HPS_HIGH); //Set HDP
	LCD_WriteRAM(HPS_LOW);
	LCD_WriteRAM(VPS_HIGH); //Set VDP
	LCD_WriteRAM(VPS_LOW);
	LCD_WriteRAM(EVEN_LINE_RGB_SEQUENECE_RGB + ODD_LINE_RGB_SEQUENECE_RGB);
	LCD_WriteCOM(SSD1963_GET_LCD_MODE);
#ifdef __DEBUG__
	printfs("about SSD1963_SET_LCD_MODE setting");
	printfs("\r\n");
	printfs("TFT_PANEL:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("LCD_PANEL_MODE:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("HPS_HIGH:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("HPS_LOW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("VPS_HIGH:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("VPS_LOW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("LINE_RGB_SEQUENECE:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
#endif

	LCD_WriteCOM(SSD1963_SET_HORI_PERIOD); //Set horizontal period
	LCD_WriteRAM(HT_HIGH); //Set HT
	LCD_WriteRAM(HT_LOW);
	LCD_WriteRAM(HDP_HIGH); //Set HPD,不可显示像素周期
	LCD_WriteRAM(HDP_LOW);
	LCD_WriteRAM(HPW); //Set HPW
	LCD_WriteRAM(LPS_HIGH); //Set LPS
	LCD_WriteRAM(LPS_LOW);
	LCD_WriteRAM(LPSPP);
	LCD_WriteCOM(SSD1963_GET_HORI_PERIOD); //get horizontal period
#ifdef __DEBUG__
	printfs("about SSD1963_SET_HORI_PERIOD setting");
	printfs("\r\n");
	printfs("HT_HIGH:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("HT_LOW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("HDP_HIGH:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("HDP_LOW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("HPW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("LPS_HIGH:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("LPS_LOW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("LPSPP:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
#endif

	LCD_WriteCOM(SSD1963_SET_VERT_PERIOD); //VSYNC
	LCD_WriteRAM(VT_HIGH); //Set VT
	LCD_WriteRAM(VT_LOW);
	LCD_WriteRAM(VDP_HIGH); //Set VPS
	LCD_WriteRAM(VDP_LOW);
	LCD_WriteRAM(VPW); //Set VPW
	LCD_WriteRAM(FPS_HIGH); //Set FPS
	LCD_WriteRAM(FPS_LOW);
	LCD_WriteCOM(SSD1963_GET_VERT_PERIOD); //get horizontal period
#ifdef __DEBUG__
	printfs("about SSD1963_GET_VERT_PERIOD setting");
	printfs("\r\n");
	printfs("VT_HIGH:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("VT_LOW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("VDP_HIGH:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("VDP_LOW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("VPW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("FPS_HIGH:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
	printfs("FPS_LOW:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
#endif
	LCD_WriteCOM(SSD1963_SET_GPIO_VALUE);
	LCD_WriteRAM(
			SET_GPIO0_VALUE + CLR_GPIO1_VALUE + CLR_GPIO2_VALUE
					+ SET_GPIO3_VALUE); //GPIO[3:0] out 1

	LCD_WriteCOM(SSD1963_SET_GPIO_CONF);
	LCD_WriteRAM(
			GPIO0_CFG_HOST + GPIO1_CFG_HOST + GPIO2_CFG_HOST + GPIO3_CFG_HOST
					+ GPIO0_OUTPUT + GPIO1_OUTPUT + GPIO2_OUTPUT + GPIO3_INPUT); //GPIO3=input, GPIO[2:0]=output
	LCD_WriteRAM(GPIO0_NORMAL); //GPIO0 normal

	LCD_WriteCOM(SSD1963_SET_ADDRESS_MODE); //rotation
	LCD_WriteRAM(
			PAGE_ADDRESS_MODE_TOP2BUTTOM + COLUMN_ADDRESS_MODE_L2R
					+ PAGE_COLUMN_ADDRESS_MODE_DISABLE
					+ LINE_ADDRESS_ORDER_TOP2BUTTOM + RGB_NO_CHANGE
					+ DISPLAY_LATCH_DATA_DISABLE + FLIP_HORIZONTAL_L2R
					+ FLIP_VERTICAL_T2B);

	LCD_WriteCOM(SSD1963_SET_PIXEL_DATA_INTERFACE); //pixel data interface
	LCD_WriteRAM(PIXEL_FORMAT_16B_565);

	delay_ms(5);

	LCD_Clear(BLUE);

	LCD_WriteCOM(SSD1963_SET_GAMMA_CURVE); //display on
	LCD_WriteRAM(GAMMA_CURVE1);

	LCD_WriteCOM(SSD1963_SET_DBC_CONF);
	LCD_WriteRAM(
			DBC_MANUAL_ENABLE + TRANSITION_EFFECT_DISABLE + DBC_AGGRESSIVE_MODE
					+ DBC_ENABLE);
	LCD_WriteCOM(SSD1963_GET_DBC_CONF);
#ifdef __DEBUG__
	printfs("about SSD1963_GET_DBC_CONF setting");
	printfs("\r\n");
	printfs("dbc:");
	printf_num(ReadData(), 'h');
	printfs("\r\n");
#endif
	LCD_WriteCOM(SSD1963_SET_DISPLAY_ON); //display on
}
/**
 * @brief 将屏幕刷成一种颜色。
 * @param Color: 要刷的颜色
 *  这个参数可以取得到以下的值：
 *  	@arg BLACK  黑色
 @arg NAVY  	深蓝色
 @arg DGREEN  深绿色
 @arg DCYAN   深蓝绿色
 @arg MAROON    栗色
 @arg PURPLE    紫色
 @arg OLIVE    橄榄色
 @arg LGRAY       浅灰色
 @arg DGRAY  深灰色
 @arg BLUE   蓝色
 @arg GREEN     绿色
 @arg CYAN   蓝绿色
 @arg RED         红色
 @arg MAGENTA      品红色
 @arg YELLOW     黄色
 @arg WHITE    白色
 *
 * @retval none
 * \date 2012-5-19 下午4:26:40
 * @note 填充的颜色也可以自定义，上面只是提供了一些颜色的方案做参考
 */
void LCD_Clear(uint16_t Color)
{
	unsigned int l = _VPS, w;

	LCD_WriteCOM(SSD1963_SET_COLUMN_ADDRESS);
	LCD_WriteRAM(0);
	LCD_WriteRAM(0);
	LCD_WriteRAM(HPS_HIGH);
	LCD_WriteRAM(HPS_LOW);
	LCD_WriteCOM(SSD1963_SET_PAGE_ADDRESS);
	LCD_WriteRAM(0);
	LCD_WriteRAM(0);
	LCD_WriteRAM(VPS_HIGH);
	LCD_WriteRAM(VPS_LOW);
	LCD_WriteCOM(SSD1963_WRITE_MEMORY_START);

	while (l--)
	{
		for (w = 0; w < _HPS; w++)
		{
			LCD_WriteRAM((Color));
		}
	}
}
/**
 * @brief  索引SSD1963写上寄存器index
 * @param  RGB_Code: 要寻址的寄存器
 *  这个参数可以取得到以下的值：\n
 *  	@arg 可以使用的寄存器index都在头文件上定义了
 * @retval none
 * \date 2012-5-19 下午4:16:53
 * @note
 */

void LCD_WriteCOM(uint16_t RGB_Code)
{
	/* Write 16-bit GRAM Reg */
	LCD_REG = RGB_Code;
}
/**
 * @brief  这个配合SSD1963_WRITE_MEMORY_START等指令使用，往frame buffer写上颜色数据
 * @param RGB_Code： 要写的颜色数据
 *  这个参数可以取得到以下的值：\n
 *  	@arg
 * @retval none
 * \date 2012-5-19 下午4:18:46
 * @note
 */
void LCD_WriteRAM(uint16_t RGB_Code)
{
	/* Write 16-bit GRAM Reg */
	LCD_RAM = RGB_Code;
}
/**
 * @brief 当写上了读取功能的寄存器index的话，每使用一次就将会读取一个参数
 * @param
 *  这个参数可以取得到以下的值：\n
 *  	@arg
 * @retval
 * \date 2012-5-19 下午4:22:03
 * @note
 */
INT8U ReadData(void)
{
	return LCD_RAM;
}
