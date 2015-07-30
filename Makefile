#
#    Makefile for wasawasa
#

obj-m	= wasawasa.o
TARGET	= wasawasa.ko
PREFIX	:= /lib/modules/$(shell uname -r)/kernel/drivers/block
KERNDIR	:= /lib/modules/$(shell uname -r)/build
BUILDIR	:= $(shell pwd)
MAKE	:= make
CC	:= cc
RM	:= rm

all: $(TARGET)

$(TARGET): $(TARGET:.ko=.c)
	$(MAKE) -C $(KERNDIR) SUBDIRS=$(BUILDIR) modules

install: install-module mknod

install-module: $(TARGET)
	cp  wasawasa.ko $(PREFIX)/wasawasa.ko

mknod:
	mknod /dev/wasawasa c 254 0
	chmod 0666 /dev/wasawasa

uninstall: uninstall-module rmnod

uninstall-module:
	-$(RM) -f $(PREFIX)/wasawasa.ko

rmnod:
	-$(RM) -f /dev/wasawasa

clean:
	-$(RM) -f *.o *.ko *.mod.[co] *.symvers *.order

.PHONY:	all install install-module mknod uninstall uninstall-module rmnod clean
