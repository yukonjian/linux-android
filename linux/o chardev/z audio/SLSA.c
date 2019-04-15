https://blog.csdn.net/droidphone/article/category/1118446
一、snd_card
1.创建snd_card的一个实例
err = snd_card_create(index, id, THIS_MODULE, sizeof(struct mychip), &card);
index           一个整数值，该声卡的编号
id                字符串，声卡的标识符
第四个参数    该参数决定在创建snd_card实例时，需要同时额外分配的私有数据的大小，
该数据的指针最终会赋值给snd_card的private_data数据成员
card             返回所创建的snd_card实例的指针
2.创建声卡的专用数据
private_data数据成员
3.设置driver的ID名字
strcpy(card->driver, "My Chip");
strcpy(card->shortname, "My Own Chip 123");
sprintf(card->longname, "%s at 0x%lx irq %i",
            card->shortname, chip->ioport, chip->irq);
longname字段则会出现在/proc/asound/cards中
4.创建声卡的功能部件（逻辑设备），PCM , Mixer
snd_device_new();不过一般不直接调用该函数，而是调用相应的封装
snd_pcm_new();
snd_ctl_ctrate();
5.注册声卡
err = snd_card_register(card);
if (err < 0) {
    snd_card_free(card);
    return err;
}
二、创建PCM设备
int snd_pcm_new(struct snd_card *card, const char *id, int device, int playback_count, int capture_count,
                struct snd_pcm ** rpcm);
device 表示目前创建的是该声卡下的第几个pcm，第一个pcm设备从0开始。
playback_count 表示该pcm将会有几个playback substream。
capture_count 表示该pcm将会有几个capture substream。
void snd_pcm_set_ops(struct snd_pcm *pcm, int direction, struct snd_pcm_ops *ops);
三、ASoC架构中的Codec
ret =  snd_soc_register_codec(&i2c_client->dev, &soc_codec_dev_es8374,
    &es8374_dai[0], ARRAY_SIZE(es8374_dai));
Codec驱动的首要任务就是确定snd_soc_codec和snd_soc_dai的实例，并把它们注册到系统中，
注册后的codec和dai才能为Machine驱动所用。
snd_soc_register_dais函数其实也是和snd_soc_register_codec类似，显示为每个snd_soc_dai实例分配内存，确定dai的名字，用snd_soc_dai_driver实例的字段对它进行必要初始化，
最后把该dai链接到全局链表dai_list中，和Codec一样，最后也会调用snd_soc_instantiate_cards函数触发一次匹配绑定的操作
