#include "rk3399_gpio.h"


#ifndef SPI_BUS
//gpio -1
#define RK3399_GPIO1_BASE 0xff730000
#define RK3399_GPIO_DATA  0x0000
#define RK3399_GPIO_DIRC  0x0004

	int gpio_mmap_fd = 0;
	uint8_t* gpio1_mmap_base_reg = NULL;
	static const char *map_path="/dev/mem";

	void Gpio_MMap_Close()
	{
		close(gpio_mmap_fd);
	}

	//MMap
	int Gpio_MMap_Init()
	{
	  	if ((gpio_mmap_fd = open(map_path, O_RDWR|O_SYNC)) < 0) {
			fprintf(stderr, "unable to open mmap file");
			return -1;
		}
		return 0;
	}

	int  Gpio1_MMap()
	{
		 gpio1_mmap_base_reg = (uint8_t*) mmap(NULL, 4096, PROT_READ | PROT_WRITE,
			MAP_SHARED, gpio_mmap_fd,RK3399_GPIO1_BASE);
	   	if (gpio1_mmap_base_reg == MAP_FAILED)
	   	 {
			perror("failed ---gpio1 ");
			fprintf(stderr, "failed to mmap");
			gpio1_mmap_base_reg = NULL;
			close(gpio_mmap_fd);
			return -1;
		}
	}

	void Gpio1_Set_Pin_Value(int pin,int value)
	{
	   uint32_t tmp;

	   tmp = (1u<<pin);
	   // printf("the data is %x\n",tmp );
	   if(value)
	    *(volatile uint32_t *)(gpio1_mmap_base_reg+RK3399_GPIO_DATA) |= tmp;
	   else
	   	*(volatile uint32_t *)(gpio1_mmap_base_reg+RK3399_GPIO_DATA)&=(~tmp);
	}

#else  /* tgl mark */
	int gpio_fd;
	static const char *device_gpio = "/dev/gpio_demo";

	int Gpio_Init_Spi()
	{
	    gpio_fd = open(device_gpio,O_RDWR);
	    if(gpio_fd<0)
	    {
	        printf("open /dev/gpio_demo error \n");
	        return -1;
	    }
	        return 0;   
	}


	void set_pin_value(int pin,int value)
	{
	   ioctl(gpio_fd,pin,value);
	}

	void Gpio_Close_Spi()
	{
	    close(gpio_fd);
	}

#endif