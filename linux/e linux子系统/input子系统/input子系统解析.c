https://www.cnblogs.com/lifexy/p/7542989.html
////////////////////////////////////////////////////////////////////////////////
全局变量保存区：
struct class input_class； /* 定义一个输入类，/sys/class/input */

struct file_operations input_fops；    /* 打开设备文件后，调用的file_operations;
打开所有的设备文件，均调用该 ops */

struct input_handler *input_table[8]; /* 保存所有的已经注册的input_handler的指针 */

struct evdev *evdev_table[EVDEV_MINORS];
/* 事件设备表，在调用open函数时，根据次设备号，选择相应的evdev传递给evdev_list
  每一个evdev对应一个设备文件*/

////////////////////////////////////////////////////////////////////////////////
设备文件的打开流程
1. open("event0", O_RDONLY);
2. input_fops.open
    struct input_handler *handler = input_table[iminor(inode) >> 5];  /* 获取该设备文件对应的handler */
    new_fops = fops_get(handler->fops); /* 获取handler中的 file_operations */
    new_fops->open(inode, file);    /* 调用新的open函数 */
3. evdev_open /* 调用的打开函数（若是event handler） */
    kmalloc(sizeof(struct evdev_list), GFP_KERNEL) /* 申请一个evdev_list */
    list->evdev = evdev_table[iminor(inode) - EVDEV_MINOR_BASE];   /* 将相应evdev指针传递给evdev_list */
    file->private_data = list;     /* 文件的私有数据保存分配的evdev_list */
4. evdev_read()
    wait_event_interruptible(list->evdev->wait,	list->head != list->tail）
    /* 等待list->evdev中有数据 */
    copy_to_user(buffer, list->buffer + list->tail，sizeof(struct input_event))
    /* 将list->buffer中的第list->tail的数据拷贝给应用程序 */
    list->tail = (list->tail + 1) & (EVDEV_BUFFER_SIZE - 1);
////////////////////////////////////////////////////////////////////////////////
数据的上报流程
1. input_event  /* 上报事件函数 */
    list_for_each_entry(handle, &dev->h_list, d_node)
			 if (handle->open)
				   handle->handler->event(handle, type, code, value);
/* 查找到handle，并调用handler的 event函数进行事件上报 */
2. evdev_event
    struct evdev *evdev = handle->private;    /* 获取到对应的事件指针 */
		list_for_each_entry(list, &evdev->list, node) { /* 通过evdev指针获取evdev_list指针 */

			do_gettimeofday(&list->buffer[list->head].time);
			list->buffer[list->head].type = type;
			list->buffer[list->head].code = code;
			list->buffer[list->head].value = value;
			list->head = (list->head + 1) & (EVDEV_BUFFER_SIZE - 1);

			kill_fasync(&list->fasync, SIGIO, POLL_IN);
		}

    wake_up_interruptible(&evdev->wait);  /* 唤醒等待队列 */
////////////////////////////////////////////////////////////////////////////////
input_handler和input_dev的匹配过程



////////////////////////////////////////////////////////////////////////////////
