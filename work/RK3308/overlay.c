1.深入理解overlayfs（二）：使用与原理分析
https://blog.csdn.net/luckyapple1028/article/details/78075358

mount -t jffs2 /dev/mtdblock5 /app
mount -t overlay overlay -o lowerdir=lower1:lower2,upperdir=upper,workdir=work merge

mount -t overlay overlay -o lowerdir=config,upperdir=/
