example# syslogd --help
BusyBox v1.20.0 (2019-01-16 17:22:45 CST) multi-call binary.

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

#

syslogd -S -O /tmp/Messages -s 100 -b5
