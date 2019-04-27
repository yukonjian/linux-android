https://www.cnblogs.com/lifexy/p/7542989.html
基于2.6的内核进行分析
////////////////////////////////////////////////////////////////////////////////
1. 全局变量保存区：
1.1 struct class input_class； /* 定义一个输入类，/sys/class/input */

1.2 struct file_operations input_fops；    /* 打开设备文件后，调用的file_operations;
打开所有的设备文件，均调用该 ops */

1.3 struct input_handler *input_table[8]; /* 保存所有的已经注册的input_handler的指针 */

1.4 struct evdev *evdev_table[EVDEV_MINORS];
/* 事件设备表，在调用open函数时，根据次设备号，选择相应的evdev传递给evdev_list
  每一个evdev对应一个设备文件*/

1.5 struct input_handler evdev_handler； /* evdev_open, evdev_input函数 */

1.6 static LIST_HEAD(input_dev_list);     /* input_dev会挂到该链表头下 */
    static LIST_HEAD(input_handler_list); /* input_handler会挂到该链表头下 */
/* 用于匹配input_dev和input_handler */

////////////////////////////////////////////////////////////////////////////////
1. 设备文件的打开读写流程
1.1 open("event0", O_RDONLY);
1.1.1 input_fops.open
    struct input_handler *handler = input_table[iminor(inode) >> 5];  (get 1.3)/*  获取该设备文件对应的handler */
    handler->fops->open(inode, file);    /* 调用新的open函数 */
1.1.2 evdev_open  /* 调用的打开函数（若是event handler） */
    kmalloc(sizeof(struct evdev_list), GFP_KERNEL) /* 申请一个evdev_list */
    list->evdev = evdev_table[iminor(inode) - EVDEV_MINOR_BASE];   (get 1.4)/* 将相应evdev指针传递给evdev_list */
    file->private_data = list;     /* 文件的私有数据保存分配的evdev_list */
1.1.3 evdev_read
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
////////////////////////////////////////////////////////////////////////////////
2. input_handler和input_dev的匹配过程
2.1 input_register_handler
    input_table[handler->minor >> 5] = handler;            (set 1.3) /* 将函数的传递参数放入input_table中 */
    list_add_tail(&handler->node, &input_handler_list);    (set 1.6)/* 将input_handler加入input_handler_list链表 */
    list_for_each_entry(dev, &input_dev_list, node)        (get 1.6)/* 轮询input_dev_list进行匹配 */
      input_attach_handler(dev, handler);
2.2 input_register_device
    ist_add_tail(&dev->node, &input_dev_list);              (set 1.6)/* 将input_dev加入input_dev_list链表 */
    list_for_each_entry(handler, &input_handler_list, node) (get 1.6)/* 轮询input_handler_list进行匹配 */
      input_attach_handler(dev, handler);
2.3 input_attach_handler
    /* 判断input_dev和input_handler是否匹配，evdev设备一定会匹配 */
    handler->connect(handler, dev, id);     /* 调用handler的connect函数 */
2.3.1 evdev_connect
    for (minor = 0; minor < EVDEV_MINORS && evdev_table[minor]; minor++);/* 查找一个可以使用的次设备号 */
    kzalloc(sizeof(struct evdev), GFP_KERNEL);    /* 分配一个evdev设备 */
    evdev->minor = minor;                         /* 将次设备号保存到evdev->minor中 */
    evdev_table[minor] = evdev;                   (set 1.4)/* 将分配的evdev放入evdev_table中 */
    sprintf(evdev->name, "event%d", minor);      /* 生成设备文件 */
    class_device_create();
    input_register_handle(&evdev->handle);      /* 注册handle */
2.3.1.1 input_register_handle
  list_add_tail(&handle->d_node, &handle->dev->h_list);       /* 这样就可以使用，input_dev和input_handler获取handle */
  list_add_tail(&handle->h_node, &handler->handler->h_list);
////////////////////////////////////////////////////////////////////////////////
/* 查找到handle，并调用handler的 event函数进行事件上报 */
3. 上报输入事件input_event
3.1 input_event
    /* 检查EV_KEY等标志位，确定事件是否可以上报 */
    list_for_each_entry(handle, &dev->h_list, d_node);  /* 通过input_dev获取对应的handle;看：3.3.1.1*/
    handle->handler->event(handle, type, code, value);  /* 调用handler中的事件上报函数 */
3.1.1 evdev_event
    struct evdev *evdev = handle->private;    /* 获取到对应的事件指针 */
		list_for_each_entry(list, &evdev->list, node) { /* 通过evdev指针获取evdev_list指针 */

		do_gettimeofday(&list->buffer[list->head].time);  /* 将事件拷贝到evdev_list中 */
		list->buffer[list->head].type = type;
		list->buffer[list->head].code = code;
		list->buffer[list->head].value = value;
		list->head = (list->head + 1) & (EVDEV_BUFFER_SIZE - 1);
		kill_fasync(&list->fasync, SIGIO, POLL_IN);
		}
    wake_up_interruptible(&evdev->wait);  /* 唤醒等待队列，通知evdev_read函数可以读取输入事件 */
