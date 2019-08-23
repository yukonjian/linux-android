名称解析：
SNR：signal noise ratio (信躁比)
ALC: Automatic Level Control (自动电平控制，声音录制平滑)
HiFi：High Fidelity (高保真)
bist: Built-in Self-Test(内部自测);


寄存器解析：
1. ACODEC_GLB_CON：
ADC_BIST_RESET[7]: adc 自测模块复位
DAC_BIST_RESET[6]: dac 自测模块复位
ADC_MCLK_GATING[5]: adc 主时钟选通
DAC_MCLK_GATING[4]: dac 主时钟选通host 172.16.0.6
CODEC_ADC_DIGITAL_RST[2]: adc 数字部分复位
CODEC_DAC_DIGITAL_RST[1]: dac 数字部分复位
CODEC_SYSTEM_RST[0]: codec 系统复位

ACODEC_ADC_DIG_CONx
When configure ACODEC_ADC_DIG_CONx, user should add a offset address to correspond channel:
add offset 0x000 for left_0(ADC1) and right_0(ADC2) channel,
add offset 0x0c0 for left_1(ADC3) and right_1(ADC4) channel,
add offset 0x180 for left_2(ADC5) and right_2(ADC6) channel,
add offset 0x240 for left_3(ADC7) and right_3(ADC8) channel
1. ACODEC_ADC_DIG_CON1
ADC_I2S_LRC_POL[7]: adc i2s LRCK极性
ADC_I2S_VALID_LEN[6:5]: adc i2s 有效数据长度
ADC_I2S_MODE[4:3]: adc i2s 模式选择(i2s mode; pcm mode;)
ADC_I2S_SWAP[1]: adc i2s 左右声道交换
ADC_I2S_TYPE[0]: adc i2s 单声道和立体声选择
2. ACODEC_ADC_DIG_CON2
ADC_MODE_IO[5]: adc IO引脚的i2s主从选择
ADC_MODE[4]: adc 内部的i2s主从选择
ADC_I2S_FRAME_LEN[3:2]: adc i2s 帧(1/2Frame)的长度
ADC_I2S_RST[1]： adc i2s 复位
ADC_I2S_BIT_CLK_POL[0]: adc i2s 位时钟极性选择
3. ACODEC_ADC_DIG_CON3
ADC_LEFT_CHANNEL_BIST[3:2]: adc 左通道自测配置
ADC_RIGHT_CHANNEL_BIST[1:0]:  adc 右通道自测配置
4. ACODEC_ADC_DIG_CON4
HPF_DIS[2]: adc 使能高通滤波器
HPF_CUT_FREQ[1:0]: 高通滤波器的截止频率
5. ACODEC_ADC_DIG_CON7
Config_ADCL_DATA[5:4]: 当[1]不选择正常的通道，则由这里指定
Config_ADCR_DATA[3:2]: 当[0]不选择正常的通道，则由这里指定
ADCL_DATA_SEL[1]: ADCL的输入通道选择
ADCR_DATA_SEL[0]: ADCR的输入通道选择
