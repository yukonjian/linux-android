busybox的编译、使用及安装
busybox是什么？

     （1）busybox是Linux上的一个应用程序(application)，即只有一个ELF文件头。

     （2）它整合了许多Linux上常用的工具和命令（utilities)， 如rm, ls, gzip, tftp等。对于这些工具和命令，busybox中的实现可能不是最全的，但却是最常用的，因此它的特点就是短小精悍，特别适合对尺寸很敏感的嵌入式系统。

     （3）busybox的官方网站是http://www.busybox.net/，在这里你可以找到与busybox相关的所有资料。

busybox编译和移植

     busybox 的编译与Linux内核的编译过程类似。从http://www.busybox.net/downloads/ 下载最新的源码，解压后，通过以下几步，即可完成busybox的编译和移植：

    （1）make xxxxxxconfig

         busybox提供了几种配置：defconfig (缺省配置)、allyesconfig（最大配置）、 allnoconfig（最小配置），一般选择缺省配置即可。

          这一步结束后，将生成.config

      (2)make menuconfig

         这一步是可选的，当你认为上述配置中还有不尽如意的地方，可以通过这一步进行微调，加入或去除某些命令。

         这一步实际上是修改.config

      （3）make CROSS_COMPILE=arm-linux-

          这一步就是根据.config，生成busybox，当然你也可以指定其他的编译器， 如arm-linux-gnueabi-。（"make CROSS_COMPILE="将用gcc编译PC机上运行的busybox.

busybox的使用

    busybox的使用很简单，有以下三种方式：

    （1） busybox后直接跟命令，如

          busybox ls

          busybox tftp

     (2)  直接将busybox重命名，如

          cp busybox tftp

          cp busybox tar

          然后再执行tftp, tar

     （3）创建符号链接（symbolic link）， 如

          ln -s busybox rm

          ln -s busybox mount

          然后就可以执行rm，mount等

busybox的安装

      以上三种方法中，第三种方法是最简洁最方便的，可是如果手工为busybox中每个命令都创建一个软链接，那是相当的费事。为此，busybox提供了一种自动方法：

      在busybox编译成功后，接着执行“make install”,则会产生一个_install目录，其中包含了busybox及每个命令的软链接。以后只要将这个目录拷贝到目标平台上就可以了。
