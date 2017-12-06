#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <time.h>
#include "font.h"
static const char *device = "/dev/gpio_demo";

#define CLK 0
#define CS 1
#define SDI 5
#define RST 4
#define VPP 2


#define OLED28_CMD	0x70	//0111,0000b
#define OLED28_DAT 0x72	//0111,0010b

#define RED	  0XF800
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
int fd;

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

void WriteCommand(unsigned int com)  //写入命令
{
	unsigned int i;
	ioctl(fd,CS,1);
	ioctl(fd,CLK,1);
	ioctl(fd,CS,0);
	for(i=0x80;i!=0;i/=2)
	{
       ioctl(fd,CLK,0); //OLED_SCLK=0;
       if(OLED28_CMD&i) ioctl(fd,SDI,1);//OLED_SDI=1;
		else ioctl(fd,SDI,0);//OLED_SDI=0;
		ioctl(fd,CLK,1); //OLED_SCLK=1;
	}	
	for(i=0x8000;i!=0;i/=2)
	{
	   ioctl(fd,CLK,0);//OLED_SCLK=0;	
		if(com&i) ioctl(fd,SDI,1);//OLED_SDI=1;
		else ioctl(fd,SDI,0);//OLED_SDI=0;
		ioctl(fd,CLK,1); //OLED_SCLK=1;
	}	
	// delay_us(1);	 //5
	 ioctl(fd,CS,0);//OLED_CS=1;	 
}


void WriteData(unsigned int display_data)  //写入命令
{
	unsigned int i;
	ioctl(fd,CS,1);//OLED_CS=1;
	ioctl(fd,CLK,1);//OLED_SCLK=1;
	ioctl(fd,CS,0);//OLED_CS=0;
	for(i=0x80;i!=0;i/=2)
	{
	    ioctl(fd,CLK,0);//OLED_SCLK=0;
		if(OLED28_DAT&i) ioctl(fd,SDI,1);//OLED_SDI=1;
		else ioctl(fd,SDI,0);//OLED_SDI=0;
		ioctl(fd,CLK,1);//OLED_SCLK=1;
	}	
	
	for(i=0x8000;i!=0;i/=2)
	{
	   ioctl(fd,CLK,0);//OLED_SCLK=0;	
		if(display_data&i) ioctl(fd,SDI,1);//OLED_SDI=1;
		else ioctl(fd,SDI,0);//OLED_SDI=0;
		ioctl(fd,CLK,1);//OLED_SCLK=1;
	}	

	delay_us(1);	 //5
	ioctl(fd,CS,0);//OLED_CS=1;	
}



void display_cls(unsigned int ch)  
{ 
	unsigned int i;
	//VPP_EN = 0;
   WriteCommand(0x0020);WriteData(0); //x
   WriteCommand(0x0021);WriteData(0); //y
   WriteCommand(0x0005);WriteData(0x0000);//disyplay_OFF
	for(i = 0; i < 76800;i++)
	{
	 WriteCommand(0x0022);
	 WriteData(ch);
	}
	//VPP_EN = 1;
 WriteCommand(0x0005);WriteData(0x0001);//disyplay_ON

 } 
void init_oled()
{
	ioctl(fd,VPP,0);
	
	ioctl(fd,RST,1);
	ioctl(fd,RST,0);	
	delay_ms(80);	//22.1184mhz
	ioctl(fd,RST,1);
	
	WriteCommand(0x0023);	//Select 18-/16-bit Data Bus Interface

	WriteCommand(0x0005);WriteData(0x0000);//WriteData(0x00); 	//Display Control1 //0--关闭显示，1--打开显示
	WriteCommand(0x0018);WriteData(0x002f);//WriteData(0x28);	//Oscillator Control x1.0
	WriteCommand(0x0004);WriteData(0x0030);//WriteData(0x03);	//Clock Control

	WriteCommand(0x0002);WriteData(0x0030);//WriteData(0x28);	//RGB Interface Control	System模式


	WriteCommand(0x0003);WriteData(0x0130);//WriteData(0x6030);	//System模式,16bit接口65K, 0x6030 262k

	WriteCommand(0x0010);WriteData(0x0000);//WriteData(0x00);	//1--待机模式，0--正常模式 
   	
	//gamma setting 250 nits(标准值)
	WriteCommand(0x0070);	WriteData(0x2b80);// Gamma Top/Bottom R(亮度，值越大越亮，最大值3f8f)
   	WriteCommand(0x0071); 	WriteData(0x2c80);// Gamma Top/Bottom G(亮度，值越大越亮，最大值3f8f)
   	WriteCommand(0x0072);  	WriteData(0x3980);// Gamma Top/Bottom B(亮度，值越大越亮，最大值3f8f)
   	WriteCommand(0x0073);  	WriteData(0x1912);// Gamma Top Bottom R1,2(对比度，值越大对比度越高，最大值3f3f)
 	WriteCommand(0x0074); 	WriteData(0x1a0d);// Gamma Top Bottom R3,4(对比度，值越大对比度越高，最大值3f3f)
   	WriteCommand(0x0075); 	WriteData(0x2014);// Gamma Top Bottom G1,2(对比度，值越大对比度越高，最大值3f3f)
   	WriteCommand(0x0076); 	WriteData(0x1811);// Gamma Top Bottom G3,4(对比度，值越大对比度越高，最大值3f3f)
   	WriteCommand(0x0077);  	WriteData(0x2218);// Gamma Top Bottom B1,2(对比度，值越大对比度越高，最大值3f3f)
   	WriteCommand(0x0078);  	WriteData(0x1e11);// Gamma Top Bottom B3,4(对比度，值越大对比度越高，最大值3f3f)
    

  	display_cls(0);	  
	ioctl(fd,VPP,1);
//	delay_ms(1); 
	WriteCommand(0x0005);WriteData(0x0001);//WriteData(0x00); 
}

void TFT_DrawPoint(unsigned int x,unsigned int y,unsigned int fontcolor)
{  
/*
	WriteCommand(0x0035);WriteData(0);//0	  //Vertical RAM Address Position (R35h, R36h)
   WriteCommand(0x0036);WriteData(0);//319  0x013f  //Vertical RAM Address Position (R35h, R36h)
//0-159
   WriteCommand(0x0037);WriteData(0x0000);//239  0x00ef  //Horizontal RAM Address Position (R37h)
*/
#ifdef  cross  //横屏处理
	x = x + y;
	y = x - y;
	x = 240 + y - x;
#endif
   WriteCommand(0x0020);WriteData(x); //x
   WriteCommand(0x0021);WriteData(y); //y

   WriteCommand(0x0022);
	 WriteData(fontcolor);//
}

void lcd_char16(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc, char *s)
{
	unsigned char i,j;
	unsigned int k;

	while(*s) 
  {
		if( *s < 0x80 )
		{
			k=*s;
			if (k>32) 
				k-=32;
			else k=0;

		 for(i=0;i<16;i++)
			for(j=0;j<8;j++) 
				{
			    	if(asc16[k*16+i]&(0x80>>j))	
							TFT_DrawPoint(x+j,y+i,fc);
					else 
						{
						if (fc!=bc) 
							TFT_DrawPoint(x+j,y+i,bc);
					  }
				}
			s++;x+=8;
		}
	}
}

void gpio_test()
{
	int i;
	for(i=0;i<100;i++)
	{
			// ioctl(fd,CLK,0);
			ioctl(fd,SDI,0);
			// ioctl(fd,CS,0);
			// ioctl(fd,RST,0);
			// ioctl(fd,VPP,0);
	    delay_ms(800);
			// ioctl(fd,CLK,1);
			ioctl(fd,SDI,1);
			// ioctl(fd,CS,1);
			// ioctl(fd,RST,1);
			// ioctl(fd,VPP,1);
		delay_ms(800);

	}
}

int main()
{
	
	int ret,i;
	unsigned long tmp=1;
	unsigned long value=4;

	fd = open(device,O_RDWR);
	if(fd<0)
		printf("open error \n");

	// gpio_test();
	
    
	init_oled();
	printf("\n == start \n");
	   display_cls(RED);  
   delay_ms(80);	
   display_cls(GREEN);  
   delay_ms(500);
   display_cls(GRAY);  
   delay_ms(500);
   display_cls(BRED);  
   delay_ms(500);
   display_cls(GRED);  
   delay_ms(500);
   display_cls(GBLUE);  
   delay_ms(500);
   display_cls(WHITE); 
   delay_ms(500); 
	 display_cls(BLACK); 
   delay_ms(500); 
	 display_cls(BRRED); 
   delay_ms(500); 
	 display_cls(BLUE); 
   delay_ms(500); 


    lcd_char16(10,50,WHITE,BLUE,"ABCDEFGHIJKLMNOPQRSTUYWXYZ"); 
	 lcd_char16(10,70,WHITE,BLUE,"abcdefghijklmnopqrstuywxyz");
	 
	 
	 printf("\n == end \n");
	 
	while(1)
	{
		//tmp=1;
		// ioctl(fd,1,tmp);
		// delay_ms(800);
		// ioctl(fd,0,tmp);
		/*delay_ms(800);
       
		ioctl(fd,0,1);  
		ioctl(fd,1,1);
		ioctl(fd,2,1);
		ioctl(fd,3,1);
		ioctl(fd,4,1);
		ioctl(fd,5,1);

		delay_ms(800);

		ioctl(fd,0,0);
		ioctl(fd,1,0);
		ioctl(fd,2,0);
		ioctl(fd,3,0);
		ioctl(fd,4,0);
		ioctl(fd,5,0);


*/
		// printf("the value is %ld \n",value);

	}
   // close(fd);
	return 0;

}
