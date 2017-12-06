#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>	
#include <time.h>
#define MMAP_PATH	"/dev/mem"


#define RK3399_GPIO_DATA  0x0000
#define RK3399_GPIO_DIRC  0x0004

#define RK3399_GPIO0_CON1 0x0104

// #define RK3399_GPIO1_DATA  0x00730000
// #define RK3399_GPIO1_DIRC  0x00730004

#define RK3399_GPIO_0A_IOMUX 0x00000000
#define RK3399_GPIO_0B_IOMUX 0x00000004
#define RK3399_GPIO_1A_IOMUX 0x00000010
#define RK3399_GPIO_1B_IOMUX 0x00000014

#define RK3399_PIN_0  0xfffffffc
#define RK3399_PIN_1  0xfffffff3
#define RK3399_PIN_2  0xffffffcf
#define RK3399_PIN_3  0xffffff3f
#define RK3399_PIN_4  0xfffffcff
#define RK3399_PIN_5  0xfffff3ff
#define RK3399_PIN_6  0xffffcfff
#define RK3399_PIN_7  0xffff3fff


#define DIRC_OUTPUT 1
#define DIRC_INPUT 0

#define DATA_LOW 0
#define DATA_HIGH 1

#define GPIO_BASE 0xff000000
#define RK3399_GPIO_IOMUX_BASE 0xff320000
#define RK3399_GPIO0_BASE 0xff720000
#define RK3399_GPIO1_BASE 0xff730000
#define RK3399_GPIO0_CONF_BASE 0xff750000


static uint8_t* gpio_mmap_reg = NULL;
static uint8_t* gpio_iomux_mmap_reg = NULL;
static uint8_t* gpio0_mmap_reg = NULL;
static uint8_t* gpio0_con_reg = NULL;

int gpio_mmap_fd = 0;

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

int gpio_mmap(void)
{
	if ((gpio_mmap_fd = open(MMAP_PATH, O_RDWR)) < 0) {
		fprintf(stderr, "unable to open mmap file");
		return -1;
	}

	gpio_iomux_mmap_reg = (uint8_t*) mmap(NULL, 1024, PROT_READ | PROT_WRITE,
		MAP_FILE | MAP_SHARED, gpio_mmap_fd,RK3399_GPIO_IOMUX_BASE);
	if (gpio_iomux_mmap_reg == MAP_FAILED) {
		perror("foo1");
		fprintf(stderr, "failed to mmap");
		gpio_iomux_mmap_reg = NULL;
		close(gpio_mmap_fd);
		return -1;
	}


	gpio0_mmap_reg = (uint8_t*) mmap(NULL, 1024, PROT_READ | PROT_WRITE,
		MAP_FILE | MAP_SHARED, gpio_mmap_fd,RK3399_GPIO0_BASE);
	if (gpio0_mmap_reg == MAP_FAILED) {
		perror("foo2");
		fprintf(stderr, "failed to mmap");
		gpio0_mmap_reg = NULL;
		close(gpio_mmap_fd);
		return -1;
	}


	// gpio0_con_reg = (uint8_t*) mmap(NULL, 1024, PROT_READ | PROT_WRITE,
	// 	MAP_FILE | MAP_SHARED, gpio_mmap_fd,RK3399_GPIO0_CONF_BASE);
	// if (gpio0_con_reg == MAP_FAILED) {
	// 	perror("foo3");
	// 	fprintf(stderr, "failed to mmap");
	// 	gpio0_con_reg = NULL;
	// 	close(gpio_mmap_fd);
	// 	return -1;
	// }

	return 0;
}


int main()
{
   uint32_t con,iom,data,dirc;
   int i;
   gpio_mmap();

   // tmp = *(volatile uint32_t *)(gpio_iomux_mmap_reg + RK3399_GPIO_0B_IOMUX);

   // printf("the imux is %ud \n",tmp);
   // tmp |=  RK3399_PIN_4;
   //  con = *(volatile uint32_t *)(gpio0_con_reg + RK3399_GPIO0_CON1);
   //  printf("before the con is %0x \n",con);
   //  con  |= 0xffffffef;
   //  printf("after the con is %0x \n",con);

    iom = *(volatile uint32_t *)(gpio_iomux_mmap_reg + RK3399_GPIO_1B_IOMUX);
    printf("before the con is %0x \n",iom);
    *(volatile uint32_t *)(gpio_iomux_mmap_reg + RK3399_GPIO_1B_IOMUX) = 0x0000814a;
    iom = *(volatile uint32_t *)(gpio_iomux_mmap_reg + RK3399_GPIO_1B_IOMUX);
    printf("after the con is %0x \n",iom);


   // dirc = *(volatile uint32_t *)(gpio0_mmap_reg + RK3399_GPIO_DIRC);
   //  printf("before the dirc is %0x \n",dirc);
   //  dirc |= 0x00003100;
   //  printf("after the dirc is %0x \n",dirc);

   data = *(volatile uint32_t *)(gpio0_mmap_reg + RK3399_GPIO_DATA);
    printf("before the data is %0x \n",data);
   *(volatile uint32_t *)(gpio0_mmap_reg + RK3399_GPIO_DATA) = 0x00001604;
    data = *(volatile uint32_t *)(gpio0_mmap_reg + RK3399_GPIO_DATA);
    printf("before  A the data is %0x \n",data);
   
   delay_ms(800);
   printf("begine === \n");

   for(i=0;i<10;i++)
   {
   	 *(volatile uint32_t *)(gpio0_mmap_reg + RK3399_GPIO_DATA) = 0x00001604;
   	delay_ms(800);
   	 *(volatile uint32_t *)(gpio0_mmap_reg + RK3399_GPIO_DATA) =0x00000604;
   	delay_ms(800);
   }
    printf("end === \n");

	return 0;
}
#if 0

void rk3399_gpio_set_pin_direction(unsigned int pin, int is_output)
{
	uint32_t tmp;
	unsigned int pin_rel;

   if (pin <= 31)
   {
	    if(pin <= 7 )
	    {
	    	tmp = *(volatile uint32_t *)(gpio_mmap_reg + RK3399_GPIO_0A_IOMUX);
			if (is_output)
				tmp |=  (1u << pin);
			else
				tmp &= ~(1u << pin);
	    }
	    else if(pin <= 15)
	    {
	    	tmp = *(volatile uint32_t *)(gpio_mmap_reg + RK3399_GPIO_0B_IOMUX);
			if (is_output)
				tmp |=  (1u << pin);
			else
				tmp &= ~(1u << pin);
	    }
	    else if(pin <=31)
	    {
	    	printf("erro no the pin \n");
	    }
	   

	} else if(pin <= 63) {
		pin_rel = pin-32;

		 if(pin <= 7 )
	    {
	    	tmp = *(volatile uint32_t *)(gpio_mmap_reg + RK3399_GPIO_1A_IOMUX);
			if (is_output)
				tmp |=  (1u << pin);
			else
				tmp &= ~(1u << pin);
	    }
	    else if(pin <= 15)
	    {
	    	tmp = *(volatile uint32_t *)(gpio_mmap_reg + RK3399_GPIO_1B_IOMUX);
			if (is_output)
				tmp |=  (1u << pin);
			else
				tmp &= ~(1u << pin);
	    }
	    else if(pin <=31)
	    {
	    	printf("erro no the pin \n");
	    }

	}
     
    


	
	if (pin <= 31) {
        
        if(pin<)
		tmp = *(volatile uint32_t *)(gpio_mmap_reg + RK3399_GPIO_0B_IOMUX);
		if (is_output)
			tmp |=  (1u << pin);
		else
			tmp &= ~(1u << pin);
		*(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIODIR) = tmp;
	} else if (pin <= 63) {
		tmp = *(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO6332DIR);
		if (is_output)
			tmp |=  (1u << (pin-32));
		else
			tmp &= ~(1u << (pin-32));
		*(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO6332DIR) = tmp;
	} else if (pin <= 95) {
		tmp = *(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO9564DIR);
		if (is_output)
			tmp |=  (1u << (pin-64));
		else
			tmp &= ~(1u << (pin-64));
		*(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO9564DIR) = tmp;
	}
}

void mt76x8_gpio_set_pin_value(int pin, int value)
{
	uint32_t tmp;

	/* MT7621, MT7628 */
	if (pin <= 31) {
		tmp = (1u << pin);
		if (value)
			*(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIOSET) = tmp;
		else
			*(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIORESET) = tmp;
	} else if (pin <= 63) {
		tmp = (1u << (pin-32));
		if (value)
			*(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO6332SET) = tmp;
		else
			*(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO6332RESET) = tmp;
	} else if (pin <= 95) {
		tmp = (1u << (pin-64));
		if (value)
			*(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO9564SET) = tmp;
		else
			*(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO9564RESET) = tmp;
	}
}

int mt76x8_gpio_get_pin(int pin)
{
	uint32_t tmp = 0;

	/* MT7621, MT7628 */
	if (pin <= 31) {
		tmp = *(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIODATA);
		tmp = (tmp >> pin) & 1u;
	} else if (pin <= 63) {
		tmp = *(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO6332DATA);
		tmp = (tmp >> (pin-32)) & 1u;
	} else if (pin <= 95) {
		tmp = *(volatile uint32_t *)(gpio_mmap_reg + RALINK_REG_PIO9564DATA);
		tmp = (tmp >> (pin-64)) & 1u;
		tmp = (tmp >> (pin-24)) & 1u;
	}
	return tmp;

}
#endif