1.在编译时将函数都静态编译到程序中
arm-none-linux-gnueabi-gcc -static -o hello hello.c
在android中使用NDK提供的android工具链，添加-pie -fPIE，非静态编译也可以运行。
arm-linux-androideabi-gcc -pie -fPIE -o helloa hello.c

2.重新挂载目录
mount -o remount /

3.dmesg打印
dmesg | tail -20      //打印最后20行
dmesg --help          //查看帮助信息

4. android 编译
1)  m mm mmm 的使用
m      /* 相当于make编译整个项目 */
mm    /* 编译当前目录下的模块，使用 mm -B 可以清楚并编译当前模块 */
mmm   /* 编译指定目录下的模块 */

2) make 和 make clean
make <target name>      /* 编译指定模块 */
make clean-<target name> /* 清楚指定模块 */
/* 在android的根目录下运行 make和make clean将编译和清楚整个项目 */

5. system.img 打包
make snod

6. boot.img 打包
make bootimage
