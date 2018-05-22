1.内核模块编译 Makefile
ARCH := arm
CROSS_COMPILE := /home/steven/work/lichee/out/sun8iw11p1/androidm/common/buildroot/external-toolchain/bin/arm-linux-gnueabi-
KERN_DIR = /home/steven/work/lichee/linux-3.10

all:
	make -C $(KERN_DIR) M=`pwd` ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)  modules

clean:
	make -C $(KERN_DIR) M=`pwd` ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules clean

obj-m	+= sunxi_wdt.o

2.测试应用的编译 makefile
CC=/home/steven/work/mt7628-1/openwrt-sdk/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-gcc

OBJS=pcm_api.o  pcm_func_7628.o test.o

all:pcm_test

pcm_test: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f pcm_test *.o

$@--目标文件，$^--所有的依赖文件，$<--第一个依赖文件。

3.测试应用编译shell的写法 build_app.sh
#!/bin/bash
arm-linux-androideabi-gcc -pie -fPIE -o wdt_test wdt_test.c
chmod 777 ./wdt_test
