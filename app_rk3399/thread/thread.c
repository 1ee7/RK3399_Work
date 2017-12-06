#include "thread.h"
#include "gui.h"
#include "key.h"

static uint8_t key_current_page=0;
struct input_event t; 

void *Thread_Key(void *arg) 
{    
	key_open_event();
  
  while(1)
  {

     if (read(keys_fd, &t, sizeof (t)) == sizeof (t))  
     {
      if(t.type == EV_KEY )
      { 
           switch(t.code)
           {
             case PAGE_DOWN:
             {
               if(t.value) 
               {
                if(key_current_page>=PAGE_NUM)
                   key_current_page = 1 ;
                 else
                   key_current_page++;

                 printf("page is %d\n",key_current_page );

                  Gui_Next_Screen(key_current_page);
               } 
             }
             break;

             default:
             break;
         }
      }
      
     }

  }
  pthread_exit(NULL);

}

void *Thread_Status(void *arg)
{
	while(1)
  {
    Gui_Index_Update();
    sleep(1);
  }
   pthread_exit(NULL);
}