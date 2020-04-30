
n66进入调试模式的方法是  touch /config/debug_mode，然后重启设备就可以了
进入调试模式后，/app和/basic下的所有文件都可以替换，但重启就恢复了

dsp调试修改
pConnParams->ucEcancel   = 0;//ucEcancel是命令0X8006是LEC的开关1开，0关；而0X80E5是AEC默认打开的；
  //设置增益
    pConnParams->GainVal = 0;//pVoiceParams->agc_target;    //GainVal参数其实没用
    //有效范围：-14~6optind
    //dsp_set_rxtx_gain((pVoiceParams->agc_recv ? pVoiceParams->agc_target : 0),
                        //(pVoiceParams->agc_send ? pVoiceParams->agc_target : 0));

    //开启噪声抑制功能，关闭tone音检测功能
    ///dsp_set_enable_ns(1);
    dsp_set_disable_tone_detect(1);

    //agc设置 1290行

    pConnParams->ucEcancel   = 0;//ucEcancel是命令0X8006，而0X80E5是默认打开的 // LEC  647行

    //打印优先级设置
    /home/steven/work/project/linux_driver/linux-driver/libdsp/dsp_bootload.c
    dsp_set_debug_level(pDsp->usDspNo,0, 0, 0);


cp /tmp/mount/dsp_dbg/softdsparm_h8_conf4  /tmp/dsp
cp /tmp/mount/dsp_dbg/libvoice.so /app/lib/libvoice.so
cp /tmp/mount/dsp_dbg/libdsp.so  /app/lib/libdsp.so

shell中先设置个环境变量
export LD_LIBRARY_PATH=/tmp/lib:/lib:/usr/lib:/app/lib:/basic/lib
cp /tmp/mount/upgrader /basic/bin/upgrader
/bin:/sbin:/usr/bin:/usr/sbin:/userdata:/userdata/bin:/data/bin:/data/bin/rk_pcba_test
/app/bin/vaMain -v dsp查dsp版本号，要先把正在执行的vaMain杀死
export PATH=$PATH:./

如果不知道是哪个程序，可以 执行
/app/scripts/killapps.sh 杀死所有程序，再执行
/app/scripts/pmonitor.sh &  启动所有程序

//测试效果
1. 双讲没削音；2双讲回声达；3单讲回声明显。
2

//版本调试
\\172.16.0.55\鼎信\研发\软件测试\话机-Test\N66\N66-2.66.6.0.73\rom固件下取2.66.6.0.73.src.tgz文件放到rk3308sdk/rockdev目录下
在sdk docker环境中运行./merge_rootfs.sh rockdev/2.66.6.0.73.src.tgz 将app和root.img融合生成最终的rootfs.img
以后的版本发布都会包含src.tgz文件，方便系统合入
