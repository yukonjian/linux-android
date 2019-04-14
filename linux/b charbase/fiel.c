1. 文件节点
inode: information node,[UNIX]索引节，信息节点
struct indoe
{
  dev_t			i_rdev;     /* 对应的设备文件 */
  struct cdev		*i_cdev;   /* 字符设备结构体指针 */
}

2. 文件结构体
struct file
{
  struct inode		*f_inode;	/* 指向文件的节点 */
  const struct file_operations	*f_op; /* 指向操作结构体指针 */
  void			*private_data; /* 指向文件的私有数据 */
}
