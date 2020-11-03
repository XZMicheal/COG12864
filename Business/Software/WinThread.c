#include "WinThread.h"

static osThreadId sWinThreadHandle;
static void WinThread_Callback(const void *argument);
void WinThread_Init(void)
{
  osThreadDef(sWinThreadHandle, WinThread_Callback, osPriorityNormal, 0, 128);
  sWinThreadHandle = osThreadCreate(osThread(sWinThreadHandle), NULL);
}



static void WinThread_Callback(const void *argument)
{
  uint8_t invert = 1;
  //∆¡ƒª≥ı ºªØ
  Display_Init();
  Display_Clear();
  Display_PrintChinese(0,0,"“∫æßœ‘ æ∆¡≤‚ ‘",invert);
  Display_Draw_Rectangle(0,16,10,10,1);
  Display_Draw_Rectangle(0,16,10,20,1);
  Display_PrintString(0,26,"1234567890",1);
  Display_PrintString(0,42,"abcdefghijklmnopkrstuvwxyz",1);
  Display_PrintString(0,58,"krstuvwxyz",1);
  Display_Refresh();
  
  for(;;)
  {
    printf("Hello World\r\n");
    Display_PrintChinese(0,0,"“∫æßœ‘ æ∆¡≤‚ ‘",invert);
    Display_Refresh();
    osDelay(1000);
    invert = !invert;
  }
}


