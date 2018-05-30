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

char g_chara = 'a';
char g_charA = 'A';
int g_b     = 0;

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
    key_io_init();
    uart_init();/*115200 8n1*/

    while(1)
    {
        putchar(g_charA);
        g_charA++;
        putchar(g_chara);
        g_chara++;
        delay(100000);
        if(g_charA=='Z')
        {
            g_charA = 'A';
            g_chara = 'a'; 
            printf(" 0x%x",g_b++);
            putchar(0x0a);  
            putchar(0x0d);    
        }
 
    }
    return 0;
}
