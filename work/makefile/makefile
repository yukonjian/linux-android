1. c72 android
驱动：
ARCH := arm
CROSS_COMPILE :=/home/steven/work/lichee/out/sun8iw11p1/androidm/common/buildroot/external-toolchain/bin/arm-linux-gnueabi-
KERN_DIR = /home/steven/work/lichee/linux-3.10
app:
arm-linux-androideabi-gcc -pie -fPIE -o wdt_test wdt_test.c  //其需要添加-pie -fPIE选项

2. c72 dragonboard
驱动：
ARCH := arm
CROSS_COMPILE := /home/steven/work/lichee/out/sun8iw11p1/androidm/common/buildroot/external-toolchain/bin/arm-linux-gnueabi-
KERN_DIR = /home/steven/work/lichee/linux-3.10
app:
CC=/home/steven/work/lichee/out/sun8iw11p1/androidm/common/buildroot/external-toolchain/bin/arm-linux-gnueabi-gcc

3. c62b
驱动:
ARCH := mips
CROSS_COMPILE := /opt/buildroot-gcc463/usr/bin/mipsel-buildroot-linux-uclibc-
KERN_DIR = /home/steven/work/MTK_APSoC_SDK/source/linux-3.10.14.x
app:
CC=/opt/buildroot-gcc463/usr/bin/mipsel-buildroot-linux-uclibc-gcc

4. c62
ARCH := arm
CROSS_COMPILE := /opt/emlix/pnx8181/bin/arm-linux-gnueabi-
KERN_DIR = /home/steven/work/project/xm_c62/src/emb/DVFD8181x/kernel/src/linux

all:
	make -C $(KERN_DIR) M=`pwd` ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)  modules

clean:
	make -C $(KERN_DIR) M=`pwd` ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules clean

obj-m	+= drvtest.o
