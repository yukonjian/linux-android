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
