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
2. data(46~1500)bytes
  IP,ARP报文的具体封装部分
3. FCS
  4个字节的帧校验序列（Frame. Check Sequence，FCS）

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
