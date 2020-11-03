#ifndef __FONT_GB2312_H__
#define __FONT_GB2312_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

  typedef struct{
    char index[2];
    unsigned char code[32];
  }FontGB2312_t;

void FontGB2312_Init(void);
const unsigned char * Font_GetChar(char ch);
const unsigned char * FontGB2312_Get_ChineseCode(const char *code);

#endif //__FONT_GB2312_H__
