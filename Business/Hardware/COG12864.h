#ifndef __COG_12864_H__
#define __COG_12864_H__

#ifdef __cplusplus
extern "C"{
#endif //__cplusplus
  
#include "stdint.h"
#include "HwConfig.h"
  
#define COG12864_HIGH 64//64ÐÐ=8*8
#define COG12864_WIDTH 132
  
#define COG12864_SHOW_HIGH 64
#define COG12864_SHOW_WIDTH 128
  
#define COG12864_DATA_HIGH 8
#define COG12864_DATA_WIDTH 132
  
void COG12864_Set_BackLight(uint8_t status);
void COG12864_Clear(void);
void COG12864_SetPostion(uint8_t page,uint8_t column);
void COG12864_ShowBmp(int page,int column,int height,int width,const unsigned char *data);
void COG12864_ShowBmp_Invert(int page,int column,int height,int width,const unsigned char *data,unsigned char invert);
void COG12864_ReverseShow(uint8_t show);
void COG12864_Init(void);
void COG12864_Refresh(void);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__COG_12864_H__
