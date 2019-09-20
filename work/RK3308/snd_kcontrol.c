1. Mixer 和 Mux的区别
 o Mixer      - Mixes several analog signals into a single analog signal.
 o Mux        - An analog switch that outputs only one of many inputs.
Mixer可以混合多个输入到输出
Mux只能从多个输入里选择一个作为输出
Mixer当然也可以只从多个输入里选择一个作为输出


2. snd_kcontrol_new
struct snd_kcontrol_new {
	snd_ctl_elem_iface_t iface;	/* interface identifier */
	unsigned int device;		/* device/client number */
	unsigned int subdevice;		/* subdevice (substream) number */
	const unsigned char *name;	/* ASCII name of item */
	unsigned int index;		/* index of item */
	unsigned int access;		/* access rights */
	unsigned int count;		/* count of same elements */
	snd_kcontrol_info_t *info;
	snd_kcontrol_get_t *get;
	snd_kcontrol_put_t *put;
	union {
		snd_kcontrol_tlv_rw_t *c;
		const unsigned int *p;
	} tlv;
	unsigned long private_value;
};

name定义的标准是“SOURCE DIRECTION FUNCTION”即“源 方向 功能”，SOURCE定义了kcontrol的源，
如“Master”、“PCM”等；DIRECTION 则为“Playback”、“Capture”等，如果DIRECTION忽略，意味着Playback和capture双向；FUNCTION则可以是“Switch”、“Volume”和“Route”等。

https://blog.csdn.net/luckywang1103/article/details/49095655
kcontrol与dapm kcontrol区别
kcontrol通常用于控件的音量等控制，而dapm kcontrol相关的kcontrol则是用于widget电源管理的开关。
