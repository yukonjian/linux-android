int  DAP1902_init(void)
{
	int ret;
	ret = alloc_chrdev_region(&test_devno, 0, 1, test_name);
	if(ret)
		return ret;

	cdev_init(&test_cdev, &test_fops);

	ret = cdev_add(&test_cdev, test_devno, 1);
	if (ret) {
		goto err_unreg_chrdev_region;
	}

	printk("DAP1902 init;\n");
	return 0;

err_unreg_chrdev_region:
	unregister_chrdev_region(test_devno, 1);

	return ret;
}
