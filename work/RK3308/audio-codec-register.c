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

ACODEC_ALC_DIG_CONX
When configure ACODEC_ALC_DIG_CONx, user should add a offset address to correspond channel:
add offset 0x000 for left channel ALC1,
add offset 0x040 for right channel ALC2,
add offset 0x0c0 for left channel ALC3,
add offset 0x100 for right channel ALC4,
add offset 0x180 for left channel ALC5,
add offset 0x1c0 for right channel ALC6,
add offset 0x240 for left channel ALC7,
add offset 0x280 for right channel ALC8.
ACODEC_ALC_DIG_CON0
GAIN_ATT_METHOD[6]: 选择gain attack(增益启动)的方法（normal，jack） ?
CTRL_GEN_METHOD[5:4]: 控制信号的产生选择（normal, jack）
AGC_HOLD_TIME[3:0]: AGC的保持时间，在增益增加到正常模式

ACODEC_ALC_DIG_CON1
DECAY_TIME[7:4]: 增益上升的衰减时间
ATTACK_TIME[3:0]: 增益下降的启动时间

ACODEC_ALC_DIG_CON2
AGC_MODE[7]: AGC的模式选择
AGC_ZERO_CRO_EN[6]: AGC过0使能
LOW_AMPLITUDE_RECOVERY[5]: 低振幅改善
FAST_DEC_CTRL[4]: 当振幅达到87.5%，则快速降低信号
GC_NOISE_GATE_EN[3]: AGC噪声阀值使能
AGC_NOISE_GATE_THRESHOLD[2:0]: AGC噪声阀值的值

ACODEC_ALC_DIG_CON3
LEFT_CHANNEL_PGA_ZERO_CRO_EN[5]: 左通道的PGA过0使能
LEFT_CHANNEL_PGA_GAIN[4:0]: 左通道的PGA增益

ACODEC_ALC_DIG_CON4
SLOW_CLOCK_EN[3]: 低速时钟使能，用于过0超时
APPROXIMATE_RATE[2:0]: 采样频率选择

ACODEC_ALC_DIG_CON5
LOW_8_BITS_AGC_MAX[7:0]: AGC的最大值（低8位）

ACODEC_ALC_DIG_CON6
HIGH_8_BITS_AGC_MAX[7:0]: AGC的最大值（高8位）

ACODEC_ALC_DIG_CON7
LOW_8_BITS_AGC_MIN[7:0]: AGC的最小值（低8位）

ACODEC_ALC_DIG_CON8
HIGH_8_BITS_AGC_MAX[7:0]: AGC的最小值（高8位）

ACODEC_ALC_DIG_CON9
AGC_FUNCTION_SELECT[6]: AGC功能使能
MAX_GAIN_PGA[5:4]: PGA最大的增益
MIN_GAIN_PGA[2:0]: PGA最小的增益

ACODEC_ALC_DIG_CON12
AGC_GAIN_VALUE[4:0]: 显示当前AGC的gain值（RO）

/*****************************************************
When configure ACODEC_ADC_ANA_CONx, user should add a offset address to correspond channel:
add offset 0x000 for left_0(ADC1) and right_0(ADC2) channel,
add offset 0x040 for left_1(ADC3) and right_1(ADC4) channel,
add offset 0x080 for left_2(ADC5) and right_2(ADC6) channel,
add offset 0x0c0 for left_3(ADC7) and right_3(ADC8) channel.
ACODEC_ADC_ANA_CON0
ADC_CH2_MIC_MUTE[7]: adc mic的通道2静音
ADC_CH2_MIC_INIT[6]: adc mic的通道2初始化
ADC_CH2_MIC_EN[5]: adc mic的通道2使能
ADC_CH2_BUF_REF_EN[4]: adc mic的通道2的参考电压buffer使能
ADC_CH2_MIC_MUTE[3]: adc mic的通道1静音
ADC_CH2_MIC_INIT[2]: adc mic的通道1初始化
ADC_CH2_MIC_EN[1]: adc mic的通道1使能
ADC_CH2_BUF_REF_EN[0]: adc mic的通道1的参考电压buffer使能

ACODEC_ADC_ANA_CON1
ADC_CH2_MIC_GAIN[5:4]: adc mic的通道2增益设置
ADC_CH2_MIC_GAIN[1:0]: adc mic的通道1增益设置
