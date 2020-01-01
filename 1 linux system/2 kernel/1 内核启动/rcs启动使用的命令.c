1. mount
Mount a filesystem. Filesystem autodetection requires /proc.

        -a              Mount all filesystems in fstab
        -r              Read-only mount
        -w              Read-write mount (default)
        -t FSTYPE[,...] Filesystem type(s)
        -O OPT          Mount only filesystems with option OPT (-a only)

1.1 mount -a 是自动挂载 /etc/fstab 里面的东西。
1.2 mount -t proc proc /proc
1.3 mount -t tmpfs dev /dev
1.4 mount -t ramfs tmp /tmp
1.5 mount -t sys sys /sys
1.6 mount -r -t squashfs /dev/mtdblock5 /basic
1.7 mount --bind(mount -o bind)  olddir/ newdir/  #把newdir 作为olddird的一个镜像， 它们的内容完全1样。
2. shell判据
https://blog.csdn.net/tiantang_1986/article/details/78281432
if [ -e $i -a ! -e /config$i ];
//-e 判断是否存在
//-a 逻辑与
2. syslogd
BusyBox v1.20.0 (2019-05-14 16:17:55 CST) multi-call binary.
Usage: syslogd [OPTIONS]
System logging utility
        -n              Run in foreground
        -O FILE         Log to FILE (default:/var/log/messages)
        -l N            Log only messages more urgent than prio N (1-8)
        -S              Smaller output
        -s SIZE         Max size (KB) before rotation (default:200KB, 0=off)
        -b N            N rotated logs to keep (default:1, max=99, 0=purge)
        -R HOST[:PORT]  Log to IP or hostname on PORT (default PORT=514/UDP)
        -L              Log locally and via network (default is network only if -R)
        -D              Drop duplicates
        -C[size_kb]     Log to shared mem buffer (use logread to read it)
        -f FILE         Use FILE as config (default:/etc/syslog.conf)
例子：
syslogd -S -O /tmp/Messages -s 100 -b5
#include <syslog.h>
https://blog.csdn.net/qq_33348709/article/details/53068954
void syslog(int priority, const char *message, arguments...);
priority:
facility value（转自syslog.h头文件）：
/* facility codes */
#define LOG_KERN        (0<<3)  /* kernel messages */
#define LOG_USER        (1<<3)  /* random user-level messages */
#define LOG_MAIL        (2<<3)  /* mail system */
#define LOG_DAEMON      (3<<3)  /* system daemons */
#define LOG_AUTH        (4<<3)  /* security/authorization messages */
#define LOG_SYSLOG      (5<<3)  /* messages generated internally by syslogd */
#define LOG_LPR         (6<<3)  /* line printer subsystem */
#define LOG_NEWS        (7<<3)  /* network news subsystem */
#define LOG_UUCP        (8<<3)  /* UUCP subsystem */
#define LOG_CRON        (9<<3)  /* clock daemon */
#define LOG_AUTHPRIV    (10<<3) /* security/authorization messages (private) */
#define LOG_FTP         (11<<3) /* ftp daemon */
syslog(LOG_ERR|LOG_USER,"test - %m/n");   //控制转换符%m可用于插入与错误变量errno当前值对应的出错消息字符串

3. telnet
Usage: telnet [-8] [-E] [-L] [-S tos] [-a] [-c] [-d] [-e char] [-l user]
        [-n tracefile] [-b hostalias ] [-r]
        [host-name [port]]
例子：
telnet 192.168.25.133 22

3.1 telnetd
Usage: telnetd [OPTIONS]
Handle incoming telnet connections

        -l LOGIN        Exec LOGIN on connect
        -f ISSUE_FILE   Display ISSUE_FILE instead of /etc/issue
        -K              Close connection as soon as login exits
                        (normally wait until all programs close slave pty)
        -p PORT         Port to listen on
        -b ADDR[:PORT]  Address to bind to
        -F              Run in foreground
        -i              Inetd mode
http://blog.chinaunix.net/uid-24565138-id-2127568.html
busybox配置telnetd
https://blog.csdn.net/zuosifengli/article/details/7815717
例子：
/sbin/telnetd &
