#include <linux/module.h>
#include <linux/init.h>


#include <linux/cdev.h>		/* cdev_add */

#include <linux/slab.h>		/* kmalloc */
#include <linux/device.h>	/* device_create */


#define XXX_NAME	"xxx-name"
struct xxx_info{
	struct cdev cdev;
	dev_t devno;
	struct class *class;
};
static struct xxx_info *xxx_infp;


int xxx_open(struct inode * indoe, struct file * filp)
{
	return 0;
}
int xxx_release(struct inode * inode, struct file * filp)
{
	return 0;
}
struct file_operations xxx_fops = {
	.owner = THIS_MODULE,
	.open  = xxx_open,
	.release = xxx_release,
};


static int __init xxx_init(void)
{
	int retval = 0;

	xxx_infp = kmalloc(sizeof(struct xxx_info), GFP_KERNEL);
	if(!xxx_infp)
		return -ENOMEM;

	retval = alloc_chrdev_region(&xxx_infp->devno, 0, 1, XXX_NAME);
	if(IS_ERR_VALUE(retval))
		goto alloc_chrdev_region_failed;
	cdev_init(&xxx_infp->cdev, &xxx_fops);
	retval = cdev_add(&xxx_infp->cdev, xxx_infp->devno, 1);
	if(IS_ERR_VALUE(retval))
		goto cdev_add_failed;

	xxx_infp->class = class_create(THIS_MODULE, XXX_NAME);
	if(IS_ERR(xxx_infp->class)){
		retval = PTR_ERR(xxx_infp->class);
		goto class_create_failed;
	}
	device_create(xxx_infp->class, NULL, xxx_infp->devno, NULL, XXX_NAME);

	return 0;

	class_create_failed:
		cdev_del(&xxx_infp->cdev);
	cdev_add_failed:
		unregister_chrdev_region(xxx_infp->devno,1);
	alloc_chrdev_region_failed:
		kfree(xxx_infp);

	return retval;
}

static void __exit xxx_exit(void)
{
	device_destroy(xxx_infp->class, xxx_infp->devno);
	class_destroy(xxx_infp->class);
	cdev_del(&xxx_infp->cdev);
	unregister_chrdev_region(xxx_infp->devno,1);
	kfree(xxx_infp);
}

module_init(xxx_init);
module_exit(xxx_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yu konjian");
MODULE_VERSION("1.0");
