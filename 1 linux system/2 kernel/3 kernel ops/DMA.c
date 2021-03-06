1. cache(快速缓存)的概念
CPU在访问内存时，首先判断所要访问的内容是否在Cache中，如果在，就称为“命中（hit）”，
此时CPU直接从Cache中调用该内容；否则，就 称为“ 不命中”，CPU只好去内存中调用所需的子程序或指令了。

Cache的一致性就是指Cache中的数据，与对应的内存中的数据是一致的。
2. write buffer 写缓冲器
写缓冲器是一个非常小的高速存储缓冲器，用来临时存放处理器将要写入到主存中的数据，在没有写缓冲器的系统中，
处理器直接写数据到主存中。在带有写缓冲器的系统中，cache直接将数据先写到写缓冲器中，然后写缓冲器再以低速写入主存中。
http://lib.csdn.net/article/embeddeddevelopment/34103
2. DMA映射
DAM的映射就分为：一致性DMA映射和流式DMA映射。
  1) 一致性DMA映射
  一致性DMA映射申请的缓存区能够使用cache，并且保持cache一致性。
  一致性映射具有很长的生命周期，在这段时间内占用的映射寄存器，即使不使用也不会释放。生命周期为该驱动的生命周期。
  2) 流式DMA映射
  生命周期比较短，而且禁用cache。

3. 一致行dma分配的2种方法
  1) void *dma_alloc_writecombine(struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t flag)
      不使用cache但使用写缓冲器
  2) void *dma_alloc_coherent(struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t flag);
      不使用cache和写缓冲器
参数：
dma_handle：保存dma实地址的指针，通过该指针得到实地址
size:分配的字节数
flag: GFP_KERNEL
return: 返回实际操作的虚拟地址
