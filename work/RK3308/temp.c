
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
