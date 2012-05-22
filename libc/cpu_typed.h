/**
 *  \file	cpu_typed.h
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-5-3 上午10:16:18
 */


#ifndef CPU_TYPED_H_
#define CPU_TYPED_H_

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char           BOOLEAN;
typedef unsigned char           INT8U;                    /*!< Unsigned  8 bit quantity*/
typedef signed   char           INT8S;                    /*!< Signed    8 bit quantity */
typedef char                    INT8;                     /*!< Signed    8 bit quantity*/
typedef unsigned short          INT16U;                   /*!< Unsigned 16 bit quantity*/
typedef signed   short          INT16S;                   /*!< Signed   16 bit quantity*/
typedef unsigned int            INT32U;                   /*!< Unsigned 32 bit quantity*/
typedef signed   int            INT32S;                   /*!< Signed   32 bit quantity*/


#define BYTE                    INT8S                     /* Define data types for backward compatibility ...   */
#define UBYTE                   INT8U                     /* ... to uC/OS V1.xx.  Not actually needed for ...   */
#define WORD                    INT16S                    /* ... uC/OS-II.                                      */
#define UWORD                   INT16U
#define LONG                    INT32S
#define ULONG                   INT32U


#endif /* CPU_TYPED_H_ */
