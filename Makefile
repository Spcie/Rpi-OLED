ifneq ($(KERNELRELEASE),)

obj-m := OLED_Dev.o
OLED_Dev-objs :=hw_gpio.o hw_i2c.o hw_delay.o oled.o oled_dev.o soft_i2c.o

else


KDIR := /lib/modules/4.9.44-v7+/build

all:
	make -C $(KDIR) M=$(shell pwd) modules
clean:
	rm -f *.ko *.o *.mod.o *mod.c *.symvers *.order

endif
