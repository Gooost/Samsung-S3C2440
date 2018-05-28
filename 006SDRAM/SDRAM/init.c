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
