/*
 * main.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#include "S3C2440.h"
#include "init.h"
#include "led.h"
#include "key.h"
#include "uart.h"


/**
  * @brief  main. 
  * @param  None.
  * @retval None.
  */
int main(void)
{
    unsigned char c;

    sdram_init();
    led_io_init();
    key_io_init();
    uart_init();/*115200 8n1*/

    printf ("sdram test %d \r\n",sdram_test());

    while(1)
    {
        c = getchar();
        gpf_config(GPF6,0);
        if(c=='\r')
        {
            putchar('\n');
        }
        else if(c=='\n')
        {
            putchar('\r');
        }

        putchar(c);
        gpf_config(GPF6,1);     
        key_scan();        
    }
    return 0;
}
