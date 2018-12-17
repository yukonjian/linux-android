1. linux中likely()和unlikely()
likely()与unlikely()在2.6内核中，随处可见，那为什么要用它们？它们之间有什么区别呢？
首先明确：
if (likely(value))等价于if (value)
if (unlikely(value))等价于if (value)

也就是说likely()和unlikely()从阅读和理解的角度是一样的。
这两个宏在内核中定义如下：
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
这里的__built_expect()函数是gcc(version >= 2.96)的内建函数,提供给程序员使用的，目的是将"分支转移"的信息提供给编译器，这样编译器对代码进行优化，以减少指令跳转带来的性能下降。
__buildin_expect((x), 1)表示x的值为真的可能性更大.
__buildin_expect((x), 0)表示x的值为假的可能性更大.
也就是说，使用likely(),执行if后面的语句的机会更大，使用unlikely(),执行else后面的语句机会更大一些。

通过这种方式，编译器在编译过程中，会将可能性更大的代码紧跟着后面的代码，从而减少指令跳转带来的性能上的下降。

2. BUG_ON（）和WARN_ON（）
    内核中有许多地方调用类似BUG（）的语句，它非常像一个内核运行时的断言，意味着本来不该执行到BUG（）这条语句，一旦执行即抛出Oops。BUG（）的定义为：
include/asm-generic/bug.h
#define BUG() do { \
       printk("BUG: failure at %s:%d/%s()!\n", __FILE__, __LINE__, __func__); \
       panic("BUG!"); \
} while (0)
其中panic（）定义在kernel/panic.c中，会导致内核崩溃，并打印Oops。
