1. cut
cut是切割命令，参数-d表示按什么划分，参数-f表示截取哪些字段。
例如: env | grep "USER" | cut -d "=" -f 2;
env | grep "USER"执行结果为：USER=root
cut -d "=" -f 2   表示将其=号作为分隔符，选取其第2个字段，所有就是root
