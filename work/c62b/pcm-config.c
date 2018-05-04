1. 复位pcm
/* PCM controller reset */
data = pcm_inw(RALINK_SYSCTL_BASE+0x34);
data |= 0x00000800;
pcm_outw(RALINK_SYSCTL_BASE+0x34,data);
data = pcm_inw(RALINK_SYSCTL_BASE+0x34);
data &= 0xFFFFF7FF;
pcm_outw(RALINK_SYSCTL_BASE+0x34,data);

11 PCM_RST PCM reset control
          1: Reset Assert
          0: Reset Deassert
2. 配置管脚模式
10000060 GPIO1_MODE GPIO1 purpose selection
7:6 I2S_MODE I2S GPIO mode
              3: ANTSEL[5:2]
              2: PCM
              1: GPIO
              0: I2S
3. 配置pcm
1) 10002000 GLB_CFG Global Config
18:16 TFF_THRES TXFIFO Threshold     //4
22:20 RFF_THRES RXFIFO Threshold    //4
30 DMA_EN DMA Enable                //1
31 PCM_EN PCM Enable                //1
3:0 CH_EN Channels 3 to 0 Tx and Rx Enable  //f
/* Set GLBCFG's threshold fields */
data = pcm_inw(PCM_GLBCFG);
data |= REGBIT(4, TFF_THRES);
data |= REGBIT(4, RFF_THRES);
data |= REGBIT(0x1, PCM_EN);
data |= REGBIT(0x1, DMA_EN);
data |= 0xf;  // Enable pcm channels
pcm_outw(PCM_GLBCFG, data);

2)10002004 PCM_CFG PCM configuration
27 EXT_FSYNC FSYNC is provided externally //0
26 LONG_SYNC FSYNC Mode                   //0
25 FSYNC_POL FSYNC Polarity               //1
