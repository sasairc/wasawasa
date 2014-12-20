obj-m	:= wasawasa.o
clean-files := *.o *.ko *.mod.[co] *.symvers *.order

TARGET	:= wasawasa.ko
PREFIX	:= /lib/modules/$(shell uname -r)/kernel/drivers/block
KERNDIR	:= /lib/modules/$(shell uname -r)/build
BUILDIR	:= $(shell pwd)
EXTRA_CFLAGS +=
MAKE	:= make
CC		:= cc
RM		:= rm

.PHONY:	all
all: $(TARGET)

wasawasa.ko: wasawasa.c
	$(MAKE) -C $(KERNDIR) SUBDIRS=$(BUILDIR) modules

install:
	cp -v wasawasa.ko $(PREFIX)/wasawasa.ko
	mknod /dev/wasawasa c 254 0
	chmod 0666 /dev/wasawasa

mknod:
	mknod /dev/wasawasa c 254 0
	chmod 0666 /dev/wasawasa

rmnod:
	-$(RM) -f /dev/wasawasa

uninstall:
	-$(RM) -f $(PREFIX)/wasawasa.ko
	-$(RM) -f /dev/wasawasa

clean:
	-$(RM) -f $(obj-m) $(clean-files)
