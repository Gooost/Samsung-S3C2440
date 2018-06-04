/*
 * init.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#include "S3C2440.h"
#include "init.h"

/**
  * @brief  sdram init. 
  * @param  None.
  * @retval None.
  */
void sdram_init(void)
{
    BWSCON   = 0x22000000;
    BANKCON6 = 0x18001;
    BANKCON7 = 0x18001;
    REFRESH  = 0x8404f5;
    BANKSIZE = 0xb1;
    MRSRB6   = 0x20;
    MRSRB7   = 0x20;
}
/**
  * @brief  copy2sdram . copy all data to sdram.
  * @param  none
  * @retval None.
  */
void copy2sdram(void)
{
    /*从lds文件中获取 __code_start,__bss_start
    **然后从0地址把数据复制到 __code_start
    */
    extern int __code_start,__bss_start;
    volatile unsigned int *dest = (volatile unsigned int *)&__code_start;
    volatile unsigned int *end  = (volatile unsigned int *)&__bss_start;
    volatile unsigned int *src  = (volatile unsigned int *)0;

    while(dest < end)
    {
        *dest++ = *src++;
    }
}
/**
  * @brief  clean_bss . 
  * @param  none.
  * @retval None.
  */
void clean_bss(void)
{
    /*从lds文件中获取 _end,__bss_start
    **然后把地址内容清零
    */
    extern int _end,__bss_start;
    volatile unsigned int *dest = (volatile unsigned int *)&__bss_start;
    volatile unsigned int *end  = (volatile unsigned int *)&_end;


    while(dest <= end)
    {
        *dest++ = 0;
    }
}


/**
  * @brief  sdram test. 
  * @param  None.
  * @retval -1 sdram is offline,0 sdram is online.
  */
int sdram_test(void)
{
    volatile unsigned char *p = (volatile unsigned char *) 0x30000000;
    int i;

    /*write sdram test*/
    for(i = 0;i<1000;i++)
        p[i] = 0x55;
    /*read sdram test*/
    for(i = 0;i<1000;i++)
    {
        if(p[i] != 0x55)
        {
            return -1;           
        }
        else
        {
            printf("0x%x\n\r", p[i]) ;
        }
    }
    return 0;

}
