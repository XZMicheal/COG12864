#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "COG12864.h"
#include "Font_GB2312.h"

void COG12864_Set_LocalBuffer(uint8_t row,uint8_t column,uint8_t height,uint8_t width,uint8_t data[],uint8_t invert);
void Display_Init(void);
void Display_Clear(void);
void Display_Refresh(void);
void Display_Draw_Point(int x,int y,unsigned char point);
void Display_Draw_A_HLine(int x,int y,int width,unsigned char invert);
void Display_Draw_A_VLine(int x,int y,int heigh,unsigned char invert);
void Display_Draw_Rectangle(int x,int y,int heigh,int width,unsigned char invert);
void Display_PrintChar(int x,int y,char ch,unsigned char invert);
void Display_PrintString(int x,int y,char *str,unsigned char invert);
void Display_PrintChinese(int x,int y,char *code,unsigned char invert);

#endif //__DISPLAY_H__
