#include "gui.h"
#include "display.h"

char *const PageIndex[] = 
{
  "Data: ",
  "Time:",
};

char *const PageState[] = 
{
  " Status: ",
};

char *const Page1Str[]=
{

  "烟台北方星空科技有限公司",
  "  测试菜单  ",
  "           ",
  "           ",
  "  测试菜单  ",
  "           ",
  "           ",
  "           ",
  "     页  一 ",

};
char *const Page2Str[]=
{
  "烟台北方星空科技有限公司",
  "  测试菜单   ",
  "           ",
  "           ",
  "  测试菜单  ",
  "           ",
  "           ",
  "           ",
  "     页  二 ",

};
char *const Page3Str[]=
{
  "烟台北方星空科技有限公司",
  "  测试菜单   ",
  "           ",
  "           ",
  "  测试菜单  ",
  "           ",
  "           ",
  "           ",
  "      页  三",

};

void page_1()
{ 
  uint8_t i;
  uint8_t static test=0;
  if(test==0)
  { 
    Display_Str(32,18,Page1Str[0],WHITE,BLUE ,LCDREOUT);
    for(i=1;i<MAXLINE;i++)
     {      
        Display_Str(68,18+i*SIZE_HIGH_HZ,Page1Str[i],WHITE,BLUE ,LCDOUT);
     }
      test =1;
    }
    else
    {
       Display_Str(68,18+8*SIZE_HIGH_HZ,Page1Str[8],WHITE,BLUE ,LCDOUT);
    }
}

void page_2()
{
   uint8_t i=8;
   // Display_Str(32,0,Page2Str[0],WHITE,BLUE ,LCDREOUT);
    // for(i=1;i<MAXLINE;i++)
     {      
        Display_Str(68,18+i*SIZE_HIGH_HZ,Page2Str[i],WHITE,BLUE ,LCDOUT);
     }
}

void page_3()
{
   uint8_t i=8;
   // Display_Str(32,0,Page3Str[0],WHITE,BLUE ,LCDREOUT);
    // for(i=1;i<MAXLINE;i++)
     {      
        Display_Str(68,18+i*SIZE_HIGH_HZ,Page3Str[i],WHITE,BLUE ,LCDOUT);
     }
}


void Gui_Index_Update()
{
  // Display_Str(0,0,PageIndex[0],WHITE,BLACK,LCDOUT);
  // Display_Str(16,0,"2017-10-24 TIME;15:50 ",WHITE,BLACK,LCDOUT);

}




void Gui_Next_Screen(uint8_t page_index)
{

  switch(page_index)
  {
    case 1:
           page_1();
    break;

    case 2:
          page_2();
    break;

    case 3:
          page_3();
    break;

    default:     break;
  }
    
}
