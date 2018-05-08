1.查看文件夹的大小
du -h --max-depth=1 ./
-h 表示加，K,M,G
--max-depth 表示查看的深度
2.shell脚本
 #！/bin/sh
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
