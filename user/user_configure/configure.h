#ifndef CFG_H__
#define CFG_H__
/**
 *  @file	configure.h
 *  @brief      这个文件是配置doxygen中的分组代码，方便以后对注释文档进行维护与控制一些开关宏
 *
 *      能使用的开关宏有:\n
 *          __DEBUG__:当定义这个宏时，将会打印调试信息，并可以使用调试信息的函数。具体可以看debug_package.h\n
 *          PARAM_CHECK:当定义了这个宏，函数将会进行对参数检查，如果开了将会增加函数的健壮性\n
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

#define __DEBUG__
#define PARAM_CHECK

#endif
