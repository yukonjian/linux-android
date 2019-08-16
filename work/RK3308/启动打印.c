pwm-regulator(vdd-core): init 1044000 uV
regulator(vdd-core) init 1044000 uV
MMC:   dwmmc@ff490000: 0
Using default environment

In:    serial@ff0c0000
Out:   serial@ff0c0000
Err:   serial@ff0c0000
Model: Rockchip RK3308 EVB
MMC Device 1 not found
no mmc device at slot 1
switch to partitions #0, OK
mmc0(part 0) is current device
boot mode: None
CLK:
apll 816000 KHz
dpll 1300000 KHz
vpll0 1179647 KHz
vpll1 903167 KHz
aclk_bus 185714 KHz
hclk_bus 100000 KHz
pclk_bus 100000 KHz
aclk_peri 185714 KHz
hclk_peri 100000 KHz
pclk_peri 100000 KHz
hclk_audio 98303 KHz
pclk_audio 98303 KHz
Net:   Net Initialization Skipped
No ethernet found.
Hit any key to stop autoboot:  0
ANDROID: reboot reason: "(none)"
FDT load addr 0x10f00000 size 253 KiB
Booting kernel at 0x4080000 with fdt at 4508000...


## Booting Android Image at 0x04080000 ...
Kernel load addr 0x02080000 size 4635 KiB
## Flattened Device Tree blob at 04508000
   Booting using the fdt blob at 0x4508000
   Uncompressing Kernel Image ... OK
   Loading Device Tree to 000000000f501000, end 000000000f514376 ... OK
Adding bank: start=0x00200000, size=0x0fe00000

Starting kernel ...


[    0.000000] Booting Linux on physical CPU 0x0
[    0.000000] Linux version 4.4.143 (root@e8d037608652) (gcc version 6.3.1 20170404 (Linaro GCC 6.3-2017.05) ) #12 SMP PREEMPT Wed Aug 7 19:15:35 CST 2019
[    0.000000] Boot CPU: AArch64 Processor [410fd042]
[    0.000000] earlycon: Early serial console at MMIO32 0xff0c0000 (options '')
[    0.000000] bootconsole [uart0] enabled
[    0.000000] Reserved memory: failed to reserve memory for node 'drm-logo@00000000': base 0x0000000000000000, size 0 MiB
[    0.000000] psci: probing for conduit method from DT.
[    0.000000] psci: PSCIv1.0 detected in firmware.
[    0.000000] psci: Using standard PSCI v0.2 function IDs
[    0.000000] psci: MIGRATE_INFO_TYPE not supported.
[    0.000000] PERCPU: Embedded 19 pages/cpu @ffffffc00ff54000 s40088 r8192 d29544 u77824
[    0.000000] Detected VIPT I-cache on CPU0
[    0.000000] Built 1 zonelists in Zone order, mobility grouping on.  Total pages: 64008
[    0.000000] Kernel command line: storagemedia=emmc androidboot.mode=emmc androidboot.slot_suffix= androidboot.serialno=c3d9b8674f4b94f6  rootwait earlycon=uart8250,mmio32,0xff0c0000 swiotlb=1 console=ttyFIQ0,115200 root=PARTUUID=614e0000-0000 rootfstype=squashfs snd_aloop.index=7
[    0.000000] PID hash table entries: 1024 (order: 1, 8192 bytes)
[    0.000000] Dentry cache hash table entries: 32768 (order: 6, 262144 bytes)
[    0.000000] Inode-cache hash table entries: 16384 (order: 5, 131072 bytes)
[    0.000000] software IO TLB [mem 0x0feb4000-0x0fef4000] (0MB) mapped at [ffffffc00feb4000-ffffffc00fef3fff]
[    0.000000] Memory: 245300K/260096K available (5758K kernel code, 418K rwdata, 2112K rodata, 384K init, 502K bss, 14796K reserved, 0K cma-reserved)
[    0.000000] Virtual kernel memory layout:
[    0.000000]     modules : 0xffffff8000000000 - 0xffffff8008000000   (   128 MB)
[    0.000000]     vmalloc : 0xffffff8008000000 - 0xffffffbdbfff0000   (   246 GB)
[    0.000000]       .init : 0xffffff8008840000 - 0xffffff80088a0000   (   384 KB)
[    0.000000]       .text : 0xffffff8008080000 - 0xffffff8008620000   (  5760 KB)
[    0.000000]     .rodata : 0xffffff8008620000 - 0xffffff8008840000   (  2176 KB)
[    0.000000]       .data : 0xffffff80088a0000 - 0xffffff8008908808   (   419 KB)
[    0.000000]     fixed   : 0xffffffbffe7fd000 - 0xffffffbffec00000   (  4108 KB)
[    0.000000]     PCI I/O : 0xffffffbffee00000 - 0xffffffbfffe00000   (    16 MB)
[    0.000000]     memory  : 0xffffffc000200000 - 0xffffffc010000000   (   254 MB)
[    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=4, Nodes=1
