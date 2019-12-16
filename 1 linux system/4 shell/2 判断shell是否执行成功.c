shell脚本中判断上一个命令是否执行成功
shell脚本中判断上一个命令是否执行成功

shell中使用符号“$?”来显示上一条命令执行的返回值，如果为0则代表执行成功，其他表示失败。
结合if-else语句实现判断上一个命令是否执行成功。

示例如下：
if [ $? -ne 0 ]; then
    echo "failed"
else
    echo "succeed"
fi

或者：
if [ $? -eq 0 ]; then
     echo "succeed"
else
     echo "failed"
fi
另外
shell中的比较符号如下：

-eq 	等于
-ne	不等于
-gt	大于
-lt	小于
-ge	大于等于
-le	小于等于
