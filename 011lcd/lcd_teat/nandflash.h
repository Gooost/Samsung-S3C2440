/*
 * nandflash.h
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#ifndef __NANDFLASH_H
#define __NANDFLASH_H

void nand_init(void);
void nand_read(unsigned int addr, unsigned char *buf, unsigned int len);
void nand_flash_test(void);

#endif // __NANDFLASH_H

