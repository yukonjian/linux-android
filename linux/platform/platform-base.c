1.平台相关的结构
struct platform_device {
	const char * name; //设备的名字，这将代替device->dev_id，用作sys/device下显示的目录名
	int id; //设备id，用于给插入给该总线并且具有相同name的设备编号，如果只有一个设备的话填-1。
	struct device dev; //结构体中内嵌的device结构体。
	u32 num_resources; //资源数。
	struct resource * resource; //用于存放资源的数组。
  const struct platform_device_id	*id_entry;
};

/*
 * Resources are tree-like, allowing
 * nesting etc..
 */
struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	unsigned long flags;
	struct resource *parent, *sibling, *child;
};

struct platform_device_id {
	char name[PLATFORM_NAME_SIZE];
	kernel_ulong_t driver_data;
};

struct platform_driver {
	int (*probe)(struct platform_device *);
	int (*remove)(struct platform_device *);
	void (*shutdown)(struct platform_device *);
	int (*suspend)(struct platform_device *, pm_message_t state);
	int (*resume)(struct platform_device *);
	struct device_driver driver;
	const struct platform_device_id *id_table;
};

2.平台设备的注册和注销
int platform_device_register(struct platform_device *pdev) //同样的，需要判断返回值
int platform_driver_register(struct platform_driver *drv)

void platform_device_unregister(struct platform_device *pdev)
void platform_driver_unregister(struct platform_driver *drv)

3.资源resource的定义和使用
sample：
static struct resource snirm_82596_rsrc[] = {
	{
		.start = 0x1ff00000,
		.end   = 0x1ff00020,
		.flags = IORESOURCE_MEM
	},
	{
		.start = 22,
		.end   = 22,
		.flags = IORESOURCE_IRQ
	},
};

static struct platform_device snirm_82596_pdev = {
	.name		= "snirm_82596",
  .id             = -1,
	.num_resources	= ARRAY_SIZE(snirm_82596_rsrc),
	.resource	= snirm_82596_rsrc
};

4.设备树在平台设备中的使用
struct of_device_id
{
	char	name[32];
	char	type[32];
	char	compatible[128];
	const void *data;
};

struct device_driver {
  const struct of_device_id	*of_match_table;
};
struct device {
  struct device_node	*of_node;
  void		*platform_data;	 /* Platform specific data, device core doesn't touch it */
};
sample:
static const struct of_device_id sunxi_disp_match[] = {
	{ .compatible = "allwinner,sun8iw10p1-disp", },
	{ .compatible = "allwinner,sun50i-disp", },
	{},
};

static struct platform_driver disp_driver = {
	.probe    = disp_probe,
	.remove   = disp_remove,
	.shutdown = disp_shutdown,
	.driver   =
	{
		.name   = "disp",
		.owner  = THIS_MODULE,
		.pm	= &disp_runtime_pm_ops,
		.of_match_table = sunxi_disp_match,
	},
};

5.设备相关的文件位置
/sys/devices/platform/
/sys/bus/platform/devices/
/sys/bus/platform/drivers/
