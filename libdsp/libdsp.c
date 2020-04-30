1. libdsp相关的文档，在git libdsp\doc目录下
2. dsp_mspd_const.h里定义命令码的宏

1、dsp_chan_update_rxtx_gain->dsp_chan_update_dgain_msg把命令和参数放入消息队列。
2、dsp_cmdmsg_proc 取出消息，
    case MIRO_MSG_UPDATE_DGAIN_CMD:
      dsp_chan_update_dgain(构造发给dsp进程的命令报文，并挂到发送队列)
     break；

3. 设置dsp的打印级别
libdsp/source/driver/dsp/dsp_bootload.c

dsp_set_debug_level(pDsp->usDspNo,0, 0, 0);
//dsp_set_debug_level(pDsp->usDspNo,0, 0, 0);
dsp_set_debug_level(pDsp->usDspNo,2, 0, 0);
2级别打印最多，0级别打印最少
