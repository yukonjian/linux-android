
1. void *dma_alloc_coherent(struct device *dev,size_t size,dma_addr_t *dma_handle,gfp_t gfp);
禁止页表项中的 C （Cacheable） 域以及 B (Bufferable)域。
C 代表是否使用高速缓冲存储器， 而 B 代表是否使用写缓冲区。
2. 调用
A = dma_alloc_writecombine(B,C,D,GFP_KERNEL);
含义：

A: 内存的虚拟起始地址，在内核要用此地址来操作所分配的内存

B: struct device指针，可以平台初始化里指定，主要是dma_mask之类，可参考framebuffer

C: 实际分配大小，传入dma_map_size即可

D: 返回的内存物理地址，dma就可以用。

所以，A和D是一一对应的，只不过，A是虚拟地址，而D是物理地址。对任意一个操作都将改变缓冲区内容。
3. A = dma_alloc_writecombine(struct device *dev, size_t size,dma_addr_t *handle, gfp_t gfp);
只禁止 C （Cacheable） 域.
4. PAGE_SIZE = 4096=4k;
