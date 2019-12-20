1. 统一设备模型：kobj、kset分析
http://www.wowotech.net/device_model/421.html
2. 浅析/sys/class目录的创建流程
http://blog.chinaunix.net/uid-30091091-id-5783251.html
3. linux设备驱动模型之Kobject、kobj_type、kset
https://www.cnblogs.com/zzb-Dream-90Time/p/7250096.html
4. 设备模型的uevent机制
https://www.cnblogs.com/black-mamba/p/5055683.html
5. Netlink机制详解
https://blog.csdn.net/xinyuan510214/article/details/52635085?utm_source=blogxgwz0

1. kobj代表一个目录
1) kobj的添加
kobject_init_and_add();
  kobject_init();
    kobject_init_internal();
    kobj->ktype = ktype;
  kobject_add();
    kobject_set_name_vargs();
    kobj->parent = parent;
    kobject_add_internal();   /* 若kset存在且没有设置parent；则使用kset的kobj作为parent */
      create_dir();


static struct kobj_type dynamic_kobj_ktype = {
	.release	= dynamic_kobj_release,
	.sysfs_ops	= &kobj_sysfs_ops,
};
kobject_create_and_add(); /* 函数内部会分配kobj结构体，其余和 kobject_init_and_add一样*/
  kobject_init(kobj, &dynamic_kobj_ktype);  /* 使用了dynamic_kobj_ktype */

2) kset的添加；kset包含有kobj,并添加了uevent操作；kset=kobj+uevent;
static struct kobj_type kset_ktype = {
	.sysfs_ops	= &kobj_sysfs_ops,
	.release = kset_release,
};
kset_create_and_add();
  kset_create();
    kobject_set_name();
    kset->uevent_ops = uevent_ops;
    kset->kobj.parent = parent_kobj;
    kset->kobj.ktype = &kset_ktype;
    kset->kobj.kset = NULL;   /* 指定为空，只能使用parent_kobj */
  kset_register();
    kobject_init_internal();
    kobject_add_internal();
    kobject_uevent(&k->kobj, KOBJ_ADD); /* 发送kobj添加事件 */
      kobject_uevent_env();

2. 属性文件的创建
static inline int __must_check sysfs_create_file(struct kobject *kobj, const struct attribute *attr)
