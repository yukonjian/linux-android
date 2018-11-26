objdump -D -b binary -m arm a.bin > ./test.txt
-D表示对全部文件进行反汇编，-b表示二进制，-m表示指令集架构，a.bin就是我们要反汇编的二进制文件
objdump使用arm-linux-gnueabi-objdump类型的更好

[<c0454b60>] (cpufreq_governor_interactive+0x220/0x5d4) from [<c044ec70>] (__cpufreq_governor+0xe0/0x190)
linux下的System.map可查找cpufreq_governor_interactive的地址
查找该bug出现的地方
./arm-linux-gnueabi-addr2line -e   ~/work/lichee/linux-3.10/vmlinux c0454b60
结果：/home/steven/work/lichee/linux-3.10/drivers/cpufreq/cpufreq_interactive.c:1411
