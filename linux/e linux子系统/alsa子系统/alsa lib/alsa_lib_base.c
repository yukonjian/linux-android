1. 下载网站
http://www.alsa-project.org/
2. arecord,aplay,amixer的使用
2.1 arecord
-D : 用于指定音频设备PCM 以hwx,x表示；第一个‘x’表示声卡号，第二个‘x’表示设备号；
-r : 采样频率
-f : 指定采样格式
-l : 列出所有的声卡和数字音频设备
arecord -D hw:7,0 -r 16000 -f S16_LE -c 2 /userdata/steven/8803.wav

2.2 aplay
-D : 用于指定音频设备PCM 以hwx,x表示；第一个‘x’表示声卡号，第二个‘x’表示设备号；
-r : 采样频率
-f : 指定采样格式
-l : 列出所有的声卡和数字音频设备
aplay -D hw:7,0 -r 16000 -f S16_LE -c 2 /userdata/steven/8803.wav
aplay -D hw:7,0 -r 48000 -f S16_LE -c 2 /userdata/steven/8803.wav
aplay -D plughw:7,0 -r 16000 -f S16_LE -c 2 ./tsts.wav
2.3 amixer
-c,--card N     select the card
-D,--device N   select the device, default 'default'

scontrols       show all mixer simple controls
scontents       show contents of all mixer simple controls (default command)
sset sID P      set contents for one mixer simple control
sget sID        get contents for one mixer simple control
controls        show all controls for given card
contents        show contents of all controls for given card
cset cID P      set control contents for one control
cget cID        get control contents for one control
sample:
得到一项设置:
amixer cget -c 7 numid=95,iface=PCM,name='PCM Slave Rate'
设置一项设置:
 amixer cset  numid=5,iface=MIXER,name='Line In Volume'  25

/////////////////////////////////////////////////////////////////////////////////
debug
/userdata/steven # aplay -l
**** List of PLAYBACK Hardware Devices ****
card 0: rockchiprk3308v [rockchip,rk3308-vad], device 0: dailink-multicodecs multicodec-0 []
  Subdevices: 0/1
  Subdevice #0: subdevice #0
card 1: rockchiprk3308p [rockchip,rk3308-pcm], device 0: dailink-multicodecs dummy_codec-0 []
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 7: Loopback [Loopback], device 0: Loopback PCM [Loopback PCM]
  Subdevices: 8/8
  Subdevice #0: subdevice #0
  Subdevice #1: subdevice #1
  Subdevice #2: subdevice #2
  Subdevice #3: subdevice #3
  Subdevice #4: subdevice #4
  Subdevice #5: subdevice #5
  Subdevice #6: subdevice #6
  Subdevice #7: subdevice #7
card 7: Loopback [Loopback], device 1: Loopback PCM [Loopback PCM]
  Subdevices: 8/8
  Subdevice #0: subdevice #0
  Subdevice #1: subdevice #1
  Subdevice #2: subdevice #2
  Subdevice #3: subdevice #3
  Subdevice #4: subdevice #4
  Subdevice #5: subdevice #5
  Subdevice #6: subdevice #6
  Subdevice #7: subdevice #7


numid=2,iface=PCM,name='PCM Notify'
numid=1,iface=PCM,name='PCM Rate Shift 100000'
numid=3,iface=PCM,name='PCM Slave Active'
numid=6,iface=PCM,name='PCM Slave Channels'
numid=4,iface=PCM,name='PCM Slave Format'
numid=5,iface=PCM,name='PCM Slave Rate'
numid=8,iface=PCM,name='PCM Notify',subdevice=1
numid=7,iface=PCM,name='PCM Rate Shift 100000',subdevice=1
numid=9,iface=PCM,name='PCM Slave Active',subdevice=1
numid=12,iface=PCM,name='PCM Slave Channels',subdevice=1
numid=10,iface=PCM,name='PCM Slave Format',subdevice=1
numid=11,iface=PCM,name='PCM Slave Rate',subdevice=1
/////////////////////////////////////////////////////////////////////////////////
/ # amixer controls
numid=52,iface=MIXER,name='Master Playback Volume'
numid=33,iface=MIXER,name='ADC ALC Group 0 Left Volume'
numid=34,iface=MIXER,name='ADC ALC Group 0 Right Volume'
numid=35,iface=MIXER,name='ADC ALC Group 1 Left Volume'
numid=36,iface=MIXER,name='ADC ALC Group 1 Right Volume'
numid=37,iface=MIXER,name='ADC ALC Group 2 Left Volume'
numid=38,iface=MIXER,name='ADC ALC Group 2 Right Volume'
numid=39,iface=MIXER,name='ADC ALC Group 3 Left Volume'
numid=40,iface=MIXER,name='ADC ALC Group 3 Right Volume'
numid=41,iface=MIXER,name='ADC Group 0 HPF Cut-off'
numid=42,iface=MIXER,name='ADC Group 1 HPF Cut-off'
numid=43,iface=MIXER,name='ADC Group 2 HPF Cut-off'
numid=44,iface=MIXER,name='ADC Group 3 HPF Cut-off'
numid=25,iface=MIXER,name='ADC MIC Group 0 Left Volume'
numid=26,iface=MIXER,name='ADC MIC Group 0 Right Volume'
numid=27,iface=MIXER,name='ADC MIC Group 1 Left Volume'
numid=28,iface=MIXER,name='ADC MIC Group 1 Right Volume'
numid=29,iface=MIXER,name='ADC MIC Group 2 Left Volume'
numid=30,iface=MIXER,name='ADC MIC Group 2 Right Volume'
numid=31,iface=MIXER,name='ADC MIC Group 3 Left Volume'
numid=32,iface=MIXER,name='ADC MIC Group 3 Right Volume'
numid=9,iface=MIXER,name='ALC AGC Group 0 Left Max Volume'
numid=17,iface=MIXER,name='ALC AGC Group 0 Left Min Volume'
numid=1,iface=MIXER,name='ALC AGC Group 0 Left Volume'
numid=10,iface=MIXER,name='ALC AGC Group 0 Right Max Volume'
numid=18,iface=MIXER,name='ALC AGC Group 0 Right Min Volume'
numid=2,iface=MIXER,name='ALC AGC Group 0 Right Volume'
numid=11,iface=MIXER,name='ALC AGC Group 1 Left Max Volume'
numid=19,iface=MIXER,name='ALC AGC Group 1 Left Min Volume'
numid=3,iface=MIXER,name='ALC AGC Group 1 Left Volume'
numid=12,iface=MIXER,name='ALC AGC Group 1 Right Max Volume'
numid=20,iface=MIXER,name='ALC AGC Group 1 Right Min Volume'
numid=4,iface=MIXER,name='ALC AGC Group 1 Right Volume'
numid=13,iface=MIXER,name='ALC AGC Group 2 Left Max Volume'
numid=21,iface=MIXER,name='ALC AGC Group 2 Left Min Volume'
numid=5,iface=MIXER,name='ALC AGC Group 2 Left Volume'
numid=14,iface=MIXER,name='ALC AGC Group 2 Right Max Volume'
numid=22,iface=MIXER,name='ALC AGC Group 2 Right Min Volume'
numid=6,iface=MIXER,name='ALC AGC Group 2 Right Volume'
numid=15,iface=MIXER,name='ALC AGC Group 3 Left Max Volume'
numid=23,iface=MIXER,name='ALC AGC Group 3 Left Min Volume'
numid=7,iface=MIXER,name='ALC AGC Group 3 Left Volume'
numid=16,iface=MIXER,name='ALC AGC Group 3 Right Max Volume'
numid=24,iface=MIXER,name='ALC AGC Group 3 Right Min Volume'
numid=8,iface=MIXER,name='ALC AGC Group 3 Right Volume'
numid=49,iface=MIXER,name='DAC HPMIX Left Volume'
numid=50,iface=MIXER,name='DAC HPMIX Right Volume'
numid=47,iface=MIXER,name='DAC HPOUT Left Volume'
numid=48,iface=MIXER,name='DAC HPOUT Right Volume'
numid=45,iface=MIXER,name='DAC LINEOUT Left Volume'
numid=46,iface=MIXER,name='DAC LINEOUT Right Volume'
numid=51,iface=MIXER,name='vad switch'
////////////////////////////////////////////////////////////////////////////////
Simple mixer control 'DAC HPMIX Left',0
  Capabilities: volume volume-joined
  Playback channels: Mono
  Capture channels: Mono
  Limits: 0 - 1
  Mono: 0 [0%] [-6.00dB]
Simple mixer control 'DAC HPMIX Right',0
  Capabilities: volume volume-joined
  Playback channels: Mono
  Capture channels: Mono
  Limits: 0 - 1no-hp-det
  Mono: 0 [0%] [-6.00dB]

amixer -c 7 cset numid=2,iface=PCM,name='PCM Notify' on
amixer -c 7 cget numid=2,iface=PCM,name='PCM Notify'

amixer cset numid=51,iface=MIXER,name='vad switch' on
arecord -D hw:7,0 -r 16000 -f S16_LE -c 1 /userdata/steven/8803.wav
numid=41,iface=MIXER,name='ADC Group 0 HPF Cut-off'

amixer -c 0 cset numid=41,iface=MIXER,name='ADC Group 3 HPF Cut-off' 2
amixer -c 0 cset numid=49,iface=MIXER,name='DAC HPMIX Left Volume' 1
amixer -c 0 cset numid=50,iface=MIXER,name='DAC HPMIX Right Volume' 1

numid=49,iface=MIXER,name='DAC HPMIX Left Volume'
  ; type=INTEGER,access=rw---R--,values=1,min=0,max=1,step=0
  : values=0
  | dBscale-min=-6.00dB,step=6.00dB,mute=0
numid=50,iface=MIXER,name='DAC HPMIX Right Volume'
  ; type=INTEGER,access=rw---R--,values=1,min=0,max=1,step=0
  : values=0
  | dBscale-min=-6.00dB,step=6.00dB,mute=0
