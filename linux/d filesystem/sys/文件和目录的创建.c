sys 文件系统的使用
一. 文件的创建
1.设备文件的创建
1)定义文件的读写函数
 ssize_t xxx_show(struct device *d, struct device_attribute*attr, char *buf) //对应read
 ssize_t xxx_store(struct device *d, struct device_attribute*attr,const char *buf,size_t count)  //对应write
2)创建属性结构体
#define DEVICE_ATTR(_name, _mode, _show, _store) \
 struct device_attribute dev_attr_##_name = __ATTR(_name, _mode, _show, _store)
 这是一个宏定义,将定义一个 dev_attr_xxxtest,类型为struct device_attribute的结构体。
 xxxtest为要创建的sys文件名
 读写函数若不使用，可以带入NULL参数
3)调用sysfs_create_file创建文件
 sysfs_create_file(&pdev->dev.kobj,&dev_attr_xxxtest);
4)卸载驱动时，可以注销文件
 sysfs_remove_file(&pdev->dev.kobj,&dev_attr_xxxtest);

2.一组设备文件的创建
1)定义文件的读写函数
2)创建属性结构体
 static DEVICE_ATTR(xxxtest, S_IWUSR |S_IRUGO, xxx_show, xxx_store);
 static DEVICE_ATTR(xxxset, S_IWUSR |S_IRUGO, xxx_show, xxx_store);
3)创建属性指针数组
 static struct attribute *xxx_attrs[] = {
       &dev_attr_xxxtest.attr,
       &dev_attr_xxxset.attr,
       NULL
 };
4)创建属性组结构体
 static const struct attribute_group xxx_attr_grp = {
       .attrs = xxx_attrs,
 }  ;
5)创建一组设备文件
 sysfs_create_group(&pdev->dev.kobj,&xxx_attr_grp);
6)卸载驱动时，注销一组设备文件
 sysfs_remove_group(&pdev->dev.kobj,&xxx_attr_grp);

3.再指定目录下创建sys文件
 1)创建sys文件目录
 struct kobject *  kobject_create_and_add(const char *name, struct kobject *parent);
 name是目录名
 parent是父节点的指针
 /sys目录的kobject是NULL;平台目录的kobject是platform_bus
 2)创建文件
 int sysfs_create_file(struct kobject *kobj, const struct attribute *attr);
 3)卸载驱动时删除文件
 void sysfs_remove_file(struct kobject *kobj, const struct attribute *attr);
 4)卸载驱动时释放kobject
void kobject_put(struct kobject *kobj)
