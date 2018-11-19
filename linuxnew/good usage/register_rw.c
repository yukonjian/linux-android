int snd_soc_update_bits(struct snd_soc_codec *codec, unsigned short reg,
				unsigned int mask, unsigned int value)
{
	bool change;
	unsigned int old, new;
	unsigned int ret;

	if (codec->using_regmap) {
		ret = regmap_update_bits_check(codec->control_data, reg,
					       mask, value, &change);
	} else {
		ret = snd_soc_read(codec, reg);
		if (ret < 0)
			return ret;

		old = ret;
		new = (old & ~mask) | (value & mask);
		change = old != new;
		if (change)
			ret = snd_soc_write(codec, reg, new);
	}

	if (ret < 0)
		return ret;

	return change;
}

snd_soc_update_bits(codec, SUNXI_MIC1G_MICBIAS_CTR, (1<<MMICBIASEN), (1<<MMICBIASEN));
#define SUNXI_MIC1G_MICBIAS_CTR	(SUNXI_PR_CFG + 0x0B)
/* SUNXI_MIC1G_MICBIAS_CTR:0x0B */
#define HMICBIASEN		7
#define MMICBIASEN		6
#define HMICBIASMODE		5
#define MIC2_SS			4
#define MIC1_AMPEN		3
#define MIC1_BOOST		0
