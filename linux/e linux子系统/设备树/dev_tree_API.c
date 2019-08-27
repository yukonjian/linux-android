参考文档：
https://www.cnblogs.com/xiaojiang1025/archive/2017/02/06/6368260.html

#include <linux/of.h>
struct device_node {
      const char *name;   /* 节点名 */
      const char *type;   /* 设备类型 */
      phandle phandle;    /* lable标签的节点有该属性 */
      const char *full_name; /* 全路径节点名 */
}；

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

4. 提取中断号
/**
 * of_irq_get - 从设备树中提取中断号
 * @np - 设备节点指针
 * @index - 要提取的中断号的标号
 * 成功：中断号；失败：负数，其绝对值是错误码
int of_irq_get(struct device_node *dev, int index);
