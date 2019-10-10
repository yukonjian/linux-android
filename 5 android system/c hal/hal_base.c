1.HAL 主要存储目录
libhardware_legacy/ - 旧的架构、采取链接库模块的观念进行
libhardware/ - 新架构、调整为 HAL stub 的观念
2.HAL层涉及的三个关键结构体
struct hw_module_t;
struct hw_module_methods_t;
struct hw_device_t;
3.文件目录
androidm/hardware/libhardware/include/hardware  //modules 头文件
androidm/hardware/libhardware/modules           //modules 的c文件
4.模块ID
 #define LED_HARDWARE_MODULE_ID "led"  //定义一个MODULE_ID，HAL层可以根据这个ID找到我们这个HAL stub
Android HAL 实例——mokoid LEDTest
http://www.xuebuyuan.com/2215354.html
http://www.doc88.com/p-4999901968727.html
5.JNI层
目录：androidm/frameworks/base/services/core/jni
6.HAL
Hardware Stub 运行在用户空间，直接操作设备文件，对上提供操作接口。
本层生成一个so文件，作为Android HAL 层的Stub。
按照Android HAL 的要求，此文件必须放在固定的目录下面，并且具有特定的文件名。
一般放在hw/<OVERLAY_HARDWARE_MODULE_ID>.<ro.product.board>.so
在本例中:#define LED_HARDWARE_MODULE_ID "led"
生成在：system/lib/hw/led.default.so
