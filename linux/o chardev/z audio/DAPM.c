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
#define SOC_SINGLE_TLV(xname, reg, shift, max, invert, tlv_array) \
{       .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
        .access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
                 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
        .tlv.p = (tlv_array), \
        .info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
        .put = snd_soc_put_volsw, \
        .private_value =  SOC_SINGLE_VALUE(reg, shift, max, invert) }
用户空间可以通过对声卡的control设备发起以下两种ioctl来访问tlv字段所指向的数组：
SNDRV_CTL_IOCTL_TLV_READ
SNDRV_CTL_IOCTL_TLV_WRITE

4. tlv.p 的定义
#define DECLARE_TLV_DB_SCALE(name, min, step, mute)
展开如下:
unsigned int boost_tlv[] = { SNDRV_CTL_TLVT_DB_SCALE, 2个int的大小，min, setp | mute}
例如：
static const DECLARE_TLV_DB_SCALE(mixin_boost_tlv, 0, 900, 0);
寄存器的最小值对应是0dB，寄存器每增加一个单位值，对应的dB数增加是9dB（0.01dB*900）

5. mixer控件
Mixer控件用于音频通道的路由控制，由多个输入和一个输出组成，多个输入可以自由地混合在一起，形成混合后的输出
对于Mixer控件，我们可以认为是多个简单控件的组合，定义一个soc_kcontrol_new数组
static const struct snd_kcontrol_new left_speaker_mixer[] = {
SOC_SINGLE("Input Switch", WM8993_SPEAKER_MIXER, 7, 1, 0),
SOC_SINGLE("IN1LP Switch", WM8993_SPEAKER_MIXER, 5, 1, 0),
};

6. mux控件（Mux多路复用器）
mux是多个输入端和一个输出端的组合控件,mux控件的多个输入端同时只能有一个被选中。
mux控件所对应的寄存器，通常可以设定一段连续的数值，每个不同的数值对应不同的输入端被打开，与上述的mixer控件不同
/* enumerated kcontrol */
struct soc_enum {
        unsigned short reg;
        unsigned short reg2;
        unsigned char shift_l;
        unsigned char shift_r;
        unsigned int max;
        unsigned int mask;
        const char * const *texts;
        const unsigned int *values;
};
tests:字符串数组指针用于描述每个输入端对应的名字
alue:字段则指向一个数组，该数组定义了寄存器可以选择的值，每个值对应一个输入端，如果value是一组连续的值，通常我们可以忽略values参数。
mux控件定义步骤
1）定义字符串和values数组，以下的例子因为values是连续的，所以不用定义
static const char *drc_path_text[] = {
        "ADC",
        "DAC"
};
2）利用ASoc提供的辅助宏定义soc_enum结构
#define SOC_ENUM_SINGLE(xreg, xshift, xmax, xtexts) \
	SOC_ENUM_DOUBLE(xreg, xshift, xshift, xmax, xtexts)
  static const struct soc_enum drc_path =
          SOC_ENUM_SINGLE(WM8993_DRC_CONTROL_1, 14, 2, drc_path_text);
3）利痛ASoc提供的辅助宏，定义soc_kcontrol_new结构，该结构最后用于注册该mux控件：
#define SOC_ENUM(xname, xenum) \
{	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,\
	.info = snd_soc_info_enum_double, \
	.get = snd_soc_get_enum_double, .put = snd_soc_put_enum_double, \
	.private_value = (unsigned long)&xenum }
static const struct snd_kcontrol_new wm8993_snd_controls[] = {
SOC_ENUM("DRC Path", drc_path),
}
