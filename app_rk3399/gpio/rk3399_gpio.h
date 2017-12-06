#ifndef RK3399_GPIO_H
#define RK3399_GPIO_H

#include "rk3399_global.h"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>  
#include <stdbool.h> //bool




#ifndef SPI_BUS
    int  Gpio_MMap_Init();
	int  Gpio1_MMap();	
	void Gpio1_Set_Pin_Value(int pin,int value);
	void Gpio_MMap_Close();
#else  /* tgl mark */
	int  Gpio_Init_Spi();
	void set_pin_value(int pin,int value);
	void Gpio_Close_Spi();
#endif

#endif
