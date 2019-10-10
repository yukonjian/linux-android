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
6. spi flash  https://blog.csdn.net/m0_37580896/article/details/79686004
SPI一种通信接口。那么严格的来说SPI Flash是一种使用SPI通信的Flash，即，可能指NOR也可能是NAND。
但现在大部分情况默认下人们说的SPI Flash指的是SPI NorFlash。早期Norflash的接口是parallel的形式，
即把数据线和地址线并排与IC的管脚连接。但是后来发现不同容量的Norflash不能硬件上兼容
（数据线和地址线的数量不一样），并且封装比较大，占用了较大的PCB板位置，所以后来逐渐被SPI（串行接口）Norflash所取代。
同时不同容量的SPI Norflash管脚也兼容封装也更小。，至于现在很多人说起NOR flash直接都以SPI flash来代称。

5. Nand flash 的通用接口
引脚名称

引脚功能

CLE 命令锁存功能

ALE 地址锁存功能

/CE 芯片使能

/RE 读使能

/WE 写使能

/WP 写保护

R/B 就绪/忙输出信号

ALE 是英文"Address Latch Enable"的缩写
1. 命令、地址、数据都通过8个I/O口传输
2. 写命令、地址、数据时，都需要将WE、CE信号同时拉低
3. 数据在WE信号的上升沿被NAND Flash锁存
4. 命令锁存信号CLE和地址锁存信号ALE用来分辨、锁存命令或地址
5. 在CLE上升沿，命令被锁存
6. 在ALE上升沿，地址被锁存
