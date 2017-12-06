#ifndef OLED_H
#define OLED_H

#include "rk3399_global.h"

#define OLED_CMD 0x70
#define OLED_DAT 0x72

#define PIN_SPI_RST 7
#define PIN_SPI_SDI 8
#define PIN_SPI_CLK 9
#define PIN_SPI_CS  10

#ifndef SPI_BUS
	#define SPI_RST_1 Gpio1_Set_Pin_Value(PIN_SPI_RST,1)
	#define SPI_RST_0 Gpio1_Set_Pin_Value(PIN_SPI_RST,0)

	#define SPI_SDI_1 Gpio1_Set_Pin_Value(PIN_SPI_SDI,1)
	#define SPI_SDI_0 Gpio1_Set_Pin_Value(PIN_SPI_SDI,0)

	#define SPI_CLK_1 Gpio1_Set_Pin_Value(PIN_SPI_CLK,1)
	#define SPI_CLK_0 Gpio1_Set_Pin_Value(PIN_SPI_CLK,0)

	#define SPI_CS_1 Gpio1_Set_Pin_Value(PIN_SPI_CS,1)
	#define SPI_CS_0 Gpio1_Set_Pin_Value(PIN_SPI_CS,0)
#else
	#define SPI_RST_1 set_pin_value(GPIO_PIN_RST,1);
	#define SPI_RST_0 set_pin_value(GPIO_PIN_RST,0);
	#define SPI_VPP_1 set_pin_value(GPIO_PIN_VPP,1);
	#define SPI_VPP_0 set_pin_value(GPIO_PIN_VPP,0);
#endif

void OLED_Init();
// void OLED_Reset();
// void OLED_Clear();

void OLED_Draw_Point(uint16_t x,uint16_t y,uint16_t fontcolor);
void OLED_COLOR(uint16_t ch);

void OLED_DisplayOn(void);
void OLED_DisplayOff(void);

void OLED_COLOR_ONEBYONE(uint16_t ch);


#endif