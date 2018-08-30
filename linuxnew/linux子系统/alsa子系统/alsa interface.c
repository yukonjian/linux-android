一、proc接口
1. 音频的proc接口路径
cd /proc/asound/
2. 查看有几个声卡
cat cards
3. 列出系统card下所有注册的device，包括control，pcm，timer，seq等等
cat devices
4. 列出系统的pcm设备，包括capture和playback
cat pcm

二、dev接口
1. 设备节点的位置
/dev/snd
2. 各个设备文件的功能
control:      用于声卡的控制。
pcmC0D0c:     用于录音的pcm设备。
pcmC0D0p:     用于播音的pcm设备。
seq:          音序器接口。
timer:        定时器接口。
3. Linux内核定义的设备类型
enum {
	SNDRV_DEVICE_TYPE_CONTROL,
	SNDRV_DEVICE_TYPE_SEQUENCER,
	SNDRV_DEVICE_TYPE_TIMER,
	SNDRV_DEVICE_TYPE_HWDEP,
	SNDRV_DEVICE_TYPE_RAWMIDI,
	SNDRV_DEVICE_TYPE_PCM_PLAYBACK,
	SNDRV_DEVICE_TYPE_PCM_CAPTURE,
	SNDRV_DEVICE_TYPE_COMPRESS,
};
