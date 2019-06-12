一、以太网报文格式

  | ether_dhost | ehter_shost | ether_type | data(46~1500)bytes | FCS |

Ethernet II类型以太网帧的最小长度为64字节（6＋6＋2＋46＋4），最大长度为1518字节（6＋6＋2＋1500＋4）。
1. 报文头
typedef struct {
        unsigned char   dest_mac[6];
        unsigned char   src_mac[6];
        unsigned short  eth_type;
} ethernet_header;
1. ether_type
  0x0800　　网际协议（IP）
  0x0806　　地址解析协议（ARP）
  0x8035　　反向地址解析协议
  小于0600H（1536）的值是用于IEEE802的，表示数据包的长度。
2. data(46~1500)bytes
  IP,ARP报文的具体封装部分
3. FCS
  4个字节的帧校验序列（Frame. Check Sequence，FCS）
  32位数据校验位.为32位的CRC校验,该校验由网卡自动计算,自动生成,自动校验,自动在数据段后面填入.
4. PAD
填充位。由于以太网帧传输的数据包最小不能小于60字节, 除去（DA，SA，TYPE 14字节），还必须传输46字节的数据，当数据段的数据不足46字节时，后面补000000.....(当然也可以补其它值)

注：
[1]事实上,PR,SD,PAD,FCS这几个数据段我们不用理它 ,它是由网卡自动产生的,我们要理的是DA,SA,TYPE,DATA四个段的内容.
[2]所有数据位的传输由低位开始(但传输的位流是用曼彻斯特编码的)
[3]以太网的冲突退避算法就不介绍了,它是由硬件自动执行的.
[4]DA+SA+TYPE+DATA+PAD最小为60字节,最大为1514字节.
[5]以太网卡可以接收三种地址的数据,一个是广播地位,一个是多播地址(我们用不上),一个是它自已的地址.但网卡也可以设置为接收任何数据包(用于网络分析和监控).
[6]任何两个网卡的物理地址都是不一样的,是世界上唯一的,网卡地址由专门机构分配.不同厂家使用不同地址段,同一厂家的任何两个网卡的地址也是唯一的.
[7]根据网卡的地址段(网卡地址的前三个字节),可以知道网卡的生产厂家.有些网卡的地址也可以由用户去设定,但一般不需要.
[8]Ethernet_II的主要特点是通过类型域标识了封装在帧里的数据包所采用的协议，类型域是一个有效的指针，通过它，数据链路层就可以承载多个上层（网络层）协议。

但是，Ethernet_II的缺点是没有标识帧长度的字段。
二、IP报文格式
1. IP报文头部
typedef struct {
        unsigned char header_len:4; /* 低4位，头部长度=header_len*4字节 */
        unsigned char version:4;    /* 版本号 */
        unsigned char tos:8;        /* 服务类型 */
        unsigned short total_len;   /* 总长度（包括头部和IP数据）,字节为单位 */
        unsigned short ident;       /* 认证 */
        unsigned short flags;       /* 高3位为标志, 低13位为片偏移 */
        unsigned char  ttl:8;       /* 表示数据包在网络上生存多久，每通过一个路由器该值减一，为0时将被路由器丢弃。 */
        unsigned char  proto:8;     /* 传输层的协议 */
        unsigned short checksum;    /* IPv4数据报包头的校验和 */
        unsigned char  src_ip[4];   /* 源IP地址 */
        unsigned char  dest_ip[4];  /* 目的IP地址 */
} ip_header;
1）proto表示传输层的协议
  Internet控制消息（ICMP）    1
  Internet组管理（IGMP）      2
  传输控制（TCP）             6
  用户数据报文（UDP）         17
2) flags
  保留位：1位
  不分段位：1位，取值：0（允许数据报分段）、1（数据报不能分段）
  更多段位：1位，取值：0（数据包后面没有包，该包为最后的包）、1（数据包后面有更多的包）
  段偏移量：当数据分组时，它和更多段位（MF, More fragments）进行连接，帮助目的主机将分段的包组合。

三、ARP报文格式
1. ARP字段
typedef struct arphdr
{
//arp首部
unsigned short arp_hrd;    /* format of hardware address，硬件类型 */
unsigned short arp_pro;    /* format of protocol address，协议类型 */
unsigned char arp_hln;    /* length of hardware address，硬件地址长度（6），mac长度 */
unsigned char arp_pln;    /* length of protocol address，协议地址长度 （4），IP长度 */
unsigned short arp_op;     /* OP指示当前包是请求包还是应答包，对应的值分别是0x0001和0x0002 */

unsigned char arp_sha[6];    /* sender hardware address，发送者的MAC地址 */
unsigned long arp_spa;    /* sender protocol address，发送者的IP地址 */
unsigned char arp_tha[6];    /* target hardware address，接收者的MAC地址 */
unsigned long arp_tpa;    /* target protocol address,接收者的IP地址 */
}ARPHDR, *PARPHDR;

四、以太网帧格式
每种格式的以太网帧的开始处都有64比特（8字节）的前导字符。
其中，前7个字节称为前同步码（Preamble），内容是16进制数0xAA，
最后1字节为帧起始标志符0xAB，它标识着以太网帧的开始。
https://www.cnblogs.com/smartjourneys/articles/8124490.html
