1. 1000BASE-t
1000BASE-T使用非屏蔽双绞线作为传输介质传输的最长距离是100米。
2. 1000BASE-X
1000指传输速率是1000M,BASE是基带传输,X代表单模或多模光纤.-X表示-CX、-SX以及-LX或(非标准化的)-ZX。
3. RGMII/MII/RMII
RGMII（Reduced Gigabit Media Independent Interface）是Reduced GMII（吉比特介质独立接口）。
4. lookup engine or ARL (Address Resolution Logic)
retrieves the DA and SA from each frame received from each port.
5. QoS（Quality of Service，服务质量）
而当网络发生拥塞的时候，所有的数据流都有可能被丢弃；为满足用户对不同应用不同服务质量的要求，
就需要网络能根据用户的要求分配和调度资源，对不同的数据流提供不同的服务质量：对实时性强且重要的数据报
文优先处理；对于实时性不强的普通数据报文，提供较低的处理优先级，网络拥塞时甚至丢弃。
https://baike.baidu.com/item/qos/404053?fr=aladdin
6. ACL（Access Control List，访问控制列表）
是路由器和交换机接口的指令列表，用来控制端口进出的数据包。ACL适用于所有的被路由协议，如IP、IPX、AppleTalk等。
信息点间通信和内外网络的通信都是企业网络中必不可少的业务需求，为了保证内网的安全性，
需要通过安全策略来保障非授权用户只能访问特定的网络资源，从而达到对访问进行控制的目的。
7. igmp snooping (Internet Group Management Protocol Snooping 互联网组管理协议窥探)
运行IGMP Snooping的二层设备通过对收到的IGMP报文进行分析，为端口和MAC组播地址建立起映射关系，并根据这样的映射关系转发组播数据。当二层设备没有运行IGMP Snooping时，组播数据在二层被广播；
当二层设备运行了IGMP Snooping后，已知组播组的组播数据不会在二层被广播，而在二层被组播给指定的接收者。
https://baike.baidu.com/item/igmp%20snooping/1550759?fr=aladdin
8. mib （Management Information Base, 管理信息库）
MIB定义了受管设备必须保存的数据项、允许对每个数据项进行的操作及其含义，即管理系统可访问的受管设备的控制和状态信息等数据变量都保存在MIB中。
https://baike.baidu.com/item/mib/4490795?fr=aladdin
9. SMI (MDC, MDIO)Switch Management Interface
https://blog.csdn.net/jasonchen_gbd/article/details/51628992
10. SMBus (System Management Bus,系统管理总线)
https://baike.baidu.com/item/SMBus/1190006?fr=aladdin
//////////////////////////////////////////////////////////////////////////
MAC和PHY的区别
https://blog.csdn.net/xiaomifengxxxx/article/details/79564133
网口扫盲
https://www.cnblogs.com/jason-lu/tag/%E7%BD%91%E5%8F%A3/

浅析uboot网络程序结构
https://blog.csdn.net/nanaoxue/article/details/22782887

Linux DM9000网卡驱动程序完全分析
https://blog.csdn.net/ypoflyer/article/details/6209922

以太网PHY 芯片之 MII/MDIO接口详解
https://www.cnblogs.com/touchblue/p/3535576.html
