obj-m	:= wasawasa.o
clean-files := *.o *.ko *.mod.[co] *.symvers *.order

PREFIX	:= /lib/modules/$(shell uname -r)/kernel/drivers/block
KERNDIR	:= /lib/modules/$(shell uname -r)/build
BUILDIR	:= $(shell pwd)
CC		:= cc
RM		:= rm

.PHONY:	all
all:
	$(MAKE) -C $(KERNDIR) SUBDIRS=$(BUILDIR) modules

install:
	cp -v wasawasa.ko $(PREFIX)/wasawasa.ko
	mknod /dev/wasawasa c 254 0
	chmod 0666 /dev/wasawasa

uninstall:
	-$(RM) -f $(PREFIX)/wasawasa.ko
	-$(RM) -f /dev/wasawasa

clean:
	-$(RM) -f $(obj-m) $(clean-files)

clean_all:
	-$(RM) -f $(obj-m) $(clean-files-all)
