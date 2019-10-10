1. Linux C Socket编程原理及简单实例
https://www.cnblogs.com/xudong-bupt/p/3483059.html
2. Socket常用函数的使用
2.1 创建套接字
int socket(int domain, int type, int protocol);
domain：协议域，又称协议族（family）。
常用的协议族有AF_INET、AF_INET6、AF_LOCAL（或称AF_UNIX，Unix域Socket）、AF_ROUTE等。
协议族决定了socket的地址类型，在通信中必须采用对应的地址，如：
AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合、
AF_UNIX决定了要用一个绝对路径名作为地址。

type：指定Socket类型。
常用的socket类型有SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等。
流式Socket（SOCK_STREAM）是一种面向连接的Socket，针对于面向连接的TCP服务应用。
数据报式Socket（SOCK_DGRAM）是一种无连接的Socket，对应于无连接的UDP服务应用。

protocol：指定协议。
常用协议有IPPROTO_TCP、IPPROTO_UDP、IPPROTO_STCP、IPPROTO_TIPC等，
分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议。

return: 如果调用成功就返回新创建的套接字的描述符，如果失败就返回INVALID_SOCKET（Linux下失败返回-1）。
套接字描述符是一个整数类型的值。

注意：1.type和protocol不可以随意组合，如SOCK_STREAM不可以跟IPPROTO_UDP组合。
当第三个参数为0时，会自动选择第二个参数类型对应的默认协议。

2.2 让套接字和套接字数据结构建立对应关系
int bind(SOCKET socket, const struct sockaddr* address, socklen_t address_len);
socket：是一个套接字描述符。
address：是一个sockaddr结构指针，该结构中包含了要结合的地址和端口号。
address_len：确定address缓冲区的长度。
