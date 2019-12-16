1. 统一设备模型：kobj、kset分析
http://www.wowotech.net/device_model/421.html
2. 浅析/sys/class目录的创建流程
http://blog.chinaunix.net/uid-30091091-id-5783251.html
3. linux设备驱动模型之Kobject、kobj_type、kset
https://www.cnblogs.com/zzb-Dream-90Time/p/7250096.html

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

kobject_create_and_add(); /* 函数内部会分配kobj结构体，其余和 kobject_init_and_add一样*/

2) kset的添加
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
