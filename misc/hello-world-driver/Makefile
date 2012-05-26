

EXTRA_CFLAGS=-Wall

KVERSION=$(shell uname -r)

MOD_DIR=/lib/modules/$(shell uname -r)/build

obj-m += helloworld.o

all:
	make -C $(MOD_DIR) M=$(PWD) modules

clean:
	make -C $(MOD_DIR) M=$(PWD) clean

