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

//gpio --- reset\dcen
#define TRIGGER "trigger"
#define LED_PATH "/sys/class/leds/"
#define LED_STATUS "brightness"
#define TRIGGER_NONE "none"


#define OLED28_CMD 0x70
#define OLED28_DAT 0x72

#define OLED_ON 1


 #define RED   0xF800
 #define GREEN 0x07E0
 #define BLUE  0x001F  
 #define BRED  0xF81F
 #define GRED  0xFFE0
 #define GBLUE 0x07FF
 #define WHITE 0xFFFF 
 #define BLACK 0x0000 
 #define BROWN 0xBC40 
 #define BRRED 0xFC07 
 #define GRAY  0x8430 
 #define LGRAY 0xC618


#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))  
  
static const char *device = "/dev/spidev32766.0";  
static uint8_t mode; //mode-1
static uint8_t bits = 8;  
static uint32_t speed = 50000;//500000;  
static uint16_t delay=10;


#define GPIO_OLED_RST 0
#define GPIO_VPP_EN 1
#define GPIO_SPI_CS 2
#define GPIO_SPI_CLK 3
#define GPIO_SPI_SDI  4

#define YELLOW_LED "firefly:yellow:user"

#define OLED_RST "firefly:output:reset"
#define VPP_EN "firefly:output:dcen"
#define CMD_SPI_CS "firefly:output:cs"
#define CMD_SPI_CLK "firefly:output:clk"
#define CMD_SPI_SDI  "firefly:output:sdi"
 

static int spi_fd_cs;
static int spi_fd_clk;
static int spi_fd_vpp;
static int spi_fd_sdi;
static int spi_fd_rst;

static int ij=0;

char path[25],data[2];

time_t start,stop;

int testGpio(unsigned int pinx)
{
    // char path[25],data[2];
    int fd,ret,flag;
      strcpy(path,LED_PATH);

      if(pinx == GPIO_OLED_RST)
        strcat(path,OLED_RST);
      else if(pinx == GPIO_VPP_EN)
        strcat(path,VPP_EN);
      else if(pinx == GPIO_SPI_CLK)
        strcat(path,CMD_SPI_CLK);
      else if(pinx == GPIO_SPI_CS)
        strcat(path,CMD_SPI_CS);
      else if(pinx == GPIO_SPI_SDI)
        strcat(path,CMD_SPI_SDI);
     
      strcat(path,"/"TRIGGER);
      fd = open(path,O_RDWR);
  
      if(fd<0)
      {
        perror("open");
        close(fd);
        return -1;
      }

      ret = write(fd,TRIGGER_NONE,strlen(TRIGGER_NONE));
      if(ret <0)
      {
        perror("write");
        close(fd);
        return -1;
      }
     close(fd);

    return 0;

}

void Gpio_Pin_Close()
{
  close(spi_fd_cs);
   
   close(spi_fd_clk);
   close(spi_fd_vpp);
   close(spi_fd_sdi);
   close(spi_fd_rst);
}

int Gpio_Rst_Open()
{
    strcpy(path,LED_PATH);
    strcat(path,OLED_RST);
    strcat(path,"/"LED_STATUS);

    spi_fd_rst = open(path,O_RDWR);

    if(spi_fd_rst<0)
    {
         perror("open");   
         close(spi_fd_rst);  
         return -1;
    }

  }


int Gpio_Vpp_Open()
{
    strcpy(path,LED_PATH);
    strcat(path,VPP_EN);
    strcat(path,"/"LED_STATUS);

    spi_fd_vpp = open(path,O_RDWR);

    if(spi_fd_vpp<0)
    {
         perror("open");   
         close(spi_fd_vpp);  
         return -1;
    }

  }

int Gpio_Cs_Open()
{
    strcpy(path,LED_PATH);
    strcat(path,CMD_SPI_CS);
    strcat(path,"/"LED_STATUS);

    spi_fd_cs = open(path,O_RDWR);

    if(spi_fd_cs<0)
    {
         perror("open");   
         close(spi_fd_cs);  
         return -1;
    }

  }


  int Gpio_Clk_Open()
{
    strcpy(path,LED_PATH);
    strcat(path,CMD_SPI_CLK);
    strcat(path,"/"LED_STATUS);

    spi_fd_clk = open(path,O_RDWR);

    if(spi_fd_clk<0)
    {
         perror("open");   
         close(spi_fd_clk);  
         return -1;
    }

  }


  int Gpio_Sdi_Open()
{
    strcpy(path,LED_PATH);
    strcat(path,CMD_SPI_SDI);
    strcat(path,"/"LED_STATUS);

    spi_fd_sdi = open(path,O_RDWR);

    if(spi_fd_sdi<0)
    {
         perror("open");   
         close(spi_fd_sdi);  
         return -1;
    }

  }


int Gpio_Rst_Set(bool value)
{
     int ret;
     data[0]=value?'1':'0';
     ret=write(spi_fd_rst,data,1);
     if(ret<0)
     {
        perror("write");
        close(spi_fd_rst);
        return -1;
      }
      return 0;
}


int Gpio_Cs_Set(bool value)
{
     int ret;
     data[0]=value?'1':'0';
     ret=write(spi_fd_cs,data,1);
     if(ret<0)
     {
        perror("write");
        close(Gpio_Cs_Set);
        return -1;
      }
      return 0;
}


int Gpio_Clk_Set(bool value)
{    
     int ret;
     data[0]=value?'1':'0';
     ret=write(spi_fd_clk,data,1);
     if(ret<0)
     {
        perror("write");
        close(Gpio_Clk_Set);
        return -1;
      }
      return 0;
}


int Gpio_Vpp_Set(bool value)
{
     int ret;
     data[0]=value?'1':'0';
     ret=write(spi_fd_vpp,data,1);
     if(ret<0)
     {
        perror("write");
        close(spi_fd_vpp);
        return -1;
      }
      return 0;
}

int Gpio_Sdi_Set(bool value)
{
     int ret;
     data[0]=value?'1':'0';
     ret=write(spi_fd_sdi,data,1);
     if(ret<0)
     {
        perror("write");
        close(spi_fd_sdi);
        return -1;
      }
      return 0;
}




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




//==============spi===============//

static void pabort(const char *s)
{
        perror(s);
        abort();
}


void Oled_WriteCommand(unsigned short com)
{

	
	unsigned int i;
	
  Gpio_Cs_Set(1); // OLED_CS=1;
	
  Gpio_Clk_Set(1); //OLED_SCLK=1;
	
  Gpio_Cs_Set(0); 	//OLED_CS=0;

	for(i=0x80;i!=0;i/=2)
	{
		Gpio_Clk_Set(0);    //OLED_SCLK=0;
	
		if(OLED28_CMD&i) 
			Gpio_Sdi_Set(1);   //OLED_SDI=1;
		else 
			Gpio_Sdi_Set(0);//OLED_SDI=0;
			
		 Gpio_Clk_Set(1);  //OLED_SCLK=1;
	}	

	for(i=0x8000;i!=0;i/=2)
	{	
		Gpio_Clk_Set(0);   // OLED_SCLK=0;	
		
		if(com&i) 
		  Gpio_Sdi_Set(1);	// OLED_SDI=1;
		else 
		  Gpio_Sdi_Set(0);	// OLED_SDI=0;
			
		 Gpio_Clk_Set(1);  // OLED_SCLK=1;
		
	}	
	delay_us(1);	 //5
	  Gpio_Cs_Set(1); // OLED_CS=1;
	
}



void Oled_WriteData(unsigned short data)
{
  unsigned int i;
  Gpio_Cs_Set(1); // OLED_CS=1;
  
  Gpio_Clk_Set(1); //OLED_SCLK=1;
  
  Gpio_Cs_Set(0);   //OLED_CS=0;

	for(i=0x80;i!=0;i/=2)
	{
		  Gpio_Clk_Set(0);   // OLED_SCLK=0;

		if(OLED28_DAT&i) 
			Gpio_Sdi_Set(1);   // OLED_SDI=1;
		
		else 
		  Gpio_Sdi_Set(0);	// OLED_SDI=0;
			
		 Gpio_Clk_Set(1);  // OLED_SCLK=1;
		
	}	
	
	for(i=0x8000;i!=0;i/=2)
	{	
		 Gpio_Clk_Set(0);   // OLED_SCLK=0;	
		
		if(data&i) 
		   Gpio_Sdi_Set(1);	// OLED_SDI=1;
		else 
	     Gpio_Sdi_Set(0);		// OLED_SDI=0;
		
    Gpio_Clk_Set(1);		// OLED_SCLK=1;
		
	}	

	delay_us(1);	 //5
   Gpio_Cs_Set(1);	// OLED_CS=1;	
	
}



void DsplayCls(unsigned short ch)
{

    Oled_WriteCommand(0x0020);Oled_WriteData(0x0000);
  	Oled_WriteCommand(0x0021);Oled_WriteData(0x0000);
    Oled_WriteCommand(0x0005);Oled_WriteData(0x0000);

     // start=time(NULL);


    for (ij=0;ij<76800;ij++)
   {
    
      Oled_WriteCommand(0x0022);
   
    	Oled_WriteData(ch);
    	
   }

   // stop=time(NULL);
   // printf("Use Time: %ld \n",(stop-start));

  
    Oled_WriteCommand(0x0005);Oled_WriteData(0x0001);
  
}



//====================//
void TFT_DrawPoint(unsigned short x,unsigned short y,unsigned short fontcolor)
{  
 
   Oled_WriteCommand(0x0020);Oled_WriteData(x); //x
   Oled_WriteCommand(0x0021);Oled_WriteData(y); //y
   Oled_WriteCommand(0x0022);Oled_WriteData(fontcolor);//

}



//=================//
void lcd_char16(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, char *s)
{
	unsigned char i,j;
	unsigned short k;

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
//====================//
void Lcd_One_Hz(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, unsigned char s)
{
	unsigned char i,j;
	unsigned short y0;
	unsigned char temp;
	y0 = y;
	for(i = 0;i < 32;i++)
	{
		temp = Hz_16[s][i] ;
		for(j = 0;j < 8;j++)
		{
			if(temp & 0x80)
			{
				TFT_DrawPoint(x,y0,fc);
			}
			else 
			{
				TFT_DrawPoint(x,y0,bc);
			}
			temp = temp << 1;
			y0++;
		}
		if(i % 2)
		{
			x++;
			y0 = y;	
		}
	}
}

//=========0-10========//
void Lcd_String_Hz(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc)
{
	unsigned char x0,i;
	x0 = x;	
	for(i = 0;i < 10;i++)
	{
		Lcd_One_Hz(x0,y,fc,bc,i);
		x0 += 16;
	}
}




void transferCmd()
{
	Oled_WriteCommand(0x0023);	//Select 18-/16-bit Data Bus Interface

	Oled_WriteCommand(0x0005);Oled_WriteData(0x0000);//WriteData(0x00); 	//Display Control1
	Oled_WriteCommand(0x0018);Oled_WriteData(0x002f);//WriteData(0x28);	//Oscillator Control x1.0
	Oled_WriteCommand(0x0004);Oled_WriteData(0x0030);//WriteData(0x03);	//Clock Control
	Oled_WriteCommand(0x0002);Oled_WriteData(0x0030);//WriteData(0x03);	//Clock Control
	Oled_WriteCommand(0x0003);Oled_WriteData(0x0130);//WriteData(0x28);	//RGB Interface Control	System
	Oled_WriteCommand(0x0010);Oled_WriteData(0x0000);//WriteData(0x28);	//RGB Interface Control	System



  Oled_WriteCommand(0x0070);Oled_WriteData(0x2b80);// Gamma Top/Bottom R
  Oled_WriteCommand(0x0071);Oled_WriteData(0x2c80);// Gamma Top/Bottom G
  Oled_WriteCommand(0x0072);Oled_WriteData(0x3980);// Gamma Top/Bottom B
  Oled_WriteCommand(0x0073);Oled_WriteData(0x1912);// Gamma Top Bottom R1,2
  Oled_WriteCommand(0x0074);Oled_WriteData(0x1a0d);// Gamma Top Bottom R3,4
  Oled_WriteCommand(0x0075);Oled_WriteData(0x2014);// Gamma Top Bottom G1,2
  Oled_WriteCommand(0x0076);Oled_WriteData(0x1811);// Gamma Top Bottom G3,4
  Oled_WriteCommand(0x0077);Oled_WriteData(0x2218);// Gamma Top Bottom B1,2
  Oled_WriteCommand(0x0078);Oled_WriteData(0x1e11);// Gamma Top Bottom B3,4

}

int init()
{
	 int ret = 0;

  
    //===== gpio ======/
   if( (testGpio(GPIO_OLED_RST)!=0)&& (testGpio(GPIO_VPP_EN)!=0) )
    {
       printf("error:test--control-gpio \n");
       return -1;
    }

      if( (testGpio(GPIO_SPI_CLK)!=0)&& (testGpio(GPIO_SPI_CS)!=0) && (testGpio(GPIO_SPI_SDI)!=0) )
    {
       printf("error:test--control-gpio \n");
       return -1;
    }

}


void esbusini()
{
    
    Gpio_Rst_Set(1);  //setGpioValue(GPIO_OLED_RST,1);
    Gpio_Rst_Set(0); //setGpioValue(GPIO_OLED_RST,0);
     delay_ms(80);
    Gpio_Rst_Set(1); // setGpioValue(GPIO_OLED_RST,1);
 }


void init_oled()
{
	Gpio_Vpp_Set(0); //setGpioValue(GPIO_VPP_EN,0);
    esbusini();
    transferCmd();
    DsplayCls(0);
    Gpio_Vpp_Set(1);//setGpioValue(GPIO_VPP_EN,1);   
    Oled_WriteCommand(0x0005);Oled_WriteData(0x0001);
}

void init_gpio()
{
    Gpio_Rst_Open();
    Gpio_Clk_Open();
    Gpio_Cs_Open();
    Gpio_Sdi_Open();
    Gpio_Vpp_Open();
}

void gpio_test()
{
	int i;
   for(i=0;i<10;i++)
  {
  	 // Gpio_Clk_Set(1);
  	 Gpio_Sdi_Set(1);
  	 // Gpio_Vpp_Set(1);
  	 Gpio_Cs_Set(1);
  	 Gpio_Rst_Set(1);
  	  delay_ms(800);
  	  // Gpio_Clk_Set(0);
  	 Gpio_Sdi_Set(0);
  	 // Gpio_Vpp_Set(0);
  	 Gpio_Cs_Set(0);
  	 Gpio_Rst_Set(0);
  	 delay_ms(800);
  }
 
}


//*/
int main(void)  
{   
  // int i;
 
   printf("===A \n");

   init_gpio();

   init_oled();    
   printf("===C \n");
   DsplayCls(0xF800);

   
    delay_ms(800);
    DsplayCls(GREEN);
    delay_ms(800);
    DsplayCls(GRAY);
    delay_ms(800);


    lcd_char16(10,20,WHITE,BLUE,"1234567890");	
    lcd_char16(10,50,WHITE,BLUE,"ABCDEFGHIJKLMNOPQRSTUYWXYZ"); 
	  lcd_char16(10,70,WHITE,BLUE,"abcdefghijklmnopqrstuywxyz");
    Lcd_String_Hz(10,100,WHITE,BLUE);
    delay_ms(1200);

    while(1)
    {

    }
 
    Gpio_Pin_Close();

    return 0;
}  




#if 0


int setGpioValue(unsigned int pinx,bool value)
{
  
     // char path[25],data[2];
    int fd,ret,flag;

      strcpy(path,LED_PATH);

      if(pinx == GPIO_OLED_RST)
        strcat(path,OLED_RST);
      else if(pinx == GPIO_VPP_EN)
        strcat(path,VPP_EN);
      else if(pinx == GPIO_SPI_CLK)
        strcat(path,CMD_SPI_CLK);
      else if(pinx == GPIO_SPI_CS)
        strcat(path,CMD_SPI_CS);
      else if(pinx == GPIO_SPI_SDI)
         strcat(path,CMD_SPI_SDI);


     strcat(path,"/"LED_STATUS);

     fd = open(path,O_RDWR);
  
     if(fd<0)
     {
         perror("open");   
         close(fd);  
         return -1;
     }

     data[0]=value?'1':'0';
     ret=write(fd,data,1);
     if(ret<0)
     {
        perror("write");
        close(fd);
        return -1;
      }

     close(fd);

     return 0;
}

int testGpio(unsigned int pinx)
{
    // char path[25],data[2];
    int fd,ret,flag;
      strcpy(path,LED_PATH);

      if(pinx == GPIO_OLED_RST)
        strcat(path,OLED_RST);
      else if(pinx == GPIO_VPP_EN)
        strcat(path,VPP_EN);
      else if(pinx == GPIO_SPI_CLK)
        strcat(path,CMD_SPI_CLK);
      else if(pinx == GPIO_SPI_CS)
        strcat(path,CMD_SPI_CS);
      else if(pinx == GPIO_SPI_SDI)
        strcat(path,CMD_SPI_SDI);
     
      strcat(path,"/"TRIGGER);
      fd = open(path,O_RDWR);
  
      if(fd<0)
      {
        perror("open");
        close(fd);
        return -1;
      }

      ret = write(fd,TRIGGER_NONE,strlen(TRIGGER_NONE));
      if(ret <0)
      {
        perror("write");
        close(fd);
        return -1;
      }
     close(fd);

    return 0;

}




void Oled_WriteCommand(unsigned short com)
{

  // printf("DEBUG====WRITE CMD A %x \n",com);
  unsigned int i;
  // OLED_CS=1;
  setGpioValue(GPIO_SPI_CS,1);

  //OLED_SCLK=1;
  setGpioValue(GPIO_SPI_CLK,1);

  //OLED_CS=0;
  setGpioValue(GPIO_SPI_CS,0);
  for(i=0x80;i!=0;i/=2)
  {
    //OLED_SCLK=0;
    setGpioValue(GPIO_SPI_CLK,0);
    if(OLED28_CMD&i) 
      //OLED_SDI=1;
      setGpioValue(GPIO_SPI_SDI,1);
    else 
      //OLED_SDI=0;
      setGpioValue(GPIO_SPI_SDI,0);
    //OLED_SCLK=1;
    setGpioValue(GPIO_SPI_CLK,1);
  } 
  for(i=0x8000;i!=0;i/=2)
  { 
    // OLED_SCLK=0; 
    setGpioValue(GPIO_SPI_CLK,0);
    if(com&i) 
      // OLED_SDI=1;
      setGpioValue(GPIO_SPI_SDI,1);
    else 
      // OLED_SDI=0;
      setGpioValue(GPIO_SPI_SDI,0);
    // OLED_SCLK=1;
    setGpioValue(GPIO_SPI_CLK,1);
  } 
  delay_us(1);   //5
  // OLED_CS=1;
  setGpioValue(GPIO_SPI_CS,1);  

}

void WriteData(unsigned short data)
{
  int ret;
    uint8_t tx[] = {
         0x72, 0x00, 0x00, //data
    };
    tx[1]= ((data&0xff00)>>8);
    tx[2]=  (data&0x00ff);

    

    struct spi_ioc_transfer tr = {
            .tx_buf = (unsigned long)tx,
            // .rx_buf = (unsigned long)rx,
            .len = ARRAY_SIZE(tx),
            .delay_usecs = delay,
            .speed_hz = speed,
            .bits_per_word = bits,
    };

    ret = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret == 1)
            pabort("can't send spi message");

}

void Oled_WriteData(unsigned short data)
{

  unsigned int i;
  // OLED_CS=1;
  setGpioValue(GPIO_SPI_CS,1);
  // OLED_SCLK=1;
  setGpioValue(GPIO_SPI_CLK,1);
  // OLED_CS=0;
  setGpioValue(GPIO_SPI_CS,0);

  for(i=0x80;i!=0;i/=2)
  {
    // OLED_SCLK=0;
    setGpioValue(GPIO_SPI_CLK,0);
    if(OLED28_DAT&i) 
      // OLED_SDI=1;
      setGpioValue(GPIO_SPI_SDI,1);
    else 
      // OLED_SDI=0;
      setGpioValue(GPIO_SPI_SDI,0);
    // OLED_SCLK=1;
    setGpioValue(GPIO_SPI_CLK,1);
  } 
  
  for(i=0x8000;i!=0;i/=2)
  { 
    // OLED_SCLK=0; 
    setGpioValue(GPIO_SPI_CLK,0);
    if(data&i) 
      // OLED_SDI=1;
      setGpioValue(GPIO_SPI_SDI,1);
    else 
      // OLED_SDI=0;
      setGpioValue(GPIO_SPI_SDI,0);
    // OLED_SCLK=1;
    setGpioValue(GPIO_SPI_CLK,1);
  } 

  delay_us(1);   //5
  // OLED_CS=1; 
  setGpioValue(GPIO_SPI_CS,1);

}

#endif