/*
 * uart.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#include "S3C2440.h"
#include "uart.h"


/**
  * @brief  uart  init. 
  * @param  None.
  * @retval None.
  */
void uart_init(void)
{
    /*set GPH2,3 use TXD0 ,RXD0*/
    GPHCON &= ~((3<<4) | (3<<6));
    GPHCON |=  ((2<<4) | (2<<6));
    /*enable pull-up resistor*/
    GPHUP  &= ~((1<<2) | (1<<3));
    /*UBRDIVn = (int)( 50000000 / ( 115200 x 16) ) ¨C1 = 26
    * UART_clock = PCLK
    * buad_rate  = 115200
    */
    UCON0   = 0x00000005;//PCLK,Interrupt request or polling mode
    UBRDIV0 = 26;

    /*set UART line control registers 8n1 and No parity*/
    ULCON0  = 0x03;
    /**/
}

/**
  * @brief  put char to uart. 
  * @param  None.
  * @retval None.
  */
int putchar(int c)
{
    /*UTRSTAT0*/

    /*WRITE UTXHO*/
    while(!(UTRSTAT0 & (1<<2)));
    UTXH0 = (unsigned char ) c;
}
/**
  * @brief  get char from uart.
  * @param  None.
  * @retval None.
  */
int getchar(void)
{
    /*READ UTXHO*/
    while(!(UTRSTAT0 & (1<<0)));
    return URXH0;
}
/**
  * @brief  put char to uart. 
  * @param  None.
  * @retval None.
  */
int puts(const char *s )
{
  while(*s)
  {
    putchar(*s);
    s++;
  }
}

