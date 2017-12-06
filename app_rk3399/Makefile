# 
# AUTHOR: tgl
# DATE: 2017-09-26
# 

CROSS_COMPILE = aarch64-rockchip-linux-gnu-

AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
CC  = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++ 
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm

STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

CFLAGS := -Wall -O2 -g
CFLAGS += -I./sys  -I./oled -I./gpio -I./display  -I./spi -I./gui -I./key -I./thread -I./

LDFLAGS := -lpthread -lm -lrt -ldl

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)
export TOPDIR

TARGET := oled_main


obj-y += main.o
obj-y += sys/
obj-y += spi/
obj-y += oled/
obj-y += gpio/
obj-y += display/
obj-y += gui/
obj-y += key/
obj-y += thread/



all : 
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CPP) $(LDFLAGS) -o $(TARGET) built-in.o 


clean:
	rm -f $(shell find . -name "*.o")
	rm -f $(TARGET)

distclean:
	rm -f $(shell find . -name "*.o")
	rm -f $(shell find . -name "*.d")
	rm -f $(TARGET)
	
.PHONY: upload	
upload:
	scp $(TARGET) root@192.168.0.118:/root/project/