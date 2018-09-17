1. 查看卡的信息
cat /proc/asound/cards
2. tinyalsa路径
/external/tinyalsa
3. tinycap录音
Usage: tinycap file.wav [-D card] [-d device] [-c channels] [-r rate] [-b bits] [-p period_size] [-n n_periods]
note: 在使用 file.wav 要放在最前面。
4. tinyplay播放
Usage: tinyplay file.wav [-D card] [-d device] [-p period_size] [-n n_periods]
5. tinymix查看混音
tinymix
6. tinypcminfo
Usage: tinypcminfo -D card -d device
