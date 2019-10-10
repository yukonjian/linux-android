1. 总线
1.1 总线的结构体
struct bus_type {
	const char		*name;         //总线的名字，会在/sys/bus下生成一个目录
	struct bus_attribute	*bus_attrs;

	int (*match)(struct device *dev, struct device_driver *drv);
	int (*uevent)(struct device *dev, struct kobj_uevent_env *env);
	int (*probe)(struct device *dev);
};

1.2 总线的注册和注销
1.2.1 定义总线结构体
struct bus_type test_bus = {
  .name = "test_bus",           /* 会在/sys/bus下生成一个test_bus的总线目录 */
};
1.2.2 注册总线
int bus_register(struct bus_type *bus);
1.2.3 总线的注销
int bus_register(struct bus_type *bus);

2. 设备
2.1 设备结构体
struct device {
	struct device		*parent;    //指定该设备的父设备，如果不指定(NULL)，注册后的设备目录在sys/device下
	struct device_private	*p;

  const char		*init_name; /* initial name of the device */
	struct bus_type	*bus;		/* type of bus device is on */
	struct device_driver *driver;	/* which driver has allocated this device */

  struct device_node	*of_node; /* associated device tree node */

	void	(*release)(struct device *dev);  //当给设备的最后一个引用被删除时，调用该函数
};
2.2 设备的注册和注销
2.2.1 定义设备结构体
struct device test_device = {
  .init_name = "test_device",
  .bus = &test_bus,    //指定该设备的总线，这样会在sys/bus/test_bus/device目录下有一个软连接
  .release = test_dev_release,  //必须要有release函数，不然卸载时会出错
};
2.2.2 设备的注册
int device_register(struct device *device);
2.2.3 设备的注销
void device_unregister(struct device *device);

3 驱动
3.1 驱动结构体
struct device_driver {
	const char		*name;   //驱动函数的名字，在对应总线的driver目录下显示
	struct bus_type		*bus;   //指定该驱动程序所操作的总线类型，必须设置，不然会注册失败
	const struct of_device_id	*of_match_table; //platform没有用，用了其自己的struct of_device_id 匹配表

	int (*probe) (struct device *dev);
	int (*remove) (struct device *dev);

	struct driver_private *p;
};
3.2 驱动的注册和注销
struct device_driver test_driver = {
  .name = "test_driver",
  .bus = &test_bus,
};
3.2.1 驱动的注册
int driver_register(struct device_driver *driver);
3.2.2 驱动的注销
void driver_unregister(struct device_driver *driver);
