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
  * @brief д�뵥�ֽڽӿ�,��ֲ�޸��������
  * @param
  * @retval
  */
static void COG12864_Write_Byte(uint8_t byte)
{
  for(uint8_t i=0;i<8;i++){
    SCK(0);
    SDA(byte&0x80); //ȡ�����λ
    COG12864_DelayUs(10);
    SCK(1);
    byte<<=1; //����
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
  * @brief ����
  * @param
  * @retval
  */
void COG12864_Clear(void)
{
  unsigned char i,j;
  COG12864_WriteCmd(0x40); //��ʼ�У���һ�п�ʼ
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
  * @brief ����λ��page column
  * @param
  * @retval
  */
void COG12864_SetPostion(uint8_t page,uint8_t column)
{
  COG12864_WriteCmd(0xb0+page); //����ҳ��ַ��ÿ8 ��Ϊһҳ��ȫ����64 �У����ֳ�8 ҳ
  COG12864_WriteCmd(0x10+(column>>4&0x0f)); //�����е�ַ�ĸ�4 λ
  COG12864_WriteCmd(column&0x0f); //�����е�ַ�ĵ�4 λ
}
/**
  * @brief ��ӡͼƬ����,
  * @param height Ϊ8��������,���϶���,����,��Ϊ��
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
  * @brief LCM12864��ʼ��
  * @param
  * @retval
  */
void COG12864_Init(void)
{
  
  NRST(0); //�͵�ƽ��λ
  COG12864_DelayUs(1000);
  NRST(1); //��λ���
  COG12864_DelayUs(1000);
  COG12864_WriteCmd(0xe2); //��λ
  COG12864_DelayUs(5);
  COG12864_WriteCmd(0x2c); //��ѹ����1
  COG12864_DelayUs(5);
  COG12864_WriteCmd(0x2e); //��ѹ����2
  COG12864_DelayUs(5);
  COG12864_WriteCmd(0x2f); //��ѹ����3
  COG12864_DelayUs(5);
  COG12864_WriteCmd(0x27); //�ֵ��Աȶȣ������÷�Χ0x20��0x27
  COG12864_WriteCmd(0x81); //΢���Աȶ�
  COG12864_WriteCmd(0x00); //΢���Աȶȵ�ֵ�������÷�Χ0x00��0x3f
  COG12864_WriteCmd(0xa2); //1/9 ƫѹ�ȣ�bias��
  COG12864_WriteCmd(0xc8); //��ɨ��˳�򣺴��ϵ���
  COG12864_WriteCmd(0xa0); //��ɨ��˳�򣺴�����
  COG12864_WriteCmd(0x40); //��ʼ�У���һ�п�ʼ
  COG12864_WriteCmd(0xAf); //����ʾ
  
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
  COG12864_WriteCmd(0xe2); //��λ
//  wzLcm12864WriteCmd(0x27); //�ֵ��Աȶȣ������÷�Χ0x20��0x27
//  wzLcm12864WriteCmd(0x81); //΢���Աȶ�
//  wzLcm12864WriteCmd(0x00); //΢���Աȶȵ�ֵ�������÷�Χ0x00��0x3f
//  wzLcm12864WriteCmd(0xa2); //1/9 ƫѹ�ȣ�bias��
  COG12864_WriteCmd(0xc8); //��ɨ��˳�򣺴��ϵ���
  COG12864_WriteCmd(0xa0); //��ɨ��˳�򣺴�����
  COG12864_WriteCmd(0x40); //��ʼ�У���һ�п�ʼ
  COG12864_WriteCmd(0xAf); //����ʾ
}
