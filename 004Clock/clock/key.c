/*
 * key.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#include "S3C2440.h"
#include "led.h"
#include "key.h"


/**
  * @brief  key io init. 
  * @param  None.
  * @retval None.
  */
void KEY_IO_Init(void)
{
    /*set GPF0,2 and GPG3 as input*/
    GPFCON &= ~((3<<0) | (3<<4));
    GPGCON &= ~(3<<6);
}
/**
  * @brief  key io init. 
  * @param  None.
  * @retval None.
  */
void KEY_scan(void)
{
    int valueF,valueG;
    /*READ input REG */
    valueF = GPFDAT;
    valueG = GPGDAT;
    if(valueF&(1<<0))
    {
        GPF_config(GPF4,1);
    }
    else
    {
        GPF_config(GPF4,0);
    }
    if(valueF&(1<<2))
    {
        GPF_config(GPF5,1);
    }
    else
    {
        GPF_config(GPF5,0);
    }
    if(valueG&(1<<3))
    {
        GPF_config(GPF6,1);
    }
    else
    {
        GPF_config(GPF6,0);
    }        
}
