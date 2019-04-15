1. Ubuntu安装SSH SERVER
apt-get update
apt-get install openssh-server
查看ssh是否启动：ps -e |grep ssh

2. ubuntu内核路径
/usr/src/linux-headers-3.11.0-15
2.1 内核源码树路径
/lib/modules/3.11.0-15-generic/build/
3. ubuntu内核版本查看
uname -r

4. ubuntu版本
cat /etc/issue

5. ubuntu系统中linux源码下载
5.1 该条命令等于5.2和5.2.1的两条命令
apt-get install linux-source
5.2 执行用这条命令系统会提示你安装适合你内核版本的内核源码
apt-cache search linux-source
linux-source - Linux kernel source with Ubuntu patches
linux-source-3.13.0 - Linux kernel source for version 3.13.0 with Ubuntu patches
5.2.1 下载源码
sudo apt-get install linux-source-3.13.0
5.3 拷贝/boot目录下的config-2.6.35-30-generic到刚才解压好的目录下并改名为.config



6. 在ubuntu中进行模块编译时遇到的问题
root@misterlanbing-virtual-machine:/home/root/linux/char-base# make
make -C /usr/src/linux-source-3.2.0/linux-source-3.2.0 M=`pwd`  modules
make[1]: 正在进入目录 `/usr/src/linux-source-3.2.0/linux-source-3.2.0'

  ERROR: Kernel configuration is invalid.
         include/generated/autoconf.h or include/config/auto.conf are missing.
         Run 'make oldconfig && make prepare' on kernel src to fix it.


  WARNING: Symbol version dump /usr/src/linux-source-3.2.0/linux-source-3.2.0/Module.symvers
           is missing; modules will have no dependencies and modversions.

  CC [M]  /home/root/linux/char-base/char-base.o
In file included from <命令行>:0:0:
/usr/src/linux-source-3.2.0/linux-source-3.2.0/include/linux/kconfig.h:4:32: 致命错误： generated/autoconf.h：没有那个文件或目录
编译中断。
make[2]: *** [/home/root/linux/char-base/char-base.o] 错误 1
make[1]: *** [_module_/home/root/linux/char-base] 错误 2
make[1]:正在离开目录 `/usr/src/linux-source-3.2.0/linux-source-3.2.0'
make: *** [all] 错误 2
root@misterlanbing-virtual-machine:/home/root/linux/char-base#

7. Linux源码树
内核的模块要和内核源代码树中的目标文件连接，通过这种方式，可得到一个更加健壮的模块加载器，但是需要这些目标文件存在于内核目录树中”。
这里提到的内核目录树就是我们在运行我们自己构造的模块前，需要在我们的系统中已经配置好内核源代码树，
然后在把构造好的目标模块和内核树连接起来再运行。
简单的讲：就是已经配置并编译过的内核源码。

8. uubuntu12.04静态ip设置
/etc/network/interface
auto lo
iface lo inet loopback

auto eth0
iface eth0 inet static
address 192.168.1.47
netmask 255.255.255.0
gateway 192.168.1.1

然后修改DNS
/etc/resolv.conf 
nameserver 8.8.8.8

重启网络连接
/etc/init.d/networking restart
ifconfig 察看网络配置信息
