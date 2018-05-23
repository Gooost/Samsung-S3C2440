/*
 * led_on.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#include <stdio.h>
#include "S3C2440.h"

#define GPF0     0
#define GPF1     1
#define GPF2     2
#define GPF3     3
#define GPF4     4
#define GPF5     5
#define GPF6     6
#define GPF7     7


/**
  * @brief  when I/O set as output,Set GPF port value. 
  * @param  port: port can be 0-7.
  * @param  val: val can be 0 or 1.
  * @retval None.
  */
void GPF_config(unsigned char port,unsigned char val)
{
        if(val==0)
        {
            GPFDAT &= ~ (1<<port);
        }
        else
        {
            GPFDAT |= (1<<port);
        } 

}
/**
  * @brief  for a short delay. 
  * @param  num: delay time.
  * @retval None.
  */
void delay(volatile int num)
{
    while(num--);
}
/**
  * @brief  led io init. 
  * @param  None.
  * @retval None.
  */
void LED_IO_Init(void)
{
    /*set GPF4,5,6 as output*/
    GPFCON &= ~((3<<8) | (3<<10) | (3<<12));
    GPFCON |=  ((1<<8) | (1<<10) | (1<<12)); 
    /*set leds off*/
    GPFDAT |= ((1<<4) | (1<<5) | (1<<6)); 
}
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
        GPF_config(4,1);
    }
    else
    {
        GPF_config(4,0);
    }
    if(valueF&(1<<2))
    {
        GPF_config(5,1);
    }
    else
    {
        GPF_config(5,0);
    }
    if(valueG&(1<<3))
    {
        GPF_config(6,1);
    }
    else
    {
        GPF_config(6,0);
    }        
}

/**
  * @brief  main. 
  * @param  None.
  * @retval None.
  */
int main(void)
{
    LED_IO_Init();
    while(1)
    {
        KEY_scan();        
    }
    return 0;
}



