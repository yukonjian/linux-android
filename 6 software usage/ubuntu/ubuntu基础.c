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

9. 应用编译
1）查看configure的参数
./configure --help
Defaults for the options are specified in brackets.
Configuration:
  -h, --help              display this help and exit
      --help=short        display options specific to this package
      --help=recursive    display the short help of all the included packages
  -V, --version           display version information and exit
  -q, --quiet, --silent   do not print `checking...' messages
      --cache-file=FILE   cache test results in FILE [disabled]
  -C, --config-cache      alias for `--cache-file=config.cache'
  -n, --no-create         do not create output files
      --srcdir=DIR        find the sources in DIR [configure dir or `..']
Installation directories:
  --prefix=PREFIX         install architecture-independent files in PREFIX
                          [/usr/local]
  --exec-prefix=EPREFIX   install architecture-dependent files in EPREFIX
                          [PREFIX]
下载：http://sourceforge.net/projects/iperf
1. 先把iperf-2.0.4.tar.gz解压到你的目录下。
2. cd iperf-2.0.4
3. ./configure --host=arm  CXX=arm-uclinux-g++ CC=arm-uclinux-gcc
   这里的arm-uclinux -改成你自己的交叉编译器的前缀。
4. make
5. 如果make通不过的话就到 config.h 中把 #define malloc rpl_malloc 注释掉。
6. make
7. 这时候会生成一个iperf的文件。
8. 把这个文件copy到你的board上去。

如果在板子上无法执行，可能是没有执行权限或者是编译选项不对，可参考相应开发环境修改编译选项。
2) Usage
perf是client端向server端发送数据;
server端显示的是发送速率，最好加i参数，进行速率跟踪
client 显示的是发送速率,server 显示接收速率

udp :server:./iperf -s -u -P 0 -i 1 -p 5001
     client:./iperf -u -c 172.25.2.85 -P 1 -i 1 -p 5001 -n 500M -b 10M -l 1300

-s :server模式启动;
-c :client模式启动
172.16.52.6 :服务器的地址
-u :使用udp协议
-p :指定服务器端使用的端口或客户端所连接的端口
-i :秒为单位显示报告间隔
-P :number of parallel client threads to run
-b :指定发送带宽，默认是1Mbit/s
-t :测试时间，默认10秒
-n :number of bytes to transmit (instead of -t)
-l :length of buffer to read or write (default 8 KB)

./iperf -s  -P 0 -i 1 -p 5001
./iperf -c 172.25.2.86 -P 1 -i 1 -p 5001 -n 500M -b 20M -l 1300

3) iperf交叉编译
1. 先把iperf-2.0.4.tar.gz解压到你的目录下。
2. cd iperf-2.0.4
3. ./configure --host=arm  CXX=arm-uclinux-g++ CC=arm-uclinux-gcc
   这里的arm-uclinux -改成你自己的交叉编译器的前缀。
4. make
5. 如果make通不过的话就到 config.h 中把 #define malloc rpl_malloc 注释掉。
6. make
7. 这时候会生成一个iperf的文件。
8. 把这个文件copy到你的board上去。

如果在板子上无法执行，可能是没有执行权限或者是编译选项不对，可参考相应开发环境修改编译选项。

10. ubuntu 源存放路径/etc/apt/sources.list
