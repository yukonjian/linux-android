1. 消息级别设置
/proc/sys/kernel/printk

cat /proc/sys/kernel/printk
4       4       1       7
文件的4个数字值含义， 如下所示：
1) 控制台（一般是串口） 日志级别： 当前的打印级别， 优先级高于该值的消息将被打印至控制台。
2) 默认的消息日志级别： 将用该优先级来打印没有优先级前缀的消息， 也就是在直接写printk（“xxx”） 而不带打印
级别的情况下， 会使用该打印级别。
3) 最低的控制台日志级别： 控制台日志级别可被设置的最小值（一般都是1） 。
4) 默认的控制台日志级别： 控制台日志级别的默认值。
echo >> /proc/sys/kernel/printk
>: 会重写文件，如果文件里面有内容会覆盖。
>>这个是将输出内容追加到目标文件中。如果文件不存在，就创建文件。

2. 内核打印
1）dmesg
查看内核打印缓冲区（__log_buf）
dmesg -c
查看并清除内核打印缓冲区（__log_buf）
2）cat /proc/kmsg
显示内核信息。
由于/proc/kmsg是一个“永无休止的文件”， 因此，cat /proc/kmsg的进程只能通过“Ctrl+C”或kill终止。

3. 查看设备号
/proc/devices

4. 查看中断
/proc/interrupts

5. CPU信息
/proc/cpuinfo

6. 查看块设备分区信息
/proc/mtd
/proc/partitions
