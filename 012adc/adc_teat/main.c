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
#include "nandflash.h"

char g_charA = 'A';

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
    led_io_init();
    nand_init();
    //key_io_init();
    //interrupt_init();
	//key_eint_init();
    //timer_init();

    while(1)
    {
        putchar(g_charA);
        g_charA++;
        delay(100000);
        if(g_charA>'Z')
        {
            g_charA = 'A';
            puts("\r\n");     
        }
        //nand_flash_test();
        lcd_test();
    }
    return 0;
}
