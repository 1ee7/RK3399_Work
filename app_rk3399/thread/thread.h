#include "rk3399_global.h"
#include <linux/input.h>  
#include <pthread.h>
extern int keys_fd;

void *Thread_Key(void *arg) ;
void *Thread_Status(void *arg);