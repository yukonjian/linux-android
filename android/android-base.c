1.adb 操作
推送文件
adb push <local> <remote>
adb push E:\room\simple.ko	/system
adb push E:\room\simple		/system 			//推送文件夹里的所有文件
adb pull <remote> <local>
adb pull /system/simple/simple.ko		E:\room\simple
adb pull /system/simple		E:\room\simple	//推送文件夹里的所有文件

2.在编译时将函数都静态编译到程序中
arm-none-linux-gnueabi-gcc -static -o hello hello.c
在android中使用NDK提供的android工具链，添加-pie -fPIE，非静态编译也可以运行。
arm-linux-androideabi-gcc -pie -fPIE -o helloa hello.c
arm-linux-androideabi-gcc -pie -fPIE -o ov9732app ov9732_app.c
arm-linux-androideabi-gcc -pie -fPIE -o getbuffer getbuffer.c
