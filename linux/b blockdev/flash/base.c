/proc/partitions1. flash 总类
NorFlash、NandFlash、eMMC

2. NOR Flash 需要很长的时间进行抹写，但是它提供完整的寻址与数据总线，并允许随机存取存储器上的任何区域，
这使的它非常适合取代老式的ROM芯片。
3.  NAND Flash 要在NandFlash上面读写数据，要外部加主控和电路设计。NAND Flash具有较快的抹写时间, 而且每个存储单元的面积也较小，
这让NAND Flash相较于NOR Flash具有较高的存储密度与较低的每比特成本。同时它的可抹除次数也高出NOR Flash十倍。
然而NAND Flash 的I/O接口并没有随机存取外部地址总线，它必须以区块性的方式进行读取，NAND Flash典型的区块大小是数百至数千比特。
4. eMMC (Embedded Multi Media Card) 为MMC协会所订立的，eMMC 相当于 NandFlash+主控IC ，对外的接口协议与SD、TF卡一样，
主要是针对手机或平板电脑等产品的内嵌式存储器标准规格。eMMC的一个明显优势是在封装中集成了一个控制器，它提供标准接口并管理闪存，
使得手机厂商就能专注于产品开发的其它部分，并缩短向市场推出产品的时间。这些特点对于希望通过缩小光刻尺寸和降低成本的
NAND供应商来说，同样的重要。
eMMC由一个嵌入式存储解决方案组成，带有MMC（多媒体卡）接口、快闪存储器设备（Nand Flash）及主控制器，所有都在一个小型的BGA 封装。
接口速度高达每秒52MBytes，eMMC具有快速、可升级的性能。同时其接口电压可以是 1.8v 或者是 3.3v。
