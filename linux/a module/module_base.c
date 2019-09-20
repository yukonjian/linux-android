1. 内核传參
module_param(name, type, perm)
name：内核参数的名称，自己定义
type：内核参数的类型，常见的类型byte、short、int、long、ulong、bool 、charp(字符指针)
perm：内核参数的权限S_I(R/W/X)UGO(/sys/module/xxx/parameter/xxxparam读写权限)
注：读--4 ； 写--2 ； 执行--1 ；00700 ；是用8进制表示的

带入： insmod xxx.ko name=xxx ;
查看： /sys/module/xxx/parameter/xxxparam
sample:
static int param = 1;
module_param(param,int, 00700);

2. 设备节点的创建
mknod path c/b major minor
mknod /dev/led c 45 0

3. 内核间的函数调用
1） 把需要调用的函数编译进模块，与C语言的静态库类似。
Makefile ：
obj-m += test_haha.o //生成test_haha.ko
test_haha-objs += haha.o test.o //test_haha.ko有haha.o和test.o组成
注：xxx-objs 和 xxx-y 功能一样，在多文件生成一个模块时用
2） 把被调用的函数导出到符号表，方便模块使用，与C语言的动态库类似
查看： /proc/kallsyms
将函数编译为模块并使用EXPORT_SYMBOL(fun_name)导出符号;
编译的模块不一定需要init和exit函数。

4. 模块的加载顺序
#define early_initcall(fn)		module_init(fn)
#define core_initcall(fn)		module_init(fn)
#define core_initcall_sync(fn)		module_init(fn)
#define postcore_initcall(fn)		module_init(fn)
#define postcore_initcall_sync(fn)	module_init(fn)
#define arch_initcall(fn)		module_init(fn)
#define subsys_initcall(fn)		module_init(fn)
#define subsys_initcall_sync(fn)	module_init(fn)
#define fs_initcall(fn)			module_init(fn)
#define fs_initcall_sync(fn)		module_init(fn)
#define rootfs_initcall(fn)		module_init(fn)
#define device_initcall(fn)		module_init(fn)
#define device_initcall_sync(fn)	module_init(fn)
#define late_initcall(fn)		module_init(fn)
#define late_initcall_sync(fn)		module_init(fn)

#define console_initcall(fn)		module_init(fn)
#define security_initcall(fn)		module_init(fn)
