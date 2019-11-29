1、 内存/寄存器操作指令
nm      修改内存值 (指定地址)
格式： nm [.b, .w, .l] address
mm     修改内存值(地址自动加一)
格式：  mm [.b, .w, .l] address
md       显示内存值
格式：  md [.b, .w, .l] address [# of objects]
mw     用指定的数据填充内存
格式：  mw [.b, .w, .l] address value [count]
cp      内存的拷贝（包括内存与Nor Flash间的数据拷贝）
格式：cp [.b, .w, .l] source target count
上面是查看和修改内存值的指令，可以查看和修改SDRAM和寄存器值。
[.b, .w, .l]代表了查看和修改形式：Byte、word、long

2. uboot CMD命令的添加
U_BOOT_CMD(name,maxargs,repeatable,command,"usage","help")
name：命令名，非字符串，但在U_BOOT_CMD中用“#”符号转化为字符串
maxargs：命令+参数的最大数量
repeatable：是否自动重复（按Enter键是否会重复执行，1表示会重复执行）
command：该命令对应的响应函数指针
usage：简短的使用说明（字符串）
help：较详细的使用说明（字符串）
#define U_BOOT_CMD(name,maxargs,rep,cmd,usage,help) \
　　　　cmd_tbl_t __u_boot_cmd_##name Struct_Section = {#name, maxargs, rep, cmd, usage, help}
