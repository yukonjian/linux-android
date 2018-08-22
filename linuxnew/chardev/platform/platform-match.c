1. 匹配函数源码
文件路径：/drivers/base/platform.c
static int platform_match(struct device *dev, struct device_driver *drv)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct platform_driver *pdrv = to_platform_driver(drv);

	/* Attempt an OF style match first */
	if (of_driver_match_device(dev, drv))
		return 1;

	/* Then try ACPI style match */
	if (acpi_driver_match_device(dev, drv))
		return 1;

	/* Then try to match against the id table */
	if (pdrv->id_table)
		return platform_match_id(pdrv->id_table, pdev) != NULL;

	/* fall-back to driver name match */
	return (strcmp(pdev->name, drv->name) == 0);
}

2. 设备树的匹配
static inline int of_driver_match_device(struct device *dev,
					 const struct device_driver *drv)
of_driver_match_device(dev, drv)
    ----of_match_device(drv->of_match_table, dev)
        ----of_match_node(matches, dev->of_node);
struct device_node	*of_node; /* associated device tree node */

/*
 * Struct used for matching a device
 */
struct of_device_id
{
	char	name[32];
	char	type[32];
	char	compatible[128];
	const void *data;
};
会在设备数中依次匹配of_device_id的name,type,compatible.

3. 平台设备id号的匹配
static const struct platform_device_id *platform_match_id(
			const struct platform_device_id *id,struct platform_device *pdev)
platform_match_id(pdrv->id_table, pdev)
    ----struct platform_device *pdev)
        ----strcmp(pdev->name, id->name)

struct platform_device_id {
	char name[PLATFORM_NAME_SIZE];
	kernel_ulong_t driver_data;
};
平台设备专有的匹配，匹配struct platform_device_id的name,这样一个驱动可以匹配多个设备名字。

4. 设备名和驱动名的匹配
strcmp(pdev->name, drv->name)

example :
2.
static struct of_device_id mal_platform_match[] =
{
	{
		.compatible	= "ibm,mcmal",
	},
	{
		.compatible	= "ibm,mcmal2",
	},
	{},
};

static struct platform_driver mal_of_driver = {
	.driver = {
		.name = "mcmal",
		.owner = THIS_MODULE,
		.of_match_table = mal_platform_match,
	},
	.probe = mal_probe,
	.remove = mal_remove,
};

3.
static struct platform_device_id ad7606_driver_ids[] = {
	{
		.name		= "ad7606-8",
		.driver_data	= ID_AD7606_8,
	},
  {
		.name		= "ad7606-6",
		.driver_data	= ID_AD7606_6,
	},
	{ },
};
static struct platform_driver ad7606_driver = {
	.probe = ad7606_par_probe,
	.remove	= ad7606_par_remove,
	.id_table = ad7606_driver_ids,
	.driver = {
		.name	 = "ad7606",
		.owner	= THIS_MODULE,
		.pm    = AD7606_PAR_PM_OPS,
	},
};
4. drv->name = drv->driver->name ;