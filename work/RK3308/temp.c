
[    1.613938] start multicodecs_probe........................................................
[    1.613967] [MULTI MACHIN] node name:bluetooth-sound; type:<NULL>; phandle:308; fun:printk_dev_nod_info; Line:206;
[    1.613980] [MULTI MACHIN] card.name:rockchip,rk3308-pcm;
[    1.614181] [MULTI MACHIN] node name:dummy-codec; type:<NULL>; phandle:138; fun:printk_dev_nod_info; Line:206;
[    1.614232] [MULTI MACHIN] node name:i2s; type:<NULL>; phandle:137; fun:printk_dev_nod_info; Line:206;
[    1.615314] rk-multicodecs bluetooth-sound: dummy_codec <-> ff350000.i2s mapping ok
[    1.616377] end multicodecs_probe........................................................

[    1.539767] start multicodecs_probe........................................................
[    1.539788] [MULTI MACHIN] node name:vad-sound; type:<NULL>; phandle:0; fun:printk_dev_nod_info; Line:206;
[    1.539799] [MULTI MACHIN] card.name:rockchip,rk3308-vad;
[    1.539873] [MULTI MACHIN] node name:acodec; type:<NULL>; phandle:136; fun:printk_dev_nod_info; Line:206;
[    1.539905] [MULTI MACHIN] node name:vad; type:<NULL>; phandle:150; fun:printk_dev_nod_info; Line:206;
[    1.540036] [MULTI MACHIN] node name:pdm-i2s-dais; type:<NULL>; phandle:149; fun:printk_dev_nod_info; Line:206;
[    1.550251] vendor storage:20160801 ret = 0
[    1.612168] rk-multicodecs vad-sound: multicodec <-> pdm-i2s-dais mapping ok
[    1.613550] end multicodecs_probe........................................................

[    1.539457] start multicodecs_probe........................................................
[    1.539491] rk-multicodecs bluetooth-sound: card: 0 has not been locked, re-probe again
[    1.539505] rk-multicodecs bluetooth-sound: check_lock_card failed: -517


struct snd_soc_dai_link {
const char *name;			/* Codec name */
	const char *cpu_name;
	struct device_node *cpu_of_node;
	const char *cpu_dai_name;
	const char *codec_name;
	struct device_node *codec_of_node;
	const char *codec_dai_name;
	const char *platform_name;
	struct device_node *platform_of_node;


[    1.534724] [BT_RFKILL]: Enter rfkill_rk_init
[    1.535316] [BT_RFKILL]: bluetooth_platdata_parse_dt: get property: uart_rts_gpios = 135.
[    1.535383] [BT_RFKILL]: bluetooth_platdata_parse_dt: get property: BT,power_gpio = 139.
[    1.535472] [BT_RFKILL]: bluetooth_platdata_parse_dt: get property: BT,wake_host_irq = 140.
[    1.535494] [BT_RFKILL]: bluetooth_platdata_parse_dt: clk_get failed!!!.
[    1.535635] [BT_RFKILL]: Request irq for bt wakeup host
[    1.535726] [BT_RFKILL]: ** disable irq
[    1.535984] [BT_RFKILL]: bt_default device registered.
[    1.536798] flash vendor_init_thread!
[    1.536830] flash vendor storage:20170308 ret = -1
[    1.539808] input: adc-keys as /devices/platform/adc-keys/input/input0
[    1.541502] rk_multicodecs_probe.........................12345651
[    1.541566] [multicodecs] of_nod name:vad-acodec-sound;
[    1.541735] link->platform_of_node name:i2s;
[    1.541777] rk-multicodecs vad-acodec-sound: ASoC: platform (null) not registered
[    1.542298] dhd_module_init: in Dongle Host Driver, version 1.579.77.41.2 (r

[    1.542478] [BT_RFKILL]: ** disable irq
[    1.542848] [BT_RFKILL]: bt_default device registered.
[    1.543907] flash vendor_init_thread!
[    1.543952] flash vendor storage:20170308 ret = -1
[    1.546175] vendor storage:20160801 ret = 0
[    1.547510] input: adc-keys as /devices/platform/adc-keys/input/input0
[    1.549764] rk_multicodecs_probe.........................12345651
[    1.549817] [multicodecs] of_nod name:vad-acodec-sound;
 Kernel command line: storagemedia=emmc androidboot.mode=emmc androidboot.slot_suffix= androidboot.serialno=c3d9b8674f4b94f6
 rootwait earlycon=uart8250,mmio32,0xff0c0000 swiotlb=1 console=ttyFIQ0,115200 root=PARTUUID=614e0000-0000 rootfstype=squashfs
 snd_aloop.index=7

root@e8d037608652:/home/project/kernel/drivers# grep "vendor_init_thread" ./ -nr
Binary file ./built-in.o matches
Binary file ./soc/built-in.o matches
Binary file ./soc/rockchip/sdmmc_vendor_storage.o matches
Binary file ./soc/rockchip/built-in.o matches
./soc/rockchip/flash_vendor_storage.c:294:static int vendor_init_thread(void *arg)
./soc/rockchip/flash_vendor_storage.c:312:      kthread_run(vendor_init_thread, (void *)NULL, "vendor_storage_init");
Binary file ./soc/rockchip/flash_vendor_storage.o matches
./soc/rockchip/sdmmc_vendor_storage.c:593:static int vendor_init_thread(void *arg)
./soc/rockchip/sdmmc_vendor_storage.c:617:      kthread_run(vendor_init_thread, (void *)NULL, "vendor_storage_init");
root@e8d037608652:/home/project/kernel/drivers#
root@e8d037608652:/home/project/kernel/drivers#
root@e8d037608652:/home/project/kernel/drivers#
[    1.563971] VFS: Mounted root (squashfs filesystem) readonly on device 179:4.
[    1.564967] devtmpfs: mounted

Part    Start LBA       End LBA         Name
        Attributes
        Type GUID
        Partition GUID
  1     0x00000200      0x000006ff      "uboot"
        attrs:  0x0000000000000000
        type:   f27c0000-0000-4848-8000-549e00000939
        guid:   46560000-0000-4271-8000-2e18000022aa
  2     0x00000700      0x0000077f      "trust"
        attrs:  0x0000000000000000
        type:   524b0000-0000-4964-8000-2ac7000037cc
        guid:   5e320000-0000-447a-8000-1a9300001657
  3     0x00000780      0x0000377f      "boot"
        attrs:  0x0000000000000000
        type:   f46a0000-0000-4d4a-8000-00a500007444
        guid:   dc2f0000-0000-4c7a-8000-636500003bcc
  4     0x00004780      0x0000777f      "rootfs"
        attrs:  0x0000000000000000
        type:   1f650000-0000-4c0f-8000-1c7e00005d68
        guid:   076c0000-0000-443a-8000-23d7000020d2
  5     0x00006780      0x00e8ffde      "userdata"
        attrs:  0x0000000000000000
        type:   1d6e0000-0000-4d2d-8000-669b00007402
        guid:   292d0000-0000-4265-8000-143100003b31
=>


  4     0x00004780      0x0000777f      "rootfs"
        attrs:  0x0000000000000000
        type:   2f550000-0000-475a-8000-34dc00002f17
        guid:   614e0000-0000-4b53-8000-1d28000054a9

=> part list spinor 1

Partition Map for SPINOR device 1  --   Partition Type: EFI

Part    Start LBA       End LBA         Name
        Attributes
        Type GUID
        Partition GUID
  1     0x00000200      0x000006ff      "uboot"
        attrs:  0x0000000000000000
        type:   516c0000-0000-4233-8000-303000001e69
        guid:   660e0000-0000-4112-8000-2bc400003594
  2     0x00000700      0x0000077f      "trust"
        attrs:  0x0000000000000000
        type:   4e2e0000-0000-4129-8000-4dbc00001b59
        guid:   fa6e0000-0000-426d-8000-58a800006f98
  3     0x00000780      0x0000377f      "boot"
        attrs:  0x0000000000000000
        type:   9a690000-0000-471e-8000-6d5900000272
        guid:   a0790000-0000-4f10-8000-59e000002349
  4     0x00004780      0x0000777f      "rootfs"
        attrs:  0x0000000000000000
        type:   bd100000-0000-4d02-8000-658e000074bd
        guid:   614e0000-0000-4b53-8000-1d28000054a9
  5     0x00006780      0x00007fde      "userdata"
        attrs:  0x0000000000000000
        type:   3d5b0000-0000-4a49-8000-4de300001841
        guid:   43250000-0000-4b74-8000-786d00000cd3
=>
printk(KERN_INFO "start kernel_init...\n");

内核传参解析
https://blog.csdn.net/funkunho/article/details/51967137

[  240.455716] INFO: task swapper/0:1 blocked for more than 120 seconds.
[  240.455772]       Not tainted 4.4.143 #18
[  240.455793] "echo 0 > /proc/sys/kernel/hung_task_timeout_secs" disables this message.
[  240.455815] swapper/0       D ffffff8008084dfc     0     1      0 0x00000000
[  240.455860] Call trace:
[  240.455917] [<ffffff8008084dfc>] __switch_to+0x84/0xa0
[  240.455957] [<ffffff8008609260>] __schedule+0x428/0x45c
[  240.455991] [<ffffff8008609308>] schedule+0x74/0x94
[  240.456023] [<ffffff800860b868>] schedule_timeout+0x28/0x178
[  240.456058] [<ffffff8008609d30>] wait_for_common+0xbc/0x134
[  240.456094] [<ffffff8008609dbc>] wait_for_completion+0x14/0x1c
[  240.456132] [<ffffff8008273b90>] drm_dev_wait+0x14/0x1c
[  240.456167] [<ffffff800885406c>] drm_misc_init+0x10/0x84
[  240.456200] [<ffffff8008083054>] do_one_initcall+0x70/0x178
[  240.456234] [<ffffff8008840e38>] kernel_init_freeable+0x1e4/0x1e8
[  240.456267] [<ffffff80086072dc>] kernel_init+0x1c/0x104
[  240.456313] [<ffffff8008082e80>] ret_from_fork+0x10/0x50
[  240.456339] Kernel panic - not syncing: hung_task: blocked tasks
[  240.554241] CPU: 1 PID: 30 Comm: khungtaskd Not tainted 4.4.143 #18
[  240.560509] Hardware name: Firefly RK3308 roc cc digital-pdm mic board (DT)

root@ee34521683f8:/home/project/kernel# grep "drm_misc_init" ./ -nr
./System.map:46804:ffffff8008854174 t drm_misc_init
./System.map:48381:ffffff800887cb60 t __initcall_drm_misc_init7s
./.tmp_System.map:46804:ffffff8008854174 t drm_misc_init
./.tmp_System.map:48381:ffffff800887cb60 t __initcall_drm_misc_init7s
Binary file ./drivers/char/virtd matches
Binary file ./drivers/char/built-in.o matches
Binary file ./drivers/char/virtdrm.o matches
Binary file ./drivers/built-in.o matches
Binary file ./vmlinux matches
Binary file ./vmlinux.o matches
Binary file ./.tmp_vmlinux2 matches
Binary file ./.tmp_vmlinux1 matches

<*> 8250/16550 and compatible serial support                                                                                | |
[ ]   Support 8250_core.* kernel options (DEPRECATED)                                                                       | |
[*]   Console on 8250/16550 and compatible serial port                                                                      | |
[*]   DMA support for 16550 compatible UART controllers                                                                     | |
(5)   Maximum number of 8250/16550 serial ports                                                                             | |
(5)   Number of 8250/16550 serial ports to register at runtime                                                              | |
[ ]   Extended 8250/16550 serial driver options                                                                             | |
<*> Support for Synopsys DesignWare 8250 quirks

[*] Enable TTY                                                                                                              | |
[ ]   Virtual terminal                                                                                                      | |
[*]   Unix98 PTY support                                                                                                    | |
[ ]     Support multiple instances of devpts                                                                                | |
[ ]   Legacy (BSD) PTY support                                                                                              | |
[ ]   Non-standard serial port support                                                                                      | |
< >   GSM MUX line discipline support (EXPERIMENTAL)                                                                        | |
< >   Trace data sink for MIPI P1149.7 cJTAG standard                                                                       | |
[*] /dev/mem virtual device support
<*> Hardware Random Number Generator Core support  --->

root@44a3cc29d55a:/home/project/u-boot# ls -lh ./u-boot.bin
-rw-r--r-- 1 root root 587K Aug 15 09:31 ./u-boot.bin


sip_smc_lastlog_request':
fiq_debugger_arm64.c:(.text+0x1e4c): mult

create boot.img...cp -a /home/project/kernel/zboot.img /home/project/rockdev/boot.img


/home/project/kernel && make ARCH=arm64 firefly-rk3308_linux_defconfig && make ARCH=arm64 rk3308-roc-cc-dmic-pdm_emmc.img -j12 && cd -

 g_part->hdr.ui_fw_tag:0x0;line:200;

 [    0.392281] start do_mount_root;
[    0.392426] end do_mount_root;ret=-6;
[    0.392451] VFS: Cannot open root device "mtdblock4" or unknown-block(0,0): error -6
[    0.392463] Please append a correct "root=" boot option; here are the available partitions:
[    0.392477] Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block(0,0)
[    0.744734] CPU: 3 PID: 1 Comm: swapper/0 Not tainted 4.4.143 #73
[    0.750824] Hardware name: Firefly RK3308 roc cc digital-pdm mic board (DT)
[    0.757784] Call trace:


pclk_audio 98303 KHz
Net:   Net Initialization Skipped
No ethernet found.
Hit any key to stop autoboot:  0
android_bootloader_boot_flow Could not find misc partition
get part misc fail -1
ANDROID: reboot reason: "(none)"
FDT load addr 0x10f00000 size 253 KiB
Booting kernel at 0x4080000 with fdt at 4506800...


## Booting Android Image at 0x04080000 ...
Kernel load addr 0x02080000 size 4629 KiB
## Flattened Device Tree blob at 04506800
   Booting using the fdt blob at 0x4506800
   Uncompressing Kernel Image ... OK
   Loading Device Tree to 000000000f501000, end 000000000f51436a ... OK
Adding bank: start=0x00200000, size=0x0fe00000

[    1.513730] Creating 8 MTD partitions on "sfc_nor":
[    1.513782] 0x000000000000-0x000000040000 : "loader"
[    1.514625] 0x000000040000-0x0000000e0000 : "uboot"
[    1.515362] 0x0000000e0000-0x0000000f0000 : "trust"
[    1.516071] 0x0000000f0000-0x0000006f0000 : "boot"
[    1.516800] 0x0000006f0000-0x0000009f0000 : "rootfs"
[    1.517541] 0x0000009f0000-0x000000af0000 : "config"
[    1.518274] 0x000000af0000-0x000000bf0000 : "basic"
[    1.518949] 0x000000bf0000-0x001000beffff : "app"

sfc_get 0x00003780 0x02000000 8
 sfc_get 0x00005780 0x02000000 8

 $ ifconfig eth0 up
[  201.042617] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: rk_vendor_read eth mac address failed (-1)
[  201.042739] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: generate random eth mac address: 1a:$ 89:96:17:f0:a6
[  201.042773] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: rk_vendor_write eth mac address failed (-1)
[  201.042811] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: mac address: 1a:89:96:17:f0:a6
[  201.042845] eth0: device MAC address 1a:89:96:17:f0:a6

$ [  203.047595] rk_gmac-dwmac ff4e0000.ethernet eth0: Link is Up - 100Mbps/Full - flow control rx/tx
ifconfig eth0 172.25.2.85
$

bin  dev  etc  lib  lib64  linuxrc  sbin
app  basic  bin  dev  etc  lib  lib64  linuxrc  mnt  proc  root  sbin  sys  tmp  userdata  usr  var


pack file size: 476353
crc = 0xbc38f57e
pack uboot.img success!
pack uboot okay! Input: ./u-boot.bin
out:rk3308_loader_v1.24.108.bin
fix opt:rk3308_loader_v1.24.108.bin
merge success(rk3308_loader_v1.24.108.bin)
/home/project/rkbin/tools/boot_merger --replace tools/rk_tools/ ./ /home/project/rkbin/RKBOOT/RK3308MINIALL.ini
pack loader okay! Input: /home/project/rkbin/RKBOOT/RK3308MINIALL.ini
/home/project/u-boot
out:trust.img
merge success(trust.img)
/home/project/rkbin/tools/trust_merger  --rsa 3 --size 64 1 --replace tools/rk_tools/ ./ /home/project/rkbin/RKTRUST/RK3308TRUST.ini
/home/project/u-boot
pack trust okay! Input: /home/project/rkbin/RKTRUST/RK3308TRUST.ini

Platform RK3308 is build OK, with exist .config
root@c4c5eeb41873:/home/project/u-boot#
root@c4c5eeb41873:/home/project/u-boot# make menuconfig
scripts/kconfig/mconf  Kconfig

pclk_audio 98303 KHz
Net:   Net Initialization Skipped
No ethernet found.
Hit any key to stop autoboot:  0
android_bootloader_boot_flow Could not find misc partition
get part misc fail -1
ANDROID: reboot reason: "(none)"
Error: Bad gzipped data
FDT load addr 0x10f00000 size 253 KiB
Booting kernel at 0x207f800 with fdt at 2453000...


## Booting Android Image at 0x0207f800 ...
Kernel load addr 0x02080000 size 3914 KiB
## Flattened Device Tree blob at 02453000
   Booting using the fdt blob at 0x2453000
   XIP Kernel Image ... OK
   Loading Device Tree to 000000000f542000, end 000000000f555205 ... OK
Adding bank: start=0x00200000, size=0x0fe00000

Starting kernel ...


"Synchronous Abort" handler, esr 0x02000000
* Relocate offset = 000000000f966000
* ELR(PC)    =   fffffffff2d9a00c
* LR         =   0000000000601edc
* SP         =   000000000f556c00


Kernel command line: storagemedia=nor androidboot.slot_suffix= androidboot.serialno=c3d9b8674f4b94f6  rootwait earlycon=uart8250,mmio32,0xff0c0000 swiotlb=1 console=ttyFIQ0,115200 root=/dev/mtdblock4 rootfstype=squashfs snd_aloop.index=7

Kernel command line: storagemedia=nor androidboot.slot_suffix= androidboot.serialno=c3d9b8674f4b94f6  rootwait earlycon=uart8250,mmio32,0xff0c0000 swiotlb=1 console=ttyFIQ0,115200 root=/dev/mtdblock4 rootfstype=squashfs snd_aloop.index=7

$ cat /proc/meminfo
MemTotal:         246980 kB
MemFree:          229180 kB
MemAvailable:     229048 kB
Buffers:            1080 kB
Cached:             2108 kB
SwapCached:            0 kB
Active:             2924 kB
Inactive:            412 kB
Active(anon):        204 kB
Inactive(anon):        0 kB
Active(file):       2720 kB
Inactive(file):      412 kB
Unevictable:           0 kB
Mlocked:               0 kB
SwapTotal:             0 kB
SwapFree:              0 kB
Dirty:                 0 kB
Writeback:             0 kB
AnonPages:           280 kB
Mapped:             1628 kB
Shmem:                 0 kB
Slab:               8336 kB
SReclaimable:       2548 kB
SUnreclaim:         5788 kB
KernelStack:        1360 kB
PageTables:           56 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:      123488 kB
Committed_AS:        452 kB
VmallocTotal:   258867136 kB
VmallocUsed:           0 kB
VmallocChunk:          0 kB
$
mem=262144K
MemTotal:         246980 kB

mem=262128K （-12）
MemTotal:         246980 kB

mem=262080K	 (-64)
MemTotal:         246980 kB

mem=261632K  (-512k)
MemTotal:         246980 kB

mem=259072K
MemTotal:         245952 kB

mem=260080K
MemTotal:         246960 kB

mem=260076K
MemTotal:         246956 kB

[    0.000000]     memory  : 0xffffffc000200000 - 0xffffffc010000000   (   254 MB)

bootargs:storagemedia=nor### main_loop: bootcmd="boot_android ${devtype} ${devnum};bootrkp;run distro_bootcmd;"


[    1.465192] rk3308-acodec ff560000.acodec: GPIO lookup for consumer hp-ctl
[    1.465233] rk3308-acodec ff560000.acodec: using device tree for GPIO lookup
[    1.465292] of_get_named_gpiod_flags: parsed 'hp-ctl-gpios' property of node '/acodec@ff560000[0]' - status (0)
[    1.465380] rk3308-acodec ff560000.acodec: GPIO lookup for consumer spk-ctl
[    1.465407] rk3308-acodec ff560000.acodec: using device tree for GPIO lookup
[    1.465456] of_get_named_gpiod_flags: parsed 'spk-ctl-gpios' property of node '/acodec@ff560000[0]' - status (0)
[    1.465516] rk3308-acodec ff560000.acodec: GPIO lookup for consumer pa-drv
[    1.465543] rk3308-acodec ff560000.acodec: using device tree for GPIO lookup
[    1.465572] of_get_named_gpiod_flags: can't parse 'pa-drv-gpios' property of node '/acodec@ff560000[0]'
[    1.465599] of_get_named_gpiod_flags: can't parse 'pa-drv-gpio' property of node '/acodec@ff560000[0]'
[    1.465678] rk3308-acodec ff560000.acodec: using lookup tables for GPIO lookup
[    1.465708] rk3308-acodec ff560000.acodec: lookup for GPIO pa-drv failed
[    1.465735] rk3308-acodec ff560000.acodec: Don't need pa-drv gpio
[    1.465784] rk3308-acodec ff560000.acodec: De-pop as much as possible

void reserve_memory_for_DSP(void)
{
	char boot_options[128] = {0};

	snprintf(boot_options, sizeof(boot_options), "mem=%lldK", gd->ram_size/1024 - 1024*2 - 20);
//	snprintf(boot_options, sizeof(boot_options), "mem=%lldK", gd->ram_size/1024);

	env_update("bootargs", boot_options);
}


$ cat /proc/meminfo
MemTotal:         253996 kB
MemFree:          242316 kB
MemAvailable:     241376 kB

$ cat /proc/meminfo
MemTotal:         254104 kB
MemFree:          243068 kB
MemAvailable:     242116 kB
Buffers:            1036 kB
Cached:             1556 kB

MemTotal:         253808 kB
MemFree:          241872 kB
MemAvailable:     241056 kB
Buffers:            1116 kB
Cached:             1720 kB

MemTotal:         253788 kB
MemFree:          242020 kB
MemAvailable:     241196 kB
Buffers:            1116 kB
Cached:             1720 kB
SwapCached:            0 kB

$ cat /sys/kernel/debug/regmap/ff320000.i2s/registers
00: 7200000f
04: 01c9800f
08: 00003f1f
0c: 00000000
10: 000f0010
14: 01f00000
18: XXXXXXXX
1c: 00000000
20: XXXXXXXX
28: 00000000
30: 00003eff
34: 00003eff
38: 00000307

$ cat /sys/kernel/debug/regmap/ff320000.i2s/registers
00: 7200000f
04: 01c9800f
08: 00003f1f
0c: 00000000
10: 010f0010
14: 01f00000
18: 00000000
1c: 00000002
20: 00000000
28: 00000000
30: 00003eff
34: 00003eff
38: 00000307

arecord -D hw:0,0 -r 16000 -f S16_LE -c 1  ./record.wav
aplay -D hw:0,0 -r 16000 -f S16_LE -c 2  ./tsts-16k.wav

[    0.507387] flash unique id initial snor init1
[    0.507404] sfc nor id: ef 40 18
[    0.507416] snor_init;g_spi_flash_info:c053ef08;
[    0.507630] flash unique id initial start
[    0.507654] flash unique id initial finished
[    0.507665] snor_init2;g_spi_flash_info:c053ef08;
[    0.507674] sfc_nor_mtd_init start1;
[    0.507685] sfc_nor_mtd_init1;g_spi_flash_info:c053ef08;
[    0.507695] sfc_nor_mtd_init1;g_spi_flash_info_back:c053ef08;
[    0.507705] sfc_nor_mtd_init start8;g_spi_flash_info:c053ef08;
[    0.507714] sfc_nor_mtd_init start9;
[    0.507722] sfc_nor_mtd_init 1;
[    0.507731] sfc_nor_mtd_init 2;
[    0.507856] sfc_nor_mtd_init 3;
[    0.508075] Creating 8 MTD partitions on "sfc_nor":
[    0.508095] 0x000000000000-0x0000000e0000 : "uboot"
[    0.509186] 0x0000000e0000-0x0000000f0000 : "manufacture"
[    0.510245] 0x0000000f0000-0x000000100000 : "reserver"
[    0.511341] 0x000000100000-0x000000700000 : "boot"
[    0.512421] 0x000000700000-0x000000a00000 : "rootfs"
[    0.513515] 0x000000a00000-0x000000b00000 : "config"
[    0.514610] 0x000000b00000-0x000000c00000 : "basic"
[    0.515686] 0x000000c00000-0x001000bfffff : "app"


[    0.219961] [<c0061ddd>] (unwind_backtrace) from [<c005f7bb>] (show_stack+0xb/0xc)
[    0.227726] [<c005f7bb>] (show_stack) from [<c016a8f3>] (dump_stack+0x5b/0x70)
[    0.235115] [<c016a8f3>] (dump_stack) from [<c006d1a1>] (warn_slowpath_common+0x55/0x7c)
[    0.243394] [<c006d1a1>] (warn_slowpath_common) from [<c006d221>] (warn_slowpath_null+0xf/0x14)
[    0.252287] [<c006d221>] (warn_slowpath_null) from [<c0065651>] (__arm_ioremap_pfn_caller+0x71/0x100)
[    0.261693] [<c0065651>] (__arm_ioremap_pfn_caller) from [<c00656fd>] (__arm_ioremap_caller+0x1d/0x24)
[    0.271229] [<c00656fd>] (__arm_ioremap_caller) from [<c0246069>] (sip_smc_request_share_mem+0x21/0x2c)
[    0.280844] [<c0246069>] (sip_smc_request_share_mem) from [<c024622d>] (sip_fiq_debugger_request_share_memory+0xd/0x14)
[    0.291874] [<c024622d>] (sip_fiq_debugger_request_share_memory) from [<c018f047>] (rk_serial_debug_init+0xab/0x274)
[    0.302633] [<c018f047>] (rk_serial_debug_init) from [<c04e52c3>] (rk_fiqdbg_probe+0xa7/0x1a0)
[    0.311452] [<c04e52c3>] (rk_fiqdbg_probe) from [<c01a9b99>] (platform_drv_probe+0x33/0x62)
[    0.320011] [<c01a9b99>] (platform_drv_probe) from [<c01a8da1>] (driver_probe_device+0xfd/0x1a8)
[    0.329001] [<c01a8da1>] (driver_probe_device) from [<c01a8e73>] (__driver_attach+0x27/0x4a)
[    0.337636] [<c01a8e73>] (__driver_attach) from [<c01a7f15>] (bus_for_each_dev+0x3d/0x46)
[    0.345995] [<c01a7f15>] (bus_for_each_dev) from [<c01a885f>] (bus_add_driver+0xd7/0x130)
[    0.354359] [<c01a885f>] (bus_add_driver) from [<c01a931f>] (driver_register+0x4d/0x7a)
[    0.362542] [<c01a931f>] (driver_register) from [<c01a9dfb>] (__platform_driver_probe+0x33/0x84)
[    0.371534] [<c01a9dfb>] (__platform_driver_probe) from [<c0059665>] (do_one_initcall+0x41/0x13c)
[    0.380603] [<c0059665>] (do_one_initcall) from [<c04d9abb>] (kernel_init_freeable+0x10b/0x150)
[    0.389491] [<c04d9abb>] (kernel_init_freeable) from [<c036bf5b>] (kernel_init+0x7/0x9c)
[    0.397764] [<c036bf5b>] (kernel_init) from [<c005d371>] (ret_from_fork+0x11/0x20)
[    0.405528] ---[ end trace 27510aab5fd105bd ]---
[    0.410260] ------------[ cut here ]------------
[    0.415001] WARNING: CPU: 0 PID: 1 at arch/arm/mm/ioremap.c:301 __arm_ioremap_pfn_caller+0x71/0x100()
[    0.424438] Modules linked in:
[    0.427587] CPU: 0 PID: 1 Comm: swapper/0 Tainted: G        W       4.4.143 #63
[    0.435048] Hardware name: Generic DT based system
[    0.439949] [<c0061ddd>] (unwind_backtrace) from [<c005f7bb>] (show_stack+0xb/0xc)
[    0.447692] [<c005f7bb>] (show_stack) from [<c016a8f3>] (dump_stack+0x5b/0x70)
[    0.455077] [<c016a8f3>] (dump_stack) from [<c006d1a1>] (warn_slowpath_common+0x55/0x7c)
[    0.463345] [<c006d1a1>] (warn_slowpath_common) from [<c006d221>] (warn_slowpath_null+0xf/0x14)
[    0.472238] [<c006d221>] (warn_slowpath_null) from [<c0065651>] (__arm_ioremap_pfn_caller+0x71/0x100)
[    0.481668] [<c0065651>] (__arm_ioremap_pfn_caller) from [<c00656fd>] (__arm_ioremap_caller+0x1d/0x24)
[    0.491186] [<c00656fd>] (__arm_ioremap_caller) from [<c0246179>] (sip_fiq_debugger_uart_irq_tf_init+0x41/0x74)
[    0.501510] [<c0246179>] (sip_fiq_debugger_uart_irq_tf_init) from [<c018f123>] (rk_serial_debug_init+0x187/0x274)
[    0.511999] [<c018f123>] (rk_serial_debug_init) from [<c04e52c3>] (rk_fiqdbg_probe+0xa7/0x1a0)
[    0.520797] [<c04e52c3>] (rk_fiqdbg_probe) from [<c01a9b99>] (platform_drv_probe+0x33/0x62)
[    0.529345] [<c01a9b99>] (platform_drv_probe) from [<c01a8da1>] (driver_probe_device+0xfd/0x1a8)
[    0.538333] [<c01a8da1>] (driver_probe_device) from [<c01a8e73>] (__driver_attach+0x27/0x4a)
[    0.546959] [<c01a8e73>] (__driver_attach) from [<c01a7f15>] (bus_for_each_dev+0x3d/0x46)
[    0.555324] [<c01a7f15>] (bus_for_each_dev) from [<c01a885f>] (bus_add_driver+0xd7/0x130)
[    0.563688] [<c01a885f>] (bus_add_driver) from [<c01a931f>] (driver_register+0x4d/0x7a)
[    0.571863] [<c01a931f>] (driver_register) from [<c01a9dfb>] (__platform_driver_probe+0x33/0x84)
[    0.580859] [<c01a9dfb>] (__platform_driver_probe) from [<c0059665>] (do_one_initcall+0x41/0x13c)
[    0.589942] [<c0059665>] (do_one_initcall) from [<c04d9abb>] (kernel_init_freeable+0x10b/0x150)
[    0.598842] [<c04d9abb>] (kernel_init_freeable) from [<c036bf5b>] (kernel_init+0x7/0x9c)
[    0.607111] [<c036bf5b>] (kernel_init) from [<c005d371>] (ret_from_fork+0x11/0x20)
[    0.614873] ---[ end trace 27510aab5fd105be ]---
[    0.619608] sip_fiq_debugger_uart_irq_tf_init: share memory ioremap failed




[    0.162865] console [pstore-1] enabled
[    0.166693] pstore: Registered ramoops as persistent store backend
[    0.173034] ramoops: attached 0x20000@0x30000, ecc: 0/0
[    0.192849] hw-breakpoint: found 5 (+1 reserved) breakpoint and 4 watchpoint registers.
[    0.201029] hw-breakpoint: maximum watchpoint size is 8 bytes.
[    0.207486] ------------[ cut here ]------------
[    0.212228] WARNING: CPU: 0 PID: 1 at arch/arm/mm/ioremap.c:301 __arm_ioremap_pfn_caller+0x71/0x100()
[    0.221647] Modules linked in:
[    0.224800] CPU: 0 PID: 1 Comm: swapper/0 Not tainted 4.4.143 #65
[    0.231025] Hardware name: Generic DT based system
[    0.235929] [<c0061ddd>] (unwind_backtrace) from [<c005f7bb>] (show_stack+0xb/0xc)
[    0.243661] [<c005f7bb>] (show_stack) from [<c016c573>] (dump_stack+0x5b/0x70)
[    0.251052] [<c016c573>] (dump_stack) from [<c006d1a1>] (warn_slowpath_common+0x55/0x7c)
[    0.259324] [<c006d1a1>] (warn_slowpath_common) from [<c006d221>] (warn_slowpath_null+0xf/0x14)
[    0.268210] [<c006d221>] (warn_slowpath_null) from [<c0065651>] (__arm_ioremap_pfn_caller+0x71/0x100)
[    0.277644] [<c0065651>] (__arm_ioremap_pfn_caller) from [<c00656fd>] (__arm_ioremap_caller+0x1d/0x24)
[    0.287175] [<c00656fd>] (__arm_ioremap_caller) from [<c02487e9>] (sip_smc_request_share_mem+0x21/0x2c)
[    0.296802] [<c02487e9>] (sip_smc_request_share_mem) from [<c02489ad>] (sip_fiq_debugger_request_share_memory+0xd/0x14)
[    0.307826] [<c02489ad>] (sip_fiq_debugger_request_share_memory) from [<c01917c7>] (rk_serial_debug_init+0xab/0x274)
[    0.318579] [<c01917c7>] (rk_serial_debug_init) from [<c04e93ab>] (rk_fiqdbg_probe+0xa7/0x1a0)
[    0.327383] [<c04e93ab>] (rk_fiqdbg_probe) from [<c01ac319>] (platform_drv_probe+0x33/0x62)
[    0.335918] [<c01ac319>] (platform_drv_probe) from [<c01ab521>] (driver_probe_device+0xfd/0x1a8)
[    0.344892] [<c01ab521>] (driver_probe_device) from [<c01ab5f3>] (__driver_attach+0x27/0x4a)
[    0.353518] [<c01ab5f3>] (__driver_attach) from [<c01aa695>] (bus_for_each_dev+0x3d/0x46)
[    0.361869] [<c01aa695>] (bus_for_each_dev) from [<c01aafdf>] (bus_add_driver+0xd7/0x130)
[    0.370236] [<c01aafdf>] (bus_add_driver) from [<c01aba9f>] (driver_register+0x4d/0x7a)
[    0.378415] [<c01aba9f>] (driver_register) from [<c01ac57b>] (__platform_driver_probe+0x33/0x84)
[    0.387399] [<c01ac57b>] (__platform_driver_probe) from [<c0059665>] (do_one_initcall+0x41/0x13c)
[    0.396469] [<c0059665>] (do_one_initcall) from [<c04ddabb>] (kernel_init_freeable+0x10b/0x150)
[    0.405352] [<c04ddabb>] (kernel_init_freeable) from [<c036e6db>] (kernel_init+0x7/0x9c)
[    0.413625] [<c036e6db>] (kernel_init) from [<c005d371>] (ret_from_fork+0x11/0x20)
[    0.421383] ---[ end trace fac9e7583f6930b1 ]---
[    0.426126] ------------[ cut here ]------------
[    0.430844] WARNING: CPU: 0 PID: 1 at arch/arm/mm/ioremap.c:301 __arm_ioremap_pfn_caller+0x71/0x100()
[    0.440241] Modules linked in:
[    0.443382] CPU: 0 PID: 1 Comm: swapper/0 Tainted: G        W       4.4.143 #65
[    0.450829] Hardware name: Generic DT based system
[    0.455723] [<c0061ddd>] (unwind_backtrace) from [<c005f7bb>] (show_stack+0xb/0xc)
[    0.463452] [<c005f7bb>] (show_stack) from [<c016c573>] (dump_stack+0x5b/0x70)
[    0.470841] [<c016c573>] (dump_stack) from [<c006d1a1>] (warn_slowpath_common+0x55/0x7c)
[    0.479129] [<c006d1a1>] (warn_slowpath_common) from [<c006d221>] (warn_slowpath_null+0xf/0x14)
[    0.488014] [<c006d221>] (warn_slowpath_null) from [<c0065651>] (__arm_ioremap_pfn_caller+0x71/0x100)
[    0.497429] [<c0065651>] (__arm_ioremap_pfn_caller) from [<c00656fd>] (__arm_ioremap_caller+0x1d/0x24)
[    0.506942] [<c00656fd>] (__arm_ioremap_caller) from [<c02488f9>] (sip_fiq_debugger_uart_irq_tf_init+0x41/0x74)
[    0.517253] [<c02488f9>] (sip_fiq_debugger_uart_irq_tf_init) from [<c01918a3>] (rk_serial_debug_init+0x187/0x274)
[    0.527736] [<c01918a3>] (rk_serial_debug_init) from [<c04e93ab>] (rk_fiqdbg_probe+0xa7/0x1a0)
[    0.536539] [<c04e93ab>] (rk_fiqdbg_probe) from [<c01ac319>] (platform_drv_probe+0x33/0x62)
[    0.545064] [<c01ac319>] (platform_drv_probe) from [<c01ab521>] (driver_probe_device+0xfd/0x1a8)
[    0.554030] [<c01ab521>] (driver_probe_device) from [<c01ab5f3>] (__driver_attach+0x27/0x4a)
[    0.562657] [<c01ab5f3>] (__driver_attach) from [<c01aa695>] (bus_for_each_dev+0x3d/0x46)
[    0.571006] [<c01aa695>] (bus_for_each_dev) from [<c01aafdf>] (bus_add_driver+0xd7/0x130)
[    0.579366] [<c01aafdf>] (bus_add_driver) from [<c01aba9f>] (driver_register+0x4d/0x7a)
[    0.587535] [<c01aba9f>] (driver_register) from [<c01ac57b>] (__platform_driver_probe+0x33/0x84)
[    0.596518] [<c01ac57b>] (__platform_driver_probe) from [<c0059665>] (do_one_initcall+0x41/0x13c)
[    0.605587] [<c0059665>] (do_one_initcall) from [<c04ddabb>] (kernel_init_freeable+0x10b/0x150)
[    0.614476] [<c04ddabb>] (kernel_init_freeable) from [<c036e6db>] (kernel_init+0x7/0x9c)
[    0.622758] [<c036e6db>] (kernel_init) from [<c005d371>] (ret_from_fork+0x11/0x20)
[    0.630505] ---[ end trace fac9e7583f6930b2 ]---
[    0.635226] sip_fiq_debugger_uart_irq_tf_init: share memory ioremap failed
[    0.642268] fiq debugger bind fiq to trustzone failed: -12
[[    0.648221] console [ttyFIQ0] enabled
    0.648221] console [ttyFIQ0] enabled
[    0.655614] bootconsole [uart0] disabled
[    0.655614] bootconsole [uart0] disabled
[    0.659871] RegisWARNING: suspend_mode_handler: Not support call: 0x4
tered fiq debugger ttyFIQ0
[    0.677718] vcc_1v8: regulator get failed, ret=-517
[    0.678357] vcc_1v8: supplied by vcc_io
/**********************************************************************************
32bit net problem
[    0.870741] 0x000000700000-0x000000a00000 : "rootfs"
[    0.876811] 0x000000a00000-0x000000b00000 : "config"
[    0.882923] 0x000000b00000-0x000000c00000 : "basic"
[    0.888928] 0x000000c00000-0x001000bfffff : "app"
[    0.893824] mtd: partition "app" extends beyond the end of device "sfc_nor" -- size truncated to 0x400000
[    0.904633] rkflash[1] init success
[    0.908302] sfc_nor flash registered as a mtd device
[    0.916696] rk3308-acodec ff560000.acodec: Don't need hp-ctl gpio
[    0.923267] rk3308-acodec ff560000.acodec: Don't need pa-drv gpio
[    0.929688] rk3308-acodec ff560000.acodec: De-pop as much as possible
[    1.012079] rk-multicodecs vad-sound: multicodec <-> ff320000.i2s mapping ok
[    1.021864] input: rockchip,rk3308-vad Headphones as /devices/platform/vad-sound/sound/card0/input0
[    1.032675] NET: Registered protocol family 17
[    1.037287] NET: Registered protocol family 15
[    1.042005] Bluetooth: RFCOMM TTY layer initialized
[    1.047007] Bluetooth: RFCOMM socket layer initialized
[    1.052280] Bluetooth: RFCOMM ver 1.11
[    1.056190] Bluetooth: HIDP (Human Interface Emulation) ver 1.2
[    1.062406] Bluetooth: HIDP socket layer initialized
[    1.067589] [WLAN_RFKILL]: Enter rfkill_wlan_init
[    1.072832] [WLAN_RFKILL]: Enter rfkill_wlan_probe
[    1.077883] [WLAN_RFKILL]: wlan_platdata_parse_dt: wifi_chip_type = rtl8189fs
[    1.085359] [WLAN_RFKILL]: wlan_platdata_parse_dt: enable wifi power control.
[    1.092814] [WLAN_RFKILL]: wlan_platdata_parse_dt: wifi power controled by gpio.
[    1.100599] [WLAN_RFKILL]: wlan_platdata_parse_dt: get property: WIFI,host_wake_irq = 0, flags = 1.
[    1.110089] [WLAN_RFKILL]: wlan_platdata_parse_dt: The ref_wifi_clk not found !
[    1.117767] [WLAN_RFKILL]: rfkill_wlan_probe: init gpio
[    1.123208] [WLAN_RFKILL]: Exit rfkill_wlan_probe
[    1.128162] [BT_RFKILL]: Enter rfkill_rk_init
[    1.132958] flash vendor_init_thread!
[    1.133218] Registering SWP/SWPB emulation handler
[    1.133868] bootconsole [uart0] disabled

/*****************************************************************************
good print 32bit
Starting kernel ...


[    0.000000] Booting Linux on physical CPU 0x0
[    0.000000] Linux version 4.4.143 (root@a9aa976c2900) (gcc version 6.3.1 20170404 (Linaro GCC 6.3-2017.05) ) #69 SMP PREEMPT Mon Sep 2 13:41:50 CST 2019
[    0.000000] CPU: ARMv7 Processor [410fd042] revision 2 (ARMv7), cr=50c5383d
[    0.000000] CPU: PIPT / VIPT nonaliasing data cache, VIPT aliasing instruction cache
[    0.000000] Machine model: Rockchip RK3308 Voice Module Board V10 (AArch32)
[    0.000000] earlycon: Early serial console at MMIO32 0xff0c0000 (options '')
[    0.000000] bootconsole [uart0] enabled
[    0.000000] Reserved memory: failed to reserve memory for node 'drm-logo@00000000': base 0x00000000, size 0 MiB
[    0.000000] Memory policy: Data cache writealloc
[    0.000000] psci: probing for conduit method from DT.
[    0.000000] psci: PSCIv1.0 detected in firmware.
[    0.000000] psci: Using standard PSCI v0.2 function IDs
[    0.000000] psci: MIGRATE_INFO_TYPE not supported.
[    0.000000] PERCPU: Embedded 11 pages/cpu @cfda8000 s13132 r8192 d23732 u45056
[    0.000000] Built 1 zonelists in Zone order, mobility grouping on.  Total pages: 64516
[    0.000000] Kernel command line: coherent_pool=4k user_debug=31 storagemedia=nor androidboot.slot_suffix= androidboot.serialno=c3d9b8674f4b94f6  rootwait earlycon=uart8250,mmio32,0xff0c0000 swiotlb=1 console=ttyFIQ0,115200 root=/dev/mtdblock4 rootfstype=squashfs snd_aloop.index=7
[    0.000000] PID hash table entries: 1024 (order: 0, 4096 bytes)
[    0.000000] Dentry cache hash table entries: 32768 (order: 5, 131072 bytes)
[    0.000000] Inode-cache hash table entries: 16384 (order: 4, 65536 bytes)
[    0.000000] Memory: 253808K/260096K available (3176K kernel code, 239K rwdata, 1276K rodata, 188K init, 274K bss, 6288K reserved, 0K cma-reserved)
[    0.000000] Virtual kernel memory layout:
[    0.000000]     vector  : 0xffff0000 - 0xffff1000   (   4 kB)
[    0.000000]     fixmap  : 0xffc00000 - 0xfff00000   (3072 kB)
[    0.000000]     vmalloc : 0xd0800000 - 0xff800000   ( 752 MB)
[    0.000000]     lowmem  : 0xc0000000 - 0xd0000000   ( 256 MB)
[    0.000000]     modules : 0xbf800000 - 0xc0000000   (   8 MB)
[    0.000000]       .text : 0xc0058000 - 0xc0372274   (3177 kB)
[    0.000000]       .init : 0xc04dd000 - 0xc050c000   ( 188 kB)
[    0.000000]       .data : 0xc050c000 - 0xc0547de8   ( 240 kB)
[    0.000000]        .bss : 0xc0549000 - 0xc058d898   ( 275 kB)
[    0.000000] Preemptible hierarchical RCU implementation.
[    0.000000]  Build-time adjustment of leaf fanout to 32.
[    0.000000] NR_IRQS:16 nr_irqs:16 16
[    0.000000] Architected cp15 timer(s) running at 24.00MHz (virt).
[    0.000000] clocksource: arch_sys_counter: mask: 0xffffffffffffff max_cycles: 0x588fe9dc0, max_idle_ns: 440795202592 ns
[    0.000006] sched_clock: 56 bits at 24MHz, resolution 41ns, wraps every 4398046511097ns
[    0.008214] Switching to timer-based delay loop, resolution 41ns
[    0.015145] Calibrating delay loop (skipped), value calculated using timer frequency.. 48.00 BogoMIPS (lpj=24000)
[    0.025681] pid_max: default: 4096 minimum: 301
[    0.030458] Mount-cache hash table entries: 1024 (order: 0, 4096 bytes)
[    0.037226] Mountpoint-cache hash table entries: 1024 (order: 0, 4096 bytes)
[    0.044932] CPU: Testing write buffer coherency: ok
[    0.050149] Setting up static identity map for 0x58240 - 0x5828c
[    0.071804] Brought up 4 CPUs
[    0.074837] SMP: Total of 4 processors activated (192.00 BogoMIPS).
[    0.081253] CPU: All CPU(s) started in SVC mode.
[    0.086392] devtmpfs: initialized
[    0.105122] VFP support v0.3: implementor 41 architecture 3 part 40 variant 4 rev 2
[    0.113326] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 1911260446275000 ns
[    0.123315] futex hash table entries: 16 (order: -2, 1024 bytes)
[    0.129725] pinctrl core: initialized pinctrl subsystem
[    0.136068] NET: Registered protocol family 16
[    0.140975] DMA: preallocated 4 KiB pool for atomic coherent allocations
[    0.154895] cpuidle: using governor menu
[    0.158938] Registered FIQ tty driver
[    0.164990] console [pstore-1] enabled
[    0.168809] pstore: Registered ramoops as persistent store backend
[    0.175133] ramoops: attached 0x20000@0x30000, ecc: 0/0
[    0.194929] hw-breakpoint: found 5 (+1 reserved) breakpoint and 4 watchpoint registers.
[    0.203116] hw-breakpoint: maximum watchpoint size is 8 bytes.
[    0.209593] fiq debugger fiq mode enabled
[[    0.214027] console [ttyFIQ0] enabled
    0.214027] console [ttyFIQ0] enabled
[    0.221428] bootconsole [uart0] disabled
[    0.221428] bootconsole [uart0] disabled
[    0.225680] Registered fiq debugger ttyFIQ0
WARNING: suspend_mode_handler: Not support call: 0x4
[    0.241512] vcc_1v8: regulator get failed, ret=-517
[    0.242152] vcc_1v8: supplied by vcc_io
[    0.243884] Advanced Linux Sound Architecture Driver Initialized.
[    0.244564] Bluetooth: Core ver 2.21
[    0.244607] NET: Registered protocol family 31
[    0.244620] Bluetooth: HCI device and connection manager initialized
[    0.244637] Bluetooth: HCI socket layer initialized
[    0.244651] Bluetooth: L2CAP socket layer initialized
[    0.244682] Bluetooth: SCO socket layer initialized
[    0.245644] rockchip-cpuinfo cpuinfo: Serial         : 4887e67c1a454e04
[    0.246189] clocksource: Switched to clocksource arch_sys_counter
[    0.248334] thermal thermal_zone1: power_allocator: sustainable_power will be estimated
[    0.248597] NET: Registered protocol family 2
[    0.249369] TCP established hash table entries: 2048 (order: 1, 8192 bytes)
[    0.249415] TCP bind hash table entries: 2048 (order: 2, 16384 bytes)
[    0.249460] TCP: Hash tables configured (established 2048 bind 2048)
[    0.249518] UDP hash table entries: 128 (order: 0, 4096 bytes)
[    0.249539] UDP-Lite hash table entries: 128 (order: 0, 4096 bytes)
[    0.249728] NET: Registered protocol family 1
[    0.250042] RPC: Registered named UNIX socket transport module.
[    0.250058] RPC: Registered udp transport module.
[    0.250068] RPC: Registered tcp transport module.
[    0.250079] RPC: Registered tcp NFSv4.1 backchannel transport module.
[    0.254895] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.255161] jffs2: version 2.2. (NAND) © 2001-2006 Red Hat, Inc.
[    0.258799] io scheduler noop registered (default)
[    0.259815] phy phy-ff008000.syscon:usb2-phy@100.0: Failed to get VBUS supply regulator
[    0.263325] dma-pl330 ff2c0000.dma-controller: Loaded driver for PL330 DMAC-241330
[    0.263354] dma-pl330 ff2c0000.dma-controller:       DBUFF-32x8bytes Num_Chans-6 Num_Peri-12 Num_Events-12
[    0.265692] dma-pl330 ff2d0000.dma-controller: Loaded driver for PL330 DMAC-241330
[    0.265718] dma-pl330 ff2d0000.dma-controller:       DBUFF-128x8bytes Num_Chans-8 Num_Peri-20 Num_Events-16
[    0.266003] rockchip-pvtm ff000000.grf:pmu-pvtm: failed to get rst 0 pmu
[    0.266115] rockchip-pvtm ff00c000.syscon:pvtm: failed to get rst 0 core
[    0.267416] Serial: 8250/16550 driver, 5 ports, IRQ sharing disabled
[    0.270549] random: nonblocking pool is initialized
[    0.271304] zram: Added device: zram0
[    0.272096] Rockchip WiFi SYS interface (V1.00) ...
[    0.272471] ff400000.usb supply vusb_d not found, using dummy regulator
[    0.272548] ff400000.usb supply vusb_a not found, using dummy regulator
[    0.274722] dwc2 ff400000.usb: Configuration mismatch. dr_mode forced to device
[    0.274754] dwc2 ff400000.usb: 128 invalid for host_nperio_tx_fifo_size. Check HW configuration.
[    0.274773] dwc2 ff400000.usb: 256 invalid for host_perio_tx_fifo_size. Check HW configuration.
[    0.274808] dwc2 ff400000.usb: EPs: 10, dedicated fifos, 972 entries in SPRAM
[    0.498640] phy phy-ff008000.syscon:usb2-phy@100.0: charger = USB_SDP_CHARGER
[    0.500055] rk-timer-rtc ff1a0020.rk-timer-rtc: rtc core: registered rk-timer-rtc as rtc0
[    0.500196] i2c /dev entries driver
[    0.502368] rk_tsadcv2_temp_to_code: Invalid conversion table: code=4095, temperature=2147483647
[    0.502570] rockchip-thermal ff1f0000.tsadc: tsadc is probed successfully!
[    0.502975] Bluetooth: HCI UART driver ver 2.3
[    0.502991] Bluetooth: HCI UART protocol H4 registered
[    0.503003] Bluetooth: HCI UART protocol LL registered
[    0.503240] cpu cpu0: leakage=5
[    0.503382] cpu cpu0: Failed to get pvtm
[    0.505018] /cpus/cpu@0: unsupported enable-method property: psci
[    0.505038] CPUidle arm: CPU 0 failed to init idle CPU ops
[    0.505473] rockchip-dmc dmc: failed to get the count of devfreq-event in /dmc node
[    0.505632] rockchip-dmc dmc: Failed to get leakage
[    0.505700] rockchip-dmc dmc: Failed to get pvtm
[    0.505938] rockchip-dmc dmc: failed to get vop bandwidth to dmc rate
[    0.505958] rockchip-dmc dmc: don't add devfreq feature
[    0.507521] rknandc_base v1.1 2017-01-11
[    0.507770] rknandc ff4b0000.nandc: rknandc_probe clk rate = 147456000
[    0.507819] rkflash_dev_init
[    0.507831] init rkflash[0]
[    0.507854] rkflash[0] init fail
[    0.507882] rknandc: probe of ff4b0000.nandc failed with error -1
[    0.507968] rksfc_base v1.1 2016-01-08
[    0.508149] rksfc ff4c0000.sfc: rksfc_probe clk rate = 100000000
[    0.508224] rkflash_dev_init
[    0.508236] init rkflash[1]
[    0.508255] sfc nor id: ef 40 18
[    0.508785] Creating 8 MTD partitions on "sfc_nor":
[    0.508805] 0x000000000000-0x0000000e0000 : "uboot"
[    0.509883] 0x0000000e0000-0x0000000f0000 : "manufacture"
[    0.510883] 0x0000000f0000-0x000000100000 : "reserver"
[    0.511938] 0x000000100000-0x000000700000 : "boot"
[    0.512978] 0x000000700000-0x000000a00000 : "rootfs"
[    0.514078] 0x000000a00000-0x000000b00000 : "config"
[    0.515210] 0x000000b00000-0x000000c00000 : "basic"
[    0.516248] 0x000000c00000-0x001000bfffff : "app"
[    0.516267] mtd: partition "app" extends beyond the end of device "sfc_nor" -- size truncated to 0x400000
[    0.517251] rkflash[1] init success
[    0.517268] sfc_nor flash registered as a mtd device
[    0.521089] rk3308-acodec ff560000.acodec: Don't need hp-ctl gpio
[    0.521302] rk3308-acodec ff560000.acodec: Don't need pa-drv gpio
[    0.521318] rk3308-acodec ff560000.acodec: De-pop as much as possible
[    0.595900] rk-multicodecs vad-sound: multicodec <-> ff320000.i2s mapping ok
[    0.596982] input: rockchip,rk3308-vad Headphones as /devices/platform/vad-sound/sound/card0/input0
[    0.597696] NET: Registered protocol family 17
[    0.597747] NET: Registered protocol family 15
[    0.597881] Bluetooth: RFCOMM TTY layer initialized
[    0.597902] Bluetooth: RFCOMM socket layer initialized
[    0.597935] Bluetooth: RFCOMM ver 1.11
[    0.597962] Bluetooth: HIDP (Human Interface Emulation) ver 1.2
[    0.597977] Bluetooth: HIDP socket layer initialized
[    0.597993] [WLAN_RFKILL]: Enter rfkill_wlan_init
[    0.598378] [WLAN_RFKILL]: Enter rfkill_wlan_probe
[    0.598407] [WLAN_RFKILL]: wlan_platdata_parse_dt: wifi_chip_type = rtl8189fs
[    0.598419] [WLAN_RFKILL]: wlan_platdata_parse_dt: enable wifi power control.
[    0.598430] [WLAN_RFKILL]: wlan_platdata_parse_dt: wifi power controled by gpio.
[    0.598509] [WLAN_RFKILL]: wlan_platdata_parse_dt: get property: WIFI,host_wake_irq = 0, flags = 1.
[    0.59852ifconfig: SIOCSIFADDR: No such device
5] [WLAN_RFKILL]: wlan_platdata_parse_dt: The ref_wifi_clk not found !
[    0.598538] [WLAN_RFKILL]: rfkill_wlan_probe: init gpio
[    0.598551] [WLAN_RFKILL]: Exit rfkill_wlan_probe
[    0.598611] [BT_RFKILL]: Enter rfkill_rk_init
[    0.598865] flash vendor_init_thread!
[    0.599209] Registering SWP/SWPB emulation handler
[    0.600346] flash vendor storage:20170-/bin/sh: id: not foun3d
08sh: bad number
 ret =$  0
[    0.600696] input: adc-keys as /devices/platform/adc-keys/input/input1
[    0.601802] input: gpio-keys as /devices/platform/gpio-keys/input/input2
[    0.602211] rk-timer-rtc ff1a0020.rk-timer-rtc: setting system clock to 1970-01-01 00:00:00 UTC (0)
[    0.613902] vbus_host: disabling
[    0.614281] ALSA device list:
[    0.614299]   #0: rockchip,rk3308-vad
[    0.614309]   #7: Loopback 1
[    0.616492] VFS: Mounted root (squashfs filesystem) readonly on device 31:4.
[    0.617101] devtmpfs: mounted
[    0.617410] Freeing unused kernel memory: 188K
[    0.617420] This architecture does not have kernel memory protection.

$
/*****************************************************************************
$ insmod ./snd-soc-rk3308.ko
[  326.033752] [CODEC_RK3308] FUN:rk3308_platform_probe; LINE:3892;
$ [  326.034650] rk3308-acodec ff560000.acodec: Don't need pa-drv gpio
[  326.034686] rk3308-acodec ff560000.acodec: De-pop as much as possible

$
$
$
$ insmod ./snd-soc-rockchip-i2s-tdm.ko
[  361.059519] [I2S_TDM_RK3308] FUN:rockchip_i2s_tdm_probe; LINE:1121;
[  361.06011$ 7] [DMA_ENGINE_RK3308] FUN:snd_dmaengine_pcm_register; LINE:447;

$
$
$
$ insmod ./snd-soc-rockchip-multicodecs.ko
[  391.664488] [CODEC_RK3308] FUN:rk3308_probe; LINE:3286;

[  391.736335] [I2S_TDM_RK3308] FUN:rockchip_i2s_tdm_dai_probe; LINE:916;
[  391.736390] [CODEC_RK3308] FUN:rk3308_set$
$ _dai_fmt; LINE:847;fmt:0x4001;
[  391.736439] [I2S_TDM_RK3308] FUN:rockchip_i2s_tdm_set_fmt; LINE:407;
[  391.736904] [DMA_ENGINE_RK3308] FUN:dmaengine_pcm_new; LINE:266;
[  391.737990] rk-multicodecs acodec-sound: rk3308-hifi <-> ff320000.i2s mapping ok
[  391.738148] [CODEC_RK3308] FUN:rk3308_set_bias_level; LINE:821;Level:1;
[  391.738148]
[  391.740051] input: rockchip,rk3308-acodec Headphones as /devices/platform/acodec-sound/sound/card0/input2

$


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./

[    0.651017] vbus_host: disabling
[    0.651322] ALSA device list:
[    0.651337]   #0: rockchip,rk3308-vad
[    0.651346]   #7: Loopback 1
[    0.653736] VFS: Mounted root (squashfs filesystem) readonly on device 31:4.
[    0.656158] devtmpfs: mounted
[    0.656528] Freeing unused kernel memory: 220K
[    0.656539] This architecture does not have kernel memory protection.
[    1.135859] jffs2: notice: (126) jffs2_build_xattr_subsystem: complete building xattr subsystem, 0 of xdatum (0 unchecked, 0 orphan) and 0 of xref (0 dead, 0 orphan) found.
[    1.143535] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: rk_vendor_read eth mac address failed (-1)
[    1.143585] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: generate random eth mac address: 32:cf:1e:e2:7c:af
[    1.143599] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: rk_vendor_write eth mac address failed (-1)
[    1.143617] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: mac address: 32:cf:1e:e2:7c:af
[    1.143628] eth0: device MAC address 32:cf:1e:e2:7c:af
[    1.241147] ramreserve: loading out-of-tree module taints kernel.
[    1.241664] num_physpages:0xfdfc;
[    1.241855] ramreserve_size_all:0x204000
[    1.242060] PHYS_OFFSET:0x0;ramreserve_char_start_addr:0xfffc000;
[    1.242264] num_physpages:fdfc ramreserve_head_region_addr:0 ramreserve_size_all:204000
[    1.242720] ramreservechar register success
[    3.147535] rk_gmac-dwmac ff4e0000.ethernet eth0: Link is Up - 100Mbps/Full - flow control rx/tx
$ 
