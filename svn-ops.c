1. 查看特定N条记录的目录信息
svn log --limit(-l) N
svn log -l 3 -v  //添加-v可以看到修改的文件名
2. 查看某一个文件的版本修改信息
svn log A

3. 永久更换账号
删除目录 ~/.subversion/auth/ 下的所有文件。下一次操作svn时会提示你重新输入用户名和密码的。换成你想用的就可以了。然后系统默认会记录下来的。

4. 版本回退
svn up -r 版本号  //版本号不带r，只是回退当前版本，如果重新执行svn up，则又回到最新的版本

5. 查看修改
svn diff  //查看对于当前版本的修改
svn diff -r 版本号1:版本号2 //查看版本号1和版本号2的不同
svn diff; #什么都不加，会坚持本地代码和缓存在本地.svn目录下的信息的不同;
svn diff -r 3;  #比较你的本地代码和版本号为3的所有文件的不同;

6，修改过的东西没有递交(commit)

这种情况下revert会取消之前的修改

用法：#svn revert [-R] xxx_file_dir
7. 版本回退
svn up -r 版本号
svn up -r 2101

8. 取消add的添加
svn revert --recursive（-r） example_folder
example_folder就已经添加的文件夹的名称
