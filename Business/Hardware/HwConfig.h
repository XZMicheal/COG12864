#ifndef __HW_CONFIG_H__
#define __HW_CONFIG_H__

#ifdef __cplusplus
extern "C"{
#endif //__cplusplus
  
#include "stm32f1xx_hal.h"
  
#define MSET_BIT(x,n) (x |= 1<<n)
#define MCLR_BIT(x,n) (x &= (~(1<<n)))
#define MREAD_BIT(x,n) (x>>n&1)
  
//COG12864 “˝Ω≈≈‰÷√
#define LCD_CLK(x)      x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET)
#define LCD_DAT(x)      x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)
#define LCD_CS(x)       x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET)
#define LCD_NRST(x)     x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET)
#define LCD_A0(x)       x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)
#define LCD_LIGHT(x)    x?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET)
  
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__HW_CONFIG_H__
