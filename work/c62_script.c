1. c62串口接线是一致的，不需要TX和RX线不需要交叉。波特率为：115200
2. c62运行脚本
////////////////////////////////////////////////////////////////////////////////
cat rcS
#!/bin/sh
#
#       system startup script
#
#       (C) 2007 emlix GmbH <www.emlix.com>
#

#. /etc/system.conf

# enable /proc fs
echo "Mounting filesystems ..."
export PATH=/sbin:/bin:$PATH
export HOME=/root
export TERM=linux
mount /proc
mount /tmp
#mount /dev

# mount other fs or use mount -a
mount /dev/pts
mount /sys
#mount /proc/bus/usb

# set Clock
#hwclock --hctosys


# starting network
ifconfig eth0 0.0.0.1 up
ifconfig lo 127.0.0.1


hostname R51

mount -n /dev/mtdblock5 /basic -t squashfs -o ro
mount -t jffs2 /dev/mtdblock4 /config

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

#run basic init script
if [ -x "/config/basictest.sh" ];then
 source /config/basictest.sh &
else
 source /basic/scripts/init.sh &
fi
////////////////////////////////////////////////////////////////////////////////
cat /basic/scripts/init.sh
#! /bin/sh

#mount app partition
mount -n /dev/mtdblock6 /app -t squashfs -o ro

#mkdir
mkdir -p /tmp/var/ipc


export LD_LIBRARY_PATH=/app/lib:/basic/lib

#udevstart

#start network


if [ ! -f "/app/version.conf" ];then
        sh /basic/scripts/basic.sh &
else
        sh /app/scripts/app.sh  &
fi

sleep 3
# cat
////////////////////////////////////////////////////////////////////////////////
# cat /app/scripts/app.sh
#! /bin/sh
ulimit -s 4096

#run tools
/app/scripts/tools.sh

#insmod drivers
/app/scripts/drivers.sh

/app/bin/cfgactive

#cp web config
cp -f /app/config/web/group /etc

/app/scripts/qos.sh

/app/scripts/openvpn.sh

#/app/scripts/vlan_QOS_check.sh
/app/scripts/vlan_check.sh

#run pmonitor"
sh /app/scripts/pmonitor.sh  &
#
////////////////////////////////////////////////////////////////////////////////
echo "----"
export LD_LIBRARY_PATH='/app/lib:/basic/lib/'
NetConfigFile=/config/Network/General/Network.conf
#PCType value
Router=0
Bridge=1

#PCType=`grep PCType $NetConfigFile | cut -d= -f2`
PCType=`/app/bin/inifile_wr r /config/Network/General/Network.conf "PC" "Type" "$Bridge"`
echo "PCType=$PCType"

#default to diable ROUTER
if [ "$PCType" = "$Router" ]
then :
else
        PCType=$Bridge
fi
echo "PCType=$PCType"

LanVlanEnable=`grep "LanVlanEnable" $NetConfigFile | cut -d "=" -f2`
echo "LanVlanEnable:$LanVlanEnable"
if [ -z $LanVlanEnable ];then
        LanVlanEnable=0
fi

LanVid=`grep "LanVid" $NetConfigFile | cut -d "=" -f2`
echo "LanVid:$LanVid"
if [ -z $LanVid ];then
        LanVid=1
fi

LanPriority=`grep "LanPriority" $NetConfigFile | cut -d "=" -f2`
echo "LanPriority:$LanPriority"
if [ -z $LanPriority ];then
        LanPriority=0
fi

PcVlanEnable=`grep "PcVlanEnable" $NetConfigFile | cut -d "=" -f2`
echo "PcVlanEnable:$PcVlanEnable"
if [ -z $PcVlanEnable ];then
        PcVlanEnable=0
fi

PcVid=`grep "PcVid" $NetConfigFile | cut -d "=" -f2`
echo "PcVid:$PcVid"
if [ -z $PcVid ];then
        PcVid=1
fi

PcPriority=`grep "PcPriority" $NetConfigFile | cut -d "=" -f2`
echo "PcPriority:$PcPriority"
if [ -z $PcPriority ];then
        PcPriority=0
fi

        if [ "$LanVlanEnable" -eq "1" ] && [ "$PcVlanEnable" -eq "1" ]
        then
          echo "start set vlan 1"
          /app/bin/configtitanswitch config P1VID $PcVid
          /app/bin/configtitanswitch priority port1 $PcPriority
          /app/bin/configtitanswitch config P3VID $LanVid
          /app/bin/configtitanswitch priority port3 $LanPriority
          /app/bin/configtitanswitch enable port1
          /app/bin/configtitanswitch enable port3
        elif [ "$LanVlanEnable" -eq "1" ] && [ "$PcVlanEnable" -eq "0" ]
        then
                echo "set route vlan start"
                interface="eth0"
            /sbin/ifconfig $interface 0.0.0.0 up
            /sbin/vconfig add $interface $LanVid
            /sbin/ifconfig $interface.$LanVid 0.0.0.1 up
            /sbin/vconfig set_egress_map "$interface.$LanVid" 0 $LanPriority
        fi
