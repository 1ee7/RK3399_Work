// # 
// # AUTHOR: tgl
// # DATE: 2017-09-26
// # 
#ifndef DISPLAY_H
#define DISPLAY_H

#include "rk3399_global.h"
#include <string.h>
#include <sys/time.h>

#define CHAR_HIGH 16
#define Max_Column  128
#define Max_Row   64

void Display_Str(uint16_t x,uint16_t y,char *str,uint16_t frontclr,uint16_t backclr ,unsigned char dir);

void Display_Line(uint16_t _usX1, uint16_t  _usY1,uint16_t  _usX2, uint16_t  _usY2,uint16_t _usColor);

void Display_Circle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor);

void Display_Rect(uint16_t _usX1, uint16_t _usY1,uint16_t _usX2, uint16_t _usY2,uint16_t _usX3,
                  uint16_t _usY3,uint16_t _usX4, uint16_t _usY4,uint16_t _usColor);

void Display_Char16(uint16_t x, uint16_t y, uint16_t fontcolor, uint16_t backcolor, char *s);

void Display_One_Hz(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint16_t s);

void Display_String_Hz(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc);



#endif