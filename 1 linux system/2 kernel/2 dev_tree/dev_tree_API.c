参考文档：
https://www.cnblogs.com/xiaojiang1025/archive/2017/02/06/6368260.html

#include <linux/of.h>
struct device_node {
      const char *name;   /* 节点名<name> */
      const char *type;   /* 设备类型 */
      phandle phandle;    /* lable标签的节点有该属性 pointer handle */
      const char *full_name; /* 节点路径名，<name>[@<unit_address>]是节点路径 */

      struct	property *properties;

      struct	device_node *parent;
      struct	device_node *child;
      struct	device_node *sibling;    /* 兄; 弟; 姐; 妹; */
}；

struct property {
	char	*name;
	int	length;
	void	*value;
	struct property *next;
	unsigned long _flags;
	unsigned int unique_id;
	struct bin_attribute attr;
};

1. 查找节点
/**
 * of_find_compatible_node - 通过compatible属性查找指定节点
 * @from - 指向开始路径的节点，如果为NULL，则从根节点开始
 * @type - device_type设备类型，可以为NULL
 * @compat - 指向节点的compatible属性的值（字符串）的首地址
 * 成功：得到节点的首地址；失败：NULL
 */
struct device_node *of_find_compatible_node(struct device_node *from,const char *type, const char *compat);

/**
 * of_find_matching_node - 通过compatible属性查找指定节点
 * @from - 指向开始路径的节点，如果为NULL，则从根节点开始
 * @matches - 指向设备ID表，注意ID表必须以NULL结束
 * 范例：  const struct of_device_id mydemo_of_match[] = {
                { .compatible = "fs4412,mydemo", },
                {}
            };
 * 成功：得到节点的首地址；失败：NULL
 */
struct device_node *of_find_matching_node(struct device_node *from,const struct of_device_id *matches);

2. 提取属性
/**
 * of_find_property - 提取指定属性的值
 * @np - 设备节点指针
 * @name - 属性名称
 * @lenp - 属性值的字节数
 * 成功：属性值的首地址；失败：NULL
 */
struct property *of_find_property(const struct device_node *np, const char *name, int *lenp);

/**
 * of_property_count_elems_of_size - 得到属性值中数据的数量
 * @np - 设备节点指针
 * @propname  - 属性名称
 * @elem_size - 每个数据的单位（字节数）
 * 成功：属性值的数据个数；失败：负数，绝对值是错误码
 */
int of_property_count_elems_of_size(const struct device_node *np,const char *propname, int elem_size);

/**
 * of_property_read_u32_index - 得到属性值中指定标号的32位数据值
 * @np - 设备节点指针
 * @propname  - 属性名称
 * @index  - 属性值中指定数据的标号
 * @out_value - 输出参数，得到指定数据的值
 * 成功：0；失败：负数，绝对值是错误码
 */
int of_property_read_u32_index(const struct device_node *np, const char *propname, u32 index, u32 *out_value);

/**
 * of_property_read_string - 提取字符串（属性值）
 * @np - 设备节点指针
 * @propname  - 属性名称
 * @out_string - 输出参数，指向字符串（属性值）
 * 成功：0；失败：负数，绝对值是错误码
 */
int of_property_read_string(struct device_node *np, const char *propname, const char **out_string);
3. 提取GPIO的属性
/**
 * include/of_gpio.h
 * of_get_named_gpio - 从设备树中提取gpio口
 * @np - 设备节点指针
 * @propname - 属性名
 * @index - gpio口引脚标号
 * 成功：得到GPIO口编号；失败：负数，绝对值是错误码
 */
int of_get_named_gpio(struct device_node *np, const char *propname, int index);
int of_get_gpio(struct device_node *np, int index);则需要定义一下gpios属性
例如：
gpios = <&banka 1 0     /* rdy */
          &banka 2 0 >
 plat->gpio_rdy = of_get_gpio(dev->of_node, 0);
4. 提取中断号
unsigned int irq_of_parse_and_map(struct device_node *dev, int index);
从interrupts属性解析出中断号。若设备使用了多个中断，index指定中断的索引号。
int gpio_to_irq(int gpio);  /* 从gpio号中获取该gpio口对应的外部中断 */

5. 内存映射
void __iomem *of_iomap(struct device_node *node, int index);
通过设备结点直接进行设备内存区间的 ioremap()，index是内存段的索引。
若设备结点的reg属性有多段，可通过index标示要ioremap的是哪一段，只有1段的情况，index为0。

6. 时钟
时钟和GPIO也是类似的，时钟控制器的节点被使用时钟的模块引用：
clocks = <&clks 138>, <&clks 140>, <&clks 141>;
clock-names = "uart", "general", "noc";
而驱动中则使用上述的clock-names属性作为clk_get（）或devm_clk_get（）的第二个参数来申请时钟，譬如获取第2个时钟：
devm_clk_get(&pdev->dev, "general");
<&clks 138>里的138这个index是与相应时钟驱动中clk的表的顺序对应的，很多开发者也认为这种数字出现在设备树中不太好，因此他们把clk的index作为宏定义到了arch/arm/boot/dts/include/dt-bindings/clock中。譬如include/dt-bindings/clock/imx6qdl-clock.h中存在这样的宏：
#define IMX6QDL_CLK_STEP                        16
#define IMX6QDL_CLK_PLL1_SW                  17
#define IMX6QDL_CLK_ARM                         104
