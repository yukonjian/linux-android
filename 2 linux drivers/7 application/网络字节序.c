大端 小端和网络字节序说明
https://www.cnblogs.com/langzou/p/9010899.html

转换函数
#include <arpa/inet.h>
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
