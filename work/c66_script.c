1. cat rcS
#! /bin/sh
#
# rcS           Call all S??* scripts in /etc/rcS.d in
#               numerical/alphabetical order.
#
# Version:      @(#)/etc/init.d/rcS  2.76  19-Apr-1999  miquels@cistron.nl
#
trap "" SIGHUP

PATH=/sbin:/bin:/usr/sbin:/usr/bin
runlevel=S
prevlevel=N
umask 022
export PATH runlevel prevlevel
LIB_DIR=/lib/modules
export LIB_DIR

#       Trap CTRL-C &c only in this shell so we can interrupt subprocesses.
#
trap ":" INT QUIT TSTP

mount -n /proc
mount -n -o remount,rw /
mount /tmp
mount /sys
mount /dev

udevstart

#for telnet
mkdir /dev/pts
mount -t devpts devpts /dev/pts


# If using networking, no harm enabling routing
echo "1" > /proc/sys/net/ipv4/ip_forward

# UPnP requires loopback (without this rvsip would crash on activate command)
ifconfig lo 127.0.0.1


HOSTNAME=`cat /proc/avalanche/env|grep HOSTNAME|cut -f2`
if [ -n "$HOSTNAME" ]; then
echo "HOSTNAME : $HOSTNAME "
hostname $HOSTNAME
fi


#mount basic mtd
mount -n /dev/mtdblock/5 /basic -t squashfs -o ro
mount -t jffs2 /dev/mtdblock/4 /config

if [ -d /config/etc ]; then
    for i in /etc/*; do
      if [ -e $i -a ! -e /config$i ]; then
        echo "copying $i to /config$i"
        (cd /config; tar cf - $i | tar xf -)
      fi
    done
else
    mkdir /config/etc
    (cp /etc /config/ -rf)
fi

mount --bind /config/etc /etc
chmod 777 /config -R
chmod 700 /config/etc -R
chmod 777 /lib/libc*
chmod 777 /lib/libm*

#run basic init script
if [ -x "/config/basictest.sh" ];then
 source /config/basictest.sh &
else
 source /basic/scripts/init.sh &
fi

2. /basic/scripts/init.sh
#! /bin/sh

#mount app partition
mount -n /dev/mtdblock/6 /app -t squashfs -o ro

#mkdir
mkdir -p /tmp/var/ipc

#inmod drivers
Bridge=1
Router=0
strConfigFile=/config/Network/General/Network.conf
#PCType=`grep "PCType" $strConfigFile | grep -v "grep" | cut -d= -f2`
if [ -f "/config/Network/General/Network.conf" ];then
        PCType=`/app/bin/inifile_wr r /config/Network/General/Network.conf "PC" "Type" "$Bridge"`
else
        PCType=`/app/bin/inifile_wr r /app/factory/Network/General/Network.conf "PC" "Type" "$Bridge"`
fi

if [ "$PCType" = "$Router" -a -f "/app/version.conf" ];then
        insmod /basic/drivers/cpmac.ko
        ifconfig eth0 0.0.0.1 up
else
        insmod /basic/drivers/eswitch.ko
        ifconfig esw0 0.0.0.1 up
        /app/bin/configtitanswitch rsvdmcastfwding  enable
fi


insmod /basic/drivers/misc.ko
Gtype=`cat /proc/misc/hwver | cut -d. -f8`
if [ $Gtype = "1" ];then
        /app/bin/configtitanswitch port 2 disable
        insmod /basic/drivers/rtl8367nb.ko
        mount --bind /app/resources/www/htdocs/css/config_G.css /app/resources/www/htdocs/css/config.css
fi

insmod /basic/drivers/glcd.ko


export LD_LIBRARY_PATH=/app/lib:/basic/lib

udevstart

#start network


if [ ! -f "/app/version.conf" ];then
        sh /basic/scripts/basic.sh &
else
        sh /app/scripts/app.sh  &
fi

sleep 3

3. /app/scripts/app.sh
# cat /app/scripts/app.sh
#! /bin/sh

#run tools
/app/scripts/tools.sh

#insmod drivers
/app/scripts/drivers.sh

#start lighttpd server
#/app/scripts/lighttpd.sh &

#start cfgd_server
#/app/bin/cfgd_server &

#run netconfig
#/app/scripts/netconfig.sh &

#run telnetd
#/usr/sbin/telnetd &

#run autop
#/app/scripts/autop.sh &

#run acgVoice
#sh /app/scripts/acgVoice.sh  &

#run phone"
#sh /app/scripts/phone.sh  &

#run sip
#sh /app/scripts/sip.sh  0 &
#sh /app/scripts/sip.sh  1 &
#sh /app/scripts/sip.sh  2 &
#sh /app/scripts/sip.sh  16 &

#run pmonitor"
sh /app/scripts/pmonitor.sh  &

#run snmp
#sh /app/scripts/snmp.sh  &

#run rcpe
#sh /app/scripts/rcpe.sh  &

#run netcat
#sh /app/scripts/netcast.sh  &

/app/scripts/dhcp_setup.sh
