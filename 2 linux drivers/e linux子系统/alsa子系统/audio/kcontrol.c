kcontrol
一个kcontrol代表着一个mixer（混音器），或者是一个mux（多路开关），又或者是一个Volume （音量控制器）等等。
static struct snd_kcontrol_new my_control __devinitdata = {
    .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
    .name = "PCM Playback Switch",
    .index = 0,
    .access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
    .private_value = 0xffff,
    .info = my_control_info,
    .get = my_control_get,
    .put = my_control_put
};
1. name
通常可以分成3部分来定义control的名字：源–方向–功能
源：Master，PCM，CD，Line
方向：Playback，Capture，Bypass，Bypass Capture
功能：Switch，Volume，Route
2. index
如果声卡中有不止一个codec，每个codec中有相同名字的control，这时我们可以通过index来区分这些controls。
当index为0时，则可以忽略这种区分策略。
3. access
access字段包含了该control的访问类型。
https://blog.csdn.net/u012719256/article/details/52162752
4. tlv （Type-Lenght-Value）
DECLARE_TLV_DB_SCALE宏定义的mixer control，它所代表的值按一个固定的dB值的步长变化。该宏的第一个参数是要定义变量的名字，第二个参数是最小值，以0.01dB为单位。
第三个参数是变化的步长，也是以0.01dB为单位。如果该control处于最小值时会做出mute时，需要把第四个参数设为1。
static const DECLARE_TLV_DB_SCALE(mixin_boost_tlv, 0, 900, 0);
SOC_SINGLE_TLV("MIXINL IN1LP Boost Volume", WM8994_INPUT_MIXER_1, 7, 1, 0,
               mixin_boost_tlv),
寄存器的地址都是WM8994_INPUT_MIXER_1，控制位分别是第7bit和第8bit，最大值是1，所以，该控件只能设定两个数值0和1，对应的dB值就是0dB和9dB。
5. Mixer控件
我们会为mixer的每个输入端都单独定义一个简单控件来控制该路输入的开启和关闭，反应在代码上，就是定义一个soc_kcontrol_new数组：
static const struct snd_kcontrol_new left_speaker_mixer[] = {
SOC_SINGLE("Input Switch", WM8993_SPEAKER_MIXER, 7, 1, 0),
SOC_SINGLE("IN1LP Switch", WM8993_SPEAKER_MIXER, 5, 1, 0),
SOC_SINGLE("Output Switch", WM8993_SPEAKER_MIXER, 3, 1, 0),
SOC_SINGLE("DAC Switch", WM8993_SPEAKER_MIXER, 6, 1, 0),
};
6. Mux控件
ASoc用soc_enum结构来描述mux控件的寄存器信息：
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
两个寄存器地址和位移字段：reg，reg2，shift_l，shift_r，用于描述左右声道的控制寄存器信息。
字符串数组指针用于描述每个输入端对应的名字。
value字段则指向一个数组，该数组定义了寄存器可以选择的值，每个值对应一个输入端，如果value是一组连续的值，通常我们可以忽略values参数。
第一步，定义字符串和values数组，以下的例子因为values是连续的，所以不用定义：
static const char *drc_path_text[] = {
        "ADC",
        "DAC"
};
第二步，利用ASoc提供的辅助宏定义soc_enum结构，用于描述寄存器：
static const struct soc_enum drc_path =
        SOC_ENUM_SINGLE(WM8993_DRC_CONTROL_1, 14, 2, drc_path_text);
第三步，利用ASoc提供的辅助宏，定义soc_kcontrol_new结构，该结构最后用于注册该mux控件：
static const struct snd_kcontrol_new wm8993_snd_controls[] = {
......
SOC_ENUM("DRC Path", drc_path),
......
}

7. widget之间的连接器：path 会根据route自动生成
8. widget的连接关系：route
struct snd_soc_dapm_route {
        const char *sink;
        const char *control;
        const char *source;
        int (*connected)(struct snd_soc_dapm_widget *source,
                         struct snd_soc_dapm_widget *sink);
};
sink指向到达端widget的名字字符串
source指向起始端widget的名字字符串
control指向负责控制该连接所对应的kcontrol名字字符串
connected回调则定义了上一节所提到的自定义连接检查回调函数
该结构的意义很明显就是：source通过一个kcontrol，和sink连接在一起，现在是否处于连接状态，请调用connected回调函数检查。
9. widget的定义


//kcontrol
1. SOC_SINGLE
#define SOC_SINGLE(xname, reg, shift, max, invert) \
{       .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
        .info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
        .put = snd_soc_put_volsw, \
        .private_value =  SOC_SINGLE_VALUE(reg, shift, max, invert) }
宏定义的参数分别是：xname（该控件的名字），reg（该控件对应的寄存器的地址），shift（控制位在寄存器中的位移），max（控件可设置的最大值），invert（设定值是否逻辑取反）。
#define SOC_DOUBLE_VALUE(xreg, shift_left, shift_right, xmax, xinvert) \
        ((unsigned long)&(struct soc_mixer_control) \
        {.reg = xreg, .rreg = xreg, .shift = shift_left, \
        .rshift = shift_right, .max = xmax, .platform_max = xmax, \
        .invert = xinvert})
#define SOC_SINGLE_VALUE(xreg, xshift, xmax, xinvert) \
        SOC_DOUBLE_VALUE(xreg, xshift, xshift, xmax, xinvert)
/* mixer control */
struct soc_mixer_control {
        int min, max, platform_max;
        unsigned int reg, rreg, shift, rshift, invert;
};

2. SOC_SINGLE_TLV
SOC_SINGLE_TLV    SOC_SINGLE_TLV是SOC_SINGLE的一种扩展，主要用于定义那些有增益控制的控件，例如音量控制器，EQ均衡器等等。
#define SOC_SINGLE_TLV(xname, reg, shift, max, invert, tlv_array) \
{       .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
        .access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
                 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
        .tlv.p = (tlv_array), \
        .info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
        .put = snd_soc_put_volsw, \
        .private_value =  SOC_SINGLE_VALUE(reg, shift, max, invert) }
