一 将dos文件格式转换为unix格式
用vim打开该sh文件，输入：
:set ff
回车，显示fileformat=dos，重新设置下文件格式：
:set ff=unix
保存退出:
:wq 
再执行，竟然可以了
