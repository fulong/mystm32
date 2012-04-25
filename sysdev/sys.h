/**
 *  \file     sys.h
 *  \brief   IO口控制的宏定义\n
 *
 *
 *  \author     fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version:   1.0\n
 *  compiler:GCC\n
 *  \date      Apr 24, 2012 2:39:58 PM
 */

#ifndef SYS_H_
#define SYS_H_

#include "../stm32f103/STM32F10x/stm32f10x.h"


/** @brief IO口映射到位地址的存储地址*/
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
/** @brief 将ADDR强制转换为地址*/
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
/** @brief 指定要映射那个地址，这个由bitnum与共同影响的*/
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

/** @brief IOA的输出控制首地址*/
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C
/** @brief IOB的输出控制首地址*/
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C
/** @brief IOC的输出控制首地址*/
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C
/** @brief IOD的输出控制首地址*/
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C
/** @brief IOE的输出控制首地址*/
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C
/** @brief IOF的输出控制首地址*/
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C
/** @brief IOG的输出控制首地址*/
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C

/** @brief IOA的输入控制首地址*/
#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808
/** @brief IOB的输入控制首地址*/
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08
/** @brief IOC的输入控制首地址*/
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008
/** @brief IOD的输入控制首地址*/
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408
/** @brief IOE的输入控制首地址*/
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808
/** @brief IOF的输入控制首地址*/
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08
/** @brief IOG的输入控制首地址*/
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08


/** @brief N的值不能超过15，给他赋值代表对这个位进行置位或清零，A设为输出口*/
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)
/** @brief N的值不能超过15，读这个口的值，只有一位，零或一，A设为输入口*/
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)

/** @brief N的值不能超过15，给他赋值代表对这个位进行置位或清零，B设为输出口*/
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)
/** @brief N的值不能超过15，读这个口的值，只有一位，零或一，B设为输入口*/
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)

/** @brief N的值不能超过15，给他赋值代表对这个位进行置位或清零，C设为输出口*/
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)
/** @brief N的值不能超过15，读这个口的值，只有一位，零或一，C设为输入口*/
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)

/** @brief N的值不能超过15，给他赋值代表对这个位进行置位或清零，D设为输出口*/
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)
/** @brief N的值不能超过15，读这个口的值，只有一位，零或一，D设为输入口*/
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)

/** @brief N的值不能超过15，给他赋值代表对这个位进行置位或清零，E设为输出口*/
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)
/** @brief N的值不能超过15，读这个口的值，只有一位，零或一，E设为输入口*/
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)

/** @brief N的值不能超过15，给他赋值代表对这个位进行置位或清零，F设为输出口*/
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)
/** @brief N的值不能超过15，读这个口的值，只有一位，零或一，F设为输入口*/
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)

/** @brief N的值不能超过15，给他赋值代表对这个位进行置位或清零，G设为输出口*/
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)
/** @brief N的值不能超过15，读这个口的值，只有一位，零或一，G设为输入口*/
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)

#endif /* SYS_H_ */
