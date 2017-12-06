#include <stdint.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <getopt.h>  
#include <fcntl.h>  
#include <sys/ioctl.h>  
#include <linux/types.h>  
#include <linux/spi/spidev.h>  

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdbool.h> //bool

#include "font.h"

static const char *device_gpio = "/dev/gpio_demo";
static const char *device_spi = "/dev/spidev32766.0";  
int fd_gpio;
int fd_spi;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))  
#define RST 4
#define VPP 5

static uint8_t mode = 3; /* SPI通信使用全双工，设置CPOL＝1，CPHA＝1。 */
static uint8_t bits = 8; /* ８ｂiｔｓ读写，MSB first。*/
static uint32_t speed = 24 * 1000 * 1000;/* 设置12M传输速度 */
static uint16_t delay = 0;

#define OLED28_CMD	0x70	//0111,0000b
#define OLED28_DAT 0x72	//0111,0010b

#define OLED_CMD 1
#define OLED_DATA 0

 #define RED   0XF800
 #define GREEN 0X07E0
 #define BLUE  0X001F  
 #define BRED  0XF81F
 #define GRED  0XFFE0
 #define GBLUE 0X07FF
 #define WHITE 0XFFFF //白色
 #define BLACK 0X0000 //黑色
 #define BROWN 0XBC40 //棕色
 #define BRRED 0XFC07 //棕红色
 #define GRAY  0X8430 //灰色
 #define LGRAY 0XC618 //浅灰色

#define SPI_DEBUG 0

 static uint8_t cmd_no=0x70;
 static uint8_t data_no=0x72;
 
void delay_ms(unsigned int ms)
{ 
   struct timeval delay_ms;
   delay_ms.tv_sec=0;
   delay_ms.tv_usec = ms*1000;
   select(0,NULL,NULL,NULL,&delay_ms);
}

void delay_us(unsigned int us)
{
   struct timeval delay_us;
   delay_us.tv_sec=0;
   delay_us.tv_usec = us;
   select(0,NULL,NULL,NULL,&delay_us);
}

static void pabort(const char *s)
{
    perror(s);
    abort();
}


static uint8_t tx_cmd[3] = {  
               0x70,0x00,0x00
        };  

static uint8_t tx_data[3] = {  
               0x72,0x00,0x00
        }; 

void init_spi()
{
  int ret;
	 fd_spi = open(device_spi, O_RDWR);
    if (fd_spi < 0)
        pabort("can't open device");
    else
        printf("SPI - Open Succeed. Start Init SPI...\n");

    /*
    * spi mode
    */
    ret = ioctl(fd_spi, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
        pabort("can't set spi mode");


    ret = ioctl(fd_spi, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
        pabort("can't get spi mode");

    /*
    * bits per word
    */
    ret = ioctl(fd_spi, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("can't set bits per word");


    ret = ioctl(fd_spi, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("can't get bits per word");

    /*
    * max speed hz
    */
    ret = ioctl(fd_spi, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        pabort("can't set max speed hz");


    ret = ioctl(fd_spi, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        pabort("can't get max speed hz");


    printf("spi mode: %d\n", mode);
    printf("bits per word: %d\n", bits);
    printf("max speed: %d KHz (%d MHz)\n", speed / 1000, speed / 1000 / 1000);

}


void esbusini(void)  //硬复位
{   
	ioctl(fd_gpio,RST,1); // OLED_RST=1;
	ioctl(fd_gpio,RST,0); //OLED_RST=0;
	delay_ms(800);	//22.1184mhz
	ioctl(fd_gpio,RST,1); //OLED_RST=1;
}

int SPI_Write(uint8_t *TxBuf, int len)
{
    int ret;
    // int fd = fd_spi;

    ret = write(fd_spi, TxBuf, len);
    if (ret < 0)
    printf("SPI Write error\n");
    return ret;
}

/*
void WR_Byte(unsigned char data1,unsigned char data2,unsigned char cmd)
{
   
    if(cmd)
    {
       SPI_Write(&cmd_no,1);
       // printf("the cmd is 0x%0x\n",cmd_no);
    }
    else
    {
       SPI_Write(&data_no,1);
        // printf("the data is 0x%0x\n",data_no);
    }
    // write(g_SPI_Fd,&data,1);
   
    SPI_Write(&data1,1);

     SPI_Write(&data2,1);
	
 

}
*/

void WR_Byte(unsigned char data1,unsigned char data2,unsigned char cmd)
{
   
    if(cmd)
    {
      tx_cmd[1]=data1;
      tx_cmd[2]=data2;

      SPI_Write(tx_cmd,3);

    }
    else
    {
      tx_data[1]=data1;
      tx_data[2]=data2;

      SPI_Write(tx_data,3);
    } 

}


void display_cls(unsigned int ch)  
{ 
	unsigned int i;

	//VPP_EN = 0;
   WR_Byte(0x00,0x20,OLED_CMD); WR_Byte(0x00,0x00,OLED_DATA);//WriteCommand(0x0020);WriteData(0); //x
   WR_Byte(0x00,0x21,OLED_CMD); WR_Byte(0x00,0x00,OLED_DATA);//WriteCommand(0x0021);WriteData(0); //y
   WR_Byte(0x00,0x05,OLED_CMD); WR_Byte(0x00,0x00,OLED_DATA);//WriteCommand(0x0005);WriteData(0x0000);//disyplay_OFF
	for(i = 0; i < 76800;i++)
	{
	  WR_Byte(0x00,0x22,OLED_CMD); WR_Byte((ch&0xff00)>>8,(ch&0xff),OLED_DATA);//WriteCommand(0x0022); 	 WriteData(ch);
	}
	//VPP_EN = 1;
    WR_Byte(0x00,0x05,OLED_CMD); WR_Byte(0x00,0x01,OLED_DATA);//WriteCommand(0x0005);WriteData(0x0001);//disyplay_ON

 } 

//  void display_cls_red()  
// { 
//   unsigned int i;
//   //VPP_EN = 0;
//    WR_Byte(0x00,0x20,OLED_CMD); WR_Byte(0x00,0x00,OLED_DATA);//WriteCommand(0x0020);WriteData(0); //x
//    WR_Byte(0x00,0x21,OLED_CMD); WR_Byte(0x00,0x00,OLED_DATA);//WriteCommand(0x0021);WriteData(0); //y
//    WR_Byte(0x00,0x05,OLED_CMD); WR_Byte(0x00,0x00,OLED_DATA);//WriteCommand(0x0005);WriteData(0x0000);//disyplay_OFF
//   for(i = 0; i < 76800;i++)
//   {
//     WR_Byte(0x00,0x22,OLED_CMD); WR_Byte(0xF8,0x00,OLED_DATA);//WriteCommand(0x0022);    WriteData(ch);
//   }
//   //VPP_EN = 1;
//     WR_Byte(0x00,0x05,OLED_CMD); WR_Byte(0x00,0x01,OLED_DATA);//WriteCommand(0x0005);WriteData(0x0001);//disyplay_ON

//  } 

void ini_oled(void) //初始化
{
	
	ioctl(fd_gpio,VPP,0);
	esbusini();
	WR_Byte(0x00,0x23,OLED_CMD);//WriteCommand(0x0023);	//Select 18-/16-bit Data Bus Interface

	WR_Byte(0x00,0x05,OLED_CMD); WR_Byte(0x00,0x00,OLED_DATA);//WriteCommand(0x0005);WriteData(0x0000);//WriteData(0x00); 	//Display Control1 //0--关闭显示，1--打开显示
	WR_Byte(0x00,0x18,OLED_CMD); WR_Byte(0x00,0x2f,OLED_DATA);//WriteCommand(0x0018);WriteData(0x002f);//WriteData(0x28);	//Oscillator Control x1.0
	WR_Byte(0x00,0x04,OLED_CMD); WR_Byte(0x00,0x30,OLED_DATA);//WriteCommand(0x0004);WriteData(0x0030);//WriteData(0x03);	//Clock Control

	WR_Byte(0x00,0x02,OLED_CMD); WR_Byte(0x00,0x30,OLED_DATA);//WriteCommand(0x0002);WriteData(0x0030);//WriteData(0x28);	//RGB Interface Control	System模式


	WR_Byte(0x00,0x03,OLED_CMD); WR_Byte(0x01,0x30,OLED_DATA);//WriteCommand(0x0003);WriteData(0x0130);//WriteData(0x6030);	//System模式,16bit接口65K, 0x6030 262k

	WR_Byte(0x00,0x10,OLED_CMD); WR_Byte(0x00,0x00,OLED_DATA);//WriteCommand(0x0010);WriteData(0x0000);//WriteData(0x00);	//1--待机模式，0--正常模式 
   	
	//gamma setting 250 nits(标准值)
	WR_Byte(0x00,0x70,OLED_CMD); WR_Byte(0x2b,0x80,OLED_DATA);//WriteCommand(0x0070);	WriteData(0x2b80);// Gamma Top/Bottom R(亮度，值越大越亮，最大值3f8f)
   	WR_Byte(0x00,0x71,OLED_CMD); WR_Byte(0x2c,0x80,OLED_DATA);//WriteCommand(0x0071); 	WriteData(0x2c80);// Gamma Top/Bottom G(亮度，值越大越亮，最大值3f8f)
   	WR_Byte(0x00,0x72,OLED_CMD); WR_Byte(0x39,0x80,OLED_DATA);//WriteCommand(0x0072);  	WriteData(0x3980);// Gamma Top/Bottom B(亮度，值越大越亮，最大值3f8f)
   	WR_Byte(0x00,0x73,OLED_CMD); WR_Byte(0x19,0x12,OLED_DATA);//WriteCommand(0x0073);  	WriteData(0x1912);// Gamma Top Bottom R1,2(对比度，值越大对比度越高，最大值3f3f)
 	WR_Byte(0x00,0x74,OLED_CMD); WR_Byte(0x1a,0x0d,OLED_DATA);//WriteCommand(0x0074); 	WriteData(0x1a0d);// Gamma Top Bottom R3,4(对比度，值越大对比度越高，最大值3f3f)
   	WR_Byte(0x00,0x75,OLED_CMD); WR_Byte(0x20,0x14,OLED_DATA);//WriteCommand(0x0075); 	WriteData(0x2014);// Gamma Top Bottom G1,2(对比度，值越大对比度越高，最大值3f3f)
   	WR_Byte(0x00,0x76,OLED_CMD); WR_Byte(0x18,0x11,OLED_DATA);//WriteCommand(0x0076); 	WriteData(0x1811);// Gamma Top Bottom G3,4(对比度，值越大对比度越高，最大值3f3f)
   	WR_Byte(0x00,0x77,OLED_CMD); WR_Byte(0x22,0x18,OLED_DATA);//WriteCommand(0x0077);  	WriteData(0x2218);// Gamma Top Bottom B1,2(对比度，值越大对比度越高，最大值3f3f)
   	WR_Byte(0x00,0x78,OLED_CMD); WR_Byte(0x1e,0x11,OLED_DATA);//WriteCommand(0x0078);  	WriteData(0x1e11);// Gamma Top Bottom B3,4(对比度，值越大对比度越高，最大值3f3f)
    

  	display_cls(0);	  
	ioctl(fd_gpio,VPP,1);	
//	delay_ms(1); 
	WR_Byte(0x00,0x05,OLED_CMD); WR_Byte(0x00,0x01,OLED_DATA);//WriteCommand(0x0005);WriteData(0x0001);//WriteData(0x00); 
}



void test_gpio()
{
	int i=0;
	for(;i<10;i++)
	{
		ioctl(fd_gpio,VPP,0);
		ioctl(fd_gpio,RST,0);
		delay_ms(800);
		ioctl(fd_gpio,VPP,1);
		ioctl(fd_gpio,RST,1);
		delay_ms(800);

	}
}

int main()
{
    fd_gpio = open(device_gpio,O_RDWR);
	if(fd_gpio<0)
		printf("open error \n");

	//test
	// test_gpio();


	init_spi();
    ini_oled();
    // ini_oled_test();
    // delay_ms(1200);
    // display_cls_red();
    display_cls(RED);
    delay_ms(800);
    display_cls(GREEN);
    delay_ms(800);
    display_cls(BLUE);

    delay_ms(800);
    display_cls(BRED);
    delay_ms(800);
    display_cls(GRAY);

    delay_ms(1200);

    printf("tst end \n");

    while(1)
    {
           // display_cls_red();
           //  delay_ms(800);      
      
    }
    return 0;
   
}
