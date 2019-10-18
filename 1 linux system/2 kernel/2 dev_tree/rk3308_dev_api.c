driver/of/base.c
include/of/of.h

struct property {
	char	*name;
	int	length;      /* 计算value中数据的长度，以字节为单位 */
	void	*value;
	struct property *next;
	unsigned long _flags;
	unsigned int unique_id;
	struct bin_attribute attr;
};
/* 查找设备节点中的属性 */
struct property *of_find_property(const struct device_node *np,
				  const char *name,
				  int *lenp)

/**
* phandle_name:包含phandle的属性名；
* index:属性名下的第几个phandle;
* 如：ports = <&vop_out>; phandle_name为prots; index=0，指示&vop_out；
* 使用完返完获得的 np 后，需要使用of_node_put()释放引用；
* 如：port = of_parse_phandle(np, "ports", i);  ...;  of_node_put(port);
*/
struct device_node *of_parse_phandle(const struct device_node *np,
				     const char *phandle_name, int index)




port = of_parse_phandle(np, "ports", index);
__of_parse_phandle_with_args(np, "ports", NULL, 0, index, &args)

list = of_get_property(np, "ports", &size);

struct property *pp = of_find_property(np, "ports", lenp);
