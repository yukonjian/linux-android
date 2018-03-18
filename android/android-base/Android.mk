一.Android.mk 语法
首先看一个最简单的Android.mk的例子：
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := hello-jni
LOCAL_SRC_FILES := hello-jni.c
include $(BUILD_SHARED_LIBRARY)

1.	LOCAL_PATH := $(call my-dir)
每个Android.mk文件必须以定义LOCAL_PATH为开始。它用于在开发tree中查找源文件。
宏my-dir 则由Build System提供。返回包含Android.mk的目录路径。
返回的是最近一次include的Makefile的路径。所以在Include其它Makefile后，
再调用$(call my-dir)会返回其它Android.mk 所在路径。
2.	include $(CLEAR_VARS)
CLEAR_VARS 变量由Build System提供。并指向一个指定的GNU Makefile，由它负责清理很多LOCAL_xxx.
例如：LOCAL_MODULE, LOCAL_SRC_FILES, LOCAL_STATIC_LIBRARIES等等。但不清理LOCAL_PATH.
这个清理动作是必须的，因为所有的编译控制文件由同一个GNU Make解析和执行，其变量是全局的。
所以清理后才能避免相互影响。
3.	LOCAL_MODULE    := hello-jni
LOCAL_MODULE模块必须定义，以表示Android.mk中的每一个模块。名字必须唯一且不包含空格。
Build System会自动添加适当的前缀和后缀。例如，foo，要产生动态库，则生成libfoo.so.
但请注意：如果模块名被定为：libfoo.则生成libfoo.so. 不再加前缀。
4.	LOCAL_SRC_FILES := hello-jni.c
LOCAL_SRC_FILES变量必须包含将要打包如模块的C/C++ 源码。
不必列出头文件，build System 会自动帮我们找出依赖文件。
缺省的C++源码的扩展名为.cpp. 也可以修改，通过LOCAL_CPP_EXTENSION。
5.	include $(BUILD_SHARED_LIBRARY)
BUILD_SHARED_LIBRARY：是Build System提供的一个变量，指向一个GNU Makefile Script。
它负责收集自从上次调用 include $(CLEAR_VARS)  后的所有LOCAL_XXX信息。并决定编译为什么。
BUILD_STATIC_LIBRARY：编译为静态库。
BUILD_SHARED_LIBRARY ：编译为动态库
BUILD_EXECUTABLE：编译为Native C可执行程序

二.GNU　Make 提供的功能宏,只有通过类似： $(call function) 的方式来得到其值
1.	my-dir: $(call my-dir):
LOCAL_PATH := $(call my-dir)
2.	all-subdir-makefiles:
返回一个列表，包含'my-dir'中所有子目录中的Android.mk。
include $(call all-subdir-makefiles)
三.模块描述变量
1.	LOCAL_PATH
2.	LOCAL_MODULE
3.	LOCAL_MODULE_FILENAME
可选。用来override LOCAL_MODULE. 即允许用户重新定义最终生成的目标文件名。
LOCAL_MODULE := foo-version-1  LOCAL_MODULE_FILENAME := libfoo
4.	LOCAL_SRC_FILES
为Build Modules而提供的Source 文件列表。不需要列出依赖文件。 注意：文件相对于LOCAL_PATH存放，
且可以提供相对路径。
5.	LOCAL_C_INCLUDES
一个可选的path列表。相对于NDK ROOT 目录。编译时，将会把这些目录附上。
LOCAL_C_INCLUDES := sources/foo  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../foo
6.	LOCAL_CFLAGS
一个可选的设置，在编译C/C++ source 时添加如Flags。
用来附加编译选项。 注意：不要尝试在此处修改编译的优化选项和Debug等级。它会通过您Application.mk中的信息自动指定。
也可以指定include 目录通过：LOCAL_CFLAGS += -I<path>。 这个方法比使用LOCAL_C_INCLUDES要好。
因为这样也可以被ndk-debug使用。
7.	LOCAL_STATIC_LIBRARIES
要链接到本模块的静态库list。
8.	LOCAL_SHARED_LIBRARIES
要链接到本模块的动态库。
9.	LOCAL_LDLIBS
linker flags。 可以用它来添加系统库。 如 -lz:
LOCAL_LDLIBS := -lz
