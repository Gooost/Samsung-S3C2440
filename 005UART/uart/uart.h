/*
 * uart.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#ifndef __UART_H
#define __UART_H

void uart_init(void);
int putchar(int c);
int getchar(void);
int puts(const char *s );

#endif // __UART_H
