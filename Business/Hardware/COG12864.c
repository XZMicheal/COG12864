#include "COG12864.h"

#define SDA(x) LCD_DAT(x)
#define SCK(x) LCD_CLK(x)
#define A0(x) LCD_A0(x)

#define CS(x) LCD_CS(x)

#define NRST(x) LCD_NRST(x)
#define LIGHT(x) LCD_LIGHT(!x)

#define COG12864_HAL_DELAY(x) HAL_Delay(x)

#ifdef COG12864_USE_LOCAL_BUFFER

#endif //COG12864_USE_LOCAL_BUFFER

static void COG12864_DelayUs(uint32_t delay)
{
  for(uint32_t i = 0;i < delay;i++)
  {
    for(uint32_t j = 0; j<0x72;j++);
  }
}

/**
  * @brief 写入单字节接口,移植修改这个函数
  * @param
  * @retval
  */
static void COG12864_Write_Byte(uint8_t byte)
{
  for(uint8_t i=0;i<8;i++){
    SCK(0);
    SDA(byte&0x80); //取出最高位
    COG12864_DelayUs(10);
    SCK(1);
    byte<<=1; //左移
  }
}


static void COG12864_WriteCmd(unsigned char cmd)
{
  CS(0);
  A0(0);
  COG12864_Write_Byte(cmd);
  CS(1);
}
static void COG12864_WriteData(unsigned char data)
{
  CS(0);
  A0(1);
  COG12864_Write_Byte(data);
  CS(1);
}
void COG12864_Set_BackLight(uint8_t status)
{
  LIGHT(status);
}
/**
  * @brief 清屏
  * @param
  * @retval
  */
void COG12864_Clear(void)
{
  unsigned char i,j;
  COG12864_WriteCmd(0x40); //起始行：第一行开始
  for(i=0;i<COG12864_DATA_HIGH;i++)
  {
    COG12864_WriteCmd(0xb0+i);
    COG12864_WriteCmd(0x10);
    COG12864_WriteCmd(0x00);
    for(j=0;j<COG12864_WIDTH;j++)
    {
      COG12864_WriteData(0x00);
      COG12864_WriteCmd(0x85);
    }
  }
}
/**
  * @brief 设置位置page column
  * @param
  * @retval
  */
void COG12864_SetPostion(uint8_t page,uint8_t column)
{
  COG12864_WriteCmd(0xb0+page); //设置页地址，每8 行为一页，全屏共64 行，被分成8 页
  COG12864_WriteCmd(0x10+(column>>4&0x0f)); //设置列地址的高4 位
  COG12864_WriteCmd(column&0x0f); //设置列地址的低4 位
}
/**
  * @brief 打印图片数据,
  * @param height 为8的整数倍,自上而下,左到右,上为低
  * @retval
  */
void COG12864_ShowBmp(int page,int column,int height,int width,const unsigned char *data)
{
  int i=0,j=0,k=0;
  int widthMax = column + width;
  int heightMax = (page + height)/8;
  COG12864_WriteCmd(0x40);
  for(i = page,j=0; i < heightMax; i++,j++){
    COG12864_SetPostion(i,column);
    for(k=column;k<widthMax;k++){
      COG12864_WriteData(data[j*width+k]);
    }
  }
}

void COG12864_ShowBmp_Invert(int page,int column,int height,int width,const unsigned char *data,unsigned char invert)
{
  int i=0,j=0,k=0;
  int widthMax = column + width;
  int heightMax = (page + height)/8;
  COG12864_WriteCmd(0x40);
  for(i = page,j=0; i < heightMax; i++,j++){
    COG12864_SetPostion(i,column);
    for(k=column;k<widthMax;k++){
      if(invert){
        COG12864_WriteData(~data[j*width+k]);
      }else{
        COG12864_WriteData(data[j*width+k]);
      }
    }
  }
}

void COG12864_ReverseShow(uint8_t show)
{
  if(show){
    COG12864_WriteCmd(0xa7);
  }else{
    COG12864_WriteCmd(0xa6);
  }
  
}
/**
  * @brief LCM12864初始化
  * @param
  * @retval
  */
void COG12864_Init(void)
{
  
  NRST(0); //低电平复位
  COG12864_DelayUs(1000);
  NRST(1); //复位完毕
  COG12864_DelayUs(1000);
  COG12864_WriteCmd(0xe2); //软复位
  COG12864_DelayUs(5);
  COG12864_WriteCmd(0x2c); //升压步聚1
  COG12864_DelayUs(5);
  COG12864_WriteCmd(0x2e); //升压步聚2
  COG12864_DelayUs(5);
  COG12864_WriteCmd(0x2f); //升压步聚3
  COG12864_DelayUs(5);
  COG12864_WriteCmd(0x27); //粗调对比度，可设置范围0x20～0x27
  COG12864_WriteCmd(0x81); //微调对比度
  COG12864_WriteCmd(0x00); //微调对比度的值，可设置范围0x00～0x3f
  COG12864_WriteCmd(0xa2); //1/9 偏压比（bias）
  COG12864_WriteCmd(0xc8); //行扫描顺序：从上到下
  COG12864_WriteCmd(0xa0); //列扫描顺序：从左到右
  COG12864_WriteCmd(0x40); //起始行：第一行开始
  COG12864_WriteCmd(0xAf); //开显示
  
  COG12864_DelayUs(10);
  COG12864_WriteCmd(0x30);
  COG12864_DelayUs(5);
  COG12864_WriteCmd(0x30);
  COG12864_DelayUs(10);
  COG12864_WriteCmd(0x0c);
  
  LIGHT(1);
  COG12864_Clear();
  COG12864_DelayUs(1000);
}

void COG12864_Refresh(void)
{
  COG12864_WriteCmd(0xe2); //软复位
//  wzLcm12864WriteCmd(0x27); //粗调对比度，可设置范围0x20～0x27
//  wzLcm12864WriteCmd(0x81); //微调对比度
//  wzLcm12864WriteCmd(0x00); //微调对比度的值，可设置范围0x00～0x3f
//  wzLcm12864WriteCmd(0xa2); //1/9 偏压比（bias）
  COG12864_WriteCmd(0xc8); //行扫描顺序：从上到下
  COG12864_WriteCmd(0xa0); //列扫描顺序：从左到右
  COG12864_WriteCmd(0x40); //起始行：第一行开始
  COG12864_WriteCmd(0xAf); //开显示
}
