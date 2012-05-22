/**
 *  \file	libmath.c
 *  \brief      
 *
 *  \author 	fulong\n
 *  Mail:fulong.mo@gmail.com\n
 *  \version: 	1.0\n
 *  compiler:GCC\n
 *  \date       2012-4-28 上午10:12:02
 */
#include "libmath.h"

#define WRONG                   1
#define RIGHT                   0

/**
  * @brief  将十进制变成二进制或者十六进制，由第三个参数决定，并存在buf缓冲区中。\n
  *         将disbuf最好满足有32个元素，不然可能会有严重后果
  * @param disnum
  *            这是一个要转换的数，为32位无符号整数，因而最大数值为2的31次方-1.\n
  * @param disbuf
  *            用来存储转换后的数值的缓冲区，这个数值的取值取决于缓冲区的大小。\n
  * @param hex_or_bin
  *           选择将目标数字转换为哪种方式\n
  *           ‘b’：转化为二进制。\n
  *           ‘h’：转化为十六进制。
  * @retval   math_status
                           1，为有误，可能参数检查不通过，或其他问题 \n
                           0，正确结束程序\n
                           disbuf，是间接地返回参数，可以看为返回转换后的字符串数组。
  */

math_status oct_transfer(uint32 disnum,INT8S* disbuf,const uint32 hex_or_bin)
{
  uint8 num_char[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  uint8 buf1[32];                       //暂存栈区
  uint8 *temp = buf1;
#ifdef PARAM_CHECK
  if((hex_or_bin != 'b') && (hex_or_bin != 'h'))
      return WRONG;
#endif
  if(disnum)
    {
      switch(hex_or_bin){
         case 'b'://2进制
           while(disnum)
          {
      //将要转换的数字所有的余数压进暂存栈区中，退出此循环时，就已经得到数的二进制编码了。
            *temp = num_char[disnum % 2];
            disnum >>= 1;
            temp++;
          }
           break;

         case 'h'://16进制
           while(disnum)
          {
      //将要转换的数字所有的余数压进暂存栈区中，退出此循环时，就已经得到数的二进制编码了。
            *temp = num_char[disnum % 16];
            disnum >>= 4;
            temp++;
          }
           break;
         default:
           break;
        }
      //弹出暂存栈区中的数字，这时能以正确顺序显示。
      while((--temp) != buf1)
        {
          *(disbuf++) = *temp;
        }
      *disbuf = *temp;
      if( hex_or_bin == 'b')
         {//这个数标识为二进制
            *(disbuf+1) = 'B';
         }
      else
        {//这个数标识为十六进制
          *(disbuf+1) = 'H';
        }
      *(disbuf+2) = 0;

      return RIGHT;
     }
    *disbuf = '0';
    *(disbuf+1) = 0;
    return RIGHT;
}

