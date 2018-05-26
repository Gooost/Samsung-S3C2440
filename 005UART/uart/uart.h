/*
 * uart.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#ifndef __UART_H
#define __UART_H

#define  __out_putchar      putchar
#define  MAX_NUMBER_BYTES   64


void uart_init(void);
int putchar(int c);
int getchar(void);
int puts(const char *s );
int printf(const char *fmt, ...);
int my_printf_test(void);

#endif // __UART_H
