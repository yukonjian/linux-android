/******************************************************************************/
设备数详解
https://blog.csdn.net/lq496387202/article/details/79416299
宋宝华的blog
https://blog.csdn.net/21cnbao
设备树语法讲解
https://blog.csdn.net/dzw19911024/article/details/82115101
/******************************************************************************/
1 设备数
设备数是一种描述硬件的数据结构，它起源于OpenFirmware(OF);
2 硬件描述
2.1 老版本的硬件描述
描述文件放在 arch/arm/plat-xxx 和 arch/arm/mach-xxx
2.2 设备数存放路径
arch/arm/boot/dts
3 设备树的描述
3.1 设备节点
设备名应写成形如<name>[@<unit_address>]的形式；
name就是节点名，最长可以是31个字符长度。
<name>[@<unit_address>]是节点路径，unit_address一般是设备地址，用来唯一标识一个节点；
根据节点名查找节点的API，其参数是不能有"@xxx"这部分的。
3.2 标注和引用
设备树允许我们用下面的形式为节点标注引用(起别名)，借以省去冗长的路径。这样就可以实现类似函数调用的效果。
lable的节点会有phandle属性；
编译设备树的时候，相同的节点的不同属性信息都会被合并，相同节点的相同的属性会被重写，
使用引用可以避免移植者四处找节点，直接在板级.dts增改即可。
acodec: acodec@ff560000   /* 打标注 */
&acodec                   /* 引用标注 */
3.2.1 phandle
我们可以给一个设备节点添加lable，之后可以通过&lable的形式访问这个lable，这种引用是通过phandle（pointer handle）进行的。
在经过DTC工具编译之后，&lable会变成一个特殊的整型数字n，假设n值为1，那么在引用它的节点下自动生成两个属性，属性如下：
linux,phandle = <0x00000001>;
phandle = <0x00000001>;
如a-reference-to-something = <&lable>会变成a-reference-to-something = < 0x00000001>。此处0x00000001就是一个phandle得值，
每一个phandle都有一个独一无二的整型值，在后续kernel中通过这个特殊的数字间接找到引用的节点
3.3 节点属性
3.3.1 Linux设备树语法中定义了一些具有规范意义的属性，包括：compatible, address, interrupt等
(address,interrupt能被内核自动解析生成相应的设备信息)
3.3.2 还有一些Linux内核定义好的，一类设备通用的有默认意义的属性，这些属性一般不能被内核自动解析生成相应的设备信息，
但是内核已经编写的相应的解析提取函数，常见的有 "mac_addr"，"gpio"，"clock"，"power"。"regulator" 等等。
3.3.3 compatible
compatible属性是用来查找节点的方法之一，另外还可以通过节点名或节点路径查找指定节点。
必须有compatible 和 status = "okay";内核才会生成平台设备。
3.3.4 address
#address-cells，用来描述子节点"reg"属性的地址表中用来描述首地址的cell的数量，
#size-cells，用来描述子节点"reg"属性的地址表中用来描述地址长度的cell的数量。
reg属性会生成平台的resource;
3.3.5 interrupts
interrupt-controller; 一个空属性用来声明这个node接收中断信号，即这个node是一个中断控制器。
#interrupt-cells，是中断控制器节点的属性，用来标识这个控制器需要几个单位来描述中断。
#interrupt-cells = <3>;
interrupts = <中断域 中断 触发方式>；
#interrupt-cells = <2>;
interrupts = <中断 触发方式>；
sample:
gic: interrupt-controller@ff580000 {
	compatible = "arm,gic-400";
	#interrupt-cells = <3>;
	#address-cells = <0>;
	interrupt-controller;

	reg = <0x0 0xff581000 0x0 0x1000>,
	      <0x0 0xff582000 0x0 0x2000>,
	      <0x0 0xff584000 0x0 0x2000>,
	      <0x0 0xff586000 0x0 0x2000>;
	interrupts = <GIC_PPI 9 IRQ_TYPE_LEVEL_HIGH>;
};
3.3.5 gpio
"gpio-controller"，用来说明该节点描述的是一个gpio控制器
"#gpio-cells"，用来描述gpaio使用节点的属性一个cell的内容
属性 = <&引用GPIO节点别名 GPIO标号 工作模式>
4. 常见的属性的数据结构
4.1 双引号包含的字符信息
  string-property = "a string";
4.2 cells单位信息是32位无符号整型数据
  cell-property = <0xFF01 412 0x12341283>;
4.3 二进制数据流
  binary-property = [0x01 0x02 0x03 0x04];
