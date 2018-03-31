1.查看文件夹的大小
du -h --max-depth=1 ./
-h 表示加，K,M,G
--max-depth 表示查看的深度
2.shell脚本
 #！/bin/sh
3.linux中copy软链接
 cp命令copy一个软链接时，copy的是软链接所对应的内容，而不是它本身。
# echo "1234567890" > test.txt
# ln -s test.txt test2.txt
# cp test2.txt test3.txt
test3.txt就是test.txt，而不是test2.txt 。

要直接cp软链就需要加-d参数
如：
# cp -d test2.txt test3.txt
