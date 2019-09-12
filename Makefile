# set CROSS_COMPILE
# build 4M SDK using uclibc: arm-buildroot-linux-uclibcgnueabi-
# build 8M SDK using glibc: arm-none-linux-gnueabi-
#CROSS_COMPILE = arm-buildroot-linux-uclibcgnueabi-
#CROSS_COMPILE = arm-none-linux-gnueabi-
#CROSS_COMPILE = arm-linux-
CROSS_COMPILE =
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
RM		= rm -rfv
CP		= cp -rfv
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

CFLAGS := -Wall -O2 -g
CFLAGS += -I $(shell pwd)/include

#LDFLAGS := -lm -lfreetype -lvga -lvgagl
LDFLAGS := 

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)
export TOPDIR

TARGET := read_file_picture_app

obj-y += main.o
obj-y += pa_debug/

all : 
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) built-in.o $(LDFLAGS) -o $(TARGET)

clean :
	$(RM) $(shell find -name "*.o")
	$(RM) $(TARGET)

distclean :
	$(RM) $(shell find -name "*.o")
	$(RM) $(shell find -name "*.d")
	$(RM) $(TARGET)
	
