1. 获得设备结点
1) 根据compatible属性
struct device_node *of_find_compatible_node(struct device_node *from,
         const char *type, const char *compatible);
遍历Device Tree中所有的设备结点，看看哪个结点的类型、compatible属性与本函数的输入参数匹配，
大多数情况下，from、type为NULL。

2) 根据name
1.1 static inline struct device_node *of_find_node_by_name(struct device_node *from,
	const char *name)

2. 读取设备结点np的属性名为property name，类型为32位整型数组的属性。
int of_property_read_u32_array(const struct device_node *np,
                      const char *propname, u32 *out_values, size_t sz);

static inline int of_property_read_u32(const struct device_node *np,
                                       const char *propname, u32 *out_value)

3. 读取字符串和指定的字符串
int of_property_read_string(struct device_node *np, const char
                            *propname, const char **out_string);

int of_property_read_string_index(struct device_node *np, const char
                                  *propname, int index, const char **output);

4. 内存映射
void __iomem *of_iomap(struct device_node *node, int index);
通过设备结点直接进行设备内存区间的 ioremap()，index是内存段的索引。
若设备结点的reg属性有多段，可通过index标示要ioremap的是哪一段，只有1段的情况，index为0。

5. 中断的解析和映射
unsigned int irq_of_parse_and_map(struct device_node *dev, int index);
从interrupts属性解析出中断号。若设备使用了多个中断，index指定中断的索引号。

6. 读取gpio number
static inline int of_get_named_gpio(struct device_node *np,const char *propname, int index);
6.1 static inline int of_get_gpio(struct device_node *np, int index);则需要定义一下gpios属性；
例如：
gpios = <&banka 1 0     /* rdy */
          &banka 2 0 >
 plat->gpio_rdy = of_get_gpio(dev->of_node, 0);

7. 时钟
时钟和GPIO也是类似的，时钟控制器的节点被使用时钟的模块引用：
clocks = <&clks 138>, <&clks 140>, <&clks 141>;
clock-names = "uart", "general", "noc";
而驱动中则使用上述的clock-names属性作为clk_get（）或devm_clk_get（）的第二个参数来申请时钟，譬如获取第2个时钟：
devm_clk_get(&pdev->dev, "general");
<&clks 138>里的138这个index是与相应时钟驱动中clk的表的顺序对应的，很多开发者也认为这种数字出现在设备树中不太好，因此他们把clk的index作为宏定义到了arch/arm/boot/dts/include/dt-bindings/clock中。譬如include/dt-bindings/clock/imx6qdl-clock.h中存在这样的宏：
#define IMX6QDL_CLK_STEP                        16
#define IMX6QDL_CLK_PLL1_SW                  17
#define IMX6QDL_CLK_ARM                         104
