#ifndef CFG_H__
#define CFG_H__
/**
 *  @file	configure.h
 *  @brief      这个文件是配置doxygen中的分组代码，方便以后对注释文档进行维护与控制一些开关宏。\n
 *
 *      能使用的开关宏有:\n
 *          __DEBUG__:当定义这个宏时，将会打印调试信息，并可以使用调试信息的函数。具体可以看debug_package.h\n
 *          PARAM_CHECK:当定义了这个宏，函数将会进行对参数检查，如果开了将会增加函数的健壮性\n
 *          SYSTICK_INT：当需要使用systick中断的时候，打开这个宏，在systick中，配置好
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date      Apr 24, 2012 6:06:29 PM
 */

/** @addtogroup mystm32
 * @{
 */

/** @addtogroup 变量
 * @{
 */
/**@}*/

/** @addtogroup 宏定义
 * @{
 */
/**@}*/

/** @addtogroup typedef类型
 * @{
 */
/**@}*/

/** @addtogroup 函数
 * @{
 */
/**@}*/

/**@}*/
#define STM32F103VE									1/*!<  CPU型号，1，是这个型号在程序中的代号，最后下面功能能通用的话，也可以定义这个型号*/
#define S3C2440										2/*!<  CPU型号，2，是这个型号在程序中的代号，但最后下面功能能通用的话，也可以定义这个型号*/
/*TFT屏幕在CPU中的控制方式*/
#define TFT_FSMC								1/*!<  TFT是以FSMC驱动方式，例如在stm中控制*/
#define TFT_LCD_CONTROL							2/*!<  TFT是用专门的LCD控制器控制，例如在ARM9控制*/
#define TFT_SIMULATATION_SINAL					3/*!<  模拟LCD时序控制，这种方式比较慢，如果由上面两种方式，一般会放弃这种*/
#define SSD1963_DEVICE							/*!< 使用了SSD1936TFT驱动芯片 */

/*TFT屏幕在CPU中的控制方式*/
//////////////////////////////////////////////////////////////////////////////////
#define __DEBUG__
#define PARAM_CHECK
//#define SYSTICK_INT								 /*!< 这个宏为定义的时候，表明systick将用在systick中断中，否则则只为了单纯的轮询延时。 */
#define TFT_CONTROL_WAY							TFT_FSMC
#define CPU_TYPE								STM32F103VE
#endif
