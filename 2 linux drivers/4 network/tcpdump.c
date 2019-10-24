1.
1、抓取包含10.10.10.122的数据包
# tcpdump -i eth0 -vnn host 10.10.10.122
2. 报文分析
http://www.mamicode.com/info-detail-2089175.html

3.保存抓包文件
 tcpdump -i eth0 -w dump.pcap
-i #是指定要抓取的网卡
-w #指定结果保存的位置

2. Xcap使用教程--创建、发送和分析报文
