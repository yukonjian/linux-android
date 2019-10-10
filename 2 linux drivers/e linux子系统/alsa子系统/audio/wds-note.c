一、声音采集和存储
1.声音的采集：采样率，精度，通道数
2.声音文件的存储：PCM->wav->mp3 ;wav为原始文件，有文件的头部。
二、ALSA音频框架
controlC0---->snd_register_device_for_dev-------->snd_card_create


snd_card_create--->snd_ctl_create--->snd_ctl_dev_register--->snd_register_device--->snd_register_device_for_dev
snd_pcm_new--->_snd_pcm_new--->snd_pcm_dev_register--->snd_register_device_for_dev
snd_register_device_for_dev将file_operations放入到snd_minors[]并创建设备节点

1.snd_card_create
2.snd_pcm_new
3.snd_card_register
