摄像头接口主要有：USB、DVP、MIPI（CSI）
DVP是并口，需要PCLK、VSYNC、HSYNC、D[0：11]——可以是8/10/12bit数据，看ISP或baseband是否支持，并口传输的是CMOS电平信号（重点是非差分），因为PCLK的最大速率为96M左右，而且走线长度不能过长，所有DVP最大速率最好控制在72M以下，故PCB layout会较好画，500W还可以勉强用DVP，800W及以上都采用MIPI接口
---------------------
作者：夜谭
来源：CSDN
原文：https://blog.csdn.net/wangchongttg/article/details/81668238
版权声明：本文为博主原创文章，转载请附上博文链接！
