/*
 * led.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#ifndef __LED_H
#define __LED_H


#define GPF0     0
#define GPF1     1
#define GPF2     2
#define GPF3     3
#define GPF4     4
#define GPF5     5
#define GPF6     6
#define GPF7     7


void led_io_init(void);
void gpf_config(unsigned char port,unsigned char val);

#endif // __LED_H
