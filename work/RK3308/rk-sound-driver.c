1. machine
rockchip_multicodecs.c	soc\rockchip
vad-sound {
	status = "okay";
	compatible = "rockchip,multicodecs-card";
	rockchip,card-name = "rockchip,rk3308-vad";
	rockchip,cpu = <&pdm_i2s_dais>;
	rockchip,codec = <&acodec>, <&vad>;
};
pdm_i2s_dais: pdm-i2s-dais {
	status = "okay";
	compatible = "rockchip,rk3308-multi-dais", "rockchip,multi-dais";
	dais = <&pdm_8ch>, <&i2s_8ch_2>;
	capture,channel-mapping = <6 2>;
	playback,channel-mapping = <0 2>;
	bitclock-inversion = <1 0>;
};

pdm_8ch: pdm@ff380000 {
	compatible = "rockchip,rk3308-pdm", "rockchip,pdm";
	reg = <0x0 0xff380000 0x0 0x1000>;
	clocks = <&cru SCLK_PDM>, <&cru HCLK_PDM>;
	clock-names = "pdm_clk", "pdm_hclk";
	dmas = <&dmac1 12>;
	dma-names = "rx";
	resets = <&cru SRST_PDM_M>;
	reset-names = "pdm-m";
	pinctrl-names = "default";
	pinctrl-0 = <&pdm_m2_clk
		     &pdm_m2_sdi0
		     &pdm_m2_sdi1
		     &pdm_m2_sdi2
		     &pdm_m2_sdi3>;
	status = "disabled";
};
&pdm_8ch {
status = "okay";
#sound-dai-cells = <0>;
rockchip,no-dmaengine;
pinctrl-names = "default";
pinctrl-0 = <&pdm_m2_clk
	     &pdm_m2_clkm
	     &pdm_m2_sdi0
	     &pdm_m2_sdi1
	     &pdm_m2_sdi2
	     &pdm_m2_sdi3>;
};
/*
acodec_sound: acodec-sound {
	compatible = "rockchip,multicodecs-card";
	rockchip,card-name = "rockchip,rk3308-acodec";
	rockchip,codec-hp-det;
	rockchip,mclk-fs = <256>;
	rockchip,cpu = <&i2s_8ch_2>;
	rockchip,codec = <&acodec>;
};*/
i2s_8ch_2: i2s@ff320000 {
	compatible = "rockchip,rk3308-i2s-tdm";
	reg = <0x0 0xff320000 0x0 0x1000>;
	interrupts = <GIC_SPI 50 IRQ_TYPE_LEVEL_HIGH>;
	clocks = <&cru SCLK_I2S2_8CH_TX>, <&cru SCLK_I2S2_8CH_RX>, <&cru HCLK_I2S2_8CH>,
		 <&cru SCLK_I2S2_8CH_TX_SRC>,
		 <&cru SCLK_I2S2_8CH_RX_SRC>,
		 <&cru PLL_VPLL0>,
		 <&cru PLL_VPLL1>;
	clock-names = "mclk_tx", "mclk_rx", "hclk",
		      "mclk_tx_src", "mclk_rx_src",
		      "mclk_root0", "mclk_root1";
	dmas = <&dmac1 4>, <&dmac1 5>;
	dma-names = "tx", "rx";
	resets = <&cru SRST_I2S2_8CH_TX_M>, <&cru SRST_I2S2_8CH_RX_M>;
	reset-names = "tx-m", "rx-m";
	rockchip,cru = <&cru>;
	rockchip,mclk-calibrate;
	status = "disabled";
};
acodec: acodec@ff560000 {
	compatible = "rockchip,rk3308-codec";
	reg = <0x0 0xff560000 0x0 0x10000>;
	rockchip,grf = <&grf>;
	interrupts = <GIC_SPI 114 IRQ_TYPE_LEVEL_HIGH>;
	clocks = <&cru PCLK_ACODEC>,
		 <&cru SCLK_I2S2_8CH_TX_OUT>,
		 <&cru SCLK_I2S2_8CH_RX_OUT>;
	clock-names = "acodec", "mclk_tx", "mclk_rx";
	resets = <&cru SRST_ACODEC_P>;
	reset-names = "acodec-reset";
	status = "disabled";
};
&acodec {
	status = "okay";

	rockchip,no-deep-low-power;
	rockchip,loopback-grp = <0>;
	hp-ctl-gpios = <&gpio0 RK_PA1 GPIO_ACTIVE_HIGH>;
	spk-ctl-gpios = <&gpio0 RK_PA5 GPIO_ACTIVE_HIGH>;
};
&i2s_8ch_2 {
status = "okay";
};

vad: vad@ff3c0000 {
	compatible = "rockchip,rk3308-vad", "rockchip,vad";
	reg = <0x0 0xff3c0000 0x0 0x10000>, <0x0 0xfff88000 0x0 0x38000>;
	reg-names = "vad", "vad-memory";
	clocks = <&cru HCLK_VAD>;
	clock-names = "hclk";
	interrupts = <GIC_SPI 57 IRQ_TYPE_LEVEL_HIGH>;
	rockchip,audio-src = <0>;
	rockchip,det-channel = <0>;
	rockchip,mode = <0>;
	status = "disabled";
};
&vad {
	status = "okay";
	rockchip,audio-src = <&pdm_8ch>;
	rockchip,det-channel = <0>;
	rockchip,mode = <1>;
	rockchip,buffer-time-ms = <200>;
	#sound-dai-cells = <0>;
};
2. codec
rk3308_codec.c	sound\soc\codecs

3. platform
rockchip_multi_dais.c	sound\soc\rockchip






设备树资料
https://blog.csdn.net/machiner1/article/details/47805069
https://elinux.org/
https://cloud.tencent.com/developer/ask/178043
