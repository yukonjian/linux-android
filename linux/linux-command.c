1.查看文件夹的大小,计算每个文件的磁盘用量，目录则取总用量。
du -h --max-depth=1 ./
-h 表示加，K,M,G
--max-depth 表示查看的深度
2.shell脚本
 #!/bin/sh
3.linux中copy软链接
 cp命令copy一个软链接时，copy的是软链接所对应的内容，而不是它本身。
# echo "1234567890" > test.txt
# ln -s test.txt test2.txt
# cp test2.txt test3.txt
test3.txt就是test.txt，而不是test2.txt 。

要直接cp软链就需要加-d参数
如：
# cp -d test2.txt test3.txt
4.linux之间的文件拷贝
scp -r /tmp/tempA/ wasadmin@10.127.40.25:/tmp/wang/

5.linux模块的编译
make modules  //编译所有模块文件
make modules_install INSTALL_MOD_PATH=/home/ubuntu/WorkSpace/qemu-rootfs  //最终在qemu-rootfs下生成目录lib/modules：

6.模块的操作
insmod xxx.ko
rmmod xxx.ko
remod xxx.ko

7.打包解压命令
tar:
打包解压 .tar 文件
解包：tar xvf FileName.tar
打包：tar cvf FileName.tar DirName
打包解压 .tar.gz和.tgz 文件
解压：tar xzvf FileName.tar.gz
压缩：tar czvf FileName.tar.gz DirName
打包解压 .tar.bz2 文件
解压：tar xjvf FileName.tar.bz2
压缩：tar cjvf FileName.tar.bz2 DirName
打包解压 .zip 文件
解压：unzip FileName.zip
压缩：zip FileName.zip DirName

8. scp secure copy的缩写,基于ssh登陆进行安全的远程文件拷贝命令
scp [参数] [原路径] [目标路径]
(2) 复制目录：
命令格式：
scp -r local_folder remote_username@remote_ip:remote_folder
或者
scp -r local_folder remote_ip:remote_folder

第1个指定了用户名，命令执行后需要输入用户密码；
第2个没有指定用户名，命令执行后需要输入用户名和密码；

9. MAC地址修改方法
ifconfig eth0 down
ifconfig eth0 hw ether 52:54:00:66:66:66   #设置eth0的MAC地址
ifconfig eth0 up

ethernet 以太网

10.启动脚本 rc.local
11. openwrt加载模块
模块路径：/lib/modules/
添加路径：/etc/modules.d/

11. dd 命令
dd：用指定大小的块拷贝一个文件，并在拷贝的同时进行指定的转换。
注意：指定数字的地方（ibs,obs,bs,count）若以下列字符结尾，则乘以相应的数字：b=512；c=1；k=1024；w=2
参数注释：
1) if=文件名：输入文件名，缺省为标准输入。即指定源文件。< if=input file >
2) of=文件名：输出文件名，缺省为标准输出。即指定目的文件。< of=output file >
3) ibs=bytes：一次读入bytes个字节，即指定一个块大小为bytes个字节。
    obs=bytes：一次输出bytes个字节，即指定一个块大小为bytes个字节。
    bs=bytes：同时设置读入/输出的块大小为bytes个字节。
4) cbs=bytes：一次转换bytes个字节，即指定转换缓冲区大小。
5) skip=blocks：从输入文件开头跳过blocks个块后再开始复制。
6) seek=blocks：从输出文件开头跳过blocks个块后再开始复制。
注意：通常只用当输出文件是磁盘或磁带时才有效，即备份到磁盘或磁带时才有效。
7) count=blocks：仅拷贝blocks个块，块大小等于ibs指定的字节数。
8) conv=conversion：用指定的参数转换文件。
dd 应用实例
1) 将文件file1.c 的内容全部拷贝到 file.c
dd if=./file1.c of=./file.c
dd if=/dev/hdb of=/dev/hdd
2) 指定大小的拷贝，大小为 bs*count
dd if=file1.c of=file2.c bs=3w count=1
3) 测试硬盘的读写速度
dd if=/dev/zero bs=1024 count=1000000 of=/root/1Gb.file
dd if=/root/1Gb.file bs=64k | dd of=/dev/null

/dev/null，外号叫无底洞，你可以向它输出任何数据，它通吃，并且不会撑着！
/dev/zero，是一个输入设备，你可你用它来初始化文件。该设备无穷尽地提供0，
可以使用任何你需要的数目——设备提供的要多的多。他可以用于向设备或文件写入字符串0。

12. find命令，只查找文件，需要添加 -type f
find . -type f

13. mount 挂载nfs
1）安装NFS服务
sudo apt-get install nfs-kernel-server
sudo apt-get install nfs-common
sudo apt-get install portmap
2）建立共享目录
在/etc/exports 文件的末尾添加需要共享的文件夹 如：
/home/steven/work/mount *(rw,sync,no_root_squash)
3）挂载
将虚拟机中的mount目录挂载到app目录
mount -t nfs -o nolock 172.25.2.89:/home/steven/work/mount   /mnt/work
# 挂接sys文件系统
mount -t sysfs /sys /sys
# 挂接proc文件系统
mount -t proc /proc /proc
/home/steven/work/lichee/buildroot/target/dragonboard/output/bin *(rw,sync,no_root_squash)

14. app 映像文件的生成
/work/openwrt-sdk/staging_dir/host/bin/mksquashfs4 /work/mkimage/app /work/mkimage/app.squashfs -nopad -noappend -root-owned -comp xz -Xpreset 9 -Xe -Xlc 0 -Xlp 2 -Xpb 2  -b 256k -processors 1

15. 在使用busybox制作根文件系统需要支持mdev，并且在rcS中有以下语句
echo /sbin/mdev > /proc/sys/kernel/hotplug
/sbin/mdev -s
才能在加载驱动时，自动生成节点

16. tail -f messages | grep "seg dma"

17. lzma

18. uname -a //查看虚拟机 Linux的版本信息

19. lsb_release -a  //查看ubuntu的版本信息

20. kill 和 killall
kill是Linux下常见的命令。其man手册的功能定义如下：
kill – send a signal to a process
明朗了，其实kill就是给某个进程id发送了一个信号。默认发送的信号是SIGTERM，而kill -9发送的信号是SIGKILL，即exit。exit信号不会被系统阻塞，所以kill -9能顺利杀掉进程。
当然你也可以使用kill发送其他信号给进程。
经常使用的killall呢？
killall – kill processes by name
即，通过指定进程名的方式杀死进程。

21. 修改文件的时间
修改时间为：2015年10月13
d 使用指定的日期时间，而非现在的时间。
touch -d “10/13/2013” *.sh

22. 递归删除某一个文件夹
find . -name .svn -exec rm -rf {} \;

23.
# find ./ -exec rm {} \;
# find ./ | xargs rm -rf
两者都可以把find命令查找到的结果删除，其区别简单的说是前者是把find发现的结果一次性传给exec选项，这样当文件数量较多的时候，就可能会出现“参数太多”之类的错误，相比较而言，
后者就可以避免这个错误，因为xargs命令会分批次的处理结果。这样看来，“find ./| xargs rm -rf”是更通用的方法，推荐使用！
rm不接受标准输入，所以不能用find / -name "*.txt" ｜rm

-exec 必须由一个 ; 结束，而因为通常 shell 都会对 ; 进行处理，所以用 \; 防止这种情况。
{} 可能需要写做 '{}'，也是为了避免被 shell 过滤

find ./ -type f -exec grep txt {} /dev/null \;
./表示从当前目录找
-type f，表示只找file，文件类型的，目录和其他字节啥的不要
-exec 把find到的文件名作为参数传递给后面的命令行，代替{}的部分
-exec后便跟的命令行，必须用“ \;”结束

# find ./ -type f -name "*.txt"|xargs grep "test" -n
# find . -name "*.txt" -exec grep "test" {} \; -print

23. telnet 中去掉 用户名和密码
telnetd -l /bin/sh &

24. 改变文件属主
chown -R steven ./

25. 显示每个文件所在的文件系统的信息，默认是显示所有文件系统。
df -T

26. 查看工具链的库和头文件搜索路径
echo 'main(){}'| mipsel-openwrt-linux-gcc -E -v -
