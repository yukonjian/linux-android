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
