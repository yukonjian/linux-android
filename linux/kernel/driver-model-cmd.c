1. 查看注册的驱动
 cat /proc/devices

2. 生成设备节点
mknod 设备文件名 设备的类型（c,b） 主设备号 次设备号
mknod /dev/mmcblk0 c 233 0
