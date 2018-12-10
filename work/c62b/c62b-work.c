# cat /proc/mtd
dev:    size   erasesize  name
mtd0: 00800000 00001000 "ALL"
mtd1: 0001e000 00001000 "Bootloader"
mtd2: 00001000 00001000 "Config"
mtd3: 00001000 00001000 "Factory"
mtd4: 002d0000 00001000 "Kernel"
mtd5: 00500000 00001000 "rootfs_data"
mtd6: 00010000 00001000 "app"
# mount
rootfs on / type rootfs (rw)
proc on /proc type proc (rw,relatime)
none on /var type ramfs (rw,relatime)
none on /dev type ramfs (rw,relatime)
none on /etc type ramfs (rw,relatime)
none on /tmp type ramfs (rw,relatime)
none on /media type ramfs (rw,relatime)
none on /sys type sysfs (rw,relatime)
devpts on /dev/pts type devpts (rw,relatime,mode=600,ptmxmode=000)
/dev/mtdblock6 on /app type squashfs (ro,relatime)
/dev/mtdblock5 on /flash type jffs2 (rw,relatime)
/dev/mtdblock5 on /etc_ro type jffs2 (rw,relatime)
# cat /dev/mtd
/dev/mtd0       /dev/mtd2ro     /dev/mtd5       /dev/mtd7ro     /dev/mtdblock4
/dev/mtd0ro     /dev/mtd3       /dev/mtd5ro     /dev/mtdblock0  /dev/mtdblock5
/dev/mtd1       /dev/mtd3ro     /dev/mtd6       /dev/mtdblock1  /dev/mtdblock6
/dev/mtd1ro     /dev/mtd4       /dev/mtd6ro     /dev/mtdblock2  /dev/mtdblock7
/dev/mtd2       /dev/mtd4ro     /dev/mtd7       /dev/mtdblock3
# cat /dev/mtd6 > /tmp/image
# mount
rootfs on / type rootfs (rw)
proc on /proc type proc (rw,relatime)
none on /var type ramfs (rw,relatime)
none on /dev type ramfs (rw,relatime)
none on /etc type ramfs (rw,relatime)
none on /tmp type ramfs (rw,relatime)
none on /media type ramfs (rw,relatime)
none on /sys type sysfs (rw,relatime)
devpts on /dev/pts type devpts (rw,relatime,mode=600,ptmxmode=000)
/dev/mtdblock6 on /app type squashfs (ro,relatime)
/dev/mtdblock5 on /flash type jffs2 (rw,relatime)
/dev/mtdblock5 on /etc_ro type jffs2 (rw,relatime)
#

#R50 分区描述
# cat /proc/mtd
dev:    size   erasesize  name
mtd0: 00030000 00010000 "u-boot"
mtd1: 00010000 00010000 "u-bootenv"
mtd2: 00160000 00010000 "kernel"
mtd3: 00180000 00010000 "rootfs"
mtd4: 00060000 00010000 "config"
mtd5: 00020000 00010000 "basic"
mtd6: 00460000 00010000 "app"
mtd7: 00800000 00010000 "whole flash"
#
