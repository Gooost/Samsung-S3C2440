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
#include "uart.h"

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
    unsigned char c;

    led_io_init();
    key_io_init();
    uart_init();/*115200 8n1*/
    puts("hello world !!!\r\n");
    while(1)
    {
        c = getchar();
        if(c=='\r')
        {
            putchar('\n');
        }
        else if(c=='\n')
        {
            putchar('\r');
        }
        putchar(c);
        gpf_config(GPF6,0);
        delay(100000);
        gpf_config(GPF6,1);
        delay(100000);        
        key_scan();        
    }
    return 0;
}
