#ifndef RK3399_SPI_H
#define RK3399_SPI_H

#include "rk3399_global.h"
#include <getopt.h>  
#include <fcntl.h>  
#include <sys/ioctl.h>  
#include <linux/types.h>  
#include <linux/spi/spidev.h> 
#include <string.h>


// static void pabort(const char *s);
int SPI_Transfer(const uint8_t *TxBuf, uint8_t *RxBuf, uint32_t len);
int SPI_Init(void);
int SPI_Write(uint8_t *TxBuf, int len);
int SPI_Read(uint8_t *RxBuf, int len);
int SPI_Close(void);
int SPI_LookBackTest(void);

#endif
