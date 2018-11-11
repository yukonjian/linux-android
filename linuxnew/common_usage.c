1. 在probe中获取设备树的节点
struct device_node *np = pdev->dev.of_node;
1）pdev 为平台设备指针

2. 在函数中使用 全局结构体变量，可以定义一个该结构体的指针，并将全局结构体变量地址赋值给该指针
struct snd_soc_card *card = &snd_soc_sunxi_card;
这样做的好处是：全局变量名在该函数中只会出现一次，不会在多个地方出现
