#ifndef RK3399_GLOBAL_H
#define RK3399_GLOBAL_H
#include <stdint.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>  


// #define OLED_CROSS
// #define SPI_BUS
#define TEST_RUN_TIMES


#define GPIO_PIN_RST 4
#define GPIO_PIN_VPP 5


#define SIZE_HIGH_HZ 23

#ifndef OLED_CROSS
  #define MAXLINE 9
  #define MAX_HZ_ROW 15
#else
  #define MAXLINE 9
  #define MAX_HZ_ROW 20
#endif

 #define RED   0XF800
 #define GREEN 0X07E0
 #define BLUE  0X001F  
 #define BRED  0XF81F
 #define GRED  0XFFE0
 #define GBLUE 0X07FF
 #define WHITE 0XFFFF
 #define BLACK 0X0000
 #define BROWN 0XBC40 
 #define BRRED 0XFC07
 #define GRAY  0X8430
 #define LGRAY 0XC618 

#define PAGE_DOWN 116
#define PAGE_NUM 3


#define LCDOUT 1
#define LCDREOUT 2

extern int gpio_fd;


#endif