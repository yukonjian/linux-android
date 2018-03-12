1.内核模块编译 Makefile
ARCH := arm
CROSS_COMPILE := /home/steven/work/lichee/out/sun8iw11p1/androidm/common/buildroot/external-toolchain/bin/arm-linux-gnueabi-
KERN_DIR = /home/steven/work/lichee/linux-3.10

all:
	make -C $(KERN_DIR) M=`pwd` ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)  modules

clean:
	make -C $(KERN_DIR) M=`pwd` ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules clean

obj-m	+= sunxi_wdt.o

2.测试应用编译 build_app.sh
#!/bin/bash
arm-linux-androideabi-gcc -pie -fPIE -o wdt_test wdt_test.c
chmod 777 ./wdt_test
