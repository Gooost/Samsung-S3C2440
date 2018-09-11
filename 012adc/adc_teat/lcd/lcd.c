/*
 * lcd.c
 *  
 *  Created on: 2018.05.12
 *      Author: wangmeng
 */
#include "lcd.h"
#include "lcd_controller.h"

#define LCD_NUM 10

static p_lcd_params p_array_lcd[LCD_NUM];
static p_lcd_params g_p_lcd_selected;

/**
  * @brief 	
  * @param  
  * @retval 
  */
int register_lcd(p_lcd_params plcd)
{
	int i;
	for (i = 0; i < LCD_NUM; i++)
	{
		if (!p_array_lcd[i])
		{
			p_array_lcd[i] = plcd;
			return i;
		}
	}
	return -1;		
}
/**
  * @brief 	
  * @param  
  * @retval 
  */
int select_lcd(char *name)
{
	int i;
	for (i = 0; i < LCD_NUM; i++)
	{
		if (p_array_lcd[i] && !strcmp(p_array_lcd[i]->name, name))
		{
			g_p_lcd_selected = p_array_lcd[i];
			return i;
		}
	}
	return -1;		
}
/**
  * @brief 	
  * @param  
  * @retval 
  */
void get_lcd_params(unsigned int *fb_base, int *xres, int *yres, int *bpp)
{
	*fb_base = g_p_lcd_selected->fb_base;
	*xres = g_p_lcd_selected->xres;
	*yres = g_p_lcd_selected->yres;
	*bpp = g_p_lcd_selected->bpp;
}
/**
  * @brief 	
  * @param  
  * @retval 
  */
void lcd_enable(void)
{
	lcd_controller_enable();
}
/**
  * @brief 	
  * @param  
  * @retval 
  */
void lcd_disable(void)
{
	lcd_controller_disable();
}
/**
  * @brief 	
  * @param  
  * @retval 
  */
int lcd_init(void)
{
	/* ע��LCD */
	lcd_4_3_add();

	/* ע��LCD������ */
	lcd_contoller_add();
	
	/* ѡ��ĳ��LCD */
	select_lcd("lcd_4.3");

	/* ѡ��ĳ��LCD������ */
	select_lcd_controller("s3c2440");

	/* ʹ��LCD�Ĳ���, ��ʼ��LCD������ */
	lcd_controller_init(g_p_lcd_selected);
}





