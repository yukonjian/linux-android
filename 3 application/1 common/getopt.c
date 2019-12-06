linux下getopt函数的使用
https://www.cnblogs.com/chenliyang/p/6633739.html

头文件：
#include<getopt.h>
函数原型：
extern char *optarg;         /*系统声明的全局变量 */
extern int optind, opterr, optopt;
int getopt(int argc, char * const argv[], const char * optstring);
getopt是用来解析命令行选项参数的，但是只能解析短选项: -d 100,不能解析长选项：--prefix
参数：
argc：main()函数传递过来的参数的个数
argv：main()函数传递过来的参数的字符串指针数组
optstring：选项字符串，告知 getopt()可以处理哪个选项以及哪个选项需要参数
返回：
如果选项成功找到，返回选项字母；如果所有命令行选项都解析完毕，返回 -1；如果遇到选项字符不在 optstring 中，
返回字符 '?'；如果遇到丢失参数，那么返回值依赖于 optstring 中第一个字符，如果第一个字符是 ':' 则返回':'，
否则返回'?'并提示出错误信息。

optstring:
char*optstring = “ab:c::”;
单个字符a         表示选项a没有参数            格式：-a即可，不加参数
单字符加冒号b:     表示选项b有且必须加参数      格式：-b 100或-b100,但-b=100错
单字符加2冒号c::   表示选项c可以有，也可以无     格式：-c200，其它格式错误

全局变量:
optarg —— 指向当前选项参数(如果有)的指针。
optind —— 再次调用 getopt() 时的下一个 argv指针的索引。
optopt —— 无法识别的选项(不在optstring中的选项)。
opterr ­—— 如果不希望getopt()打印出错信息，则只要将全域变量opterr设为0即可。

例子：
int opt;  /* 一定要用int型;如果是char则不会等于 -1 */
char *string = "t:p:h";
while ((opt = getopt(argc, argv, string)) != -1) {
	printf("opt = %c\t\t", opt);
	printf("optarg = %s\t\t",optarg);
	printf("optind = %d\t\t",optind);
	printf("argv[optind] = %s\n",argv[optind]);
	switch (opt) {
	case 't':
		test_num = atoi(optarg);
		printf("test_num:%d;\n", test_num);
		break;
	case 'p':
		param = atoi(optarg);
		printf("param:%d;\n", param);
		break;
	case 'h':
		printf("printf help;\n");
		usage();
		return 0;
	case '?':
		printf("unknow cmd or no value;\n");
		usage();
		return -1;
	default:
		printf("Other instance;\n");
		usage();
		return -1;
	}
}
