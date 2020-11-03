#include "Display.h"

static uint8_t sLocalSyncBuffer[COG12864_DATA_WIDTH*COG12864_DATA_HIGH] = {0};

static int find_array_postion(int row,int column)
{
  return row*COG12864_WIDTH + column;
}

void COG12864_Set_LocalBuffer(uint8_t row,uint8_t column,uint8_t height,uint8_t width,uint8_t data[],uint8_t invert)
{
  if(row > 8) row /= 8;
    int postionNo = 0;
    int i=0,j=0,k=0,h=height/8;
    for(i=0,j=column;i<width;i++,j++){
      for(k=0;k<h;k++){
        postionNo = find_array_postion(row+k,j);
        if(invert){
          sLocalSyncBuffer[postionNo] = (~data[i*h+k]);
        }else{
          sLocalSyncBuffer[postionNo] = (data[i*h+k]);
        }
      }
    }
}

void Display_Init(void)
{
  FontGB2312_Init();
  COG12864_Init();
}


void Display_Clear(void)
{
  memset(sLocalSyncBuffer, 0, COG12864_DATA_HIGH*COG12864_DATA_WIDTH);
}
/**
  * @brief 将缓存数据写入设备中,可以用定时器,也可以用在任务中
  * @param
  * @retval
  */
void Display_Refresh(void)
{
  COG12864_Refresh();
  COG12864_ShowBmp(0,0,COG12864_HIGH,COG12864_WIDTH,sLocalSyncBuffer);
}

void Display_Draw_Point(int x,int y,const unsigned char point)
{
  int m = y / 8;
  int n = y % 8;
  if((COG12864_WIDTH > x && x >= 0) && (COG12864_HIGH > y && y >= 0)){
    if(point){
      MSET_BIT(sLocalSyncBuffer[m*COG12864_DATA_WIDTH+x],n);
    }else{
      MCLR_BIT(sLocalSyncBuffer[m*COG12864_DATA_WIDTH+x],n);
    }
  }
}

void Display_Draw_A_HLine(int x,int y,int width,unsigned char invert)
{
  width += x;
  for(int i = x; i < width; i++){
    Display_Draw_Point(i,y,invert);
  }
}

void Display_Draw_A_VLine(int x,int y,int heigh,unsigned char invert)
{
  heigh += y ;
  for(int i = y; i < heigh; i++){
    Display_Draw_Point(x,i,invert);
  }
}
void Display_Draw_Rectangle(int x,int y,int heigh,int width,unsigned char invert)
{
  Display_Draw_A_HLine(x,y,width,invert);
  Display_Draw_A_HLine(x,y+heigh-1,width,invert);
  Display_Draw_A_VLine(x,y,heigh,invert);
  Display_Draw_A_VLine(x+width-1,y,heigh,invert);
}

static void Display_Draw_VLine_8(int x,int y,unsigned char data)
{
  for(int j = 0;j < 8; j++){
    Display_Draw_Point(x,y+j,MREAD_BIT(data,j));
  }
}
static void Display_Draw_VLine_Byte(int x,int y,unsigned char data,unsigned char invert)
{
  if(invert){
    Display_Draw_VLine_8(x,y,data);
  }else{
    Display_Draw_VLine_8(x,y,~data);
  }
  
}
static void Display_Data(int x,int y,int heigh,int width,const unsigned char data[],unsigned char invert)
{
  int i,j,k,m,n;
  m = heigh / 8;
  n = heigh % 8;
  //8倍数行数据处理
  
  for(i = 0;i < width; i++){
    for(k = 0;k < m; k++){
      Display_Draw_VLine_Byte(x+i,y+k*8,data[i*2+k],invert);
    }
  }
  //非8倍数数据处理
  if(n == 0){
    return ;
  }
  for(i = 0;i < width; i++){
    for(j = 0;j < n; j++){
      Display_Draw_VLine_Byte(x+k*8+i,y+k*8,data[i*2+k],invert);
    }
  }
}

void Display_PrintChar(int x,int y,char ch,unsigned char invert)
{
  Display_Data(x,y,16,8,Font_GetChar(ch),invert);
}
void Display_PrintString(int x,int y,char *str,unsigned char invert)
{
  int len = strlen(str);
  for(int i = 0;i < len; i++){
    Display_PrintChar(x+i*8,y,str[i],invert);
  }
}
//FontGB2312_Get_ChineseCode
void Display_PrintChinese(int x,int y,char *code,unsigned char invert)
{
  int len = strlen(code)/2;
  for(int i=0;i<len;i++){
    Display_Data(x+i*16,y,16,16,FontGB2312_Get_ChineseCode(&code[i*2]),invert);
  }
}