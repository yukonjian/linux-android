linux错误码定义：
#define    EPIPE        32    /* Broken pipe */

1.播放pcm时，snd_pcm_lib_write() 返回 -EPIPE，为underrun问题(上层write慢了，底层没数据了)。
  播放时音频的时候会有-EPIPE的错误,因为驱动buffer没有数据可以丢给codec所致.
  就是上层给下面喂数据的速度慢了,底层不到充足的数据,所以给上层返回一个-EPIPE错误出来。


2.录制音频时，snd_pcm_lib_read() 返回 -EPIPE， 为overrun问题(上层读取慢了，底层buffer满了)。
  在录音的时候出现-EPIPE, ALSA的驱动一块专门用来存储录音数据的buffer,上层从驱动buffer搬运数据到应
用层，再存储起来就能得到我们需要的录音文件。
  一旦驱动的buffer满了,就会出现-EPIPE的错误,因为上层读录音buffer数据的速度太慢了,所以底层报一个-
EPIPE错误。
   
3.underrun/overrun解决对策   ]
 <1>.在播放的时候,如果会出现这种-EPIPE的错误,上层调整下发数据的数据,加快一点点!
 <2>.录音的时候出现这种错误,上层应该读得更快一点!可以提高任务的优先级来处理,也可以把驱动buffer扩大
一下,给系统更多一点的缓冲时间!
 
————————————————
版权声明：本文为CSDN博主「慢慢的燃烧」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/u010164190/article/details/93646949
