1. 驱动加载调用
[CODEC_RK3308] FUN:rk3308_platform_probe; LINE:3886;
[CODEC_RK3308] FUN:rk3308_probe; LINE:3280;
[CODEC_RK3308] FUN:rk3308_set_dai_fmt; LINE:846;

2. play运行调用
[  860.467392] [CODEC_RK3308] FUN:rk3308_hw_params; LINE:2945;
[  860.468684] [CODEC_RK3308] FUN:rk3308_mute_stream; LINE:1090;
[  860.675268] [CODEC_RK3308] FUN:rk3308_pcm_trigger; LINE:3010;
[  865.674949] [CODEC_RK3308] FUN:rk3308_pcm_trigger; LINE:3010;
[  865.675316] [CODEC_RK3308] FUN:rk3308_mute_stream; LINE:1090;
[  865.677644] [CODEC_RK3308] FUN:rk3308_pcm_shutdown; LINE:3055;

3. record运行调用
[ 1624.614462] [CODEC_RK3308] FUN:rk3308_hw_params; LINE:2945;
[ 1624.615855] [CODEC_RK3308] FUN:rk3308_mute_stream; LINE:1090;
[ 1624.625873] [CODEC_RK3308] FUN:rk3308_pcm_trigger; LINE:3010;
^CAborted by signal Interrupt...
[ 1637.498704] [CODEC_RK3308] FUN:rk3308_pcm_trigger; LINE:3010;
[ 1637.499068] [CODEC_RK$ 3308] FUN:rk3308_mute_stream; LINE:1090;
[ 1637.499282] [CODEC_RK3308] FUN:rk3308_pcm_shutdown; LINE:3055;
