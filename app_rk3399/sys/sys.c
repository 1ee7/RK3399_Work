#include "sys.h"

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

