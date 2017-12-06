#include "oled.h"
#include "display.h"
#include "font_oled.h"

#ifdef OLED_CROSS   //横屏
#define MAXBYTES_ROW 60
#else
#define MAXBYTES_ROW 45 //每行最多显示的字节数
#endif

void Display_Line(uint16_t _usX1, uint16_t  _usY1,uint16_t  _usX2, uint16_t  _usY2,uint16_t _usColor)
{
  int32_t dx , dy ;
  int32_t tx , ty ;
  int32_t inc1 , inc2 ;
  int32_t d , iTag ;
  int32_t x , y ;

  OLED_Draw_Point(_usX1 , _usY1 , _usColor);

  if ( _usX1 == _usX2 && _usY1 == _usY2 )
  {
    return;
  }

  iTag = 0 ;
  /* dx = abs ( _usX2 - _usX1 ); */
  if (_usX2 >= _usX1)
  {
    dx = _usX2 - _usX1;
  }
  else
  {
    dx = _usX1 - _usX2;
  }

  /* dy = abs ( _usY2 - _usY1 ); */
  if (_usY2 >= _usY1)
  {
    dy = _usY2 - _usY1;
  }
  else
  {
    dy = _usY1 - _usY2;
  }

  if ( dx < dy )   
  {
    uint16_t temp;

    iTag = 1 ;
    temp = _usX1; _usX1 = _usY1; _usY1 = temp;
    temp = _usX2; _usX2 = _usY2; _usY2 = temp;
    temp = dx; dx = dy; dy = temp;
  }
  tx = _usX2 > _usX1 ? 1 : -1 ;    
  ty = _usY2 > _usY1 ? 1 : -1 ;
  x = _usX1 ;
  y = _usY1 ;
  inc1 = 2 * dy ;
  inc2 = 2 * ( dy - dx );
  d = inc1 - dx ;
  while ( x != _usX2 )     
  {
    if ( d < 0 )
    {
      d += inc1 ;
    }
    else
    {
      y += ty ;
      d += inc2 ;
    }
    if ( iTag )
    {
      OLED_Draw_Point ( y , x , _usColor) ;
    }
    else
    {
      OLED_Draw_Point ( x , y , _usColor) ;
    }
    x += tx ;
  }
} 


void Display_Circle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor)
{
  int32_t  D;     /* Decision Variable */
  uint32_t  CurX;  
  uint32_t  CurY;   

  D = 3 - (_usRadius << 1);
  CurX = 0;
  CurY = _usRadius;

  while (CurX <= CurY)
  {
    OLED_Draw_Point(_usX + CurX, _usY + CurY, _usColor);
    OLED_Draw_Point(_usX + CurX, _usY - CurY, _usColor);
    OLED_Draw_Point(_usX - CurX, _usY + CurY, _usColor);
    OLED_Draw_Point(_usX - CurX, _usY - CurY, _usColor);
    OLED_Draw_Point(_usX + CurY, _usY + CurX, _usColor);
    OLED_Draw_Point(_usX + CurY, _usY - CurX, _usColor);
    OLED_Draw_Point(_usX - CurY, _usY + CurX, _usColor);
    OLED_Draw_Point(_usX - CurY, _usY - CurX, _usColor);

    if (D < 0)
    {
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}

void Display_Rect(uint16_t _usX1, uint16_t _usY1,uint16_t _usX2, uint16_t _usY2,uint16_t _usX3,
  uint16_t _usY3,uint16_t _usX4, uint16_t _usY4,uint16_t _usColor)
{
  Display_Line(_usX1,_usY1,_usX2,_usY2,_usColor);
  Display_Line(_usX2,_usY2,_usX3,_usY3,_usColor);
  Display_Line(_usX3,_usY3,_usX4,_usY4,_usColor);
  Display_Line(_usX4,_usY4,_usX1,_usY1,_usColor);
}


void Display_Char16(uint16_t x, uint16_t y, uint16_t fontcolor, uint16_t backcolor, char *s)
{
  uint8_t i,j;
  uint16_t k;

  while(*s) 
  {
    if( *s < 0x80 )
    {
      k=*s;
      if (k>32) 
        k-=32;
      else k=0;


      // printf("\n ====the char is %c\n",*s);

     for(j=0;j<16;j++)
     {
      for(i=0;i<8;i++) 
        {
          // printf("acs is 0x%x\n",asc16[k*16+j] );
          // printf("x: %d ,y: %d \n",x+i,y+j );
          
            if(asc16[k*16+j]&(0x80>>i)) 
              OLED_Draw_Point(x+i,y+j,fontcolor);
            else if (fontcolor!=backcolor) 
              OLED_Draw_Point(x+i,y+j,backcolor);
            
        }
      }
      s++;
      // x+=8;
      x -= 8;
    }
  }
}

void Display_One_Hz_Revs(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint16_t s)
{
  uint8_t i,j,temp;
  uint16_t y0;

  y0 = y;
  for(i = 31;i >= 0;i--)
  {
    temp = Hz_16[s][i] ;
    for(j = 0;j < 8;j++)
    {
      if(temp & 0x80)
      {
        OLED_Draw_Point(x,y0,fc);
      }
      else 
      {
        OLED_Draw_Point(x,y0,bc);
      }
      temp = temp << 1;
      y0++;
    }
    if(i % 2)
    {
      // x++;
      x--;
      y0 = y; 
    }
  }
}



void Display_One_Hz(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint16_t s)
{
  uint8_t i,j,temp;
  uint16_t y0;

  y0 = y;
  for(i = 0;i < 32;i++)
  {
    temp = Hz_16[s][i] ;
    for(j = 0;j < 8;j++)
    {
      if(temp & 0x80)
      {
        OLED_Draw_Point(x,y0,fc);
      }
      else 
      {
        OLED_Draw_Point(x,y0,bc);
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

void Display_String_Hz(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc)
{
  uint8_t x0,i;
  x0 = x; 
  for(i = 0;i <MAX_HZ_ROW;i++)
  {
    
    Display_One_Hz(x0,y,fc,bc,i);

    x0 -= 16;
  }
}




void Display_Str(uint16_t x,uint16_t y,char *str,uint16_t frontclr,uint16_t backclr ,unsigned char dir)
{
  uint8_t *stg;
  unsigned char c=0;
  uint16_t index,num,len,HzNmb,xlocal,ylocal,i,j,mask=0x80;
  uint32_t tmp;
  uint8_t temp0;
  uint16_t y0,x0;

    xlocal = 240-x;
    ylocal = y;

    stg=(uint8_t *)str;
    len = strlen(str);

      // printf("\n******debug**** len is %d \n", len);


    if(len>MAXBYTES_ROW)  // 15 or 20 hz every row
    {
      len = MAXBYTES_ROW;
    }

    HzNmb = sizeof(CodeTable);
    
    num = len;

    while(num > 0)
    {
       if((*stg)& mask) //hanzi
      {
         index = 0x0ffff;
        
         tmp = (*stg)*65536 + (*(stg+1))*256 + *(stg+2);
         // tmp = (tmp1<<16)+ (tmp2<<8) + *(stg+2);

         for(i=0;i<HzNmb;i++)        
         {
            if(tmp==CodeTable[i])
            {
              index = i;i=HzNmb;
            }          
        }

        if(index < 0x0ffff)
        {               
            x0 = xlocal-16;
            y0 = ylocal;
            for(i = 0;i < 32;i++)
            {
              if(dir == LCDREOUT)
                  temp0 = ~(Hz_16[index][i]&0xff) ;
              else
                  temp0 = Hz_16[index][i] ;

              for(j = 0;j < 8;j++)
              {
                if(temp0 & 0x80)
                {
                  OLED_Draw_Point(x0,y0,frontclr);
                }
                else 
                if(frontclr!=backclr)
                {
                  OLED_Draw_Point(x0,y0,backclr);
                }
                temp0 = temp0 << 1;
                y0++;
              }
              if(i % 2)
              {
                x0++;
                y0 = ylocal; 
              }
            }          

        }      
        
         num -= 3;     stg += 3;  
         xlocal -= 16; ylocal = y;  
      
         if(xlocal == 0)       xlocal = x;   // no way to create a new row 
      }
      else
      {
          c = (*stg)-' ';//得到偏移后的值   
         
          if((xlocal-8)  ==0)
          {
            xlocal = 240-8;
            ylocal = y;  //mark tgl
          }
          if(CHAR_HIGH == 16)
          { 
              for(j=0;j<16;j++)
              {
                for(i=0;i<8;i++)  {
                
                 if(dir == LCDREOUT)
                   temp0 = ~(asc16[c*16+j]&0xff);                 
                 else
                   temp0 = asc16[c*16+j];
                 

                   if(temp0&(0x80>>i))
                   {
                     OLED_Draw_Point(xlocal+i-8,ylocal+j,frontclr);
                   }
                   else  
                  if(frontclr!=backclr) 
                   {
                     OLED_Draw_Point(xlocal+i-8,ylocal+j,backclr);
                   }
                   }
              }
              xlocal-=8;
          }
         
            if(xlocal==0)         
            {  
               xlocal = 240-8; 
               ylocal = y;   //mark tgl
            }
            num -= 1; 
            stg += 1;  
        }
    }// end while(num > 0)
}


