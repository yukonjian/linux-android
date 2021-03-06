2.sed和grep配合

命令：sed -i s/yyyy/xxxx/g `grep yyyy -rl ./`

作用：将当前目录(包括子目录)中所有txt文件中的yyyy字符串替换为xxxx字符串。其中，

-i 表示操作的是文件，``括起来的grep命令，表示将grep命令的的结果作为操作文件。

s/yyyy/xxxx/表示查找yyyy并替换为xxxx，后面跟g表示一行中有多个yyyy的时候，都替换，而不是仅替换第一个

另外，如果不需要查找子目录，仅需要在当前目录替换，用sed命令就行了，命令如下：sed -i s/xxxx/yyyy/g ./*.txt

sed -i s/RL_MODELID_C62/RL_MODELID_C61/g `grep RL_MODELID_C62 -rl ./`

sed -i s/"RL_MODELID == RL_MODELID_C63"/"RL_MODELID == RL_MODELID_C63 || RL_MODELID == RL_MODELID_C62"/g `grep "RL_MODELID == RL_MODELID_C63" -rl ./`
