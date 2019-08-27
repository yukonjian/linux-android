1.
Virtual kernel memory layout:
./arch/arm64/mm/init.c

2.
phys_addr_t __init_memblock memblock_start_of_DRAM(void)
{
	return memblock.memory.regions[0].base;
}
./arch/arm64/mm/memblock.c

3. memblock
https://blog.csdn.net/chuck_huang/article/details/78733543

4. OpenFirmware (OF)
 ARM Device Tree起源于OpenFirmware (OF)，
 Device Tree（FDT）
https://blog.csdn.net/yiyeguzhou100/article/details/76585587
https://blog.csdn.net/kunkliu/article/details/82846713

5. 启动流程
arch/arm64/kernel/setup.c
setup_arch

6. u-boot\arch\arm\mach-rockchip\sdram_common.c
	/* Reserve 0x200000 for ATF bl31 */
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE + 0x200000;
