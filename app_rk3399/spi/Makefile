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
CFLAGS += -I $(shell pwd) -I./ -I../

LDFLAGS := -lm -lrt -ldl

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)
export TOPDIR


obj-y += rk3399_spi.o


all : 
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) $(LDFLAGS) -o built-in.o


clean:
	rm -f $(shell find -name "*.o")

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	