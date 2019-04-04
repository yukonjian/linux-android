1. sysfs文件系统的目录结构
block: 存放指向/sys/device目录下的块设备(以文件夹表示)的链接文件
lrwxrwxrwx    1         0 mtdblock5 -> ../devices/platform/spi-pnx8181/spi1.17/mtd/mtd5/mtdblock5
bus:用于管理总线，每注册一条总线，在该目录下有一个对应的子目录。
bus/devices:包含系统中所有属于该总线的的设备。(链接文件，指向/sys/device)
bus/drivers:包含系统中所有属于该总线的的驱动。(包含驱动名的文件夹，文件夹下有匹配的指向设备的链接文件)
class:将系统中的设备按功能分类。(是一些指向设备的链接文件)
device:该目录提供了系统中设备拓扑结构图。
dev:已注册的设备的视图。(也是一些连接文件)
