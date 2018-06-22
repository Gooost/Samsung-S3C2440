/*
 * led.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#include "S3C2440.h"
#include "led.h"

/**
  * @brief  when I/O set as output,Set GPF port value. 
  * @param  port: port can be 0-7.
  * @param  val: val can be 0 or 1.
  * @retval None.
  */
void gpf_config(unsigned char port,unsigned char val)
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
  * @brief  led io init. 
  * @param  None.
  * @retval None.
  */
void led_io_init(void)
{
    /*set GPF4,5,6 as output*/
    GPFCON &= ~((3<<8) | (3<<10) | (3<<12));
    GPFCON |=  ((1<<8) | (1<<10) | (1<<12)); 
    /*set leds off*/
    GPFDAT |= ((1<<4) | (1<<5) | (1<<6)); 
}





