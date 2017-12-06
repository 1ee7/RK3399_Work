#include "oled.h"
#include "rk3399_gpio.h"
#include "rk3399_spi.h"
#include "sys.h"


static uint8_t tx_cmd[3]=
{
  0x70,0x00,0x00
};

static uint8_t tx_data[3]=
{
  0x72,0x00,0x00
};

static const uint8_t write_cmd =1;
static const uint8_t write_dat =0;

#ifndef  SPI_BUS

void OLED_WriteCommand(uint16_t com)
{
   uint16_t i;
  /*test*/
   // SPI_CS_1;
   // SPI_CLK_1;

   SPI_CS_0;

   // SPI_CS_0;
   // for(i=0x80;i!=0;i/=2) //
   
    for(i=0;i<8;i++)
   {
   
      // if(write_cmd&i)  //
     if((write_cmd<<i)&0x80)
        SPI_SDI_1;
      else 
       SPI_SDI_0;

     SPI_CLK_0;
     SPI_CLK_1;
   }
   // for(i=0x8000;i!=0;i/=2) //// 
    for(i=0;i<16;i++)
   {
     
      // if(com&i)  //
      if((com<<i)&0x8000)
        SPI_SDI_1;
      else 
       SPI_SDI_0;

     SPI_CLK_0;
     SPI_CLK_1;
   }
   
   // delay_us(1);
   SPI_CS_1;

   // /* test */
   //   SPI_SDI_0;
   //    SPI_SDI_1;
}

void OLED_WriteData(uint16_t data)
{
   uint16_t i;
   /* test */
   // SPI_CS_1;
   // SPI_CLK_1;


   SPI_CS_0;
   // for(i=0x80;i!=0;i/=2) //
    for(i=0;i<8;i++)
   {
    
      // if(OLED_DAT&i)  //
      if((OLED_DAT<<i)&0x80)
        SPI_SDI_1;
      else 
       SPI_SDI_0;

      SPI_CLK_0;
     SPI_CLK_1;
   }
   // for(i=0x8000;i!=0;i/=2) //// 
   for(i=0;i<16;i++)
   {
     
     // if(data&i)  //
     if((data<<i)&0x8000)
        SPI_SDI_1;
      else 
       SPI_SDI_0;
     SPI_CLK_0;
     SPI_CLK_1;
   }
   
   // delay_us(1);
   SPI_CS_1;

   /*test*/
    // SPI_CLK_0;
    // SPI_SDI_1;
}

#else
void OLED_WR_Byte(uint8_t data1,uint8_t data2,uint8_t cmd)
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
#endif

void OLED_Reset()
{
  // SPI_RST_1;   
  // SPI_RST_0;
  SPI_RST_1;
  SPI_RST_0;
  delay_ms(800);
  SPI_RST_1;
}

void OLED_Clear()
{
  OLED_COLOR(0);
}


void OLED_COLOR(uint16_t ch)  
{ 
  unsigned int i;

#ifndef SPI_BUS
   OLED_WriteCommand(0x0020);OLED_WriteData(0); //x
   OLED_WriteCommand(0x0021);OLED_WriteData(0); //y
   OLED_WriteCommand(0x0005);OLED_WriteData(0x0000);//disyplay_OFF
  for(i = 0; i < 76800;i++)
  {
   OLED_WriteCommand(0x0022);
   OLED_WriteData(ch);
  }
   OLED_WriteCommand(0x0005);OLED_WriteData(0x0001);//disyplay_ON

#else
 uint8_t col_high,col_low; 
 col_high = (ch & 0xff00)>>8;
 col_low = (ch&0xff);

 OLED_WR_Byte(0x00,0x20,write_cmd); OLED_WR_Byte(0x00,0x00,write_dat);
 OLED_WR_Byte(0x00,0x21,write_cmd); OLED_WR_Byte(0x00,0x00,write_dat);
 OLED_WR_Byte(0x00,0x05,write_cmd); OLED_WR_Byte(0x00,0x00,write_dat);
 for(i = 0; i < 76800;i++)
 {
    OLED_WR_Byte(0x00,0x22,write_cmd); 
    OLED_WR_Byte(col_high,col_low,write_dat);
 }

  OLED_WR_Byte(0x00,0x05,write_cmd); OLED_WR_Byte(0x00,0x01,write_dat);//W
#endif
} 

void OLED_COLOR_ONEBYONE(uint16_t ch)  
{ 
  unsigned int i;

#ifndef SPI_BUS
   OLED_WriteCommand(0x0020);OLED_WriteData(0); //x
   OLED_WriteCommand(0x0021);OLED_WriteData(0); //y
   // OLED_WriteCommand(0x0005);OLED_WriteData(0x0000);//disyplay_OFF
  for(i = 0; i < 76800;i++)
  {
   OLED_WriteCommand(0x0022);
   OLED_WriteData(ch);
  }
   // OLED_WriteCommand(0x0005);OLED_WriteData(0x0001);//disyplay_ON

#else
 uint8_t col_high,col_low; 
 col_high = (ch & 0xff00)>>8;
 col_low = (ch&0xff);

 OLED_WR_Byte(0x00,0x20,write_cmd); OLED_WR_Byte(0x00,0x00,write_dat);
 OLED_WR_Byte(0x00,0x21,write_cmd); OLED_WR_Byte(0x00,0x00,write_dat);
 // OLED_WR_Byte(0x00,0x05,write_cmd); OLED_WR_Byte(0x00,0x00,write_dat);
 for(i = 0; i < 76800;i++)
 {
    OLED_WR_Byte(0x00,0x22,write_cmd); OLED_WR_Byte(col_high,col_low,write_dat);
 }

  // OLED_WR_Byte(0x00,0x05,write_cmd); OLED_WR_Byte(0x00,0x01,write_dat);//W
#endif
} 

void OLED_Init()
{

  printf("== begin === OLED INIT.... \n");
  OLED_Reset();
#ifndef SPI_BUS
  OLED_WriteCommand(0x0023); //Select 18-/16-bit Data Bus Interface

  OLED_WriteCommand(0x0005);OLED_WriteData(0x0000);//Display Control1 //0--关闭显示，1--打开显示
  OLED_WriteCommand(0x0018);OLED_WriteData(0x002f);//Oscillator Control x1.0
  OLED_WriteCommand(0x0004);OLED_WriteData(0x0030);//Clock Control
  OLED_WriteCommand(0x0002);OLED_WriteData(0x0030);//RGB Interface Control System模式
  OLED_WriteCommand(0x0003);OLED_WriteData(0x0130);//System模式,16bit接口65K, 0x6030 262k
  OLED_WriteCommand(0x0010);OLED_WriteData(0x0000);//1--待机模式，0--正常模式 
    
  //gamma setting 250 nits(标准值)
  OLED_WriteCommand(0x0070); OLED_WriteData(0x2b80);// Gamma Top/Bottom R(亮度，值越大越亮，最大值3f8f)
  OLED_WriteCommand(0x0071); OLED_WriteData(0x2c80);// Gamma Top/Bottom G(亮度，值越大越亮，最大值3f8f)
  OLED_WriteCommand(0x0072); OLED_WriteData(0x3980);// Gamma Top/Bottom B(亮度，值越大越亮，最大值3f8f)
  OLED_WriteCommand(0x0073); OLED_WriteData(0x1912);// Gamma Top Bottom R1,2(对比度，值越大对比度越高，最大值3f3f)
  OLED_WriteCommand(0x0074); OLED_WriteData(0x1a0d);// Gamma Top Bottom R3,4(对比度，值越大对比度越高，最大值3f3f)
  OLED_WriteCommand(0x0075); OLED_WriteData(0x2014);// Gamma Top Bottom G1,2(对比度，值越大对比度越高，最大值3f3f)
  OLED_WriteCommand(0x0076); OLED_WriteData(0x1811);// Gamma Top Bottom G3,4(对比度，值越大对比度越高，最大值3f3f)
  OLED_WriteCommand(0x0077); OLED_WriteData(0x2218);// Gamma Top Bottom B1,2(对比度，值越大对比度越高，最大值3f3f)
  OLED_WriteCommand(0x0078); OLED_WriteData(0x1e11);// Gamma Top Bottom B3,4(对比度，值越大对比度越高，最大值3f3f)

  OLED_Clear(); 

  OLED_WriteCommand(0x0005); OLED_WriteData(0x0001);//OLED_WriteData(0x00); 
#else
  SPI_VPP_0;
  OLED_Reset();

  OLED_WR_Byte(0x00,0x23,write_cmd);
  OLED_WR_Byte(0x00,0x05,write_cmd); OLED_WR_Byte(0x00,0x00,write_dat);
  OLED_WR_Byte(0x00,0x18,write_cmd); OLED_WR_Byte(0x00,0x48,write_dat);//OLED_WR_Byte(0x00,0x2f,write_dat);  x1.0->1.256
  OLED_WR_Byte(0x00,0x04,write_cmd); OLED_WR_Byte(0x00,0x30,write_dat);  //Clock Control
  OLED_WR_Byte(0x00,0x02,write_cmd); OLED_WR_Byte(0x00,0x30,write_dat);  //RGB Interface Control System
  OLED_WR_Byte(0x00,0x03,write_cmd); OLED_WR_Byte(0x01,0x30,write_dat);  //System 0x6030 262k
  OLED_WR_Byte(0x00,0x10,write_cmd); OLED_WR_Byte(0x00,0x00,write_dat);  //
    
  //gamma setting 250 nits
  OLED_WR_Byte(0x00,0x70,write_cmd); OLED_WR_Byte(0x2b,0x80,write_dat);// Gamma Top/Bottom R()
  OLED_WR_Byte(0x00,0x71,write_cmd); OLED_WR_Byte(0x2c,0x80,write_dat);// Gamma Top/Bottom G()
  OLED_WR_Byte(0x00,0x72,write_cmd); OLED_WR_Byte(0x39,0x80,write_dat);// Gamma Top/Bottom B()
  OLED_WR_Byte(0x00,0x73,write_cmd); OLED_WR_Byte(0x19,0x12,write_dat);// Gamma Top Bottom R1,2()
  OLED_WR_Byte(0x00,0x74,write_cmd); OLED_WR_Byte(0x1a,0x0d,write_dat);// Gamma Top Bottom R3,4()
  OLED_WR_Byte(0x00,0x75,write_cmd); OLED_WR_Byte(0x20,0x14,write_dat);// Gamma Top Bottom G1,2()
  OLED_WR_Byte(0x00,0x76,write_cmd); OLED_WR_Byte(0x18,0x11,write_dat);// Gamma Top Bottom G3,4()
  OLED_WR_Byte(0x00,0x77,write_cmd); OLED_WR_Byte(0x22,0x18,write_dat);// Gamma Top Bottom B1,2()
  OLED_WR_Byte(0x00,0x78,write_cmd); OLED_WR_Byte(0x1e,0x11,write_dat);// Gamma Top Bottom B3,4()

  OLED_Clear(); 
  SPI_VPP_1;
  OLED_WR_Byte(0x00,0x05,write_cmd); OLED_WR_Byte(0x00,0x01,write_dat);//OLED_WriteData(0x00); 
#endif
  printf("== end === OLED INIT.... \n");
   OLED_COLOR(BLUE);

}



void OLED_Draw_Point(uint16_t x,uint16_t y,uint16_t fontcolor)
{
  #ifdef OLED_CROSS
    x = x+y;
    y = x-y;          //y=x;
    x = 240+y-x; // x=240-y;
  #endif

#ifndef SPI_BUS
   OLED_WriteCommand(0x0020);OLED_WriteData(x); //x
   OLED_WriteCommand(0x0021);OLED_WriteData(y); //y

   OLED_WriteCommand(0x0022);
   OLED_WriteData(fontcolor);//

#else
  OLED_WR_Byte(0x00,0x20,write_cmd); OLED_WR_Byte((x&0xff00)>>8,x&0xff,write_dat);
  OLED_WR_Byte(0x00,0x21,write_cmd); OLED_WR_Byte((y&0xff00)>>8,y&0xff,write_dat);
  OLED_WR_Byte(0x00,0x22,write_cmd); OLED_WR_Byte((fontcolor&0xff00)>>8,fontcolor&0xff,write_dat);
#endif
}


void OLED_DisplayOn(void)
{
  #ifndef SPI_BUS
   OLED_WriteCommand(0x0005);OLED_WriteData(0x0001); //x
  #else
  OLED_WR_Byte(0x00,0x05,write_cmd); OLED_WR_Byte(0x00,0x01,write_dat);
  #endif
}

void OLED_DisplayOff(void)
{
  #ifndef SPI_BUS
  OLED_WriteCommand(0x0005);OLED_WriteData(0x0000); //x
  #else
  OLED_WR_Byte(0x00,0x05,write_cmd); OLED_WR_Byte(0x00,0x00,write_dat);
  #endif
}