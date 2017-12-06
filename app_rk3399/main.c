

#include <signal.h>
 

#include "rk3399_gpio.h"
#include "rk3399_spi.h"
#include "sys.h"
#include "oled.h"
#include "display.h"
#include "rk3399_global.h"
#include "thread.h"


// static uint8_t run=1;
pthread_t pthread_id[3];//线程ID


char *const InitStrCh[]=
{
  "测试一",
  "1-a菜单零-1",
  "1-b菜单一-2",
  "1-c菜单二-3 ",
  "1-d菜单三-4 ",
  "1-e菜单四-5 ",
  "1-f菜单五-6 ",
  "1-g菜单六-7 ",
  "1-h菜单七-8 ",
  "1-i菜单九-9 ",
  "1-j菜单十-10",
  "1-k菜单零-11",
  "1-0菜单一-12",
  "1-1菜单二-13",
  "1-2菜单三-14",
  "1-3菜单四-15",
  "1-4菜单五-16",
  "1-5菜单六-17",
  "1-6菜单七-18",
  "1-7菜单九-19",
};

char *const InitStrCh0[]=
{
  "测试二",
  "2-a菜单零-0 ",
  "2-b菜单二-3 ",
  "2-c菜单二-3 ",
  "2-d菜单三-4 ",
  "2-e菜单四-5 ",
  "2-f菜单五-6 ",
  "2-g菜单六-7 ",
  "2-h菜单七-8 ",
  "2-i菜单九-9 ",
  "2-j菜单十-10",
  "2-k菜单零-11",
  "2-0菜单一-12",
  "2-1菜单二-13",
  "2-2菜单三-14",
  "2-3菜单四-15",
  "2-4菜单五-16",
  "2-5菜单六-17",
  "2-6菜单七-18",
  "2-7菜单九-20",
};

char *const InitStrCh2[]=
{
  "测试三",
  "3-a菜单零-0 ",
  "3-b菜单二-3 ",
  "3-c菜单二-3 ",
  "3-d菜单三-4 ",
  "3-e菜单四-5 ",
  "3-f菜单五-6 ",
  "3-g菜单六-7 ",
  "3-h菜单七-8 ",
  "3-i菜单九-9 ",
  "3-j菜单十-10",
  "3-k菜单零-11",
  "3-0菜单一-12",
  "3-1菜单二-13",
  "3-2菜单三-14",
  "3-3菜单四-15",
  "3-4菜单五-16",
  "3-5菜单六-17",
  "3-6菜单七-18",
  "3-7菜单九-20",
};




void test_color()
{
printf("===  TEST COLOR START...\n");

#ifdef TEST_RUN_TIMES
 struct timeval pstart,pend;
 float timeuser;
#endif

   
 OLED_COLOR(RED);  delay_ms(800);

 OLED_COLOR(BLUE); delay_ms(800);

#ifdef TEST_RUN_TIMES
 gettimeofday(&pstart,NULL);
#endif
 OLED_COLOR(BRED); 

#ifdef TEST_RUN_TIMES
 gettimeofday(&pend,NULL);
 timeuser = 1000000*(pend.tv_sec-pstart.tv_sec)+(pend.tv_usec-pstart.tv_usec);
 timeuser/=1000000;
 printf("\n****timeuser is %f*******\n",timeuser);
#endif

 delay_ms(800);


 OLED_COLOR(GRED); delay_ms(800);

 OLED_COLOR(GBLUE);delay_ms(800);

 OLED_COLOR(WHITE);delay_ms(800);

 OLED_COLOR(BLACK);delay_ms(800);

 OLED_COLOR(BROWN);delay_ms(800);

 OLED_COLOR(BRRED);delay_ms(800);

 OLED_COLOR(GRAY );delay_ms(800);

 OLED_COLOR(GREEN);delay_ms(800);

 OLED_COLOR(LGRAY);delay_ms(800);

 printf("=== TEST COLOR END === \n");
}


void test_font()
{
  printf("===  TEST Font START...\n");

   OLED_COLOR(BLUE);
   Display_Char16(232,20,WHITE,BLUE,"1234556565");
   Display_Char16(232,50,WHITE,BLUE,"abcdefghijklmnopqrstuvw00");
   Display_String_Hz(224,100,WHITE,BLUE);
   delay_ms(1200);
   printf("=== TEST Font END === \n");
}

void test_change_screen()
{
    uint8_t i;
    static uint8_t first;

#ifdef TEST_RUN_TIMES
    struct timeval pstart,pend;
    float timeuser;
#endif

    printf("=== TEST Change_Screen START...\n");

  
    if(first==0)
    {
      OLED_COLOR(BLUE);
      first=1;
    }       

      OLED_DisplayOff();
    #ifdef TEST_RUN_TIMES
      gettimeofday(&pstart,NULL);
    #endif

      Display_Str(100,0,InitStrCh[0],WHITE,BLUE ,LCDREOUT);
     for(i=1;i<MAXLINE;i++)
     {  
         Display_Str(68,i*SIZE_HIGH_HZ,InitStrCh[i],WHITE,BLUE ,LCDOUT);   
     }
     #ifdef TEST_RUN_TIMES
       gettimeofday(&pend,NULL);
    #endif
      OLED_DisplayOn();  


     delay_ms(800);
   
     OLED_DisplayOff();
     Display_Str(100,0,InitStrCh0[0],WHITE,BLUE ,LCDREOUT);
     for(i=1;i<MAXLINE;i++)
     {
      
        Display_Str(68,i*SIZE_HIGH_HZ,InitStrCh0[i],WHITE,BLUE ,LCDOUT);
     }
     OLED_DisplayOn();
     delay_ms(800);

      OLED_DisplayOff();
     Display_Str(100,0,InitStrCh2[0],WHITE,BLUE ,LCDREOUT);
     for(i=1;i<MAXLINE;i++)
     {
      
        Display_Str(68,i*SIZE_HIGH_HZ,InitStrCh2[i],WHITE,BLUE ,LCDOUT);
     }
     OLED_DisplayOn();
     delay_ms(800);

    
#ifdef TEST_RUN_TIMES
     timeuser = 1000000*(pend.tv_sec-pstart.tv_sec)+(pend.tv_usec-pstart.tv_usec);

     timeuser/=1000000;

     printf("timeuser is %f\n",timeuser);
#endif

   printf("=== TEST Change_Screen END === \n");
}


void test_while_time()
{ 
    uint8_t i;
   struct timeval pstart,pend;
   float timeuser;
     printf("=== TEST TIMES START...\n");
      gettimeofday(&pstart,NULL);


      Display_Str(100,0,InitStrCh[0],WHITE,BLUE ,LCDREOUT);
     for(i=1;i<MAXLINE;i++)
     {  
         Display_Str(68,i*SIZE_HIGH_HZ,InitStrCh[i],WHITE,BLUE ,LCDOUT);   
     }

       gettimeofday(&pend,NULL);

     timeuser = 1000000*(pend.tv_sec-pstart.tv_sec)+(pend.tv_usec-pstart.tv_usec);

     timeuser/=1000000;

     printf("****timeuser 1 is %f\n",timeuser);
    
    delay_ms(800);

      gettimeofday(&pstart,NULL);

      Display_Str(100,0,InitStrCh0[0],WHITE,BLUE ,LCDREOUT);
     for(i=1;i<MAXLINE;i++)
     {  
         Display_Str(68,i*SIZE_HIGH_HZ,InitStrCh0[i],WHITE,BLUE ,LCDOUT);   
     }

       gettimeofday(&pend,NULL);


     timeuser = 1000000*(pend.tv_sec-pstart.tv_sec)+(pend.tv_usec-pstart.tv_usec);

     timeuser/=1000000;

     printf("*****timeuser 2 is %f\n",timeuser);

    delay_ms(800);
      gettimeofday(&pstart,NULL);

     OLED_COLOR(BRED); 

     gettimeofday(&pend,NULL);
     timeuser = 1000000*(pend.tv_sec-pstart.tv_sec)+(pend.tv_usec-pstart.tv_usec);
     timeuser/=1000000;
     printf("\n****timeuser color red is %f*******\n",timeuser);

     delay_ms(800);

       gettimeofday(&pstart,NULL);
     OLED_COLOR_ONEBYONE(BLUE); 
      gettimeofday(&pend,NULL);
       timeuser = 1000000*(pend.tv_sec-pstart.tv_sec)+(pend.tv_usec-pstart.tv_usec);
     timeuser/=1000000;
     printf("\n****timeuser color blue is %f*******\n",timeuser);
     delay_ms(800);
     printf("=== TEST TIMES END === \n"); 
}

int create_task()
{
  printf("** create task for keys \n");
   if (pthread_create(&pthread_id[0], NULL, Thread_Key , NULL))
        printf("Create thread_1 error!\n");

   if (pthread_create(&pthread_id[1], NULL, Thread_Status , NULL))
        printf("Create thread_1 error!\n");

      return 0;
}

void test_for(uint16_t value)
{ 
   uint32_t i,a; 
   struct timeval pstart,pend;
   float timeuser;
   printf("=== TEST TIMES START...\n");
   gettimeofday(&pstart,NULL);
   for(i = 0; i < 76800;i++)
   {
      // a++;
      // SPI_RST_1;
      // SPI_VPP_1;
      // SPI_RST_1;
      // SPI_SDI_1;
      // SPI_CLK_1;
      // a++;
      // set_pin_value(0,value);
     
     //  SPI_RST_0;
      //SPI_VPP_0;
      //printf("a is %d\n", a);
   }
    gettimeofday(&pend,NULL);
     timeuser = 1000000*(pend.tv_sec-pstart.tv_sec)+(pend.tv_usec-pstart.tv_usec);
     timeuser/=1000000;
     printf("*****timeuser 2 is %f\n",timeuser);
      printf("=== TEST TIMES END====\n");
}

uint16_t arry[]={
  0x7f,0x3f,0x1f,0x0f,
  0x07,0x03,0x01,0x00,
};

int main()
{
  int i;
#ifndef SPI_BUS
    Gpio_MMap_Init();
    Gpio1_MMap();
#else  /* tgl mark */
    Gpio_Init_Spi();
    SPI_Init();
#endif

   //OLED_Init(); /* tgl mark */

   // test_color();
   // test_change_screen();
    
   //create_task();

   //OLED_COLOR(BLUE); /* tgl mark */
 
   while(1)
   {

      // test_change_screen();
    // test_while_time();
// for(i=0;i<8;i++)
//    test_for(arry[i]);

      
   }
#ifndef SPI_BUS
   Gpio_MMap_Close();
#else
   SPI_Close();
   Gpio_Close_Spi();
#endif

    if(pthread_id[0] !=0 ) 
    { 
          pthread_join(pthread_id[0],NULL);
          printf("thread_1 %ld exit!\n",pthread_id[0]);
     }
     return 0;

}

