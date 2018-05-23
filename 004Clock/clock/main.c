/*
 * main.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#include <stdio.h>
#include "S3C2440.h"
#include "led.h"
#include "key.h"


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
  * @brief  main. 
  * @param  None.
  * @retval None.
  */
int main(void)
{
    LED_IO_Init();
    KEY_IO_Init();
    while(1)
    {
        GPF_config(GPF6,0);
        delay(100000);
        GPF_config(GPF6,1);
        delay(100000);        
        KEY_scan();        
    }
    return 0;
}
