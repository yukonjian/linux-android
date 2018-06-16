1.查看文件夹的大小
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
cp -r /tmp/tempA/ wasadmin@10.127.40.25:/tmp/wang/

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

ifconfig br-lan up
ifconfig br-lan hw ether 00:0C:43:28:81:AB
ifconfig br-lan up

ifconfig eth0 down
ifconfig eth0 hw ether 00:0C:43:28:82:AB
ifconfig eth0 up

ifconfig eth0.1 down
ifconfig eth0.1 hw ether 00:0C:43:28:83:AB
ifconfig eth0.1 up

ifconfig eth0.2 down
ifconfig eth0.2 hw ether 00:0C:43:28:84:AB
ifconfig eth0.2 up



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
mount -t nfs -o nolock 172.25.2.89:/home/steven/work/mount   /app

14. app 映像文件的生成
/work/openwrt-sdk/staging_dir/host/bin/mksquashfs4 /work/mkimage/app /work/mkimage/app.squashfs -nopad -noappend -root-owned -comp xz -Xpreset 9 -Xe -Xlc 0 -Xlp 2 -Xpb 2  -b 256k -processors 1

15. 在使用busybox制作根文件系统需要支持mdev，并且在rcS中有以下语句
echo /sbin/mdev > /proc/sys/kernel/hotplug
/sbin/mdev -s
才能在加载驱动时，自动生成节点
