1. kcontrol: 定义一个kcontrol主要就是定义一个snd_kcontrol_new结构
struct snd_kcontrol_new {
  snd_ctl_elem_iface_t iface;     /* interface identifier（标识符） */
  const unsigned char *name;      /* ASCII name of item */
  snd_kcontrol_info_t *info;
  snd_kcontrol_get_t *get;
  snd_kcontrol_put_t *put;
  union {
                snd_kcontrol_tlv_rw_t *c;
                const unsigned int *p;
        } tlv;
  unsigned long private_value;
}

2. 简单的控件SOC_SINGLE
SOC_SINGLE应该算是最简单的控件了，这种控件只有一个控制量，比如一个开关，
或者是一个数值变量（比如Codec中某个频率，FIFO大小等等）。

#define SOC_SINGLE(xname, reg, shift, max, invert) \
{       .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
        .info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
        .put = snd_soc_put_volsw, \
        .private_value =  SOC_SINGLE_VALUE(reg, shift, max, invert) }

/* mixer control，定义该结构体并将指针传递给private_value */
struct soc_mixer_control {
	int min, max, platform_max;
	unsigned int reg, rreg, shift, rshift, invert;
};

3. SOC_SINGLE_TLV
SOC_SINGLE_TLV    SOC_SINGLE_TLV是SOC_SINGLE的一种扩展，主要用于定义那些有增益控制的控件，
例如音量控制器，EQ均衡器等等。
用户空间可以通过对声卡的control设备发起以下两种ioctl来访问tlv字段所指向的数组：
SNDRV_CTL_IOCTL_TLV_READ
SNDRV_CTL_IOCTL_TLV_WRITE
