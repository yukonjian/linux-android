sys 文件系统的使用
#include <linux/device.h>
#include <linux/sysfs.h>
1 设备文件的创建
1.1设备文件的创建
1.1.1定义设备文件的读写函数
 ssize_t xxx_show(struct device *d, struct device_attribute*attr, char *buf) //对应read
 ssize_t xxx_store(struct device *d, struct device_attribute*attr,const char *buf,size_t count)  //对应write
1.2 创建设备属性结构体
2.2.1 设备属性结构体
struct device_attribute {
	struct attribute	attr;
	ssize_t (*show)(struct device *dev, struct device_attribute *attr,
			char *buf);
	ssize_t (*store)(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);
};
1.2.2 设备属性结构体的定义
 static DEVICE_ATTR(xxxtest, S_IWUSR |S_IRUGO, xxx_show, xxx_store);
#define DEVICE_ATTR(_name, _mode, _show, _store) \
	struct device_attribute dev_attr_##_name = __ATTR(_name, _mode, _show, _store)
#define __ATTR(_name,_mode,_show,_store) { 				\
.attr = {.name = __stringify(_name), .mode = _mode },		\
.show	= _show,						\
.store	= _store,						\
}
1.3 设备文件的创建
1.3.1 使用device文件接口
int device_create_file(struct device *device, const struct device_attribute *entry);
1.3.2 使用sys文件创建通用接口
sysfs_create_file(&pdev->dev.kobj,&dev_attr_xxxtest);
1.4 设备文件的移除
void device_remove_file(struct device *device, const struct device_attribute *entry);

2 sys文件系统目录和文件的创建
2.1 创建sys文件目录
struct kobject *  kobject_create_and_add(const char *name, struct kobject *parent);
name是目录名
parent是父节点的指针
/sys目录的kobject是NULL;平台目录的kobject是platform_bus
2.2 创建文件
int sysfs_create_file(struct kobject *kobj, const struct attribute *attr);
2.3 卸载驱动时删除文件
void sysfs_remove_file(struct kobject *kobj, const struct attribute *attr);
2.4 卸载驱动时释放kobject
void kobject_put(struct kobject *kobj)
注：创建文件时，若直接定义一个struct attribute attr，然后使用该attr创建文件是无法通过cat,echo访问的,因为没有show和store函数。
必须和struct device_attribute 类似的定义才行；然后调用sysfs_create_file才能有访问函数；
也可以使用DEVICE_ATTR直接定义属性文件。
如：
struct test_attribute {
	struct attribute	attr;
	ssize_t (*show)(struct attribute *dev，	char *buf);
	ssize_t (*store)(struct attribute *dev,  const char *buf, size_t count);
};
#define test_ATTR(_name, _mode, _show, _store) \
  struct test_attribute dev_attr_##_name = __ATTR(_name, _mode, _show, _store)

3 一组设备文件的创建
3.1 创建属性结构体
 static DEVICE_ATTR(xxxtest, S_IWUSR |S_IRUGO, xxx_show, xxx_store);
 static DEVICE_ATTR(xxxset, S_IWUSR |S_IRUGO, xxx_show, xxx_store);
3.2 创建属性指针数组
static struct attribute *xxx_attrs[] = {
     &dev_attr_xxxtest.attr,
     &dev_attr_xxxset.attr,
     NULL
};
3.3 创建属性组结构体
static const struct attribute_group xxx_attr_grp = {
     .attrs = xxx_attrs,
};
3.4 创建一组设备文件
sysfs_create_group(&pdev->dev.kobj,&xxx_attr_grp);
3.5 卸载驱动时，注销一组设备文件
sysfs_remove_group(&pdev->dev.kobj,&xxx_attr_grp);
