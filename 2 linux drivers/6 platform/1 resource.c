1. 平台资源
struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	unsigned long flags;
	struct resource *parent, *sibling, *child;
};
结构体重主要的参数为三个，start、end、flags
start：资源的起始值
end：资源的终止值
flags：资源类型
IORESOURCE_IO	GPIO范围	起始GPIO号	终止GPIO号
IORESOURCE_MEM	内存	内存起始地址	内存终止地址
IORESOURCE_IRQ	中断	起始中断号	终止中断号

2. 平台资源的获取
struct resource * platform_get_resource(struct platform_device *dev, unsigned int type, unsigned int num)；
dev: platform device
type: resource type
num: resource index
return: 获取到资源返回资源指针；未获取到资源返回NULL
platform_get_resource(pdev, IORESOURCE_MEM, 0);
platform_get_resource(pdev, IORESOURCE_IRQ, 0);
