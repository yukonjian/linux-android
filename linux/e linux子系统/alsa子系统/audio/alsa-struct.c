ALSA代码目录结构
core                该目录包含了ALSA驱动的中间层，它是整个ALSA驱动的核心部分
drivers             放置一些与CPU、BUS架构无关的公用代码；dummy.c可以参考；sound/arm/pxa2xx-ac97.c也可以参考；
soc                 针对system-on-chip体系的中间层代码
soc/codecs          针对soc体系的各种codec的代码，与平台无关
一、声卡的创建
https://blog.csdn.net/droidphone/article/details/6289712
struct snd_card  // include/sound/core.h
snd_card可以说是整个ALSA音频驱动最顶层的一个结构，整个声卡的软件逻辑结构开始于该结构，
几乎所有与声音相关的逻辑设备都是在snd_card的管理之下

err = snd_card_create(index, id, THIS_MODULE, 0, &card);
index           一个整数值，该声卡的编号，若为-1，则自动分配
id                字符串，声卡的标识符
第四个参数    该参数决定在创建snd_card实例时，需要同时额外分配的私有数据的大小，
分配的内存指针最终会赋值给snd_card的private_data数据成员
card             返回所创建的snd_card实例的指针
二 其他目录
https://blog.csdn.net/DroidPhone/article/list/3

https://blog.csdn.net/zyuanyun/article/category/6752337
