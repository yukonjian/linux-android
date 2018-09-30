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
