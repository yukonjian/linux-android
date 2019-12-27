Linux awk命令详解
https://www.cnblogs.com/ftl1012/p/9250541.html

1. 使用方法
awk '{pattern + action}' {filenames}
变量如下：可以在print中使用
ARGC               命令行参数个数
ARGV               命令行参数排列
ENVIRON            支持队列中系统环境变量的使用
FILENAME           awk浏览的文件名
FNR                浏览文件的记录数
FS                 设置输入域分隔符，等价于命令行 -F选项
NF                 浏览记录的域的个数
NR                 已读的记录数
OFS                输出域分隔符
ORS                输出记录分隔符
RS                 控制记录分隔符
$0变量是指整条记录。$1表示当前行的第一个域,$2表示当前行的第二个域,......以此类推。
$NF是number finally,表示最后一列的信息，跟变量NF是有区别的，变量NF统计的是每行列的总数

2. sample
awk -F ':' '{print $2}' ./file.c
":" 和':'效果一样
" " 匹配空格是连续的多个空格算一个
