1. char device init exit 

static struct misc_c62b_info *cdev_file_alloc(struct file_operations *fops, const char *name)
{
	int retval;
	struct misc_c62b_info *infop;

	infop = kmalloc(sizeof(struct misc_c62b_info), GFP_KERNEL);
	if(!infop)
		return -ENOMEM;

	retval = alloc_chrdev_region(&infop->devno, 0, 1, name);
	if(IS_ERR_VALUE(retval))
		goto alloc_chrdev_region_failed;

	cdev_init(&infop->cdev, fops);
	retval = cdev_add(&infop->cdev, infop->devno, 1);
	if(IS_ERR_VALUE(retval))
		goto cdev_add_failed;

	infop->class = class_create(THIS_MODULE, name);
	if(IS_ERR(infop->class)) {
		retval = PTR_ERR(infop->class);
		goto class_create_failed;
	}
	if(IS_ERR(device_create(infop->class, NULL, infop->devno, NULL, name))) {
		retval = PTR_ERR(infop->class);
		goto device_create_failed;
	}

	dprintk("The cdev_device_alloct finished.\n");
	return infop;

device_create_failed:
	class_destroy(infop->class);
class_create_failed:
	cdev_del(&infop->cdev);
cdev_add_failed:
	unregister_chrdev_region(infop->devno,1);
alloc_chrdev_region_failed:
	kfree(infop);

	return ERR_PTR(retval);
}

static int cdev_file_release(struct misc_c62b_info *infop)
{
	if (infop == NULL)
		return -1;

	device_destroy(infop->class, infop->devno);
	class_destroy(infop->class);
	cdev_del(&infop->cdev);
	unregister_chrdev_region(infop->devno,1);
	kfree(infop);

	return 0;
}
