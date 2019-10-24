platform虚拟总线
#include <linux/platform_device.h>

1. flatform总线
1.1 platform总线结构体
struct bus_type platform_bus_type = {
	.name		= "platform",
	.match		= platform_match,
	.uevent		= platform_uevent,
};
1.2 platform_match函数
static int platform_match(struct device *dev, struct device_driver *drv)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct platform_driver *pdrv = to_platform_driver(drv);

	/* Attempt an OF style match first */
	if (of_driver_match_device(dev, drv))
		return 1;

	/* Then try to match against the id table */
	if (pdrv->id_table)
		return platform_match_id(pdrv->id_table, pdev) != NULL;

	/* fall-back to driver name match */
	return (strcmp(pdev->name, drv->name) == 0);
}
1.3 platform的设备
struct device platform_bus = {
	.init_name	= "platform",
};
在初平台总线初始化的时候调用了device_register(&platform_bus)，会在设备下生成一个platform的文件夹。
是所有平台设备的父设备。

2. platform设备
2.1 平台设备的结构体（内嵌struct device）
struct platform_device {
	const char	*name;    /* 设备名字，会覆盖，struct device内的init_name */
	int		id;  //设备id，用于给插入给该总线并且具有相同name的设备编号，如果只有一个设备的话填-1。
	struct device	dev;
	u32		num_resources;
	struct resource	*resource;
	const struct platform_device_id	*id_entry; //保存匹配上的platform_device_id
};
2.2 平台设备的注册函数
int platform_device_register(struct platform_device *pdev)
{
  return platform_device_add(pdev);
}
指定bus类型为struct bus_type platform_bus_type，devices的父设备为struct device platform_bus
若存在设备id，则dev.init_name为：name.id
2.3 平台设备的注销函数
void platform_device_unregister(struct platform_device *pdev)；

3. platform驱动
3.1 平台驱动结构体(内嵌struct device_driver)
struct platform_driver {
	int (*probe)(struct platform_device *);
	int (*remove)(struct platform_device *);
	struct device_driver driver;   //驱动的名字在driver中指定
	const struct platform_device_id *id_table;
};
3.1.1 platform_device_id的使用
struct platform_device_id {
	char name[PLATFORM_NAME_SIZE];
	kernel_ulong_t driver_data;
};
sample：
static struct platform_device_id ad7606_driver_ids[] = {
	{
		.name		= "test_match",
		.driver_data	= ID_AD7606_8,
	},
	{ }
};
3.1.2 struct device_driver中的struct of_device_id	*of_match_table的使用
struct of_device_id
{
	char	name[32];
	char	type[32];
	char	compatible[128];
	const void *data;
};
当name,type,compatible存在，会依次进行匹配；
compatible是在最后一次的匹配，故以compatible匹配较好
sample：
static const struct of_device_id ab8500_charger_match[] = {
	{ .compatible = "stericsson,ab8500-charger", },
	{ },
};

3.2 平台驱动的注册函数
int platform_driver_register(struct platform_driver *drv)；
指定bus类型为struct bus_type platform_bus_type，
3.3 平台驱动的注销函数
void platform_driver_unregister(struct platform_driver *drv)；
