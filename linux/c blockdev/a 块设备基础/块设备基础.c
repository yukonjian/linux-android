Linux块设备总结（二）
https://blog.csdn.net/weixin_37867857/article/details/88322091
QEMU+GDB调试Linux内核总结（全）
https://blog.csdn.net/weixin_37867857/article/details/88205130

一、块设备框架
字符设备和设备交互的过程是以字节为单位的，块设备和设备交互的过程是以数据块为单位的。
块设备文件是带有缓存特性的，最小化减少对硬盘的数据交互次数是我们块设备文件系统的设计初衷。
