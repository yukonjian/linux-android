使用的spiflash:
W25Q128

rkflash/sfc_nor.c
#ifdef CONFIG_RK_SFC_NOR_MTD
//		err = sfc_nor_mtd_init(p_dev);
//		if (err)
//			goto err_out;
#endif


rkflash/rkflash_bld.c
#ifdef CONFIG_RK_SFC_NOR_MTD
//	if (g_flash_type == FLASH_TYPE_SFC_NOR) {
//		pr_info("sfc_nor flash registered as a mtd device\n");
//		rkflash_dev_initialised = 1;
//		return 0;
//	}
#endif

kernel/block/partition-generic.c
		part = add_partition(disk, p, from, size,
				     state->parts[p].flags,
				     &state->parts[p].info);
