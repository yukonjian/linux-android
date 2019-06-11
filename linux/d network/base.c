一、名词解释
1. PPPoE：（英语：Point-to-Point Protocol Over Ethernet），以太网上的点对点协议
2. 网关：网关到底是什么呢？网关实质上是一个网络通向其他网络的IP地址。网关的IP地址是具有路由功能的设备的IP地址。
3.子网掩码：子网掩码(subnet mask)又叫网络掩码、地址掩码、子网络遮罩，它是一种用来指明一个IP地址的哪些位标识的是主机所在的子网，
以及哪些位标识的是主机的位掩码。
子网掩码只有一个作用，就是将某个IP地址划分成网络地址和主机地址两部分。
4. IGMP（Internet Group Management Protocol）
因特网协议家族中的一个组播协议。
该协议运行在主机和组播路由器之间。IGMP协议共有三个版本，即IGMPv1、v2 和v3。
5. QOS 服务质量（Quality of Service）
6. MIB 管理信息库（Management Information Base）
7. 802.3简介
https://wenku.baidu.com/view/6cbb14ed998fcc22bcd10da5.html
8.RMII时序
https://wenku.baidu.com/view/064b5da5a32d7375a41780fb.html
9. 以太网帧格式
https://baike.baidu.com/item/%E4%BB%A5%E5%A4%AA%E7%BD%91%E5%B8%A7%E6%A0%BC%E5%BC%8F/10290427?fr=aladdin
10. 以太网报文格式
https://www.cnblogs.com/yongren1zu/p/6274460.html
11. 链路层常见报文格式及长度
http://blog.chinaunix.net/uid-20530497-id-2878069.html
二、命令
1. route
1)查看有多少路由
 route -n
2)添加默认路由
route add default gw 10.0.0.253
route del default gw 10.0.0.253
实际上route add default gw 10.0.0.254 就相当于route add -net 0.0.0.0 netmask 0.0.0.0 gw 10.0.0.254
3)添加路由信息
route add -net 10.0.0.0/24 gw 10.0.1.11
4)路由表 //route -n
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
10.0.0.0        0.0.0.0         255.255.255.0   U     0      0       0 eth0
169.254.0.0     0.0.0.0         255.255.0.0     U     0      0       0 eth0
0.0.0.0         10.0.0.254      0.0.0.0         UG    0     0        0 eth0
系统的默认网关信息，表示去任何地方（0.0.0.0），都发给10.0.0.254，因为是默认网关，所以，
放在了最后一条。路由也是有顺序的，如果不符合任何一条规则就交给默认网关处理。
2. ifconfig
1)设置ip、掩码、网关
ifconfig eth0 192.168.5.40 netmask 255.255.255.0

三. VLAN 参考文献：https://blog.51cto.com/6930123/2115373
1. VLAN：在二层交换机上分割广播域的技术。
VLAN通过限制广播帧转发的范围分割了广播域，使用VLAN ID来区分不同的VLAN。
2. VLAN生成的逻辑上的交换机是互不相通的。因此，在交换机上设置VLAN后，如果未做其他处理，VLAN间是无法通信的。
VLAN间的通信也需要路由器提供中继服务，这被称作“VLAN间路由”。
VLAN间路由，可以使用普通的路由器，也可以使用三层交换机。
3. 交换机的端口
可以分为两种：访问链接(Access Link);汇聚链接(Trunk Link)
3.1 访问链接
访问链接，指的是“只属于一个VLAN，且仅向该VLAN转发数据帧”的端口。
在大多数情况下，访问链接所连的是客户机。
通常设置VLAN的顺序是：生成VLAN；设定访问链接（决定各端口属于哪一个VLAN）；
设定访问链接，可以是事先固定的、也可以是根据所连的计算机而动态改变设定。
前者被称为“静态VLAN”、后者自然就是“动态VLAN”了。
3.1.1 静态VLAN
静态VLAN又被称为基于端口的VLAN（Port Based VLAN）。明确指定各端口属于哪个VLAN的设定方法。
3.1.2 动态VLAN
动态VLAN则是根据每个端口所连的计算机，随时改变端口所属的VLAN。
动态VLAN可以大致分为3类：
基于MAC地址的VLAN（MAC Based VLAN）:就是通过查询并记录端口所连计算机上网卡的MAC地址,来决定端口的所属。
基于子网的VLAN（Subnet Based VLAN）:通过所连计算机的IP地址，来决定端口所属VLAN的。
基于用户的VLAN（User Based VLAN）:根据交换机各端口所连的计算机上当前登录的用户，来决定该端口属于哪个VLAN。
3.2 汇聚链接
汇聚链接：能够转发多个不同VLAN的通信的端口。
汇聚链路上流通的数据帧，都被附加了用于识别分属于哪个VLAN的特殊信息。
3.2.1 VLAN的汇聚方式（IEEE802.1Q与ISL）
附加VLAN信息的方法，最具有代表性的有：IEEE802.1Q；ISL；
3.2.1.1 IEEE802.1Q
1) EEE802.1Q所附加的VLAN识别信息，位于数据帧中“发送源MAC地址”与“类别域（Type Field）”之间。
具体内容为2字节的TPID和2字节的TCI，共计4字节。
2) 在数据帧中添加了4字节的内容，那么CRC值自然也会有所变化。这时数据帧上的CRC是插入TPID、TCI后，
对包括它们在内的整个数据帧重新计算后所得的值。
3) 而当数据帧离开汇聚链路时，TPID和TCI会被去除，这时还会进行一次CRC的重新计算。
4) 基于IEEE802.1Q附加的VLAN信息，就像在传递物品时附加的标签。因此，它也被称作“标签型VLAN（Tagging VLAN）”。
参考：nteowkr_map/vlan_IEEE802.1Q.png
3.2.1.2 ISL（Inter Switch Link）
每个数据帧头部都会被附加26字节的“ISL包头（ISL Header）”，并且在帧尾带上通过对包括ISL包头在内的整个数据帧进行计算后得到的4字节CRC值。
ISL有如用ISL包头和新CRC将原数据帧整个包裹起来，因此也被称为“封装型VLAN（Encapsulated VLAN）”。
注：由于ISL是Cisco独有的协议，因此只能用于Cisco网络设备之间的互联。
4. VLAN间的路由
1) 在LAN内的通信，必须在数据帧头中指定通信目标的MAC地址。而为了获取MAC地址，TCP/IP协议下使用的是ARP。ARP解析MAC地址的方法，则是通过广播。
也就是说，如果广播报文无法到达，那么就无从解析MAC地址，亦即无法直接通信。
2) 路由功能，一般主要由路由器提供。但在今天的局域网里，我们也经常利用带有路由功能的交换机——三层交换机（Layer 3 Switch）来实现。
