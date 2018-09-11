/*
 * uart.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#include "S3C2440.h"
#include "uart.h"

//==================================================================================================
typedef char *  va_list;
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
//#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_arg(ap,t)    ( *(t *)( ap=ap + _INTSIZEOF(t), ap- _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )

//==================================================================================================
unsigned char hex_tab[]={'0','1','2','3','4','5','6','7',\
		                 '8','9','a','b','c','d','e','f'};

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
    
	puts("uart 115200 8n1 \r\n");
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
/**
  * @brief  put char to uart. 
  * @param  None.
  * @retval None.
  */
static int out_num(long n, int base,char lead,int maxwidth) 
{
	unsigned long m = 0;
	char buf[MAX_NUMBER_BYTES], *s = buf + sizeof(buf);
	int count = 0,i = 0;
			
	*--s = '\0';
	
	if (n < 0)
	{
		m = -n;
	}
	else
	{
		m = n;
	}
	
	do
	{
		*--s = hex_tab[m % base];
		count++;
	}while ((m /= base) != 0);
	
	if( maxwidth && count < maxwidth)
	{
		for (i = maxwidth - count; i; i--)	
			*--s = lead;
	}

	if (n < 0)
		*--s = '-';

	return puts(s);
}
/**
  * @brief  put char to uart. 
  * @param  None.
  * @retval None.
  */   
static int my_vprintf(const char *fmt, va_list ap) 
{
	char lead = ' ';
	int  maxwidth = 0;
	
	 for(; *fmt != '\0'; fmt++)
	 {
			if (*fmt != '%') 
			{
				putchar(*fmt);
				continue;
			}
			fmt++;
			if(*fmt == '0')
			{
				lead = '0';
				fmt++;	
			}
			lead = ' ';		
			maxwidth = 0;	

			while(*fmt >= '0' && *fmt <= '9')
			{
				maxwidth *=10;
				maxwidth += (*fmt - '0');
				fmt++;
			}
		
			switch (*fmt) 
			{
				case 'd': out_num(va_arg(ap, int),          10,lead,maxwidth); break;
				case 'o': out_num(va_arg(ap, unsigned int),  8,lead,maxwidth); break;				
				case 'u': out_num(va_arg(ap, unsigned int), 10,lead,maxwidth); break;
				case 'x': out_num(va_arg(ap, unsigned int), 16,lead,maxwidth); break;
				case 'c': putchar(va_arg(ap, int   )); break;		
				case 's': puts(va_arg(ap, char *)); break;		  		
				
				default:  
					putchar(*fmt);
				break;
			}
		}
	return 0;
}
/**
  * @brief  put char to uart. 
  * @param  None.
  * @retval None.
  */
int printf(const char *fmt, ...) 
{
	va_list ap;

	va_start(ap, fmt);
	my_vprintf(fmt, ap);	
	va_end(ap);
	return 0;
}

void printException(unsigned int cpsr, char *s)
{
	puts(s);
	printf(",%x\r\n",cpsr);
}
