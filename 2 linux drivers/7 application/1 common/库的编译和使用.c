1. 静态库的生成
gcc -c func1.c
ar -r libfunc.a func1.o

2. 静态库的使用
gcc -o functest functest.c libfunc.a
注：libfunc.a库要放到-o之后，否则会找不到库中的函数

3. 动态库的生成
gcc -shared -fpic -o libfunc.so func1.c

4. 动态库的使用
gcc -o functest functest.c -lfunc
注：其会优先找libfunc.so库如果无法找到，则会查找libfunc.a库

5. 动态库和静态库的混合使用
gcc -o functest functest.c libfunc1.a -lfunc
