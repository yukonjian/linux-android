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
3. telnet
Usage: telnet [-8] [-E] [-L] [-S tos] [-a] [-c] [-d] [-e char] [-l user]
        [-n tracefile] [-b hostalias ] [-r]
        [host-name [port]]
例子：
telnet 192.168.25.133 22

telnetd
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
