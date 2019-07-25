开启vlan后switch中转发的包均是带有vlan id数据的。

/******************************************************************************/
1. access端口（untagged）
1.1 接收数据
没有vid标签，打上pvid,进入；
有vid标签，丢弃
1.2 发送数据
剥离vid标签，发出

2. trunk端口(tagged)
2.1 接收数据
没有vid标签，打上pvid，进入
有vid标签，vid在允许之列（vlan table），进入
          vid不在允许之列，丢弃
2.2 发出数据
vid标签==pvid，剥离vid标签，发出
vid标签！=pvid，直接发出

3. 在switch芯片内部的数据转发，端口只会接收vlan table允许的vlan id的vlan包。

4. vconfig的使用
https://www.jianshu.com/p/c31068cc0e5a
4.1 在eth0接口上配置VLAN
vconfig add eth0 100
4.2 设置VLAN的REORDER_HDR参数，默认就行了；cat /proc/net/vlan/eth0.100查看eth0.100参数
vconfig set_flag eth0.100 1 1
4.3 配置网络信息
ifconfig eth0 0.0.0.0
ifconfig eth0.100 192.168.100.50 netmask 255.255.255.0 up
4.4 删除VLAN
vconfig rem eth0.100
5. vlan switch配置一般步骤
5.1 配置端口属性；
5.1.1 配置端口的接收帧的类型（tag,untag，all）
5.1.2 配置端口输出的类型（tag, untag）
5.1.3 配置端口是否输入的untag包打上PVID，是否输出的包去掉PVID（有些switch无需配置，这是其默认的属性，）
5.1.4 配置端口PVID
5.1.5 配置端口的优先级（priority）
5.2 设置vlan table
5.3 使能802.1q vlan模式，并设置以vlan table进行vlan匹配
