参考网页：
https://blog.csdn.net/dzw19911024/article/details/82115101
1. 设备节点
1.1 设备名应写成形如<name>[@<unit_address>]的形式；
name就是节点名，最长可以是31个字符长度。
<name>[@<unit_address>]是节点路径，unit_address一般是设备地址，用来唯一标识一个节点；
根据节点名查找节点的API，其参数是不能有"@xxx"这部分的。
2. 引用
设备树允许我们用下面的形式为节点标注引用(起别名)，借以省去冗长的路径。这样就可以实现类似函数调用的效果。
lable的节点会有phandle属性；
编译设备树的时候，相同的节点的不同属性信息都会被合并，相同节点的相同的属性会被重写，
使用引用可以避免移植者四处找节点，直接在板级.dts增改即可。
3. KEY
3.1 键值对是描述属性的方式；
3.1.1 Linux设备树语法中定义了一些具有规范意义的属性，包括：compatible, address, interrupt等
3.1.2 还有一些Linux内核定义好的，一类设备通用的有默认意义的属性，这些属性一般不能被内核自动解析生成相应的设备信息，
但是内核已经编写的相应的解析提取函数，常见的有 "mac_addr"，"gpio"，"clock"，"power"。"regulator" 等等。
3.2 compatible
compatible属性是用来查找节点的方法之一，另外还可以通过节点名或节点路径查找指定节点。
3.3 address
(几乎)所有的设备都需要与CPU的IO口相连，所以其IO端口信息就需要在设备节点节点中说明。
#address-cells，用来描述子节点"reg"属性的地址表中用来描述首地址的cell的数量，
#size-cells，用来描述子节点"reg"属性的地址表中用来描述地址长度的cell的数量。
3.4 interrupts
3.4.1 interrupt-controller 一个空属性用来声明这个node接收中断信号，即这个node是一个中断控制器。
3.4.2 #interrupt-cells，是中断控制器节点的属性，用来标识这个控制器需要几个单位做中断描述符,用来描述子节点中"interrupts"属性使用了父节点中的interrupts属性的具体的哪个值。一般，如果父节点的该属性的值是3，
则子节点的interrupts一个cell的三个32bits整数值分别为:<中断域 中断 触发方式>,如果父节点的该属性是2，则是<中断 触发方式>
3.4.3 interrupt-parent,标识此设备节点属于哪一个中断控制器，如果没有设置这个属性，会自动依附父节点的
3.4.4 interrupts,一个中断标识符列表，表示每一个中断输出信号
- bits[3:0] trigger type and level flags
        1 = low-to-high edge triggered
        2 = high-to-low edge triggered
        4 = active high level-sensitive
        8 = active low level-sensitive
3.5 gpio
"gpio-controller"，用来说明该节点描述的是一个gpio控制器
"#gpio-cells"，用来描述gpaio使用节点的属性一个cell的内容，即 `属性 = <&引用GPIO节点别名 GPIO标号 工作模式>
3.6 驱动自定义key
4. VALUE
dts描述一个键的值有多种方式，当然，一个键也可以没有值
4.1 字符串信息
compatible = "samsung,clock-xusbxti";
4.2 32bit无符号整形数组信息
reg = <0x05000000 0x2 0x05000004 0x2>;
4.3 二进制数数组
local-mac-address = [00 00 de ad be ef];
4.4 字符串哈希表
compatible = "insignal,origen4412","samsung,exynos4412","samsung,exynos4";
4.5 混合形式
以上几种的混合形式
