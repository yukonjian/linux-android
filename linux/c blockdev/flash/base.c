/proc/partitions
1. flash 总类
NorFlash、NandFlash、eMMC

2. NOR Flash 需要很长的时间进行抹写，但是它提供完整的寻址与数据总线，并允许随机存取存储器上的任何区域;
一般4MB的小容量时具有很高的成本效益，但是很低的写入和擦除 速度大大影响了它的性能。
3.  NAND Flash 要在NandFlash上面读写数据，要外部加主控和电路设计。NAND Flash具有较快的抹写时间, 而且每个存储单元的面积也较小，
这让NAND Flash相较于NOR Flash具有较高的存储密度与较低的每比特成本。同时它的可抹除次数也高出NOR Flash十倍。
然而NAND Flash 的I/O接口并没有随机存取外部地址 总线，它必须以区块性的方式进行读取，NAND Flash典型的区块大小是数百至数千比特。
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

7. NAND flash和NOR flash的性能比较
flash闪存是非易失存储器，可以对称为块的存储器单元块进行擦写和再编程。
任何flash器件的写入操作只能在空或已擦除的单元内进行，所以大多数情况下，在进行写入操作之前必须先执行擦除。
NAND器件执行擦除操作是十分简单的，而NOR则要求在进行擦除前先要将目标块内所有的位都写为0。
由于擦除NOR器件时是以64～128KB的块进行的，执行一个写入/擦除操作的时间为5s，与此相反，擦除NAND器件是以8～32KB的块进行的，执行相同的操作最多只需要4ms。
7.1 NOR的读速度比NAND稍快一些。
7.2 NAND的写入速度比NOR快很多。
7.3 NAND的4ms擦除速度远比NOR的5s快。
7.4 大多数写入操作需要先进行擦除操作。
NOR flash占据了容量为1～16MB闪存市场的大部分，而NAND flash只是用在8～128MB的产品当中，
这也说明NOR主要应用在代码存储介质中，NAND适合于数据存储，

5. Nand flash 的通用接口
引脚名称
引脚功能
CLE 命令锁存功能;高电平为命令；低电平为数据；
ALE 地址锁存功能;高电平为地址；低电平为数据；//Address Latch Enable
/CE 芯片使能
/RE 读使能(上升沿触发读使能)
/WE 写使能(上升沿触发写使能)
/WP 写保护
R/B 就绪/忙输出信号；高电平为就绪；低电平为busy;

6.
