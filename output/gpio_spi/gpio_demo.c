#include <linux/list.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/compat.h>
#include <linux/of.h>
#include <linux/of_device.h>


#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/property.h>
#include <linux/workqueue.h>
#include <linux/of_gpio.h>
#include <linux/delay.h>


#include <linux/miscdevice.h>

#include <linux/init.h>
#include <linux/fs.h>
// #include <mach/hardware.h>
// #include <mach/regs-gpio.h>

#include <linux/sched.h>
#include <linux/interrupt.h>//mark tgl

#define DEVICE_NAME   "gpio_demo"    //设备名称
// #define GPIOCONTROL_MAJOR   231              //主设备号
// #define IOCTL_CONTROL_HIGH  1          
// #define IOCTL_CONTROL_LOW   0    

#define GPIO_LOW 0
#define GPIO_HIGH 1

#define SPI_CLK 0
#define SPI_CS 1
#define SPI_SDI 2
#define SPI_SDO 3
#define SPI_RST 4
#define SPI_DC 5

static int gpio_pinx[6];

//static int count;


static long gpio_demo_ioctl( struct file *files, unsigned int cmd, unsigned long arg)
{

    long ret=0;
     // int ret;
    // printk("Hello gpio demo  and  cmd is %d,arg is %ld\n",cmd,arg);
     
      switch(cmd)
      {
          case 0:
            {
             
              if(arg)
                gpio_set_value(gpio_pinx[SPI_CLK],GPIO_HIGH);
              else
                gpio_set_value(gpio_pinx[SPI_CLK],GPIO_LOW);
            }              
              break;
          case 1:
          {
             if(arg)
                gpio_set_value(gpio_pinx[SPI_CS],GPIO_HIGH);
              else
                gpio_set_value(gpio_pinx[SPI_CS],GPIO_LOW);
          }
          break;
          case 2:
            {
             if(arg)
                gpio_set_value(gpio_pinx[SPI_SDI],GPIO_HIGH);
              else
                gpio_set_value(gpio_pinx[SPI_SDI],GPIO_LOW);
            }
           break;

           case 4:
            {
             if(arg)
                gpio_set_value(gpio_pinx[SPI_RST],GPIO_HIGH);
              else
                gpio_set_value(gpio_pinx[SPI_RST],GPIO_LOW);
            }
           break;

            case 5:
            {
             if(arg)
                gpio_set_value(gpio_pinx[SPI_DC],GPIO_HIGH);
              else
                gpio_set_value(gpio_pinx[SPI_DC],GPIO_LOW);
            }
           break;

          //  case 4:
          //  {
          //    if(arg)
          //       gpio_set_value(gpio_pinx[SPI_RST],GPIO_HIGH);
          //     else
          //       gpio_set_value(gpio_pinx[SPI_RST],GPIO_LOW);
          //   }
          //   break;   
          //       case 5:
          //  {
          //    if(arg)
          //       gpio_set_value(gpio_pinx[SPI_DC],GPIO_HIGH);
          //     else
          //       gpio_set_value(gpio_pinx[SPI_DC],GPIO_LOW);
          //   }
          //   break;       
  
          default:
              return -EINVAL;
      }
      
      return ret;
  }

  
  
static int gpio_demo_release(struct inode *inode, struct file *file)
{      
     printk("gpio demo release\n");
     return 0;
}
  
  
static int gpio_demo_open(struct inode *inode, struct file *file)
{      
     printk("gpio demo open\n");     
     return nonseekable_open(inode,file);
}

static struct file_operations gpio_demo_ops = 
{
    .owner = THIS_MODULE,
    .open = gpio_demo_open,
    .release = gpio_demo_release,
    .unlocked_ioctl = gpio_demo_ioctl,
 };


static  struct miscdevice gpio_demo_dev = 
{
     .minor = MISC_DYNAMIC_MINOR,
     .name = DEVICE_NAME,
     .fops = &gpio_demo_ops,
 };
/*
  static irqreturn_t firefly_gpio_irq_test(int irq, void *dev_id) //Interrupt function
 {
     printk("=============== tgl  Enter firefly gpio irq test program!=============\n");
     count++;
     gpio_set_value(gpio_pinx[GPIO_3_D0],(count/2==0?GPIO_LOW:GPIO_HIGH));
     return IRQ_HANDLED;
 }*/

static int gpio_demo_probe(struct platform_device *pdev)
{
	int ret/*,gpio_led,gpio_irq_test,gpio_irq_no,gpio_irq_1,gpio_irq_2,gpio_irq_3*/;
	enum of_gpio_flags flag;
	struct device_node *firefly_gpio_node = pdev->dev.of_node;
	printk(KERN_INFO "================\n GPIO TEST \n ================= \n Firefly GPIO Test Program Probe\n");
 //=====CLK
 
	gpio_pinx[SPI_CLK] = of_get_named_gpio_flags(firefly_gpio_node,"spi-clk-gpio",0,&flag);
	//gpio_led = gpio_pinx[GPIO_3_D0];
	if(!gpio_is_valid(gpio_pinx[SPI_CLK]))
	{
		 printk("firefly-led-gpio: %d is invalid\n", gpio_pinx[SPI_CLK]);
         return -ENODEV;
	}

	while(gpio_request(gpio_pinx[SPI_CLK],"spi-clk-gpio"))
	{
		  printk("gpio_led %d request failed!\n", gpio_pinx[SPI_CLK]);
          gpio_free(gpio_pinx[SPI_CLK]);
          return -ENODEV;
	}

	gpio_direction_output(gpio_pinx[SPI_CLK],GPIO_HIGH);
  
//=====CS

  gpio_pinx[SPI_CS] = of_get_named_gpio_flags(firefly_gpio_node,"spi-cs-gpio",0,&flag);
  //gpio_led = gpio_pinx[GPIO_3_D0];
  if(!gpio_is_valid(gpio_pinx[SPI_CS]))
  {
     printk("spi-cs-gpio: %d is invalid\n", gpio_pinx[SPI_CS]);
         return -ENODEV;
  }

  while(gpio_request(gpio_pinx[SPI_CS],"spi-cs-gpio"))
  {
      printk("spi-cs-gpio %d request failed!\n", gpio_pinx[SPI_CS]);
          gpio_free(gpio_pinx[SPI_CS]);
          return -ENODEV;
  }

  gpio_direction_output(gpio_pinx[SPI_CS],GPIO_HIGH);

  //======SDI
 
    gpio_pinx[SPI_SDI] = of_get_named_gpio_flags(firefly_gpio_node,"spi-tx-gpio",0,&flag);
  //gpio_led = gpio_pinx[GPIO_3_D0];
  if(!gpio_is_valid(gpio_pinx[SPI_SDI]))
  {
     printk("spi-tx-gpio: %d is invalid\n", gpio_pinx[SPI_SDI]);
         return -ENODEV;
  }

  while(gpio_request(gpio_pinx[SPI_SDI],"spi-tx-gpio"))
  {
      printk("spi-tx-gpio %d request failed!\n", gpio_pinx[SPI_SDI]);
          gpio_free(gpio_pinx[SPI_SDI]);
          return -ENODEV;
  }
  
  gpio_direction_output(gpio_pinx[SPI_SDI],GPIO_HIGH);
  
  //=====SDO 
  /*
   gpio_pinx[SPI_CLK] = of_get_named_gpio_flags(firefly_gpio_node,"spi-clk-gpio",0,&flag);
  //gpio_led = gpio_pinx[GPIO_3_D0];
  if(!gpio_is_valid(gpio_pinx[SPI_CLK]))
  {
     printk("spi-clk-gpio: %d is invalid\n", gpio_pinx[SPI_CLK]);
         return -ENODEV;
  }

  while(gpio_request(gpio_pinx[SPI_CLK],"spi-clk-gpio"))
  {
      printk("spi-clk-gpio %d request failed!\n", gpio_pinx[SPI_CLK]);
          gpio_free(gpio_pinx[SPI_CLK]);
          return -ENODEV;
  }

  gpio_direction_output(gpio_pinx[SPI_CLK],GPIO_HIGH);
 */
 //=====RST
   gpio_pinx[SPI_RST] = of_get_named_gpio_flags(firefly_gpio_node,"spi-rst-gpio",0,&flag);
  //gpio_led = gpio_pinx[GPIO_3_D0];
  if(!gpio_is_valid(gpio_pinx[SPI_RST]))
  {
     printk("spi-rst-gpio: %d is invalid\n", gpio_pinx[SPI_RST]);
         return -ENODEV;
  }

  while(gpio_request(gpio_pinx[SPI_RST],"spi-rst-gpio"))
  {
      printk("spi-rst-gpio %d request failed!\n", gpio_pinx[SPI_RST]);
          gpio_free(gpio_pinx[SPI_RST]);
          return -ENODEV;
  }

  gpio_direction_output(gpio_pinx[SPI_RST],GPIO_HIGH);

  //=====DC
  
  gpio_pinx[SPI_DC] = of_get_named_gpio_flags(firefly_gpio_node,"spi-dc-gpio",0,&flag);
  //gpio_led = gpio_pinx[GPIO_3_D0];
  if(!gpio_is_valid(gpio_pinx[SPI_DC]))
  {
     printk("spi-dc-gpio: %d is invalid\n", gpio_pinx[SPI_DC]);
         return -ENODEV;
  }

  while(gpio_request(gpio_pinx[SPI_DC],"spi-dc-gpio"))
  {
      printk("spi-dc-gpio %d request failed!\n", gpio_pinx[SPI_DC]);
          gpio_free(gpio_pinx[SPI_DC]);
          return -ENODEV;
  }

  gpio_direction_output(gpio_pinx[SPI_DC],GPIO_HIGH);
  
	  //=============irq gpio=====
  /*  
    gpio_pinx[GPIO_3_D1] = of_get_named_gpio_flags(firefly_gpio_node,"firefly-irq-gpio",0,&flag);
    gpio_irq_test = gpio_pinx[GPIO_3_D1];
    if(!gpio_is_valid(gpio_irq_test))
   {
       printk("firefly-irq-gpio: %d is invalid\n", gpio_irq_test);
       return -ENODEV;
   }
  
    gpio_irq_no = gpio_to_irq(gpio_irq_test);

     if (gpio_irq_no)
    {
        if (gpio_request(gpio_irq_test, "firefly-irq-gpio"))   //NOTE HERE dts  tgl
       {
             printk("gpio %d request failed!\n", gpio_irq_test);
             gpio_free(gpio_irq_test);
             return IRQ_NONE;
       }
       ret = request_irq(gpio_irq_no, firefly_gpio_irq_test,
                 flag, "firefly,rk3399-gpio", NULL);
       if (ret != 0)
        {
           free_irq(gpio_irq_no, NULL);

           dev_err(&pdev->dev, "Failed to request IRQ: %d\n", ret);
         }
     }
  */
    //irp-1
  /*
    gpio_pinx[GPIO_3_D3] = of_get_named_gpio_flags(firefly_gpio_node,"firefly-irq1-gpio",0,&flag);
    gpio_irq_1 = gpio_pinx[GPIO_3_D3];
    if(!gpio_is_valid(gpio_irq_1))
   {
       printk("firefly-irq1-gpio: %d is invalid\n", gpio_irq_1);
       return -ENODEV;
   }
  
    gpio_irq_no = gpio_to_irq(gpio_irq_1);

     if (gpio_irq_no)
    {
        if (gpio_request(gpio_irq_1, "firefly-irq1-gpio"))   //NOTE HERE dts  tgl
       {
             printk("gpio %d request failed!\n", gpio_irq_1);
             gpio_free(gpio_irq_1);
             return IRQ_NONE;
       }
       ret = request_irq(gpio_irq_no, firefly_gpio_irq_test,
                 flag, "firefly,rk3399-gpio-1", NULL);
       if (ret != 0)
        {
           free_irq(gpio_irq_no, NULL);

           dev_err(&pdev->dev, "Failed to request IRQ: %d\n", ret);
         }
     }
    */
     //irq2
     /*
    gpio_pinx[GPIO_3_D6] = of_get_named_gpio_flags(firefly_gpio_node,"firefly-irq2-gpio",0,&flag);
    gpio_irq_2 = gpio_pinx[GPIO_3_D6];
    if(!gpio_is_valid(gpio_irq_2))
   {
       printk("firefly-irq2-gpio: %d is invalid\n", gpio_irq_2);
       return -ENODEV;
   }
  
    gpio_irq_no = gpio_to_irq(gpio_irq_2);

     if (gpio_irq_no)
    {
        if (gpio_request(gpio_irq_2, "firefly-irq2-gpio"))   //NOTE HERE dts  tgl
       {
             printk("gpio %d request failed!\n", gpio_irq_2);
             gpio_free(gpio_irq_2);
             return IRQ_NONE;
       }
       ret = request_irq(gpio_irq_no, firefly_gpio_irq_test,
                 flag, "firefly,rk3399-gpio-2", NULL);
       if (ret != 0)
        {
           free_irq(gpio_irq_no, NULL);

           dev_err(&pdev->dev, "Failed to request IRQ: %d\n", ret);
         }
     }

*/
     //irq-3
     /*
    gpio_pinx[GPIO_3_D4] = of_get_named_gpio_flags(firefly_gpio_node,"firefly-irq3-gpio",0,&flag);
    gpio_irq_3 = gpio_pinx[GPIO_3_D4];
    if(!gpio_is_valid(gpio_irq_2))
   {
       printk("firefly-irq3-gpio: %d is invalid\n", gpio_irq_3);
       return -ENODEV;
   }
  
    gpio_irq_no = gpio_to_irq(gpio_irq_3);

     if (gpio_irq_no)
    {
        if (gpio_request(gpio_irq_3, "firefly-irq3-gpio"))   //NOTE HERE dts  tgl
       {
             printk("gpio %d request failed!\n", gpio_irq_3);
             gpio_free(gpio_irq_3);
             return IRQ_NONE;
       }
       ret = request_irq(gpio_irq_no, firefly_gpio_irq_test,
                 flag, "firefly,rk3399-gpio-3", NULL);
       if (ret != 0)
        {
           free_irq(gpio_irq_no, NULL);

           dev_err(&pdev->dev, "Failed to request IRQ: %d\n", ret);
         }
     }
     */
      //========= regiester device =====

  printk("\n ======== tgl =======  end\n");

  ret = misc_register(&gpio_demo_dev);
  if(ret<0)
  {
      printk("gpio_demo:register device failed!\n");
      goto exit;
  }

    return 0;
 
 exit:
     misc_deregister(&gpio_demo_dev);  
     printk("%s-%d: exit\n",__FUNCTION__,__LINE__);
     return ret;
}


static int gpio_demo_remove(struct platform_device *pdv)
{
   printk("gpio_demo_remove...\n");    
   misc_deregister(&gpio_demo_dev);
   return 0;
}


#ifdef CONFIG_OF
static const struct of_device_id of_gpio_demo_match[] = {
  { .compatible = "firefly,rk3399-gpio" },

};
#endif

static struct platform_driver firefly_gpio_demo_driver = 
{
    .probe    = gpio_demo_probe,
    .remove   = gpio_demo_remove,
    .driver   = {
    .name = "gpio_demo_driver",   //????
    .owner  = THIS_MODULE,
    .of_match_table = of_gpio_demo_match,
  },

};

static int __init gpio_demo_init(void)
{
	int ret;
	ret = platform_driver_register(&firefly_gpio_demo_driver);
	printk(KERN_INFO "Info %d\n",ret);
	return 0;
}

static void  __exit gpio_demo_exit(void)
{
	platform_driver_unregister(&firefly_gpio_demo_driver);
}


module_init(gpio_demo_init);
module_exit(gpio_demo_exit);

MODULE_AUTHOR("wuQAQ");
MODULE_DESCRIPTION("Firefly gpio driver");
MODULE_LICENSE("GPL");