1.DAPM : Dynamic Audio Power Management
2.Linux-ASoC驱动归纳总结：
https://blog.csdn.net/sunruichen/article/details/8568273
3.Linux ALSA声卡驱动之一：ALSA架构简介
https://blog.csdn.net/droidphone/article/details/6271122
3.ALSA主页
http://www.alsa-project.org/main/index.php/Main_Page
4.内核设备驱动层，ALSA提供了alsa-driver，同时在应用层，ALSA为我们提供了alsa-lib，
应用程序只要调用alsa-lib提供的API，即可以完成对底层音频硬件的控制。
5. PCM是英文Pulse-code modulation的缩写，中文译名是脉冲编码调制。
6.C0D0代表的是声卡0中的设备0，pcmC0D0c最后一个c代表capture，pcmC0D0p最后一个p代表playback，
这些都是alsa-driver中的命名规则。
7. DAI (Digital Audio Interfaces) :  AC97, I2S and PCM
8.线路输出line，指1千欧、2Vrms的信号，和CD机输出类似。
喇叭输出speaker，直接接到无源音箱，是大功率输出。
耳机输出phones，可以驱动耳机，为32欧的耳机，提供50mW左右的功率。
