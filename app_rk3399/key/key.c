#include "key.h"




static const char *keys_event = "/dev/input/event1";



int  key_open_event()
{
          
    keys_fd = open(keys_event, O_RDONLY);  
    if (keys_fd <= 0)  
    {  
        printf("open /dev/input/event1 device error!\n");  
        return -1;  
    }  
    return 0;
}

