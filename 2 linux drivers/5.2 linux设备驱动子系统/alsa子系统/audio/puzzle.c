1. speaker out 和mono out 的区别
2. line input 和 mic input 区别
3. single speed 和 double speed 区别
4. 结构体中定义变量问题。
#define SOC_SINGLE(xname, reg, shift, max, invert) \
{       .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
        .info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
        .put = snd_soc_put_volsw, \
        .private_value =  SOC_SINGLE_VALUE(reg, shift, max, invert)
}

#define SOC_DOUBLE_VALUE(xreg, shift_left, shift_right, xmax, xinvert) \
        ((unsigned long)&(struct soc_mixer_control) \
        {.reg = xreg, .rreg = xreg, .shift = shift_left, \
        .rshift = shift_right, .max = xmax, .platform_max = xmax, \
        .invert = xinvert})
#define SOC_SINGLE_VALUE(xreg, xshift, xmax, xinvert) \
        SOC_DOUBLE_VALUE(xreg, xshift, xshift, xmax, xinvert)

5. codec中的struct snd_pcm_hw_params *params怎么来的
static int es8374_pcm_hw_params(struct snd_pcm_substream *substream,
			struct snd_pcm_hw_params *params,
			struct snd_soc_dai *dai)

6. static struct snd_soc_dai_ops es8374_ops 的 fmt,sysclk和mute是否是给starup和params调用的。
.startup = es8374_pcm_startup,				//nop
.hw_params = es8374_pcm_hw_params,			//
.set_fmt = es8374_set_dai_fmt,
.set_sysclk = es8374_set_dai_sysclk,
.digital_mute = es8374_mute,
7.传输的数据结构是否会少一位
8. 		/* Digital Interface */ 其中有2个名字
		SND_SOC_DAPM_AIF_OUT("I2S OUT", "I2S1 Capture",  1,
				SND_SOC_NOPM, 0, 0),
9. snd_soc_write 是对i2c设备中的寄存器进行操作，是否需要进行i2c读写封装
10. 在应用中对audio codec驱动的测试。使用库和命令还是库和测试程序。

11. #define module_param(name, type, perm)                \
    module_param_named(name, name, type, perm)

通过命令"modinfo -p ${modulename}"可以得知一个模块有哪些参数可以使用。
同时，对于已经加载到内核里的模块，它们的模块参数会列举在/sys/module/$ {modulename}/parameters/目录下面，
可以使用"echo -n ${value} > /sys/module/$ {modulename}/parameters/${parm}"这样的命令去修改。
https://blog.csdn.net/angle_birds/article/details/7975790
https://blog.csdn.net/Top_hxl_dq/article/details/74935893
